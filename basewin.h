#ifndef _BASEWIN_H
#define _BASEWIN_H
#include <Windows.h>
// (Ha még nincs máshol, érdemes biztosítani, hogy a Windows definíciók elérhetők legyenek)
// #include <Windows.h>

template <class DERIVED_TYPE> 
class BaseWindow
{
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_TYPE *pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        if (pThis)
            return pThis->HandleMessage(uMsg, wParam, lParam);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    BaseWindow() : m_hwnd(NULL) { }

    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
        )
    {
        // Ellenőrizzük, hogy már regisztrálták-e a class-t (hogy elkerüljük az ütközést).
        WNDCLASS existing = {};
        HINSTANCE hInst = GetModuleHandle(NULL);
        if (!GetClassInfo(hInst, ClassName(), &existing))
        {
            WNDCLASS wc = {};
            wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;   // <- dupla kattintás engedélyezése
            wc.lpfnWndProc   = DERIVED_TYPE::WindowProc;
            wc.hInstance     = hInst;
            wc.lpszClassName = ClassName();
            // (Igény szerint lehet: wc.hCursor = LoadCursor(NULL, IDC_ARROW); wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);)

            if (!RegisterClass(&wc))
                return FALSE;
        }

        m_hwnd = CreateWindowEx(
            dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, hInst, this
        );

        return m_hwnd != NULL;
    }

    HWND Window() const { return m_hwnd; }

protected:
    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};

#endif