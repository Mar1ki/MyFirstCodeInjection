
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Detours/include/detours.h"
#include "dllMain.h"
#define gameAddr ((uintptr_t)GetModuleHandle("GameAssembly.dll"))
DWORD_PTR mechanic1ret =0;
DWORD_PTR mechanic2ret=0;
DWORD_PTR mechanic3ret=0;
DWORD MainThread(HMODULE Module)
{
    AllocConsole();
    FILE* Dummy;
    freopen_s(&Dummy, "CONOUT$", "w", stdout);
    freopen_s(&Dummy, "CONIN$", "r", stdin);
    PDETOUR_TRAMPOLINE mechanic1i = {};
    PDETOUR_TRAMPOLINE mechanic2i = {};
    PDETOUR_TRAMPOLINE mechanic3i = {};
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    auto mechanic1 = (LPVOID)(gameAddr + 0x62CCF8);
    auto mechanic2 = (LPVOID)(gameAddr + 0x62D18B);
    auto mechanic3 = (LPVOID)(gameAddr + 0x62EC73);
    DetourAttachEx((PVOID*)&mechanic1, (PVOID)&mechanic1hk, &mechanic2i, nullptr, nullptr);

    DetourAttachEx((PVOID*)&mechanic2, (PVOID)&mechanic2hk, &mechanic1i, nullptr, nullptr);

    DetourAttachEx((PVOID*)&mechanic3, (PVOID)&mechanic3hk, &mechanic3i, nullptr, nullptr);
    DetourTransactionCommit();
    mechanic1ret = (DWORD_PTR)gameAddr + 0x62CCFD;
    mechanic2ret = (DWORD_PTR)gameAddr + 0x62D192;
    mechanic3ret = (DWORD_PTR)gameAddr + 0x62EC78;
    while (true) {

        std::cout << uintptr_t(mechanic1hk) << "\n";
        std::cout << uintptr_t(mechanic2hk) << "\n";
        std::cout << uintptr_t(mechanic3hk) << "\n";
        std::cout << "=======================" << "\n";
        if (GetAsyncKeyState(VK_DELETE) & 1) {//
            break;
        }


        Sleep(1000);
    }
    FreeLibraryAndExitThread(Module, 0);
    return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
        break;
    }

    return TRUE;
}