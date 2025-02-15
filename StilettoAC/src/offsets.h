/*
 * Game Offsets
 *
 * Contains memory offsets for various game features:
 * - LocalPlayer: Pointer to the local player entity
 * - Health: Health value offset from player base
 * - Ammo: Ammo value offset from player base
 * - ViewMatrix: Game's view matrix for coordinate conversion
 */
#pragma once

class Offsets {
public:
    static constexpr uintptr_t LocalPlayer = 0x10F4F4;
    static constexpr uintptr_t Health = 0xF8;
    static constexpr uintptr_t Ammo = 0x150;
    static constexpr uintptr_t ViewMatrix = 0x501AE8;
};