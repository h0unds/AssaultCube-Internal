# AssaultCube Internal Base

An educational internal base for AssaultCube, demonstrating basic game hacking concepts and techniques. This project serves as a learning resource for understanding game internals, memory manipulation, and cheat development.

## Features
- ImGui menu system with keyboard navigation
- OpenGL hooking
- Basic memory manipulation
- Simple cheat features (God Mode, Infinite Ammo)
- Safe memory reading/writing class
- Vector math utilities

## Prerequisites
- Visual Studio 2019 or newer
- Windows SDK 10.0
- DirectX SDK
- AssaultCube 1.2.0.2

## Dependencies
- [MinHook](https://github.com/TsudaKageyu/minhook) - Hooking library
- [ImGui](https://github.com/ocornut/imgui) - GUI library

## Building
1. Clone the repository
2. Open the solution in Visual Studio
3. Make sure to compile in Release x86 (32-bit) mode - THIS IS IMPORTANT!
4. Build the solution

## Usage
1. Run AssaultCube
2. Inject the compiled DLL using your preferred injector
3. Press INSERT to toggle the menu
4. Use arrow keys to navigate:
   - UP/DOWN: Select options
   - LEFT/RIGHT: Toggle features

## Project Structure
- `main.cpp` - DLL entry point and OpenGL hook
- `menu.h` - ImGui menu implementation
- `memory.h` - Safe memory manipulation class
- `math.h` - Vector math utilities
- `misc.cpp` - Cheat features implementation

## Educational Purpose
This project is meant for educational purposes only, to help understand:
- DLL injection and hooking
- Game memory manipulation
- GUI creation in game hacks
- Basic game math
- Game cheat structure and organization

## Disclaimer
This project is for educational purposes only. Do not use these techniques in online games or to disrupt other players' experiences.

## License
This project is licensed under the MIT License - see the LICENSE file for details.