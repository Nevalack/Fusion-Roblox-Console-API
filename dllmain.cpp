#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <TlHelp32.h>

using namespace std;

auto reloc(uintptr_t a) {
    return a + (uintptr_t)GetModuleHandleA(nullptr);
}

int main() {
    VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, new DWORD);
    *(BYTE*)(&FreeConsole) = (0xC3);
    AllocConsole();
    SetConsoleTitleA("Fusion Roblox Console");
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    HWND ConsoleHandle = GetConsoleWindow();
    ::SetWindowPos(ConsoleHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::ShowWindow(ConsoleHandle, SW_NORMAL);

    //main exploit api begins here

        cout << "User Id:";
        cout << *(uintptr_t*)reloc(0x33EF9C8) << endl; //roblox uid address (last checked 8/4/2021)
}

int __stdcall DllMain(const HMODULE Module, uintptr_t Reason, const LPVOID Reserved) {
    if (Reason == 1) {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    }
    return 1;
}
