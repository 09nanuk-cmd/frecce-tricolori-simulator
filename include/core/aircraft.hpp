#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include "../utils/config.hpp"
#include "../utils/math_utils.hpp"

/**
 * Represents complete state of an aircraft in flight
 * Handles position, orientation, velocity, and control inputs
 */
class Aircraft {
public:
    // ==================== IDENTIFIERS ====================
    int id;                                 // Unique aircraft ID (0-9)
    std::string name;                       // Aircraft name (e.g., "Freccia 1")
    bool is_player_controlled;              // True if player controls this aircraft

    // ==================== POSITION & ORIENTATION ====================
    glm::vec3 position;                     // World position (meters)
    glm::quat orientation;                  // Rotation as quaternion
    
    // Euler angles (cached for convenience, degrees)
    float pitch;                            // Nose up/down
    float yaw;                              // Left/right heading
    float roll;                             // Wing tilt

    // ==================== VELOCITY & ACCELERATION ====================
    glm::vec3 velocity;                     // Current velocity (m/s)
    glm::vec3 acceleration;                 // Current acceleration (m/s²)
    float speed;                            // Speed magnitude (m/s)
    
    // Direction vectors
    glm::vec3 forward;                      // Forward direction (nose)
    glm::vec3 right;                        // Right wing direction
    glm::vec3 up;                           // Up direction

    // ==================== CONTROL INPUTS ====================
    float throttle;                         // 0.0 to 1.0
    float pitch_input;                      // -1.0 to 1.0 (up/down)
    float roll_input;                       // -1.0 to 1.0 (left/right)
    float yaw_input;                        // -1.0 to 1.0 (rudder)
    bool smoke_enabled;                     // Smoke trail toggle

    // ==================== PHYSICAL STATE ====================
    float g_force;                          // Current G-force experienced
    float angle_of_attack;                  // AoA in degrees
    float fuel;                             // Fuel percentage (0-100)

    // ==================== CONSTRAINTS & LIMITS ====================
    bool stalled;                           // True if speed < stall speed
    bool crashed;                           // True if crashed into ground
    float health;                           // Aircraft health (0-100)

    // ==================== TIMING ====================
    float flight_time;                      // Total flight time in seconds

    // Constructor
    Aircraft(int aircraft_id, const std::string& aircraft_name, bool is_player = false);

    // ==================== STATE MANAGEMENT ====================

    /**
     * Reset aircraft to spawn position and state
     */
    void Reset(const glm::vec3& spawn_pos, const glm::vec3& spawn_heading);

    /**
     * Update aircraft state based on physics and control inputs
     * Called once per frame
     */
    void Update(float delta_time);

    /**
     * Set control input (normalized values)
     */
    void SetThrottle(float value);
    void SetPitchInput(float value);
    void SetRollInput(float value);
    void SetYawInput(float value);
    void SetSmokeEnabled(bool enabled);

    /**
     * Get control input values
     */
    float GetThrottle() const { return throttle; }
    float GetPitchInput() const { return pitch_input; }
    float GetRollInput() const { return roll_input; }
    float GetYawInput() const { return yaw_input; }
    bool GetSmokeEnabled() const { return smoke_enabled; }

    // ==================== GETTERS ====================

    glm::vec3 GetPosition() const { return position; }
    glm::quat GetOrientation() const { return orientation; }
    glm::vec3 GetVelocity() const { return velocity; }
    glm::vec3 GetAcceleration() const { return acceleration; }
    
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

    // ==================== POSITION HELPERS ====================

    /**
     * Get horizontal distance to another aircraft
     */
    float GetHorizontalDistanceTo(const Aircraft& other) const;

    /**
     * Get distance to another aircraft (3D)
     */
    float GetDistanceTo(const Aircraft& other) const;

    /**
     * Get bearing (heading) to another aircraft in degrees
     */
    float GetBearingTo(const Aircraft& other) const;

private:
    // ==================== INTERNAL PHYSICS ====================

    /**
     * Apply aerodynamic forces
     */
    void ApplyAerodynamicForces(float delta_time);

    /**
     * Apply engine thrust
     */
    void ApplyThrust(float delta_time);

    /**
     * Apply control surface effects (pitch, roll, yaw)
     */
    void ApplyControlSurfaces(float delta_time);

    /**
     * Apply gravity
     */
    void ApplyGravity(float delta_time);

    /**
     * Update orientation from angular velocity
     */
    void UpdateOrientation(float delta_time);

    /**
     * Update direction vectors based on orientation
     */
    void UpdateDirectionVectors();

    /**
     * Clamp controls and physical parameters to safe limits
     */
    void ClampLimits();

    /**
     * Check for collisions with ground
     */
    void CheckGroundCollision();

    /**
     * Calculate aerodynamic properties
     */
    float CalculateDrag() const;
    float CalculateLift() const;
    float CalculateAngleOfAttack() const;

    // Angular velocity (degrees/sec)
    glm::vec3 angular_velocity;
};

#endif // AIRCRAFT_HPP
