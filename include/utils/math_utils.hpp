#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <cmath>

namespace MathUtils {

inline glm::vec3 SafeNormalize(const glm::vec3& v, const glm::vec3& fallback = glm::vec3(0, 1, 0)) {
    float length = glm::length(v);
    if (length > 0.0001f) return glm::normalize(v);
    return fallback;
}

template<typename T>
inline T Clamp(T value, T min_val, T max_val) {
    return (value < min_val) ? min_val : (value > max_val) ? max_val : value;
}

template<typename T>
inline T Lerp(T a, T b, float t) {
    t = Clamp(t, 0.0f, 1.0f);
    return a + (b - a) * t;
}

inline float DegToRad(float degrees) {
    return degrees * 3.14159265359f / 180.0f;
}

inline float RadToDeg(float radians) {
    return radians * 180.0f / 3.14159265359f;
}

inline glm::quat EulerToQuat(float pitch, float yaw, float roll) {
    pitch = DegToRad(pitch);
    yaw = DegToRad(yaw);
    roll = DegToRad(roll);
    return glm::quat(glm::vec3(pitch, yaw, roll));
}

inline glm::vec3 QuatToEuler(const glm::quat& q) {
    glm::vec3 euler = glm::eulerAngles(q);
    return glm::vec3(RadToDeg(euler.x), RadToDeg(euler.y), RadToDeg(euler.z));
}

inline glm::quat Slerp(const glm::quat& a, const glm::quat& b, float t) {
    return glm::slerp(a, b, Clamp(t, 0.0f, 1.0f));
}

inline float WrapAngle(float angle) {
    while (angle > 180.0f) angle -= 360.0f;
    while (angle < -180.0f) angle += 360.0f;
    return angle;
}

inline float AngleDifference(float a, float b) {
    return WrapAngle(a - b);
}

inline float Distance(const glm::vec3& a, const glm::vec3& b) {
    return glm::distance(a, b);
}

inline float HorizontalDistance(const glm::vec3& a, const glm::vec3& b) {
    glm::vec2 a_flat = glm::vec2(a.x, a.z);
    glm::vec2 b_flat = glm::vec2(b.x, b.z);
    return glm::distance(a_flat, b_flat);
}

inline glm::vec3 CalcVelocity(const glm::vec3& current_pos, const glm::vec3& prev_pos, float dt) {
    if (dt < 0.0001f) return glm::vec3(0);
    return (current_pos - prev_pos) / dt;
}

inline float SpeedMagnitude(const glm::vec3& velocity) {
    return glm::length(velocity);
}

inline float ExponentialSmoothing(float current, float target, float alpha) {
    return current + (target - current) * Clamp(alpha, 0.0f, 1.0f);
}

inline glm::vec3 ExponentialSmoothingVec3(const glm::vec3& current, const glm::vec3& target, float alpha) {
    return current + (target - current) * Clamp(alpha, 0.0f, 1.0f);
}

}
#endif