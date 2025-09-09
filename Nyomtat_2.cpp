
#include "TWIST_Cpp.h"
#include <wingdi.h>

static bool GetPrinterCapsByName(const std::wstring& name, PrinterCaps& out)
{
    HDC hdc = CreateDCW(nullptr, name.c_str(), nullptr, nullptr);
    if (!hdc) return false;

    out.dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
    out.dpiY = GetDeviceCaps(hdc, LOGPIXELSY);
    out.horz = GetDeviceCaps(hdc, HORZRES);
    out.vert = GetDeviceCaps(hdc, VERTRES);

    const int pw = GetDeviceCaps(hdc, PHYSICALWIDTH);
    const int ph = GetDeviceCaps(hdc, PHYSICALHEIGHT);
    const int ox = GetDeviceCaps(hdc, PHYSICALOFFSETX);
    const int oy = GetDeviceCaps(hdc, PHYSICALOFFSETY);

    // 1/1000 inch (mil) – ez kell a meglévõ szerkezetedhez:
    // printable terület mil-ben: (pix / dpi) * 1000
    const float wPrintablePx = (float)(pw - 2 * ox);
    const float hPrintablePx = (float)(ph - 2 * oy);
    out.wMil = (wPrintablePx / (float)out.dpiX) * 1000.0f;
    out.hMil = (hPrintablePx / (float)out.dpiY) * 1000.0f;

    DeleteDC(hdc);
    return true;
}

void MainWindow::OpenPrintUI()
{
    uiPrint.visible = true;
    uiPrint.orientation = Orientation::Portrait;

    uiPrint.printers = GetAllPrinters();
    uiPrint.selected = 0;
    for (int i = 0; i < (int)uiPrint.printers.size(); ++i)
        if (uiPrint.printers[i].isDefault) { uiPrint.selected = i; break; }

    UpdatePrintCaps();
    LayoutPrintUI();
    InvalidateRect(m_hwnd, nullptr, FALSE);
}

void MainWindow::UpdatePrintCaps()
{
    const auto& p = uiPrint.printers[uiPrint.selected];
    PrinterCaps pc{};
    if (GetPrinterCapsByName(p.name, pc)) {
        uiPrint.caps.dpiX = pc.dpiX; uiPrint.caps.dpiY = pc.dpiY;
        uiPrint.caps.horz = pc.horz; uiPrint.caps.vert = pc.vert;
        uiPrint.caps.wMil = pc.wMil; uiPrint.caps.hMil = pc.hMil;

        uiPrint.caps.paperPx = D2D1::SizeF((float)pc.horz, (float)pc.vert);

        // nyomtatható (px)
        const float wPx = pc.wMil * (pc.dpiX / 1000.0f);
        const float hPx = pc.hMil * (pc.dpiY / 1000.0f);
        const float mx = (pc.horz - wPx) * 0.5f;
        const float my = (pc.vert - hPx) * 0.5f;
        uiPrint.caps.printablePx = D2D1::RectF(mx, my, mx + wPx, my + hPx);
    }
}

void MainWindow::LayoutPrintUI()
{
    // Panel a kliens terület közepén:
    RECT rc; GetClientRect(m_hwnd, &rc);
    float W = (float)(rc.right - rc.left);
    float H = (float)(rc.bottom - rc.top);

    uiPrint.panel = D2D1::RectF(W * 0.5f - 450, H * 0.5f - 300, W * 0.5f + 450, H * 0.5f + 300);

    float pad = 16.0f;
    float y = uiPrint.panel.top + pad;
    uiPrint.listArea = D2D1::RectF(uiPrint.panel.left + pad, y,
        uiPrint.panel.right - pad, y + uiPrint.rows * 28.0f);
    y = uiPrint.listArea.bottom + pad;

    uiPrint.detailsArea = D2D1::RectF(uiPrint.panel.left + pad, y,
        uiPrint.panel.right - pad, uiPrint.panel.bottom - 60.0f);

    // Orientáció gombok a details bal felsõ részén
    float bx = uiPrint.detailsArea.left;
    float by = uiPrint.detailsArea.top;
    uiPrint.btnPortrait = D2D1::RectF(bx, by, bx + 110, by + 28);
    uiPrint.btnLandscape = D2D1::RectF(bx + 120, by, bx + 230, by + 28);

    // Elõnézeti terület jobbra
    uiPrint.previewArea = D2D1::RectF(uiPrint.detailsArea.right - 360,
        uiPrint.detailsArea.top + 8,
        uiPrint.detailsArea.right - 10,
        uiPrint.detailsArea.bottom - 10);

    // OK/Mégse
    uiPrint.btnOk = D2D1::RectF(uiPrint.panel.right - 200, uiPrint.panel.bottom - 48,
        uiPrint.panel.right - 110, uiPrint.panel.bottom - 16);
    uiPrint.btnCancel = D2D1::RectF(uiPrint.panel.right - 100, uiPrint.panel.bottom - 48,
        uiPrint.panel.right - 16, uiPrint.panel.bottom - 16);
}

void MainWindow::RenderPrintUI()
{
    if (!uiPrint.visible) return;
    RECT rcCli; GetClientRect(m_hwnd, &rcCli);
    const float winW = (float)(rcCli.right - rcCli.left);
    const float winH = (float)(rcCli.bottom - rcCli.top);

	ID2D1SolidColorBrush* BrushDim = nullptr, * BrushPanelBg = nullptr, * BrushFrame = nullptr, * BrushPaperBg = nullptr, * BrushWhite = nullptr,
        * BrushSelBg = nullptr, * BrushText = nullptr, * BrushBtnOn = nullptr, * BrushBtnOff = nullptr, * BrushPrintable = nullptr;

    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0.5f), &BrushDim);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.12f, 0.12f, 0.12f, 1), &BrushPanelBg);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.7f, 0.7f, 0.7f, 1), &BrushFrame);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.25f, 0.35f, 0.55f, 1), &BrushSelBg);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.9f, 0.9f, 0.9f, 1), &BrushText);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.25f, 0.5f, 0.25f, 1), &BrushBtnOn);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.15f, 0.15f, 0.15f, 1), &BrushBtnOff);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.9f, 0.3f, 0.3f, 1), &BrushPrintable);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.95f, 0.95f, 0.95f, 1), &BrushWhite);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.8f, 0.8f, 0.8f, 1), &BrushPaperBg);

    // 1) sötétítés
    pRenderTarget->FillRectangle(D2D1::RectF(0, 0, winW, winH), BrushDim); // félátlátszó fekete

    // 2) panel
    pRenderTarget->FillRectangle(uiPrint.panel, BrushPanelBg);
    pRenderTarget->DrawRectangle(uiPrint.panel, BrushFrame, 1.0f);

    // 3) lista
    pRenderTarget->DrawTextW(L"Nyomtatók", 9, TF2_dir,
        D2D1::RectF(uiPrint.listArea.left, uiPrint.listArea.top - 22, uiPrint.listArea.right, uiPrint.listArea.top - 2),
        BrushText);
    pRenderTarget->DrawRectangle(uiPrint.listArea, BrushFrame);
    int first = uiPrint.scroll;
    int last = min((int)uiPrint.printers.size(), first + uiPrint.rows);
    float rowH = 28.0f;
    for (int i = first, r = 0; i < last; ++i, ++r) {
        D2D1_RECT_F rowRc = D2D1::RectF(uiPrint.listArea.left + 6, uiPrint.listArea.top + r * rowH,
            uiPrint.listArea.right - 6, uiPrint.listArea.top + (r + 1) * rowH);
        if (i == uiPrint.selected) pRenderTarget->FillRectangle(rowRc, BrushSelBg);
        IDWriteTextFormat* tf = (i == uiPrint.selected) ? TF2_dir : TF2;
        pRenderTarget->DrawTextW(uiPrint.printers[i].name.c_str(),
            (UINT32)uiPrint.printers[i].name.size(), tf, rowRc, BrushText);
    }

    // 4) részletek
    pRenderTarget->DrawRectangle(uiPrint.detailsArea, BrushFrame);

    // Orientáció gombok
    auto drawBtn = [&](D2D1_RECT_F rc, bool on, const wchar_t* txt) {
        pRenderTarget->FillRectangle(rc, on ? BrushBtnOn : BrushBtnOff);
        pRenderTarget->DrawRectangle(rc, BrushFrame);
        pRenderTarget->DrawTextW(txt, (UINT32)wcslen(txt), TF2,
            D2D1::RectF(rc.left + 8, rc.top + 5, rc.right - 8, rc.bottom - 5), BrushText);
        };
    drawBtn(uiPrint.btnPortrait, uiPrint.orientation == 0, L"Álló (Portrait)");
    drawBtn(uiPrint.btnLandscape, uiPrint.orientation == 1, L"Fekvõ (Landscape)");

    // Szövegek
    std::wstring info =
        L"Név: " + uiPrint.printers[uiPrint.selected].name + L"\n" +
        L"DPI: " + std::to_wstring(uiPrint.caps.dpiX) + L"x" + std::to_wstring(uiPrint.caps.dpiY);
    pRenderTarget->DrawTextW(info.c_str(), (UINT32)info.size(), TF2,
        D2D1::RectF(uiPrint.detailsArea.left, uiPrint.btnPortrait.bottom + 8,
            uiPrint.previewArea.left - 10, uiPrint.detailsArea.bottom - 10),
        BrushText);

    // 5) elõnézet (1 téglalap)
    // keret
    pRenderTarget->FillRectangle(uiPrint.previewArea, BrushPaperBg);
    pRenderTarget->DrawRectangle(uiPrint.previewArea, BrushFrame);

    // lap arányok
    D2D1_SIZE_F paper = uiPrint.caps.paperPx;
    if (uiPrint.orientation == 1) std::swap(paper.width, paper.height);

    // skála a previewArea-ba
    float pw = uiPrint.previewArea.right - uiPrint.previewArea.left - 20.0f;
    float ph = uiPrint.previewArea.bottom - uiPrint.previewArea.top - 20.0f;
    float sx = pw / paper.width;
    float sy = ph / paper.height;
    float s = std::min(sx, sy);

    float cx = (uiPrint.previewArea.left + uiPrint.previewArea.right) * 0.5f;
    float cy = (uiPrint.previewArea.top + uiPrint.previewArea.bottom) * 0.5f;

    float w = paper.width * s;
    float h = paper.height * s;
    D2D1_RECT_F page = D2D1::RectF(cx - w / 2, cy - h / 2, cx + w / 2, cy + h / 2);
    pRenderTarget->FillRectangle(page, BrushWhite);
    pRenderTarget->DrawRectangle(page, BrushFrame);

    // nyomtatható terület
    D2D1_RECT_F pr = uiPrint.caps.printablePx;
    if (uiPrint.orientation == 1) {
        // Landscape: forgatott koordináta – egyszerû: csak cseréld az arányokat
        std::swap(pr.left, pr.top); std::swap(pr.right, pr.bottom);
        // (ha pontos forgatás kell, számolj új pr-t a PHYSICALOFFSET* alapján)
    }
    // skálázd a page-re:
    auto scaleRect = [&](D2D1_RECT_F r)->D2D1_RECT_F {
        float k = s;
        return D2D1::RectF(page.left + r.left * k,
            page.top + r.top * k,
            page.left + r.right * k,
            page.top + r.bottom * k);
        };
    D2D1_RECT_F printBox = scaleRect(pr);
    pRenderTarget->DrawRectangle(printBox, BrushPrintable, 1.5f);

    // 6) OK/Mégse
    drawBtn(uiPrint.btnOk, false, L"OK");
    drawBtn(uiPrint.btnCancel, false, L"Mégse");

    SafeRelease(&BrushDim);
    SafeRelease(&BrushPanelBg);
    SafeRelease(&BrushFrame);
    SafeRelease(&BrushSelBg);
    SafeRelease(&BrushText);
    SafeRelease(&BrushBtnOn);
    SafeRelease(&BrushBtnOff);
    SafeRelease(&BrushPrintable);
	SafeRelease(&BrushWhite);
	SafeRelease(&BrushPaperBg);
}
