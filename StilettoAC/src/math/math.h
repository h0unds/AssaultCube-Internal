/*
 * Math Utilities
 *
 * This file contains basic vector mathematics needed for game hacking.
 * Includes 2D and 3D vector implementations with basic operations.
 * Also includes WorldToScreen conversion for ESP features.
 */

#pragma once
#include <cmath>
#include <Windows.h>

namespace Math {
    // 2D Vector structure
    struct Vec2 {
        float x, y;

        // Constructors
        Vec2() : x(0.f), y(0.f) {}
        Vec2(float x, float y) : x(x), y(y) {}

        // Basic vector operations
        Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
        Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
        Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }
    };

    // 3D Vector structure
    struct Vec3 {
        float x, y, z;

        // Constructors
        Vec3() : x(0.f), y(0.f), z(0.f) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        // Basic vector operations
        Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
        Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
        Vec3 operator*(float scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }

        // Convert 3D world position to 2D screen coordinates
        bool WorldToScreen(Vec2& out, float(*viewMatrix)[4][4]) const;
    };
}