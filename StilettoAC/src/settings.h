/*
 * Settings Header
 *
 * Contains all the configurable settings and states for the cheat:
 * - Menu settings (visibility, selection)
 * - Feature toggles (god mode, infinite ammo, etc.)
 */
#pragma once

namespace Settings {
    // Menu-related settings
    namespace Menu {
        inline bool show_menu = false;      // Is menu visible?
        inline int selected_item = 0;       // Currently selected menu item
        inline int max_items = 2;           // Total number of menu items
    }

    // Cheat feature toggles
    namespace Misc {
        inline bool god_mode = false;       // God mode status
        inline bool infinite_ammo = false;  // Infinite ammo status
    }
}