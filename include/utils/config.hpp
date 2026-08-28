#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <glm/glm.hpp>

// ==================== WINDOW CONFIG ====================
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr int TARGET_FPS = 60;
constexpr const char* WINDOW_TITLE = "Frecce Tricolori Simulator";

// ==================== PHYSICS CONFIG ====================
constexpr float GRAVITY = 9.81f;
constexpr float AIR_DENSITY = 1.225f;  // kg/m³ at sea level
constexpr float TIME_STEP = 1.0f / TARGET_FPS;

// ==================== AIRCRAFT CONFIG ====================
constexpr int NUM_AIRCRAFT = 10;
constexpr int PLAYER_AIRCRAFT_ID = 0;

// Aircraft physical properties (M-346 Ljet specs)
constexpr float AIRCRAFT_MASS = 5000.0f;  // kg
constexpr float WING_AREA = 25.2f;        // m²
constexpr float FUSELAGE_AREA = 3.5f;     // m²
constexpr float DRAG_COEFFICIENT = 0.25f;
constexpr float LIFT_COEFFICIENT = 0.4f;

// Speed limits (m/s)
constexpr float MIN_SPEED = 50.0f;        // Stall speed
constexpr float CRUISE_SPEED = 150.0f;
constexpr float MAX_SPEED = 280.0f;       // Max safe speed
constexpr float ENGINE_THRUST = 80000.0f; // N (Newtons)

// Maneuver limits
constexpr float MAX_PITCH = 90.0f;        // degrees
constexpr float MAX_ROLL = 180.0f;        // degrees
constexpr float MAX_G_FORCE = 9.0f;       // G's
constexpr float ANGULAR_VELOCITY_MAX = 180.0f;  // degrees/sec

// ==================== CONTROL INPUT CONFIG ====================
constexpr float PITCH_SENSITIVITY = 100.0f;      // degrees/sec
constexpr float ROLL_SENSITIVITY = 150.0f;       // degrees/sec
constexpr float YAW_SENSITIVITY = 50.0f;         // degrees/sec
constexpr float THROTTLE_RATE = 0.5f;            // per second

// ==================== CAMERA CONFIG ====================
constexpr float CAMERA_DISTANCE = 30.0f;  // meters behind aircraft
constexpr float CAMERA_HEIGHT = 5.0f;     // meters above aircraft

// ==================== WORLD CONFIG ====================
constexpr float WORLD_SIZE = 50000.0f;    // World is 50km x 50km
constexpr float SEA_LEVEL = 0.0f;
constexpr float MAX_ALTITUDE = 10000.0f;  // 10km max altitude

// ==================== AI CONFIG ====================
constexpr float AI_REACTION_TIME = 0.2f;  // seconds
constexpr float AI_LOOKAHEAD = 50.0f;     // meters
constexpr float AI_FORMATION_DISTANCE = 30.0f;  // meters from leader

// ==================== SCORING CONFIG ====================
constexpr float TRAJECTORY_TOLERANCE = 15.0f;  // meters
constexpr float PERFECT_SCORE_MULTIPLIER = 1.0f;
constexpr float GOOD_SCORE_MULTIPLIER = 0.8f;
constexpr float POOR_SCORE_MULTIPLIER = 0.5f;

// ==================== COLOR SCHEME ====================
constexpr glm::vec3 COLOR_RED = glm::vec3(1.0f, 0.0f, 0.0f);
constexpr glm::vec3 COLOR_WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
constexpr glm::vec3 COLOR_GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
constexpr glm::vec3 COLOR_SKY_BLUE = glm::vec3(0.53f, 0.81f, 0.92f);
constexpr glm::vec3 COLOR_GROUND = glm::vec3(0.34f, 0.45f, 0.23f);
constexpr glm::vec3 COLOR_RUNWAY = glm::vec3(0.3f, 0.3f, 0.3f);

#endif // CONFIG_HPP
