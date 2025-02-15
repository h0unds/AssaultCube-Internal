/*
 * Misc Features Header
 *
 * Defines functions for basic cheat features like:
 * - God Mode
 * - Infinite Ammo
 * Each feature can be toggled through the menu
 */
#pragma once
#include <Windows.h>
#include "../../utils/memory.h"
#include "../../offsets.h"
#include "../../settings.h"

namespace Misc {
    // Sets player health to 1337 when enabled
    void GodMode();

    // Sets player ammo to 1337 when enabled
    void InfiniteAmmo();
}