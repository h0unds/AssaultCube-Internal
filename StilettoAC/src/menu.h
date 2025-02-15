/*
 * Menu System Header
 *
 * Handles the game's cheat menu interface including:
 * - Input handling (arrow keys for navigation)
 * - Menu rendering with ImGui
 * - Toggle states for different cheats
 */
#pragma once
#include "imgui.h"
#include <Windows.h>
#include "settings.h"

namespace Menu {
    // Track previous key states to detect key press events
    inline bool lastUpState = false;
    inline bool lastDownState = false;
    inline bool lastLeftState = false;
    inline bool lastRightState = false;

    // Process keyboard input for menu navigation
    inline void HandleInput() {
        // Don't process input if menu is hidden
        if (!Settings::Menu::show_menu) return;

        // Get current state of navigation keys
        bool currentUpState = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
        bool currentDownState = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
        bool currentLeftState = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
        bool currentRightState = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;

        // Handle menu item selection (UP/DOWN keys)
        if (currentUpState && !lastUpState) {
            Settings::Menu::selected_item--;
            if (Settings::Menu::selected_item < 0)
                Settings::Menu::selected_item = Settings::Menu::max_items - 1;
        }

        if (currentDownState && !lastDownState) {
            Settings::Menu::selected_item++;
            if (Settings::Menu::selected_item >= Settings::Menu::max_items)
                Settings::Menu::selected_item = 0;
        }

        // Handle feature toggling (LEFT/RIGHT keys)
        if ((currentLeftState && !lastLeftState) || (currentRightState && !lastRightState)) {
            bool newState = currentRightState && !lastRightState;

            // Update feature states based on selected item
            switch (Settings::Menu::selected_item) {
            case 0:
                Settings::Misc::god_mode = newState;
                break;
            case 1:
                Settings::Misc::infinite_ammo = newState;
                break;
            }
        }

        // Update previous key states
        lastUpState = currentUpState;
        lastDownState = currentDownState;
        lastLeftState = currentLeftState;
        lastRightState = currentRightState;
    }

    // Render the cheat menu using ImGui
    inline void Render() {
        if (!Settings::Menu::show_menu) return;

        // Set window flags
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;

        // Create main window
        ImGui::Begin("Stiletto by Shiz0Fr", nullptr, window_flags);

        // Set fixed window size
        ImGui::SetWindowSize(ImVec2(200, 250));

        // Display controls info
        ImGui::Text("Navigation: UP/DOWN");
        ImGui::Text("LEFT = OFF, RIGHT = ON");
        ImGui::Separator();

        // Menu items format strings
        const char* items[] = {
            "God Mode: %s",
            "Infinite Ammo: %s"
        };

        // Render each menu item
        for (int i = 0; i < Settings::Menu::max_items; i++) {
            // Highlight selected item
            if (Settings::Menu::selected_item == i) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
            }

            // Display item status
            switch (i) {
            case 0:
                ImGui::Text(items[i], Settings::Misc::god_mode ? "ON" : "OFF");
                break;
            case 1:
                ImGui::Text(items[i], Settings::Misc::infinite_ammo ? "ON" : "OFF");
                break;
            }

            // Remove highlight if item was selected
            if (Settings::Menu::selected_item == i) {
                ImGui::PopStyleColor();
            }
        }

        ImGui::End();
    }
}