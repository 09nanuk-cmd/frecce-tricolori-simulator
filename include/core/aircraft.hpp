#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include "../utils/config.hpp"
#include "../utils/math_utils.hpp"

class Aircraft {
public:
    int id;
    std::string name;
    bool is_player_controlled;

    glm::vec3 position;
    glm::quat orientation;
    float pitch, yaw, roll;

    glm::vec3 velocity;
    glm::vec3 acceleration;
    float speed;
    
    glm::vec3 forward, right, up;

    float throttle;
    float pitch_input, roll_input, yaw_input;
    bool smoke_enabled;

    float g_force;
    float angle_of_attack;
    float fuel;

    bool stalled, crashed;
    float health;
    float flight_time;

    Aircraft(int aircraft_id, const std::string& aircraft_name, bool is_player = false);

    void Reset(const glm::vec3& spawn_pos, const glm::vec3& spawn_heading);
    void Update(float delta_time);

    void SetThrottle(float value);
    void SetPitchInput(float value);
    void SetRollInput(float value);
    void SetYawInput(float value);
    void SetSmokeEnabled(bool enabled);

    float GetThrottle() const { return throttle; }
    float GetPitchInput() const { return pitch_input; }
    float GetRollInput() const { return roll_input; }
    float GetYawInput() const { return yaw_input; }
    bool GetSmokeEnabled() const { return smoke_enabled; }

    glm::vec3 GetPosition() const { return position; }
    glm::quat GetOrientation() const { return orientation; }
    glm::vec3 GetVelocity() const { return velocity; }
    float GetSpeed() const { return speed; }
    float GetPitch() const { return pitch; }
    float GetYaw() const { return yaw; }
    float GetRoll() const { return roll; }
    float GetAltitude() const { return position.y; }
    
    glm::vec3 GetForwardVector() const { return forward; }
    glm::vec3 GetRightVector() const { return right; }
    glm::vec3 GetUpVector() const { return up; }
    
    float GetGForce() const { return g_force; }
    float GetAngleOfAttack() const { return angle_of_attack; }
    float GetFuel() const { return fuel; }
    float GetHealth() const { return health; }
    bool IsStalled() const { return stalled; }
    bool IsCrashed() const { return crashed; }
    float GetFlightTime() const { return flight_time; }

    float GetHorizontalDistanceTo(const Aircraft& other) const;
    float GetDistanceTo(const Aircraft& other) const;
    float GetBearingTo(const Aircraft& other) const;

private:
    glm::vec3 angular_velocity;

    void ApplyAerodynamicForces(float delta_time);
    void ApplyThrust(float delta_time);
    void ApplyControlSurfaces(float delta_time);
    void ApplyGravity(float delta_time);
    void UpdateOrientation(float delta_time);
    void UpdateDirectionVectors();
    void ClampLimits();
    void CheckGroundCollision();
    float CalculateDrag() const;
    float CalculateLift() const;
    float CalculateAngleOfAttack() const;
};

#endif