#include "misc.h"

namespace Misc {
    void GodMode() {
        // Return if feature is disabled
        if (!Settings::Misc::god_mode) return;

        // Get local player pointer
        uintptr_t localPlayer = Memory::Read<uintptr_t>(Memory::GetModuleBase() + Offsets::LocalPlayer);
        if (!localPlayer) return;

        // Set health to 1337
        Memory::Write<int>(localPlayer + Offsets::Health, 1337);
    }

    void InfiniteAmmo() {
        // Return if feature is disabled
        if (!Settings::Misc::infinite_ammo) return;

        // Get local player pointer
        uintptr_t localPlayer = Memory::Read<uintptr_t>(Memory::GetModuleBase() + Offsets::LocalPlayer);
        if (!localPlayer) return;

        // Set ammo to 1337
        Memory::Write<int>(localPlayer + Offsets::Ammo, 1337);
    }
}