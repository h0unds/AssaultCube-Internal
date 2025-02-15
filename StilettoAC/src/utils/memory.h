/*
 * Memory Class - Safe Memory Manipulation
 *
 * This class provides safe methods for reading and writing game memory.
 * It includes error handling and protection against invalid memory access.
 *
 * Key features:
 * - Safe memory reading with templates
 * - Protected memory writing
 * - Basic module base address handling
 */

#pragma once
#include <Windows.h>

class Memory {
public:
    // Initialize the memory class by getting the game's module base address
    static bool Initialize() {
        moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA("ac_client.exe"));
        return moduleBase != 0;
    }

    // Get the base address of the game module
    static uintptr_t GetModuleBase() {
        return moduleBase;
    }

    // Safely read a value of type T from the specified memory address
    // Returns default-constructed T if read fails
    template<typename T>
    static T Read(uintptr_t address) {
        try {
            // Check if the memory address is valid and readable
            if (IsBadReadPtr(reinterpret_cast<void*>(address), sizeof(T)))
                return T{};
            return *reinterpret_cast<T*>(address);
        }
        catch (...) {
            return T{};
        }
    }

    // Safely write a value of type T to the specified memory address
    // Returns true if write succeeds, false otherwise
    template<typename T>
    static bool Write(uintptr_t address, const T& value) {
        try {
            // Change memory protection to allow writing
            DWORD oldProtect;
            if (!VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            // Write the value
            *reinterpret_cast<T*>(address) = value;

            // Restore original memory protection
            VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), oldProtect, &oldProtect);
            return true;
        }
        catch (...) {
            return false;
        }
    }

private:
    static inline uintptr_t moduleBase = 0;  // Base address of the game module
};