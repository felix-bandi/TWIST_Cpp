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
#include <codecvt>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include "TWIST_Cpp.h"
#include <strsafe.h>
#include <stdio.h>
//#include <filesystem>

void MainWindow::ALAK_rajzol()
{
	for (int i = 0; i < ALAK_vector.size(); i++)
	{
		//flo3 = 77;
		//int3 = ALAK_kk;
		rect.left = BOX_ALAK.left;
		rect.top = BOX_ALAK.top + ALAK_vector[i].y1;
		rect.right = BOX_ALAK.right;
		rect.bottom = BOX_ALAK.top + ALAK_vector[i].y2;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
		if (ALAK_k == i && !krv) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
		if (ALAK_kk == i) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
		pRenderTarget->FillRectangle(rect, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
		pRenderTarget->DrawRectangle(rect, Brush, 1);
		hossz = ALAK_vector[i].t.length();
		for (int n = 0; n < hossz; n++) text[n] = ALAK_vector[i].t[n];
		pRenderTarget->DrawText(text, hossz, TF1, rect, Brush);
	}
}

void MainWindow::MODE_rajzol()
{
	for (int i = 0; i < MODE_vector.size(); i++)
	{
		rect.left = BOX_MODE.left;
		rect.top = BOX_MODE.top + MODE_vector[i].y1;
		rect.right = BOX_MODE.right;
		rect.bottom = BOX_MODE.top + MODE_vector[i].y2;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
		if (MODE_k == i && !krv) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
		if (MODE_kk == i) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
		pRenderTarget->FillRectangle(rect, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
		pRenderTarget->DrawRectangle(rect, Brush, 1);
		hossz = MODE_vector[i].t.length();
		for (int n = 0; n < hossz; n++) text[n] = MODE_vector[i].t[n];
		pRenderTarget->DrawText(text, hossz, TF1, rect, Brush);
	}
}

void MainWindow::FILE_rajzol()
{
	for (int i = 0; i < FILE_vector.size(); i++)
	{
		rect.left = BOX_FILE.left;
		rect.top = BOX_FILE.top + FILE_vector[i].y1;
		rect.right = BOX_FILE.right;
		rect.bottom = BOX_FILE.top + FILE_vector[i].y2;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
		if (FILE_k == i && !krv) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
		if (FILE_kk == i) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
		pRenderTarget->FillRectangle(rect, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
		pRenderTarget->DrawRectangle(rect, Brush, 1);
		hossz = FILE_vector[i].t.length();
		for (int n = 0; n < hossz; n++) text[n] = FILE_vector[i].t[n];
		pRenderTarget->DrawText(text, hossz, TF1, rect, Brush);
	}
}

void MainWindow::SZINT_rajzol()
{
	for (int i = 0; i < SZINT_vector.size(); i++)
	{
		rect.left = BOX_SZINT.left + SZINT_vector[i].x1;
		rect.right = BOX_SZINT.left + SZINT_vector[i].x2;
		rect.top = BOX_SZINT.top;
		rect.bottom = BOX_SZINT.bottom;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
		if (SZINT_k == i && !krv) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
		if (SZINT_kk == i) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
		pRenderTarget->FillRectangle(rect, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
		pRenderTarget->DrawRectangle(rect, Brush, 1);
		hossz = SZINT_vector[i].t.length();
		for (int n = 0; n < hossz; n++) text[n] = SZINT_vector[i].t[n];
		pRenderTarget->DrawText(text, hossz, TF1, rect, Brush);
	}
}

void MainWindow::List_rajzol()
{
	if (list.left <= mouse.x && list.right >= mouse.x && list.top <= mouse.y && list.bottom >= mouse.y) list.BOX_k = true; 
		else list.BOX_k = false;
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawRectangle(list, Brush, 2);
	pRenderTarget->DrawRectangle(list.cs, Brush, 1);
	list.cs.value = list.cs.p - list.cs.min;
	list.cs.bar.left = list.cs.left + 2;
	list.cs.bar.right = list.cs.right - 2;
	list.cs.bar.top = list.cs.p;
	list.cs.bar.bottom = list.cs.length + list.cs.p;
	pRenderTarget->FillRectangle(list.cs.bar, Brush);
	int h;
	list.k = -1;
	for (int i = 0; i < Alkatrész.size(); i++)
	{
		rect.top = list.top + 4 + i * 25;
		rect.bottom = rect.top + 24;
		rect.right = list.cs.left - 4;
		rect.left = list.left + 4;
		if (rect.left <= mouse.x && rect.right >= mouse.x && rect.bottom >= mouse.y && rect.top < mouse.y)
		{
			list.k = i;
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		}
		else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
		if (list.kk == i ) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
		h = Alkatrész[i].név.size();
		for (int j = 0; j < h; j++) text[j] = Alkatrész[i].név[j];
		pRenderTarget->DrawText(text, h, TF2, rect, Brush);
	}
}

void MainWindow::List2_rajzol()
{
	if (list2.left <= mouse.x && list2.right >= mouse.x && list2.top <= mouse.y && list2.bottom >= mouse.y) list2.BOX_k = true;
	else list2.BOX_k = false;
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawRectangle(list2, Brush, 2);
	pRenderTarget->DrawRectangle(list2.cs, Brush, 1);
	list2.cs.value = list2.cs.p - list2.cs.min;
	list2.cs.bar.left = list2.cs.left + 2;
	list2.cs.bar.right = list2.cs.right - 2;
	list2.cs.bar.top = list2.cs.p;
	list2.cs.bar.bottom = list2.cs.length + list2.cs.p;
	pRenderTarget->FillRectangle(list2.cs.bar, Brush);

}

void MainWindow::Filedialog_rajzol()
{
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkBlue));
	pRenderTarget->FillRectangle(dialog, Brush);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawRectangle(dialog, Brush, 2);
	DWORD dr = GetLogicalDrives();
	int j = 0;
	dialog.kd = -1;
	drivers.clear();
	for (char i = 0; i < 32; i++)
	{
		if (dr & 1 << i)
		{
			driver.left = dialog.left + 10 + 40 * j;
			driver.top = dialog.top + 10;
			driver.right = driver.left + 30;
			driver.bottom = driver.top + 30;
			driver.ch = 'A' + i;
			drivers.push_back(driver);	
			j++;
		}
	}

	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawLine(dialog.p1, dialog.p2, Brush, 2);
	int1 = dialog.kkd;
	boolean v = false;

	for(int i=0; i<drivers.size(); i++)
	{
		if (drivers[i].ch == kiv_drv) { v = true; dialog.kkd = i; }
	}

	if (!v) 
	{ 
		dialog.kkd = 0; 
		kiv_drv = drivers[dialog.kkd].ch;
		dialog.dirchange = true; 
	}

	for (int i=0; i < drivers.size(); i++)
	{
		driver = drivers[i];
		rrect.rect = driver;  rrect.radiusX = 5;  rrect.radiusY = 5;
		if (driver.left <= mouse.x && driver.right >= mouse.x && driver.bottom >= mouse.y && driver.top < mouse.y)
		{
			dialog.kd = i;
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::LightGray));
		}
		else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
		if (dialog.kkd == i) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
		pRenderTarget->FillRoundedRectangle(rrect, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
		pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);
		text[0] = drivers[i].ch; text[1] = ' '; text[2] = ':';
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		pRenderTarget->DrawText(text, 3, TF1, driver, Brush);
	}

	WCHAR a[260] = L"C:/", b[260] = L"*.*";// , c[260] = L"*.*";
	a[0] = drivers[dialog.kkd].ch;
	wcscat_s(a, b);

	if (dialog.dirchange)
	{
		dialog.hFind = FindFirstFile(a, &dialog.FindFileData);
		File_vector.clear();
		if (dialog.hFind != INVALID_HANDLE_VALUE)
			do
			{
				File_vector.push_back(dialog.FindFileData);
			} while (FindNextFile(dialog.hFind, &dialog.FindFileData));
		FindClose(dialog.hFind);
		dialog.ini = true;
		dialog.dirchange = false;
	}
	size_t TF, Hely_N, File_N;
	if (dialog.ini)
	{
		dialog.cs.v = false;
		TF = 16, Hely_N = (dialog.client.bottom - dialog.client.top) / TF, File_N = File_vector.size();
		if (Hely_N < File_N) { NN = Hely_N; dialog.cs.v = true; dialog.out_N = File_N - Hely_N; }
			else NN = File_N;
		float const arány = float(Hely_N) / float(File_N);
		dialog.cs.length = arány * (dialog.client.bottom - dialog.client.top);
		dialog.cs.min = dialog.cs.p = dialog.cs.top + 3;
		//int2 = File_N; int3 = Hely_N; //int1 = File_N - Hely_N; akarmi = int1;
		if (File_N > 1)
		{
			size_t a = 0, b = File_N - 1, A, B;
			WIN32_FIND_DATA t;
			do
			{
				if (File_vector[a].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) A = 0; else A = 1;
				if (File_vector[b].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) B = 0; else B = 2;
				switch (A+B)
				{
				case 0:
					a++;
					break;
				case 1:
					t = File_vector[a];
					File_vector[a] = File_vector[b];
					File_vector[b] = t;
					a++; b--;
					break;
				case 2:
					a++; b--;
					break;
				case 3:
					b--;
				}
			} while (a <= b);
			if(a>1)
			{
				wchar_t* copy1=nullptr, * copy2=nullptr;
				errno_t err;
				for(int i=0; i < a-1; i++)
					for(int j=i+1; j < a; j++)
					{
						err = _wcslwr_s(copy1 = _wcsdup(File_vector[i].cFileName),1+ std::wcslen(File_vector[i].cFileName));
						err = _wcslwr_s(copy2 = _wcsdup(File_vector[j].cFileName),1+ std::wcslen(File_vector[j].cFileName));
						if(wcscmp(copy1,copy2)>0)
						{
							t = File_vector[i];
							File_vector[i] = File_vector[j];
							File_vector[j] = t;
						}
						free(copy1);
						free(copy2);
					}
			}
			if ((File_N - a) > 1)
			{
				wchar_t* copy1 = nullptr, * copy2 = nullptr;
				errno_t err;
				for (int i = a; i < File_N - 1; i++)
					for (int j = i + 1; j < File_N; j++)
					{
						err = _wcslwr_s(copy1 = _wcsdup(File_vector[i].cFileName), 1 + std::wcslen(File_vector[i].cFileName));
						err = _wcslwr_s(copy2 = _wcsdup(File_vector[j].cFileName), 1 + std::wcslen(File_vector[j].cFileName));
						if (wcscmp(copy1, copy2) > 0)
						{
							t = File_vector[i];
							File_vector[i] = File_vector[j];
							File_vector[j] = t;
						}
						free(copy1);
						free(copy2);
					}
			}
		}
		dialog.ini = false;
	}

	if (dialog.cs.v)
	{
		dialog.cs.k = false;
		if (dialog.cs.left <= mouse.x && dialog.cs.right >= mouse.x && dialog.cs.bottom >= mouse.y && dialog.cs.top <= mouse.y) dialog.cs.k = true;
		
		dialog.cs.max = dialog.cs.bottom - dialog.cs.length - 3;
		dialog.cs.range = dialog.cs.max - dialog.cs.min;
		dialog.cs.value = dialog.cs.p - dialog.cs.min;
		pRenderTarget->DrawRectangle(dialog.cs, Brush, 2);

		dialog.cs.bar.right = dialog.cs.right - 3;
		dialog.cs.bar.left = dialog.cs.left + 3;
		dialog.cs.bar.top = dialog.cs.p;
		dialog.cs.bar.bottom = dialog.cs.length + dialog.cs.p;
		if(dialog.cs.kk) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
			else if(dialog.cs.k) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
			else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));
		pRenderTarget->FillRectangle(dialog.cs.bar, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	}
	
	WCHAR dir[] = L"<DIR>  ", w[MAX_PATH];
	size_t const h1 = std::wcslen(dir);
	size_t k = round(dialog.out_N * (dialog.cs.value / dialog.cs.range));
	if (k > dialog.out_N) k = dialog.out_N;
	flo1 = dialog.cs.value; flo2 = dialog.cs.range; flo3 = flo1 / flo2;
	dialog.k = -1;
	for (int i = 0; i < NN; i++)
	{
		rect.left = dialog.client.left + 10;
		rect.right = dialog.client.right - 20;
		rect.top = dialog.client.top + i * 16;
		rect.bottom = dialog.client.top + (i + 1) * 16;
		if (rect.left <= mouse.x && rect.right >= mouse.x && rect.bottom >= mouse.y && rect.top < mouse.y)
		{
			dialog.k = i;
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		}
		else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));

		size_t const h2 = std::wcslen(File_vector[i+k].cFileName);
		for (size_t n = 0; n < h2; n++) text[n] = File_vector[i+k].cFileName[n];
		for (size_t n = h2; n < 260; n++) text[n] = ' ';
		if (File_vector[i+k].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			for (size_t n = 0; n < h1; n++) w[n] = dir[n];
			for (size_t n = h1; n < 260; n++) w[n] = text[n - h1];
			pRenderTarget->DrawText(w, 56, TF2, rect, Brush);
		}
		else
		{
			pRenderTarget->DrawText(text, 56, TF2, rect, Brush);
		}
	}
	dialog.edit.k = false;
	if (dialog.edit.left <= mouse.x && dialog.edit.right >= mouse.x && dialog.edit.bottom >= mouse.y && dialog.edit.top <= mouse.y) dialog.edit.k = true;
	if (dialog.edit.kk) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	else if (dialog.edit.k) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));
	pRenderTarget->DrawRectangle(dialog.edit, Brush, 1);
	for (int i = 0; i < dialog.edit.c.size(); i++) dialog.filepath[i] = dialog.edit.c[i];
	pRenderTarget->DrawText(dialog.filepath, dialog.edit.c.size(), TF2, dialog.edit, Brush);
	save1.bottom = dialog.bottom - 10;
	save1.top = save1.bottom - 30;
	save1.left = dialog.client.left;
	save1.right = save1.left + 170;
	save1.t = L"Mentés alkatrészként";
	//save1.tt = L"ezeaz";
	rrect.rect = save1;  rrect.radiusX = 5;  rrect.radiusY = 5;
	if (save1.left <= mouse.x && save1.right >= mouse.x && save1.bottom >= mouse.y && save1.top < mouse.y)
	{
		save1.k = true;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::LightGray));
	}
	else 
	{
		save1.k = false;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
	}
	//if (dialog.kkd == j) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
	pRenderTarget->FillRoundedRectangle(rrect, Brush);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
	pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);
	//text[0] = drivers[j].ch; text[1] = ' '; text[2] = ':';
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	for (int i = 0; i < save1.t.size(); i++) text[i] = save1.t[i];
	//for (int i = 0; i < save1.t.size(); i++) save1.tt[i] = save1.t[i];
	pRenderTarget->DrawText(text, save1.t.size(), TF1, save1, Brush);
}

void MainWindow::CUSTOM_rajzol()
{
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
	rect.left = BOX_CUSTOM.left;
	rect.top = BOX_CUSTOM.top;
	rect.right = BOX_CUSTOM.right;
	rect.bottom = BOX_CUSTOM.bottom;
	pRenderTarget->FillRectangle(rect, Brush);
	if (ALAK_kk >= 0)
	{
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
		rect.bottom = BOX_CUSTOM.top + 25;
		ws = L"Custom " + alak_nevek[ALAK_kk];
		hossz = ws.length();
		for (int n = 0; n < hossz; n++) text[n] = ws[n];
		pRenderTarget->DrawText(text, hossz, TF1, rect, Brush);
		int s = CUSTOM[ALAK_kk].size();
		int i = 0;
		while (s >= 1)
		{
			rect.top = BOX_CUSTOM.top + CUSTOM[ALAK_kk][i].y1;
			rect.bottom = BOX_CUSTOM.top + CUSTOM[ALAK_kk][i].y2;
			rect.left = BOX_CUSTOM.left;
			rect.right = BOX_CUSTOM.left + 60;
			ws = CUSTOM[ALAK_kk][i].t;
			hossz = ws.length();
			for (int n = 0; n < hossz; n++) text[n] = ws[n];
			if (CUSTOM_vector[i].sz)
			{
				Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
				pRenderTarget->DrawText(text, hossz, TF1, rect, Brush);
				rect.top = rect.top + 3;
				rect.left = BOX_CUSTOM.left + 70;
				rect.right = BOX_CUSTOM.right - 5;
				pRenderTarget->DrawRectangle(rect, Brush, 1);
				rect.top = rect.top - 2;
				for (int i = 0; i < edit.c.size(); i++) text[i] = edit.c[i];
				pRenderTarget->DrawText(text, edit.c.size(), TF1, rect, Brush);
			}
			else
			{
				if (CUSTOM_vector[i].k)
					Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
				else
					Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
				pRenderTarget->DrawText(text, hossz, TF1, rect, Brush);
				rect.top = rect.top + 3;
				rect.left = BOX_CUSTOM.left + 70;
				rect.right = BOX_CUSTOM.right - 5;
				pRenderTarget->DrawRectangle(rect, Brush, 1);
				rect.top = rect.top - 2;
				Kiir(CUSTOM[ALAK_kk][i].i, rect);
			}
			i++;
			s--;
		}
	}
}

void MainWindow::GRID_rajzol()
{
	rect.left = grid.x1;
	rect.top = grid.y1;
	rect.right = grid.x2;
	rect.bottom = grid.y2;
	if (grid.sz)
	{
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
		pRenderTarget->DrawRectangle(rect, Brush, 2);
		for (int i = 0; i < edit.c.size(); i++) text[i] = edit.c[i];
		for (int j = 0; j < 10; j++) w[j] = ' ';
		for (int j = 0; j < edit.c.size(); j++) w[j] = edit.c[j];
		if (edit.c.size() > 0) Kiir("Grid: ", stoi(w), rect); else Kiir("Grid:", rect);
	}
	else
	{
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
		if (grid.k) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
		pRenderTarget->DrawRectangle(rect, Brush, 2);
		Kiir("Grid: ", grid.i, rect);
	}
}

void MainWindow::ORIGO_rajzol()
{
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
	if (origo.k) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
	if (origo.kk) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->FillRectangle(origo, Brush);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
	pRenderTarget->DrawRectangle(origo, Brush, 1);
	hossz = origo.t.length();
	for (int n = 0; n < hossz; n++) text[n] = origo.t[n];
	pRenderTarget->DrawText(text, hossz, TF1, origo, Brush);
}

void MainWindow::Origo_áthelyez()
{
	float x = -xx;
	float y = -yy;
	for (int i = 0; i < VONAL_vector.size(); i++)
	{
		VONAL_vector[i].x1 += x;
		VONAL_vector[i].x2 += x;
		VONAL_vector[i].y1 += y;
		VONAL_vector[i].y2 += y;
	}
	for (int i = 0; i < ARC_vector.size(); i++)
	{
		ARC_vector[i].kpx += x;
		ARC_vector[i].kpy += y;
		ARC_vector[i].xk += x;
		ARC_vector[i].yk += y;
		ARC_vector[i].xv += x;
		ARC_vector[i].yv += y;
		SafeRelease(&ARC_vector[i].pg);
		pFactory->CreatePathGeometry(&ARC_vector[i].pg);
		ID2D1GeometrySink* pSink;
		ARC_vector[i].pg->Open(&pSink);
		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
		ak.x = ARC_vector[i].xk;
		ak.y = ARC_vector[i].yk;
		av.x = ARC_vector[i].xv;
		av.y = ARC_vector[i].yv;
		meret.width = ARC_vector[i].rx;
		meret.height = ARC_vector[i].ry;
		pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
		pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, ARC_vector[i].i, ARC_vector[i].s));
		pSink->EndFigure(D2D1_FIGURE_END_OPEN);
		pSink->Close();
		SafeRelease(&pSink);
	}
	for (int i = 0; i < POLIGON_vector.size(); i++)
	{
		for (int j = 0; j < POLIGON_vector[i].pont.size(); j++)
		{
			POLIGON_vector[i].pont[j].x += x;
			POLIGON_vector[i].pont[j].y += y;
		}
		SafeRelease(&POLIGON_vector[i].pg);
		for (int j = 0; j < POLIGON_vector[i].pont.size(); j++) pontok[j] = POLIGON_vector[i].pont[j];
		pFactory->CreatePathGeometry(&POLIGON_vector[i].pg);
		ID2D1GeometrySink* pSink;
		POLIGON_vector[i].pg->Open(&pSink);
		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
		pSink->BeginFigure(POLIGON_vector[i].pont[0], D2D1_FIGURE_BEGIN_FILLED);
		pSink->AddLines(pontok, POLIGON_vector[i].pont.size());
		pSink->AddLine(POLIGON_vector[i].pont[0]);
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pSink->Close();
		SafeRelease(&pSink);
	}
	for (int i = 0; i < EL_vector.size(); i++)
	{
		EL_vector[i].x += x;
		EL_vector[i].y += y;
	}
	for (int i = 0; i < SQ_vector.size(); i++)
	{
		SQ_vector[i].x += x;
		SQ_vector[i].y += y;
	}
	for (int i = 0; i < RR_vector.size(); i++)
	{
		RR_vector[i].x += x;
		RR_vector[i].y += y;
	}
	for (int i = 0; i < ELVIA_vector.size(); i++)
	{
		ELVIA_vector[i].x += x;
		ELVIA_vector[i].y += y;
	}
	for (int i = 0; i < SQVIA_vector.size(); i++)
	{
		SQVIA_vector[i].x += x;
		SQVIA_vector[i].y += y;
	}
	for (int i = 0; i < RRVIA_vector.size(); i++)
	{
		RRVIA_vector[i].x += x;
		RRVIA_vector[i].y += y;
	}
	origo.kk = false;
	eltolas.x += xx;
	eltolas.y += yy;
	xxx = mouse.x / nagyitas - eltolas.x;
	yyy = mouse.y / nagyitas - eltolas.y;
	xx = ((xxx + grid.i / 2) / grid.i) * grid.i;
	yy = ((yyy + grid.i / 2) / grid.i) * grid.i;
	mouse_grid.x = (xx + eltolas.x) * nagyitas;
	mouse_grid.y = (yy + eltolas.y) * nagyitas;
	Blokk_szamol();
}

void MainWindow::GC_rajzol()
{
	for (int i = 0; i < GC_vector.size(); i++)
	{
		hely.x = GC_vector[i].x + BOX_GC.left;
		hely.y = GC_vector[i].y + BOX_GC.top;
		rx = GC_vector[i].r;
		ellipse = D2D1::Ellipse(hely, rx, rx);
		if (GC_kk != i) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Wheat));
		else
		{
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::AntiqueWhite));
			pRenderTarget->FillEllipse(ellipse, Brush);
		}
		pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	}
}

void MainWindow::Cursor_rajzol()
{
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	switch (GC_kk)
	{
	case 0:
		p1.x = mouse_grid.x - 20; p2.x = mouse_grid.x + 20;
		p3.y = mouse_grid.y - 20; p4.y = mouse_grid.y + 20;
		break;
	case 1:
		p1.x = mouse_grid.x - 80; p2.x = mouse_grid.x + 80;
		p3.y = mouse_grid.y - 80; p4.y = mouse_grid.y + 80;
		break;
	case 2:
		p1.x = 0; p2.x = ablak.x;
		p3.y = 0; p4.y = ablak.y;
	}

	p1.y = mouse_grid.y;      p2.y = mouse_grid.y;
	p3.x = mouse_grid.x;      p4.x = mouse_grid.x;
	pRenderTarget->DrawLine(p1, p2, Brush, 1.0, pStrokeStyle);
	pRenderTarget->DrawLine(p3, p4, Brush, 1.0, pStrokeStyle);
}

void MainWindow::XY_rajzol()
{
	rect.bottom = BOX_XY.bottom;
	rect.top = BOX_XY.top;
	rect.left = BOX_XY.left;
	rect.right = BOX_XY.left + 100;
	Kiir("X = ", xx, rect);
	rect.left = BOX_XY.left + 100;
	rect.right = BOX_XY.right;
	Kiir("Y = ", yy, rect);
}