#include "math.h"
#include "../offsets.h"
#include "../utils/memory.h"

// Converts a 3D world position to 2D screen coordinates using the game's view matrix
// out: Reference to Vec2 that will store the screen coordinates
// viewMatrix: Pointer to the game's 4x4 view matrix
// Returns: true if point is visible on screen, false if behind camera

namespace Math {
    bool Vec3::WorldToScreen(Vec2& out, float(*viewMatrix)[4][4]) const
    {
        // Calculate w-component for perspective projection
        const float w = (*viewMatrix)[3][0] * x + (*viewMatrix)[3][1] * y + (*viewMatrix)[3][2] * z + (*viewMatrix)[3][3];

        // Check if point is behind camera (w <= 0) or too close (w < 0.01)
        if (w <= 0.01f)
            return false;

        // Calculate inverse w for perspective divide
        const float invW = 1.0f / w;

        // Get current screen dimensions
        const float screenWidth = GetSystemMetrics(SM_CXSCREEN);
        const float screenHeight = GetSystemMetrics(SM_CYSCREEN);

        // Transform to screen coordinates
        out.x = (screenWidth / 2) + (((*viewMatrix)[0][0] * x + (*viewMatrix)[0][1] * y + (*viewMatrix)[0][2] * z + (*viewMatrix)[0][3]) * invW * (screenWidth / 2));
        out.y = (screenHeight / 2) - (((*viewMatrix)[1][0] * x + (*viewMatrix)[1][1] * y + (*viewMatrix)[1][2] * z + (*viewMatrix)[1][3]) * invW * (screenHeight / 2));

        return true;
    }
}