/*
 * AssaultCube Internal Base - Educational Purpose Only
 *
 * This file contains the DLL entry point and OpenGL hook setup.
 * It demonstrates how to:
 * 1. Hook DirectX/OpenGL functions for rendering
 * 2. Initialize ImGui for menu rendering
 * 3. Set up a basic cheat structure
 */
#include <windows.h>
#include <gl/GL.h>
#include "MinHook.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"

#include "menu.h"
#include "cheats/misc/misc.h"
#include "utils/memory.h"
#include "settings.h"

 // Function pointer for the original wglSwapBuffers
typedef BOOL(WINAPI* twglSwapBuffers)(HDC hDc);
twglSwapBuffers owglSwapBuffers;

// Hooked wglSwapBuffers function - this is where we render our ImGui menu
BOOL WINAPI hwglSwapBuffers(HDC hDc) {
    // Initialize ImGui on first call
    static bool init = false;
    if (!init) {
        if (ImGui::CreateContext() == nullptr) return owglSwapBuffers(hDc);

        // Find the game window
        HWND gameWindow = FindWindowA(NULL, "AssaultCube");
        if (!gameWindow) return owglSwapBuffers(hDc);

        // Initialize ImGui with OpenGL3 and Win32
        ImGui_ImplWin32_Init(gameWindow);
        ImGui_ImplOpenGL3_Init("#version 110");

        // Set up ImGui style and disable ini file
        ImGui::StyleColorsDark();
        ImGui::GetIO().IniFilename = NULL;

        init = true;
    }

    // Toggle menu with INSERT key
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        Settings::Menu::show_menu = !Settings::Menu::show_menu;
    }

    // Start new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Handle menu input and rendering
    Menu::HandleInput();
    Menu::Render();

    // Execute cheat functions
    Misc::GodMode();
    Misc::InfiniteAmmo();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Call original function
    return owglSwapBuffers(hDc);
}

// Main thread that initializes everything
DWORD WINAPI MainThread(LPVOID lpReserved) {
    // Wait for game to fully initialize
    Sleep(1000);

    // Initialize memory class for reading/writing game memory
    if (!Memory::Initialize()) {
        return FALSE;
    }

    // Get OpenGL module handle
    HMODULE hMod = GetModuleHandleA("opengl32.dll");
    if (!hMod) return FALSE;

    // Get original wglSwapBuffers function
    owglSwapBuffers = (twglSwapBuffers)GetProcAddress(hMod, "wglSwapBuffers");
    if (!owglSwapBuffers) return FALSE;

    // Initialize MinHook
    if (MH_Initialize() != MH_OK) return FALSE;

    // Create hook for wglSwapBuffers
    if (MH_CreateHook(owglSwapBuffers, hwglSwapBuffers,
        reinterpret_cast<void**>(&owglSwapBuffers)) != MH_OK) {
        MH_Uninitialize();
        return FALSE;
    }

    // Enable all hooks
    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
        MH_Uninitialize();
        return FALSE;
    }

    return TRUE;
}

// DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
    }
    return TRUE;
}