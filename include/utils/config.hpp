#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <glm/glm.hpp>

// ==================== WINDOW CONFIG ====================
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int TARGET_FPS = 60;
const char* WINDOW_TITLE = "Frecce Tricolori Simulator";

// ==================== PHYSICS CONFIG ====================
const float GRAVITY = 9.81f;
const float AIR_DENSITY = 1.225f;  // kg/m³ at sea level
const float TIME_STEP = 1.0f / TARGET_FPS;

// ==================== AIRCRAFT CONFIG ====================
const int NUM_AIRCRAFT = 10;
const int PLAYER_AIRCRAFT_ID = 0;

// Aircraft physical properties (M-346 Ljet specs)
const float AIRCRAFT_MASS = 5000.0f;  // kg
const float WING_AREA = 25.2f;        // m²
const float FUSELAGE_AREA = 3.5f;     // m²
const float DRAG_COEFFICIENT = 0.25f;
const float LIFT_COEFFICIENT = 0.4f;

// Speed limits (m/s)
const float MIN_SPEED = 50.0f;        // Stall speed
const float CRUISE_SPEED = 150.0f;
const float MAX_SPEED = 280.0f;       // Max safe speed
const float ENGINE_THRUST = 80000.0f; // N (Newtons)

// Maneuver limits
const float MAX_PITCH = 90.0f;        // degrees
const float MAX_ROLL = 180.0f;        // degrees
const float MAX_G_FORCE = 9.0f;       // G's
const float ANGULAR_VELOCITY_MAX = 180.0f;  // degrees/sec

// ==================== CONTROL INPUT CONFIG ====================
const float PITCH_SENSITIVITY = 100.0f;      // degrees/sec
const float ROLL_SENSITIVITY = 150.0f;       // degrees/sec
const float YAW_SENSITIVITY = 50.0f;         // degrees/sec
const float THROTTLE_RATE = 0.5f;            // per second

// ==================== CAMERA CONFIG ====================
const float CAMERA_DISTANCE = 30.0f;  // meters behind aircraft
const float CAMERA_HEIGHT = 5.0f;     // meters above aircraft

// ==================== WORLD CONFIG ====================
const float WORLD_SIZE = 50000.0f;    // World is 50km x 50km
const float SEA_LEVEL = 0.0f;
const float MAX_ALTITUDE = 10000.0f;  // 10km max altitude
const float GROUND_LEVEL = 0.0f;

// ==================== AI CONFIG ====================
const float AI_REACTION_TIME = 0.2f;  // seconds
const float AI_LOOKAHEAD = 50.0f;     // meters
const float AI_FORMATION_DISTANCE = 30.0f;  // meters from leader

// ==================== SCORING CONFIG ====================
const float TRAJECTORY_TOLERANCE = 15.0f;  // meters
const float PERFECT_SCORE_MULTIPLIER = 1.0f;
const float GOOD_SCORE_MULTIPLIER = 0.8f;
const float POOR_SCORE_MULTIPLIER = 0.5f;

// ==================== COLOR SCHEME ====================
const glm::vec3 COLOR_RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 COLOR_WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 COLOR_GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 COLOR_SKY_BLUE = glm::vec3(0.53f, 0.81f, 0.92f);
const glm::vec3 COLOR_GROUND = glm::vec3(0.34f, 0.45f, 0.23f);
const glm::vec3 COLOR_RUNWAY = glm::vec3(0.3f, 0.3f, 0.3f);

#endif // CONFIG_HPP