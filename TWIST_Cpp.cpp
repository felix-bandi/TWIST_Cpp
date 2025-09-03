#include <windowsx.h>
#include <Windows.h>
#include <d2d1.h>
#include <winuser.h>
#pragma comment(lib, "d2d1")
#include <dwrite.h>
#pragma comment(lib, "dwrite")
#include <windows.graphics.h>
#include <string>
#include <memory>
#include <locale>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
//#include <time.h>
using namespace std;
#include "TWIST_Cpp.h"
#include "DPIScale.h"
#include <crtdbg.h>
#include "StringConv.h"
#include <algorithm>


void MainWindow::OnPaint()
{
	if (betoltes)
	{
		if (VONAL_betolt.size() > 0) for (size_t i = 0; i < VONAL_betolt.size(); i++)     VONAL_vector.push_back(VONAL_betolt[i]);
		if (ARC_betolt.size() > 0)   for (size_t i = 0; i < ARC_betolt.size(); i++)       ARC_vector.push_back(ARC_betolt[i]);
		if (POLIGON_betolt.size() > 0)
		{
			for (size_t i = 0; i < POLIGON_betolt.size(); i++)
			{
				poli.pont.clear();
				for (size_t p = 0; p < POLIGON_betolt[i].pont.size(); p++) poli.pont.push_back(POLIGON_betolt[i].pont[p]);
				poli.pg = POLIGON_betolt[i].pg;
				poli.szint = POLIGON_betolt[i].szint;
				POLIGON_vector.push_back(poli);
			}
		}
		if (EL_betolt.size() > 0)    for (size_t i = 0; i < EL_betolt.size(); i++)    EL_vector.push_back(EL_betolt[i]);
		if (SQ_betolt.size() > 0)    for (size_t i = 0; i < SQ_betolt.size(); i++)    SQ_vector.push_back(SQ_betolt[i]);
		if (RR_betolt.size() > 0)    for (size_t i = 0; i < RR_betolt.size(); i++)    RR_vector.push_back(RR_betolt[i]);
		if (ELVIA_betolt.size() > 0) for (size_t i = 0; i < ELVIA_betolt.size(); i++) ELVIA_vector.push_back(ELVIA_betolt[i]);
		if (SQVIA_betolt.size() > 0) for (size_t i = 0; i < SQVIA_betolt.size(); i++) SQVIA_vector.push_back(SQVIA_betolt[i]);
		if (RRVIA_betolt.size() > 0) for (size_t i = 0; i < RRVIA_betolt.size(); i++) RRVIA_vector.push_back(RRVIA_betolt[i]);
		betoltes = false;
	}

	HRESULT hr = CreateGraphicsResources();

	if (SUCCEEDED(hr))
	{
		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		sz[1] = SZINT_kk;
		if (SZINT_kk == 0) sz[0] = 1; else sz[0] = 0;


		for (int k = 0; k <= 1; k++)
		{
			kk = k;
			//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
			//if (sz[kk] == 1) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
			VONAL_rajzol();

			sc = D2D1::Matrix3x2F::Scale(nagyitas, nagyitas, D2D1::Point2F(0, 0));
			tr = D2D1::Matrix3x2F::Translation(nagyitas * eltolas.x, nagyitas * eltolas.y);
			pRenderTarget->SetTransform(sc * tr);

			for (size_t i = 0; i < ARC_vector.size(); i++)
			{
				if (ARC_vector[i].szint == sz[kk])
					pRenderTarget->DrawGeometry(ARC_vector[i].pg, bv[sz[kk]][kk], ARC_vector[i].v, pStrokeStyle);
			}

			for (size_t i = 0; i < POLIGON_vector.size(); i++)
			{
				if (POLIGON_vector[i].szint == sz[kk])
					pRenderTarget->FillGeometry(POLIGON_vector[i].pg, bv[sz[kk]][kk]);
			}

			pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
			EL_rajzol();
			SQ_rajzol();
			RR_rajzol();
		}
		EV_rajzol();
		SV_rajzol();
		RV_rajzol();
		if (list.kk >= 0 && krv) alk_krv_rajzol(list.kk);
		if (krv)
		{
			hely.x = (pont.x + eltolas.x) * nagyitas;
			hely.y = (pont.y + eltolas.y) * nagyitas;
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
			if (vonalfolyamatban)
			{
				rx = vonal_t[0] / 2 * nagyitas;
				ry = vonal_t[0] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(hely, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
				float a = mouse_grid.y - hely.y;
				float b = mouse_grid.x - hely.x;
				float c = sqrt(a * a + b * b);
				p1.x = hely.x - a * rx / c;
				p1.y = hely.y + b * ry / c;
				p2.x = mouse_grid.x - a * rx / c;
				p2.y = mouse_grid.y + b * ry / c;
				pRenderTarget->DrawLine(p1, p2, Brush, 1.0, pStrokeStyle);
				p1.x = hely.x + a * rx / c;
				p1.y = hely.y - b * ry / c;
				p2.x = mouse_grid.x + a * rx / c;
				p2.y = mouse_grid.y - b * ry / c;
				pRenderTarget->DrawLine(p1, p2, Brush, 1.0, pStrokeStyle);
			}
			else if (arcfolyamatban && korfazis == ketto)
			{
				hely.x = (arc.kpx + eltolas.x) * nagyitas;
				hely.y = (arc.kpy + eltolas.y) * nagyitas;
				rx = sqrt((arc.kpx - xx) * (arc.kpx - xx) + (arc.kpy - yy) * (arc.kpy - yy)) * nagyitas;
				ry = sqrt((arc.kpx - xx) * (arc.kpx - xx) + (arc.kpy - yy) * (arc.kpy - yy)) * nagyitas;
				//szog = atan2(arc.kpx - xx, arc.kpy - yy);
				ellipse = D2D1::Ellipse(hely, rx, ry);
				Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
				pRenderTarget->DrawEllipse(ellipse, Brush, kor_t[0] * nagyitas);
			}
			else if (arcfolyamatban && korfazis == harom)
			{
				ARC_rajzol_2();
				pRenderTarget->SetTransform(sc * tr);
				pRenderTarget->DrawGeometry(pPathGeometry_2, Brush, static_cast<float>(kor_t[0]), pStrokeStyle);
				pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
			}
			else if (polifolyamatban)
			{
				count = poligon.size();
				if (count > 0)
				{
					POLIGON_rajzol_2();
					pRenderTarget->SetTransform(sc * tr);
					pRenderTarget->DrawGeometry(pPathGeometry_4, Brush);
					pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
				}
			}
			else if (EL_folyamatban)
			{
				rx = EL_t[0] / 2 * nagyitas;  ry = EL_t[1] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
				rx = ry = EL_t[2] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
			}
			else if (SQ_folyamatban)
			{
				rx = SQ_t[0] / 2 * nagyitas;   ry = SQ_t[1] / 2 * nagyitas;
				rect.left = mouse_grid.x - rx;
				rect.top = mouse_grid.y - ry;
				rect.right = mouse_grid.x + rx;
				rect.bottom = mouse_grid.y + ry;
				pRenderTarget->DrawRectangle(rect, Brush);
				rx = ry = SQ_t[2] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
			}
			else if (RR_folyamatban)
			{
				rx = RR_t[0] / 2 * nagyitas;   ry = RR_t[1] / 2 * nagyitas;
				//rrx = RR[2] * nagyitas;   rry = RR[3] * nagyitas;
				rect.left = mouse_grid.x - rx;
				rect.top = mouse_grid.y - ry;
				rect.right = mouse_grid.x + rx;
				rect.bottom = mouse_grid.y + ry;
				rrect.rect = rect;
				rrect.radiusX = RR_t[2] * nagyitas;  rrect.radiusY = RR_t[3] * nagyitas;
				pRenderTarget->DrawRoundedRectangle(rrect, Brush);
				rx = ry = RR_t[4] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
			}
			else if (EV_folyamatban)
			{
				rx = EV_t[0] / 2 * nagyitas;  ry = EV_t[1] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
				rx = ry = EV_t[2] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
			}
			else if (SV_folyamatban)
			{
				rx = SV_t[0] / 2 * nagyitas;   ry = SV_t[1] / 2 * nagyitas;
				rect.left = mouse_grid.x - rx;
				rect.top = mouse_grid.y - ry;
				rect.right = mouse_grid.x + rx;
				rect.bottom = mouse_grid.y + ry;
				pRenderTarget->DrawRectangle(rect, Brush);
				rx = ry = SV_t[2] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
			}
			else if (RV_folyamatban)
			{
				rx = RV_t[0] / 2 * nagyitas;   ry = RV_t[1] / 2 * nagyitas;
				//rrx = RR[2] * nagyitas;   rry = RR[3] * nagyitas;
				rect.left = mouse_grid.x - rx;
				rect.top = mouse_grid.y - ry;
				rect.right = mouse_grid.x + rx;
				rect.bottom = mouse_grid.y + ry;
				rrect.rect = rect;
				rrect.radiusX = RV_t[2] * nagyitas;  rrect.radiusY = RV_t[3] * nagyitas;
				pRenderTarget->DrawRoundedRectangle(rrect, Brush);
				rx = ry = RR_t[4] / 2 * nagyitas;
				ellipse = D2D1::Ellipse(mouse_grid, rx, ry);
				pRenderTarget->DrawEllipse(ellipse, Brush, 1);
			}
		}
		//Találat.clear();
		if (mode == _torol)
		{
			Talalat.clear();
			VONAL_keres();
			EL_keres();
			SQ_keres();
			RR_keres();
			ARC_keres();
			POLIGON_keres();
			EV_keres();
			SV_keres();
			RV_keres();
			Talalat_rajzol();
		}

		for (int i = 0; i < static_cast<int>(szogek.size()); i++)
		{
			p1.x = -sin(szogek[i]) * 400 + mouse.x; p1.y = -cos(szogek[i]) * 400 + mouse.y;
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			pRenderTarget->DrawLine(mouse, p1, Brush, 1.0, pStrokeStyle);
			if (i == sz_sz || i == (sz_sz+1)% static_cast<int>(szogek.size())) {
				Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
				pRenderTarget->DrawLine(mouse, p1, Brush, 5.0, pStrokeStyle);
				
			}
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
			Kiir(i, p1.x - 150, p1.y);
			if (i < static_cast<int>(szogek.size()) - 1)
			{
				p1.x = static_cast<FLOAT>(-sin(szogek[i] - (szogek[i] - szogek[i + 1]) / 2.0) * 300 + mouse.x);
				p1.y = static_cast<FLOAT>(-cos(szogek[i] - (szogek[i] - szogek[i + 1]) / 2.0) * 300 + mouse.y);
				Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
				pRenderTarget->DrawLine(mouse, p1, Brush, 1.0, pStrokeStyle);
			}
		}
		/*p1.x = -sin(delta_) * 500 + mouse.x; p1.y = -cos(delta_) * 500 + mouse.y;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
		pRenderTarget->DrawLine(mouse, p1, Brush, 5.0, pStrokeStyle);*/

		EL_lyuk_rajzol();
		SQ_lyuk_rajzol();
		RR_lyuk_rajzol();
		EV_lyuk_rajzol();
		SV_lyuk_rajzol();
		RV_lyuk_rajzol();
		if (ny_kep)
		{
			rect.top = eltolas.y * nagyitas;
			rect.left = eltolas.x * nagyitas;
			rect.bottom = (flo6 - 1 + eltolas.y) * nagyitas;
			rect.right = (flo5 - 1 + eltolas.x) * nagyitas;
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
			pRenderTarget->DrawRectangle(rect, Brush, 1);
		}
		if (vanrajz)
			for (size_t i = 0; i < Blokk.size(); i++)
			{
				rect.bottom = (Blokk[i].bottom + eltolas.y) * nagyitas;
				rect.top = (Blokk[i].top + eltolas.y) * nagyitas;
				rect.left = (Blokk[i].left + eltolas.x) * nagyitas;
				rect.right = (Blokk[i].right + eltolas.x) * nagyitas;
				Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
				pRenderTarget->DrawRectangle(rect, Brush, 1);
			}
		if (mode == _file) 
		{
			Filedialog_rajzol();
			//FILE_rajzol(); 
			//List2_rajzol();
		}
		ALAK_rajzol();
		CUSTOM_rajzol();
		GC_rajzol();
		GRID_rajzol();
		MODE_rajzol();
		List_rajzol();
		SZINT_rajzol();
		ORIGO_rajzol();
		XY_rajzol();

		/*Kiir("Mentees", save, 100, 100);
		Kiir("arc.ksz", arc.ksz, 100, 150);
		Kiir("arc.vsz", arc.vsz, 100, 200);
		Kiir("save", save, 100, 250);
		Kiir("int1", int1, 100, 300);
		Kiir("int2", int2, 100, 350);
		Kiir("int3", int3, 100, 400);
		Kiir("int4", int4, 100, 450);
		Kiir("flo5", flo5, 100, 500);
		Kiir("flo6", flo6, 100, 550);
		Kiir("int5", int5, 100, 600);
		Kiir("int6", int6, 100, 650);*/

		//Kiir("metsz", metsz, 100, 450);
		//Kiir("alfa_-gamma", alfa_-gamma, 100, 300);

		//if (ALAK_k < 0 && GetCursor() == hCursor && BOX_GC_k == false) Cursor_rajzol();
		if (GetCursor() == Cursor_system) Cursor_rajzol();
		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
	}
}

void MainWindow::Resize()
{
	if (pRenderTarget != NULL)
	{
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		pRenderTarget->Resize(size);
		if (GetCursorPos(eger))
		{
			ScreenToClient(m_hwnd, eger);
			mouse.x = static_cast<FLOAT>(eger->x);
			mouse.y = static_cast<FLOAT>(eger->y);
		}
		ablak.x = static_cast<float>(rc.right - rc.left); ablak.y = static_cast<float>(rc.bottom - rc.top);
		BOX_GC.bottom = ablak.y;
		BOX_GC.top = ablak.y - 40;
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
{
	DPIScale::EnsureProcessDpiAwareness();
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    MainWindow* win = new MainWindow();

    if (!win->Create(L"TWIST", WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_EX_TOPMOST | WS_POPUP))
    {
        delete win;
        return 0;
    }

    HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(HOTKEYS));

    ShowWindow(win->Window(), nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(win->Window(), hAccel, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete win;
    _CrtDumpMemoryLeaks();
    return 0;
}

void MainWindow::Kiir(bool v, float x, float y)
{
	std::string st = std::to_string(v);
	std::wstring wst = Utf8ToW(st);
	const size_t cap = std::size(text);                 // ha C++17: works
	const size_t len = std::min(wst.size(), cap);
	std::copy_n(wst.data(), len, text);
	D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 300, y);
	pRenderTarget->DrawText(text, static_cast<UINT32>(len), TF1, layoutRect, Brush);
}

void MainWindow::Kiir(int v, float x, float y)
{
	std::string st = std::to_string(v);
	std::wstring wst = Utf8ToW(st);
	const size_t cap = std::size(text);                 // ha C++17: works
	const size_t len = std::min(wst.size(), cap);
	std::copy_n(wst.data(), len, text);
	D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 300, y);
	pRenderTarget->DrawText(text, static_cast<UINT32>(len), TF1, layoutRect, Brush);
}

void MainWindow::Kiir(int v, D2D1_RECT_F t)
{
	std::string st = std::to_string(v);
	std::wstring wst = Utf8ToW(st);
	const size_t cap = std::size(text);                 // ha C++17: works
	const size_t len = std::min(wst.size(), cap);
	std::copy_n(wst.data(), len, text);
	pRenderTarget->DrawText(text, static_cast<UINT32>(len), TF1, t, Brush);
}

void MainWindow::Kiir(const char* s, int v, D2D1_RECT_F t)
{
	//string s1(s);
	//string st = to_string(v);
	const std::wstring ws1 = Utf8ToW(s ? std::string(s) : std::string{});//wstring ws1 = convert.from_bytes(s1);
	std::wstring wst = std::to_wstring(v);//wstring wst = convert.from_bytes(st);
	wst = ws1 + wst;
	const size_t cap = std::size(text);                 // ha C++17: works
	const size_t len = std::min(wst.size(), cap);
	std::copy_n(wst.data(), len, text);
	pRenderTarget->DrawText(text, static_cast<UINT32>(len), TF1, t, Brush);
}

void MainWindow::Kiir(const char* s, D2D1_RECT_F t)
{
	string s1(s);
	const std::wstring wst = Utf8ToW(s ? std::string(s) : std::string{});//wstring ww = convert.from_bytes(s1);
	const size_t cap = std::size(text);                 // ha C++17: works
	const size_t len = std::min(wst.size(), cap);
	std::copy_n(wst.data(), len, text);
	pRenderTarget->DrawText(text, static_cast<UINT32>(len), TF1, t, Brush);
}

void MainWindow::Kiir(const char* s, float v, float x, float y)
{
	const char* c_s = " = ";
	//string s1(s);
	//string s2(c_s);
	string st = to_string(v);
	const std::wstring ws1 = Utf8ToW(s ? std::string(s) : std::string{});//wstring ws1 = convert.from_bytes(s1);
	const std::wstring ws2 = Utf8ToW(s ? std::string(c_s) : std::string{});//wstring ws2 = convert.from_bytes(s2);
	std::wstring wst = Utf8ToW(s ? std::string(st) : std::string{});//wstring wst = convert.from_bytes(st);
	wst = ws1 + ws2 + wst;
	const size_t cap = std::size(text);                 // ha C++17: works
	const size_t len = std::min(wst.size(), cap);
	std::copy_n(wst.data(), len, text);
	D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 300, y);
	pRenderTarget->DrawText(text, static_cast<UINT32>(len), TF1, layoutRect, Brush);
}
