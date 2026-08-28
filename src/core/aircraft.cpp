#include "../../include/core/aircraft.hpp"
#include <cmath>
#include <algorithm>

Aircraft::Aircraft(int aircraft_id, const std::string& aircraft_name, bool is_player)
    : id(aircraft_id),
      name(aircraft_name),
      is_player_controlled(is_player),
      position(glm::vec3(0, 500, 0)),
      orientation(glm::quat(1, 0, 0, 0)),
      pitch(0), yaw(0), roll(0),
      velocity(glm::vec3(0)),
      acceleration(glm::vec3(0)),
      speed(0),
      forward(0, 0, 1),
      right(1, 0, 0),
      up(0, 1, 0),
      throttle(0),
      pitch_input(0), roll_input(0), yaw_input(0),
      smoke_enabled(false),
      g_force(1.0f),
      angle_of_attack(0),
      fuel(100),
      stalled(false),
      crashed(false),
      health(100),
      flight_time(0),
      angular_velocity(0)
{
}

void Aircraft::Reset(const glm::vec3& spawn_pos, const glm::vec3& spawn_heading) {
    position = spawn_pos;
    velocity = glm::vec3(0);
    acceleration = glm::vec3(0);
    speed = 0;
    
    orientation = glm::quat(1, 0, 0, 0);
    pitch = yaw = roll = 0;
    angular_velocity = glm::vec3(0);
    
    throttle = 0;
    pitch_input = roll_input = yaw_input = 0;
    smoke_enabled = false;
    
    g_force = 1.0f;
    angle_of_attack = 0;
    fuel = 100;
    stalled = false;
    crashed = false;
    health = 100;
    flight_time = 0;
    
    UpdateDirectionVectors();
}

void Aircraft::Update(float delta_time) {
    if (crashed) return;
    
    flight_time += delta_time;
    
    ApplyThrust(delta_time);
    ApplyAerodynamicForces(delta_time);
    ApplyControlSurfaces(delta_time);
    ApplyGravity(delta_time);
    
    velocity += acceleration * delta_time;
    position += velocity * delta_time;
    
    UpdateOrientation(delta_time);
    
    speed = glm::length(velocity);
    angle_of_attack = CalculateAngleOfAttack();
    
    stalled = (speed < MIN_SPEED);
    
    ClampLimits();
    CheckGroundCollision();
    
    UpdateDirectionVectors();
    
    if (throttle > 0) {
        fuel -= throttle * delta_time * 5.0f;
        fuel = std::max(0.0f, fuel);
    }
}

void Aircraft::SetThrottle(float value) {
    throttle = MathUtils::Clamp(value, 0.0f, 1.0f);
}

void Aircraft::SetPitchInput(float value) {
    pitch_input = MathUtils::Clamp(value, -1.0f, 1.0f);
}

void Aircraft::SetRollInput(float value) {
    roll_input = MathUtils::Clamp(value, -1.0f, 1.0f);
}

void Aircraft::SetYawInput(float value) {
    yaw_input = MathUtils::Clamp(value, -1.0f, 1.0f);
}

void Aircraft::SetSmokeEnabled(bool enabled) {
    smoke_enabled = enabled;
}

float Aircraft::GetHorizontalDistanceTo(const Aircraft& other) const {
    return MathUtils::HorizontalDistance(position, other.position);
}

float Aircraft::GetDistanceTo(const Aircraft& other) const {
    return MathUtils::Distance(position, other.position);
}

float Aircraft::GetBearingTo(const Aircraft& other) const {
    glm::vec3 delta = other.position - position;
    float bearing = atan2(delta.x, delta.z);
    return MathUtils::RadToDeg(bearing);
}

void Aircraft::ApplyThrust(float delta_time) {
    if (fuel <= 0) throttle = 0;
    
    float thrust_force = ENGINE_THRUST * throttle;
    acceleration += forward * (thrust_force / AIRCRAFT_MASS) * delta_time;
}

void Aircraft::ApplyAerodynamicForces(float delta_time) {
    if (speed < 0.1f) return;
    
    float drag = CalculateDrag();
    float lift = CalculateLift();
    
    glm::vec3 drag_force = -glm::normalize(velocity) * drag;
    glm::vec3 lift_direction = up;
    glm::vec3 lift_force = lift_direction * lift;
    
    acceleration += (drag_force + lift_force) / AIRCRAFT_MASS;
}

void Aircraft::ApplyControlSurfaces(float delta_time) {
    if (pitch_input != 0) {
        float pitch_rate = PITCH_SENSITIVITY * pitch_input;
        angular_velocity.x = pitch_rate;
    }
    
    if (roll_input != 0) {
        float roll_rate = ROLL_SENSITIVITY * roll_input;
        angular_velocity.z = roll_rate;
    }
    
    if (yaw_input != 0) {
        float yaw_rate = YAW_SENSITIVITY * yaw_input;
        angular_velocity.y = yaw_rate;
    }
}

void Aircraft::ApplyGravity(float delta_time) {
    acceleration.y -= GRAVITY;
}

void Aircraft::UpdateOrientation(float delta_time) {
    glm::vec3 ang_vel_rad = glm::vec3(
        MathUtils::DegToRad(angular_velocity.x),
        MathUtils::DegToRad(angular_velocity.y),
        MathUtils::DegToRad(angular_velocity.z)
    );
    
    glm::quat delta_rot = glm::quat(1, 0, 0, 0);
    float ang_mag = glm::length(ang_vel_rad);
    if (ang_mag > 0.001f) {
        delta_rot = glm::angleAxis(ang_mag * delta_time, glm::normalize(ang_vel_rad));
    }
    
    orientation = delta_rot * orientation;
    orientation = glm::normalize(orientation);
    
    glm::vec3 euler = MathUtils::QuatToEuler(orientation);
    pitch = euler.x;
    yaw = euler.y;
    roll = euler.z;
    
    angular_velocity *= 0.95f;
}

void Aircraft::UpdateDirectionVectors() {
    forward = glm::normalize(orientation * glm::vec3(0, 0, 1));
    right = glm::normalize(orientation * glm::vec3(1, 0, 0));
    up = glm::normalize(orientation * glm::vec3(0, 1, 0));
}

void Aircraft::ClampLimits() {
    if (position.y < 0) position.y = 0;
    if (position.y > MAX_ALTITUDE) position.y = MAX_ALTITUDE;
    
    speed = MathUtils::Clamp(speed, 0.0f, MAX_SPEED);
    
    pitch = MathUtils::WrapAngle(pitch);
    yaw = MathUtils::WrapAngle(yaw);
    roll = MathUtils::WrapAngle(roll);
    
    float vertical_accel = acceleration.y + GRAVITY;
    g_force = std::sqrt(acceleration.x * acceleration.x + vertical_accel * vertical_accel) / GRAVITY;
    g_force = MathUtils::Clamp(g_force, 0.0f, MAX_G_FORCE);
    
    if (g_force > 8.0f) {
        health -= (g_force - 8.0f) * 0.1f;
    }
}

void Aircraft::CheckGroundCollision() {
    if (position.y <= 0 && speed > 10.0f) {
        crashed = true;
        health = 0;
    }
}

float Aircraft::CalculateDrag() const {
    if (speed < 0.1f) return 0;
    
    float dynamic_pressure = 0.5f * AIR_DENSITY * speed * speed;
    float total_area = WING_AREA + FUSELAGE_AREA;
    return DRAG_COEFFICIENT * dynamic_pressure * total_area;
}

float Aircraft::CalculateLift() const {
    if (speed < MIN_SPEED) return 0;
    
    float dynamic_pressure = 0.5f * AIR_DENSITY * speed * speed;
    float lift = LIFT_COEFFICIENT * dynamic_pressure * WING_AREA;
    
    float aoa_factor = std::cos(MathUtils::DegToRad(angle_of_attack));
    return lift * aoa_factor;
}

float Aircraft::CalculateAngleOfAttack() const {
    if (speed < 0.1f) return 0;
    
    glm::vec3 velocity_normalized = glm::normalize(velocity);
    float dot_product = glm::dot(velocity_normalized, forward);
    dot_product = MathUtils::Clamp(dot_product, -1.0f, 1.0f);
    
    return MathUtils::RadToDeg(acos(dot_product));
}