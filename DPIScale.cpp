#include "DPIScale.h"
#include <shellscalingapi.h>   // MONITOR_DPI_TYPE
#pragma comment(lib, "Shcore.lib") // ha statikusan linkelnéd; dinamikus betöltésnél nem muszáj

// Statikus tagok
UINT DPIScale::s_dpiX = 96;
UINT DPIScale::s_dpiY = 96;

// --- Lokális helper-ek dinamikus betöltéshez ---
static HMODULE GetUser32()
{
    static HMODULE h = LoadLibraryW(L"user32.dll");
    return h;
}

static HMODULE GetShcore()
{
    static HMODULE h = LoadLibraryW(L"shcore.dll");
    return h;
}

static DPI_AWARENESS_CONTEXT GetPerMonV2Context()
{
    // Lehet, hogy régi Windows-on nincs – ezért dinamikusan kérjük le
    static DPI_AWARENESS_CONTEXT ctx =
        reinterpret_cast<DPI_AWARENESS_CONTEXT>(-4); // DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
    return ctx;
}

void DPIScale::EnsureProcessDpiAwareness()
{
    // 1) Win10+: SetProcessDpiAwarenessContext(PER_MONITOR_AWARE_V2)
    if (auto user32 = GetUser32())
    {
        using FnSetProcessDpiAwarenessContext = BOOL(WINAPI*)(DPI_AWARENESS_CONTEXT);
        auto p = reinterpret_cast<FnSetProcessDpiAwarenessContext>(
            GetProcAddress(user32, "SetProcessDpiAwarenessContext"));
        if (p)
        {
            if (p(GetPerMonV2Context()))
                return; // siker
        }
    }

    // 2) Win8.1: SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE)
    if (auto shcore = GetShcore())
    {
        using FnSetProcessDpiAwareness = HRESULT(WINAPI*)(PROCESS_DPI_AWARENESS);
        auto p = reinterpret_cast<FnSetProcessDpiAwareness>(
            GetProcAddress(shcore, "SetProcessDpiAwareness"));
        if (p)
        {
            if (p(PROCESS_PER_MONITOR_DPI_AWARE) == S_OK)
                return;
        }
    }

    // 3) Vista/7: SetProcessDPIAware()
    if (auto user32 = GetUser32())
    {
        using FnSetProcessDPIAware = BOOL(WINAPI*)();
        auto p = reinterpret_cast<FnSetProcessDPIAware>(
            GetProcAddress(user32, "SetProcessDPIAware"));
        if (p) p();
    }
}

void DPIScale::Init(HWND hwnd)
{
    Refresh(hwnd);
}

std::optional<RECT> DPIScale::HandleDpiChanged(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    // wParam: HIWORD = új Y DPI, LOWORD = új X DPI (Win8.1+)
    UINT newDpiX = LOWORD(wParam);
    UINT newDpiY = HIWORD(wParam);

    if (newDpiX >= 48 && newDpiY >= 48) // némi sanity check
    {
        s_dpiX = newDpiX;
        s_dpiY = newDpiY;
    }
    else
    {
        // ha valamiért hibás lenne, frissítünk az ablakból
        Refresh(hwnd);
    }

    // lParam: ajánlott új ablak-geometria (RECT*)
    if (lParam)
    {
        const RECT* rc = reinterpret_cast<const RECT*>(lParam);
        return *rc;
    }
    return std::nullopt;
}

UINT DPIScale::TryGetDpiForWindow(HWND hwnd)
{
    if (auto user32 = GetUser32())
    {
        using FnGetDpiForWindow = UINT(WINAPI*)(HWND);
        auto p = reinterpret_cast<FnGetDpiForWindow>(
            GetProcAddress(user32, "GetDpiForWindow"));
        if (p)
            return p(hwnd);
    }
    return 0;
}

bool DPIScale::TryGetDpiForMonitor(HMONITOR hmon, UINT* dpiX, UINT* dpiY)
{
    if (!hmon) return false;
    if (auto shcore = GetShcore())
    {
        using FnGetDpiForMonitor = HRESULT(WINAPI*)(HMONITOR, MONITOR_DPI_TYPE, UINT*, UINT*);
        auto p = reinterpret_cast<FnGetDpiForMonitor>(
            GetProcAddress(shcore, "GetDpiForMonitor"));
        if (p)
        {
            UINT x = 0, y = 0;
            if (SUCCEEDED(p(hmon, MDT_EFFECTIVE_DPI, &x, &y)))
            {
                if (dpiX) *dpiX = x;
                if (dpiY) *dpiY = y;
                return true;
            }
        }
    }
    return false;
}

void DPIScale::GetDeviceCapsDpi(HDC hdc, UINT* dpiX, UINT* dpiY)
{
    int x = 96, y = 96;
    if (hdc)
    {
        x = GetDeviceCaps(hdc, LOGPIXELSX);
        y = GetDeviceCaps(hdc, LOGPIXELSY);
        if (x <= 0) x = 96;
        if (y <= 0) y = 96;
    }
    if (dpiX) *dpiX = static_cast<UINT>(x);
    if (dpiY) *dpiY = static_cast<UINT>(y);
}

void DPIScale::Refresh(HWND hwnd)
{
    // 1) Win10: GetDpiForWindow
    if (UINT w = TryGetDpiForWindow(hwnd))
    {
        s_dpiX = s_dpiY = w;
        return;
    }

    // 2) Win8.1: GetDpiForMonitor
    HMONITOR hmon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    UINT mx = 0, my = 0;
    if (TryGetDpiForMonitor(hmon, &mx, &my))
    {
        s_dpiX = mx;
        s_dpiY = my;
        return;
    }

    // 3) Fallback: GetDeviceCaps a képernyő DC-ből
    HDC hdc = GetDC(hwnd);
    GetDeviceCapsDpi(hdc, &s_dpiX, &s_dpiY);
    ReleaseDC(hwnd, hdc);
}

UINT DPIScale::GetDpiX() { return s_dpiX; }
UINT DPIScale::GetDpiY() { return s_dpiY; }

UINT DPIScale::GetWndDpiX(HWND hwnd)
{
    if (UINT w = TryGetDpiForWindow(hwnd)) return w;
    HMONITOR hmon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    UINT x = 0, y = 0;
    if (TryGetDpiForMonitor(hmon, &x, &y)) return x;
    HDC hdc = GetDC(hwnd); GetDeviceCapsDpi(hdc, &x, &y); ReleaseDC(hwnd, hdc);
    return x;
}

UINT DPIScale::GetWndDpiY(HWND hwnd)
{
    if (UINT w = TryGetDpiForWindow(hwnd)) return w;
    HMONITOR hmon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    UINT x = 0, y = 0;
    if (TryGetDpiForMonitor(hmon, &x, &y)) return y;
    HDC hdc = GetDC(hwnd); GetDeviceCapsDpi(hdc, &x, &y); ReleaseDC(hwnd, hdc);
    return y;
}

UINT DPIScale::GetMonDpiX(HMONITOR hmon)
{
    UINT x = 0, y = 0;
    if (TryGetDpiForMonitor(hmon, &x, &y)) return x;
    // fallback: képernyő DC
    HDC hdc = GetDC(nullptr); GetDeviceCapsDpi(hdc, &x, &y); ReleaseDC(nullptr, hdc);
    return x;
}

UINT DPIScale::GetMonDpiY(HMONITOR hmon)
{
    UINT x = 0, y = 0;
    if (TryGetDpiForMonitor(hmon, &x, &y)) return y;
    HDC hdc = GetDC(nullptr); GetDeviceCapsDpi(hdc, &x, &y); ReleaseDC(nullptr, hdc);
    return y;
}

float DPIScale::ScaleFrom96_X() { return static_cast<float>(s_dpiX) / 96.0f; }
float DPIScale::ScaleFrom96_Y() { return static_cast<float>(s_dpiY) / 96.0f; }

float DPIScale::PxToDipX(float px) { return px * 96.0f / static_cast<float>(s_dpiX); }
float DPIScale::PxToDipY(float px) { return px * 96.0f / static_cast<float>(s_dpiY); }

float DPIScale::DipToPxX(float dip) { return dip * static_cast<float>(s_dpiX) / 96.0f; }
float DPIScale::DipToPxY(float dip) { return dip * static_cast<float>(s_dpiY) / 96.0f; }

// mm <-> px: 1 inch = 25.4 mm, dpi = pixel/inch
static constexpr float kMMPerInch = 25.4f;

float DPIScale::PxToMM_X(float px) { return px * kMMPerInch / static_cast<float>(s_dpiX); }
float DPIScale::PxToMM_Y(float px) { return px * kMMPerInch / static_cast<float>(s_dpiY); }

float DPIScale::MMToPx_X(float mm) { return mm * static_cast<float>(s_dpiX) / kMMPerInch; }
float DPIScale::MMToPx_Y(float mm) { return mm * static_cast<float>(s_dpiY) / kMMPerInch; }

float DPIScale::D2DUserToDipScale_X()
{
    // Ha a "user space" px-ben van, és D2D-ben DIP egységben szeretnél 1:1-et,
    // akkor DIP = px * (96 / dpiX).
    return 96.0f / static_cast<float>(s_dpiX);
}
float DPIScale::D2DUserToDipScale_Y()
{
    return 96.0f / static_cast<float>(s_dpiY);
}
