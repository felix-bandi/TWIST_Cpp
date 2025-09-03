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

// Helper function to convert string to wstring safely
std::wstring string_to_wstring(const std::string& str) {
    if (str.empty()) {
        return std::wstring();
    }
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);		
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

HRESULT MainWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK;

	if (pRenderTarget == NULL)
	{
		RECT rc1;
		GetClientRect(m_hwnd, &rc1);
		ablak.x = static_cast<float>(rc1.right - rc1.left); ablak.y = static_cast<float>(rc1.bottom - rc1.top);
		D2D1_SIZE_U size = D2D1::SizeU(rc1.right, rc1.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget);

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(
				DXGI_FORMAT_B8G8R8A8_UNORM,
				D2D1_ALPHA_MODE_IGNORE),
			0,
			0,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
		);

		hr = pFactory->CreateDCRenderTarget(&props, &m_pDCRT);

		if (SUCCEEDED(hr))
		{
			D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0);
			pRenderTarget->CreateSolidColorBrush(color, &fekete);
			color = D2D1::ColorF(1.0f, 1.0f, 1.0);
			pRenderTarget->CreateSolidColorBrush(color, &feher);
			pRenderTarget->CreateSolidColorBrush(color, &Brush);
			color = D2D1::ColorF(0, 1.0f, 1.0f);
			pRenderTarget->CreateSolidColorBrush(color, &cyan);
			//----------------------------------------------------
			color = D2D1::ColorF(1.0f, 0, 0);
			pRenderTarget->CreateSolidColorBrush(color, &bv[0][1]);
			color = D2D1::ColorF(0.5f, 0.0f, 0.0f);
			pRenderTarget->CreateSolidColorBrush(color, &bv[0][0]);
			color = D2D1::ColorF(0, 1.0f, 0);
			pRenderTarget->CreateSolidColorBrush(color, &bv[1][1]);
			color = D2D1::ColorF(0.0f, 0.5f, 0.0f);
			pRenderTarget->CreateSolidColorBrush(color, &bv[1][0]);
			//-----------------------------------------------------
			color = D2D1::ColorF(0.6f, 0.2f, 0.2f);
			pRenderTarget->CreateSolidColorBrush(color, &bp[0][1]);
			color = D2D1::ColorF(0.3f, 0.1f, 0.1f);
			pRenderTarget->CreateSolidColorBrush(color, &bp[0][0]);
			color = D2D1::ColorF(0.2f, 0.6f, 0.2f);
			pRenderTarget->CreateSolidColorBrush(color, &bp[1][1]);
			color = D2D1::ColorF(0.1f, 0.3f, 0.1f);
			pRenderTarget->CreateSolidColorBrush(color, &bp[1][0]);
			//-----------------------------------------------------
			pFactory->CreateStrokeStyle(D2D1::StrokeStyleProperties(
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_LINE_JOIN_ROUND,
				1.0f,
				D2D1_DASH_STYLE_SOLID,
				0.0f),
				NULL,
				0,
				&pStrokeStyle);

			DWriteCreateFactory(
				DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(IDWriteFactory),
				reinterpret_cast<IUnknown**>(&pDWriteFactory)
			);
			_wsetlocale(LC_ALL, L"");
			pDWriteFactory->CreateTextFormat(
				L"Georgia",                // Font family name.
				NULL,                       // Font collection (NULL sets it to use the system font collection).
				DWRITE_FONT_WEIGHT_REGULAR,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				17.0f,
				L"",
				&TF1
			);
			TF1->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			TF1->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			pDWriteFactory->CreateTextFormat(
				L"Ariel",                // Font family name.
				NULL,                       // Font collection (NULL sets it to use the system font collection).
				DWRITE_FONT_WEIGHT_REGULAR,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				17.0f,
				L"",
				&TF2
			);
			TF2->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			TF2->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			pDWriteFactory->CreateTextFormat(
				L"Georgia",                // Font family name.
				NULL,                       // Font collection (NULL sets it to use the system font collection).
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				17.0f,
				L"",
				&TF2_dir
			);
			TF2_dir->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			TF2_dir->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			pFactory->CreatePathGeometry(&pPathGeometry);
			pFactory->CreatePathGeometry(&pPathGeometry_2);
			pFactory->CreatePathGeometry(&pPathGeometry_3);
			pFactory->CreatePathGeometry(&pPathGeometry_4);
			pFactory->CreatePathGeometry(&pPathGeometry_5);
			ALAK_init();
			CUSTOM_init();
			Filedialog_init();
			GC_init();
			GRID_init();
			ORIGO_init();
			XY_init();
			MODE_init();
			FILE_init();
			SZINT_init();
			Load(alkatresz);
			List_init();
			List2_init();
		}
	}
	return hr;
}

void MainWindow::ALAK_init()
{
	BOX_ALAK.top = 0;
	BOX_ALAK.right = static_cast<float>(ScreenWidth);
	BOX_ALAK.bottom = BOX_ALAK.top + alak_nevek.size() * 25 - 1;
	BOX_ALAK.left = BOX_ALAK.right - 79;
	for (size_t i = 0; i < alak_nevek.size(); i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25);
		gomb.x2 = 79;
		gomb.y2 = static_cast<float>(i * 25 + 24);
		gomb.t = L"----";
		gomb.k = false;
		gomb.kk = false;
		ALAK_vector.push_back(gomb);
	}
	ALAK_vector[0].kk = true;
	for (size_t i = 0; i < alak_nevek.size(); i++) ALAK_vector[i].t = alak_nevek[i];
}


 void MainWindow::Filedialog_init()
 {
	 float w1 = static_cast<float>(ScreenWidth) / 6;
	 float h1 = static_cast<float>(ScreenHeight) / 8;
	 dialog.left = 2 * w1;
	 dialog.right = 4 * w1;
	 dialog.top = h1;
	 dialog.bottom = 7 * h1;
	 dialog.p1.x = dialog.left; dialog.p2.x = dialog.right;
	 dialog.p1.y = dialog.p2.y = dialog.top + 50;
	 dialog.cs.k = false;
	 dialog.cs.kk = false;
	 dialog.kk = -1;
	 dialog.kd = -1;
	 dialog.kkd = 0;
	 dialog.dirchange = true;
	 dialog.out_N = 0;
	 dialog.client.left = dialog.left + 10;
	 dialog.client.right = dialog.right - 10;
	 dialog.client.top = dialog.top + 60;
	 dialog.client.bottom = dialog.bottom - 90;
	 dialog.cs.top = dialog.client.top + 4;
	 dialog.cs.bottom = dialog.client.bottom - 4;
	 dialog.cs.right = dialog.right - 4;
	 dialog.cs.left = dialog.right - 22;
	 dialog.edit.bottom = dialog.bottom - 50;
	 dialog.edit.top = dialog.edit.bottom - 30;
	 dialog.edit.left = dialog.client.left;
	 dialog.edit.right = dialog.client.right;
 }

 
void MainWindow::CUSTOM_init()
{
	BOX_CUSTOM.top = BOX_ALAK.bottom;
	BOX_CUSTOM.right = static_cast<float>(ScreenWidth);
	BOX_CUSTOM.bottom = BOX_CUSTOM.top + 159;
	BOX_CUSTOM.left = BOX_CUSTOM.right - 139;
	for (int i = 1; i <= 5; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = L"----";
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		CUSTOM_vector.push_back(gomb);
	}
	//for (int i = 0; i <= 5; i++) CUSTOM.push_back(vector<GOMB>);
	for (int i = 1; i <= 1; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_vonal[i-1];
		gomb.i = vonal_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
		
	}
	CUSTOM.push_back(gt);
	gt.clear();
	for (int i = 1; i <= 1; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_kor[i-1];
		gomb.i = kor_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
	}
	CUSTOM.push_back(gt);
	gt.clear();
	CUSTOM.push_back(gt);
	for (int i = 1; i <= 3; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_EL[i-1];
		gomb.i = EL_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
	}
	CUSTOM.push_back(gt);
	gt.clear();
	for (int i = 1; i <= 3; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_SQ[i-1];
		gomb.i = SQ_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
	}
	CUSTOM.push_back(gt);
	gt.clear();
	for (int i = 1; i <= 5; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_RR[i-1];
		gomb.i = RR_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		wst = to_wstring(gomb.i);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
	}
	CUSTOM.push_back(gt);
	gt.clear();
	for (int i = 1; i <= 3; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_EV[i - 1];
		gomb.i = EV_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
	}
	CUSTOM.push_back(gt);
	gt.clear();
	for (int i = 1; i <= 3; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_SV[i - 1];
		gomb.i = SV_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
	}
	CUSTOM.push_back(gt);
	gt.clear();
	for (int i = 1; i <= 5; i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25 + 5);
		gomb.x2 = 120;
		gomb.y2 = static_cast<float>(i * 25 + 29);
		gomb.t = ws_RV[i - 1];
		gomb.i = RV_t[i - 1];
		gomb.k = false;
		gomb.kk = false;
		gomb.sz = false;
		std::string st = std::to_string(gomb.i);
		std::wstring wst = string_to_wstring(st);
		wst = to_wstring(gomb.i);
		hossz = wst.length();
		gomb.c.clear();
		for (size_t k = 0; k < hossz; k++) gomb.c.push_back(static_cast<char>(wst[k]));
		gt.push_back(gomb);
	}
	CUSTOM.push_back(gt);
	gt.clear();
}

void MainWindow::MODE_init()
{
	BOX_MODE.top = BOX_CUSTOM.bottom;
	BOX_MODE.right = static_cast<float>(ScreenWidth);
	BOX_MODE.bottom = BOX_MODE.top + mode_nevek.size() * 25;
	BOX_MODE.left = BOX_MODE.right - 79;
	for (size_t i = 0; i < mode_nevek.size(); i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25);
		gomb.x2 = 79;
		gomb.y2 = static_cast<float>(i * 25 + 24);
		gomb.t = L"----";
		gomb.k = false;
		gomb.kk = false;
		MODE_vector.push_back(gomb);
	}
	MODE_vector[0].kk = true;
	for (size_t i = 0; i < mode_nevek.size(); i++) MODE_vector[i].t = mode_nevek[i];
}

void MainWindow::FILE_init()
{
	BOX_FILE.top = BOX_MODE.top;
	BOX_FILE.bottom = BOX_MODE.bottom;
	BOX_FILE.right = BOX_MODE.left - 40;
	BOX_FILE.left = BOX_FILE.right - 150;
	for (size_t i = 0; i < file_nevek.size(); i++)
	{
		gomb.x1 = 0;
		gomb.y1 = static_cast<float>(i * 25);
		gomb.x2 = 1499;
		gomb.y2 = static_cast<float>(i * 25 + 24);
		gomb.t = L"----";
		gomb.k = false;
		gomb.kk = false;
		FILE_vector.push_back(gomb);
	}
	for (size_t i = 0; i < file_nevek.size(); i++) FILE_vector[i].t = file_nevek[i];
}

void MainWindow::List_init()
{
	list.k = -1;
	list.kk = -1;
	list.BOX_k = false;
	list.top = BOX_MODE.bottom;
	list.right = static_cast<float>(ScreenWidth);
	list.left = list.right - 139;
	list.bottom = static_cast<float>(ScreenHeight);
	list.cs.top = list.top + 4;
	list.cs.bottom = list.bottom - 4;
	list.cs.right = list.right - 4;
	list.cs.left = list.cs.right - 20;
	float m=0, H=0, N=0;
	m = 25;
	H = (list.bottom - list.top) / m;
	N = static_cast<float>(Alkatresz.size());
	if (N == 0) N = 2;
	float arány = H/N;
	list.cs.length = list.cs.bottom - list.cs.top - 4;
	if (arány < 1) list.cs.length = arány * (list.bottom - list.top - 10);
	list.cs.min = list.cs.p = list.cs.top + 2;
	list.cs.max = list.cs.bottom - list.cs.length - 2;
	list.cs.range = list.cs.max - list.cs.min;
}

void MainWindow::List2_init()
{
	float w = static_cast<float>(ScreenWidth) / 6;
	float h = static_cast<float>(ScreenHeight) / 8;
	list2.k = -1;
	list2.kk = -1;
	list2.BOX_k = false;
	list2.top = h;
	list2.right = 4 * w;
	list2.left = 2 * w;
	list2.bottom = 7 * h;
	list2.cs.top = list2.top + 4;
	list2.cs.bottom = list2.bottom - 4;
	list2.cs.right = list2.right - 4;
	list2.cs.left = list2.cs.right - 20;
	float m = 0, H = 0;// , N = 0;
	m = 25;
	H = (list2.bottom - list2.top) / m;
	list2.cs.length = list2.cs.bottom - list2.cs.top - 4;
	list2.cs.min = list2.cs.p = list2.cs.top + 2;
	/*N = Alkatrész.size();
	if (N == 0) N = 2;
	float arány = float(H) / float(N);
	if (arány < 1) list2.cs.length = arány * (list2.bottom - list2.top - 10);
	list2.cs.max = list2.cs.bottom - list2.cs.length - 2;
	list2.cs.range = list2.cs.max - list2.cs.min;*/
}

void MainWindow::SZINT_init()
{
	BOX_SZINT.bottom = ablak.y;
	BOX_SZINT.top = BOX_SZINT.bottom - 30;
	BOX_SZINT.right = ablak.x - 150;
	BOX_SZINT.left = BOX_SZINT.right - 160;
	for (size_t i = 0; i < szint_nevek.size(); i++)
	{
		gomb.x1 = static_cast<float>(0 + i * 80);
		gomb.x2 = static_cast<float>(79 + i * 80);
		gomb.y1 = 0;
		gomb.y2 = BOX_SZINT.bottom - BOX_SZINT.top;
		gomb.t = L"----";
		gomb.k = false;
		gomb.kk = false;
		SZINT_vector.push_back(gomb);
	}
	SZINT_vector[0].kk = true;
	for (size_t i = 0; i < szint_nevek.size(); i++) SZINT_vector[i].t = szint_nevek[i];
}

void MainWindow::GC_init()
{
	BOX_GC.bottom = ablak.y;
	BOX_GC.top = ablak.y - 40;
	BOX_GC.left = 0;
	BOX_GC.right = 80;
	for (int i = 0; i < 3; i++)
	{
		gc.x = static_cast<float>(20 + 20 * i);
		gc.y = 20;
		gc.r = 8;
		GC_vector.push_back(gc);
	}
}

void MainWindow::GRID_init()
{
	grid.x1 = BOX_GC.right + 1;
	grid.y2 = ablak.y;
	grid.x2 = grid.x1 + 120;
	grid.y1 = grid.y2 - 30;
	grid.t = L"Grid:";
	grid.c.push_back('1');
	//grid.c.push_back('0');
	size_t h = grid.c.size();
	char w[10];
	for (int i = 0; i < 10; i++) w[i] = ' ';
	for (size_t i = 0; i < h; i++) w[i] = grid.c[i];
	grid.i = stoi(w);
}

void MainWindow::ORIGO_init()
{
	origo.bottom = ablak.y;
	origo.top = origo.bottom - 30;
	origo.left = grid.x2 + 1;
	origo.right = origo.left + 120;
	origo.t = L"Origo_megado";
	origo.k = false;
	origo.kk = false;
}

void MainWindow::XY_init()
{
	BOX_XY.bottom = ablak.y;
	BOX_XY.top = ablak.y - 30;
	BOX_XY.left = origo.right + 1;
	BOX_XY.right = BOX_XY.left + 200;

}

void MainWindow::Betolt_clear()
{
	VONAL_betolt.clear();
	ARC_betolt.clear();
	POLIGON_betolt.clear();
	EL_betolt.clear();
	SQ_betolt.clear();
	RR_betolt.clear();
	ELVIA_betolt.clear();
	SQVIA_betolt.clear();
	RRVIA_betolt.clear();
}

void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&m_pDCRT);
	SafeRelease(&Brush);
	SafeRelease(&pPathGeometry);
	SafeRelease(&pPathGeometry_2);
	SafeRelease(&pPathGeometry_3);
	SafeRelease(&pPathGeometry_4);
	SafeRelease(&pPathGeometry_5);
	SafeRelease(&pFactory);
	SafeRelease(&pDWriteFactory);
	SafeRelease(&TF1);
	SafeRelease(&TF2);
	SafeRelease(&TF2_dir);
	SafeRelease(&fekete);
	SafeRelease(&feher);
	SafeRelease(&cyan);
	SafeRelease(&pStrokeStyle);
	SafeRelease(&bv[0][0]);
	SafeRelease(&bv[0][1]);
	SafeRelease(&bv[1][0]);
	SafeRelease(&bv[1][1]);
	SafeRelease(&bp[0][0]);
	SafeRelease(&bp[0][1]);
	SafeRelease(&bp[1][0]);
	SafeRelease(&bp[1][1]);
	for (size_t i = 0; i < ARC_vector.size(); i++) SafeRelease(&ARC_vector[i].pg);
	for (size_t i = 0; i < POLIGON_vector.size(); i++) SafeRelease(&POLIGON_vector[i].pg);
	for (size_t i = 0; i < ARC_v.size(); i++) SafeRelease(&ARC_v[i].pg);
	for (size_t i = 0; i < POLIGON_v.size(); i++) SafeRelease(&POLIGON_v[i].pg);
	for (size_t i = 0; i < Alkatresz.size(); i++)
	{
		for (size_t j = 0; j < Alkatresz[i].a.size(); j++) SafeRelease(&Alkatresz[i].a[j].pg);
		for (size_t j = 0; j < Alkatresz[i].p.size(); j++) SafeRelease(&Alkatresz[i].p[j].pg);
	}
}
