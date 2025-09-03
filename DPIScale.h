#pragma once
#include <optional>
#include <windows.h>
#include <wrl.h>
#include <string>
//using std::optional;

//
// DPIScale – per-monitor v2 DPI támogatás, biztonságos visszaeséssel.
// - Init(HWND) egyszer az ablak létrehozása után.
// - HandleDpiChanged(HWND, WPARAM, LPARAM) a WM_DPICHANGED-ben.
// - GetDpiX/Y(), PxToDip/DipToPx, PxToMM/MMToPx, stb.
// - Közvetlenül kérhető a window-DPI (GetWndDpiX/Y), a monitor-DPI (GetMonDpiX/Y).
//
// Megjegyzés: DIP = device-independent pixel = 96 DPI alapú egység.
//

class DPIScale
{
public:
    static void Initialize(HWND hwnd) { Init(hwnd); }  // régi név támogatása

    // Meghívható a WinMain/InitInstance kezdetén, beállítja a folyamat DPI-t.
    static void EnsureProcessDpiAwareness();

    // Meghívandó egyszer az ablak létrejötte után (pl. WM_NCCREATE/WM_CREATE).
    static void Init(HWND hwnd);

    // Meghívandó WM_DPICHANGED üzenetnél.
    // Visszaadja a javasolt új ablak-geometriát (rcSuggested), ha volt.
    static std::optional<RECT> HandleDpiChanged(HWND hwnd, WPARAM wParam, LPARAM lParam);

    // Jelenlegi (ablakhoz/monitorhoz tartozó) DPI lekérdezése
    static UINT GetDpiX();
    static UINT GetDpiY();

    // Közvetlen lekérdezések
    static UINT GetWndDpiX(HWND hwnd);
    static UINT GetWndDpiY(HWND hwnd);
    static UINT GetMonDpiX(HMONITOR hmon);
    static UINT GetMonDpiY(HMONITOR hmon);

    // Konverziók (jelenlegi DPI szerint)
    static float PxToDipX(float px);
    static float PxToDipY(float px);
    static float DipToPxX(float dip);
    static float DipToPxY(float dip);

    // Milliméter konverziók – a fizikai DPI alapján (X/Y külön számolva)
    static float PxToMM_X(float px);
    static float PxToMM_Y(float px);
    static float MMToPx_X(float mm);
    static float MMToPx_Y(float mm);

    // Nyers skálák (jelenlegi állapot)
    static float ScaleFrom96_X(); // = dpiX / 96.f
    static float ScaleFrom96_Y(); // = dpiY / 96.f

    // Direct2D-hez jól jön: 1 DIP = 1 egység, képernyő DPI szerint.
    // Ezzel a szorzóval lehet egy D2D világmátrixot beállítani (ha szükséges).
    static float D2DUserToDipScale_X(); // = 96.f / dpiX (ha px-alapú rajzot DIP-re tolunk)
    static float D2DUserToDipScale_Y();

    // Frissíti a belső DPI értéket a megadott ablak szerint
    static void Refresh(HWND hwnd);

private:
    static UINT s_dpiX;
    static UINT s_dpiY;

    // SHCore/GetDpiForMonitor dinamikus hívása
    static bool TryGetDpiForMonitor(HMONITOR hmon, UINT* dpiX, UINT* dpiY);
    // user32:GetDpiForWindow dinamikus hívása
    static UINT TryGetDpiForWindow(HWND hwnd);

    // Fallback a klasszikus GetDeviceCaps LOGPIXELSX/Y-ra
    static void GetDeviceCapsDpi(HDC hdc, UINT* dpiX, UINT* dpiY);
};
