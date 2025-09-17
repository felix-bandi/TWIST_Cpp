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
#include <strsafe.h>
#include <stdio.h>
#include <algorithm>
#include "PrintHelpers.h"
#include <wrl/client.h>
#include <iostream>

static bool IsDriveReady(wchar_t letter)
{
	wchar_t root[] = L"X:\\";
	root[0] = letter;
	DWORD attrs = GetFileAttributesW(root);
	if (attrs == INVALID_FILE_ATTRIBUTES)
	{
		// Próbáljuk eszköz handle-lal
		std::wstring dev = L"\\\\.\\"; dev += letter; dev += L":";
		HANDLE h = CreateFileW(dev.c_str(), 0,
			FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
			OPEN_EXISTING, 0, nullptr);
		if (h == INVALID_HANDLE_VALUE)
		{
			DWORD err = GetLastError();
			if (err == ERROR_NOT_READY || err == ERROR_PATH_NOT_FOUND ||
				err == ERROR_DEVICE_NOT_CONNECTED)
				return false;
			return false;
		}
		CloseHandle(h);
	}
	return true;
}

void MainWindow::ALAK_rajzol()
{
	for (int i = 0; i < static_cast<int>(ALAK_vector.size()); i++)
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
		for (size_t n = 0; n < hossz; n++) text[n] = ALAK_vector[i].t[n];
		pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

void MainWindow::MODE_rajzol()
{
	for (int i = 0; i < static_cast<int>(MODE_vector.size()); i++)
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
		for (size_t n = 0; n < hossz; n++) text[n] = MODE_vector[i].t[n];
		pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

void MainWindow::FILE_rajzol()
{
	for (int i = 0; i < static_cast<int>(FILE_vector.size()); i++)
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
		for (size_t n = 0; n < hossz; n++) text[n] = FILE_vector[i].t[n];
		pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

void MainWindow::SZINT_rajzol()
{
	for (int i = 0; i < static_cast<int>(SZINT_vector.size()); i++)
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
		for (size_t n = 0; n < hossz; n++) text[n] = SZINT_vector[i].t[n];
		pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

void MainWindow::List_rajzol()
{
	if (list.left <= mouse.x && list.right >= mouse.x && list.top <= mouse.y && list.bottom >= mouse.y) list.BOX_k = true; 
		else list.BOX_k = false;
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawRectangle(list, Brush, 2);
	pRenderTarget->DrawRectangle(list.sb, Brush, 1);
	list.sb.value = list.sb.pos - list.sb.posMin;
	list.sb.thumb.left = list.sb.left + 2;
	list.sb.thumb.right = list.sb.right - 2;
	list.sb.thumb.top = list.sb.pos;
	list.sb.thumb.bottom = list.sb.length + list.sb.pos;
	pRenderTarget->FillRectangle(list.sb.thumb, Brush);
	list.k = -1;
	for (int i = 0; i < static_cast<int>(Alkatresz.size()); i++)
	{
		rect.top = list.top + 4 + i * 25;
		rect.bottom = rect.top + 24;
		rect.right = list.sb.left - 4;
		rect.left = list.left + 4;
		if (rect.left <= mouse.x && rect.right >= mouse.x && rect.bottom >= mouse.y && rect.top < mouse.y)
		{
			list.k = i;
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		}
		else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
		if (list.kk == i ) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
		hossz = Alkatresz[i].nev.size();
		for (size_t j = 0; j < hossz; j++) text[j] = Alkatresz[i].nev[j];
		pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF2, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

void MainWindow::List2_rajzol()
{
	if (list2.left <= mouse.x && list2.right >= mouse.x && list2.top <= mouse.y && list2.bottom >= mouse.y) list2.BOX_k = true;
	else list2.BOX_k = false;
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawRectangle(list2, Brush, 2);
	pRenderTarget->DrawRectangle(list2.sb, Brush, 1);
	list2.sb.value = list2.sb.pos - list2.sb.posMin;
	list2.sb.thumb.left = list2.sb.left + 2;
	list2.sb.thumb.right = list2.sb.right - 2;
	list2.sb.thumb.top = list2.sb.pos;
	list2.sb.thumb.bottom = list2.sb.length + list2.sb.pos;
	pRenderTarget->FillRectangle(list2.sb.thumb, Brush);

}

void MainWindow::Filedialog_rajzol()
{
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkBlue));
	pRenderTarget->FillRectangle(dialog, Brush);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawRectangle(dialog, Brush, 2);

	// Meghajtó gombok felépítése
	dialog.kd = -1;
	drivers.clear();
	DWORD mask = GetLogicalDrives();
	int col = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (mask & (1 << i))
		{
			driver.left = dialog.left + 10 + 40 * col;
			driver.top = dialog.top + 10;
			driver.right = driver.left + 30;
			driver.bottom = driver.top + 30;
			driver.ch = static_cast<char>('A' + i);
			drivers.push_back(driver);
			col++;
		}
	}

	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawLine(dialog.p1, dialog.p2, Brush, 2);

	// Ellenőrizzük a kiválasztott meghajtót (ha nincs, fallback 0)
	bool talált = false;
	for (size_t i = 0; i < drivers.size(); ++i)
	{
		if (drivers[i].ch == kiv_drv) { talált = true; dialog.kkd = i; break; }
	}
	if (!talált && !drivers.empty())
	{
		dialog.kkd = 0;
		kiv_drv = drivers[0].ch;
		dialog.dirchange = true;
	}

	// Meghajtó gombok kirajzolása
	for (size_t i = 0; i < drivers.size(); i++)
	{
		bool ready = IsDriveReady(drivers[i].ch);
		driver = drivers[i];
		rrect.rect = driver; rrect.radiusX = 5; rrect.radiusY = 5;

		bool hover = (driver.left <= mouse.x && driver.right >= mouse.x &&
			driver.top <= mouse.y && driver.bottom >= mouse.y);
		if (hover) dialog.kd = static_cast<int>(i);

		if (!ready)
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkRed));
		else if (dialog.kkd == i)
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
		else if (hover)
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::LightGray));
		else
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));

		pRenderTarget->FillRoundedRectangle(rrect, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
		pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);

		text[0] = drivers[i].ch; text[1] = ' '; text[2] = ':';
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		pRenderTarget->DrawText(text, 3, TF1, driver, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}

	// --- RÉGI enumerációs kód TÖRÖLVE ---
	// Helyette: központosított frissítés
	UpdateDialogContents();
	
	// Görgetősáv (ha kell)
	if (dialog.sb.isHover)
	{
		dialog.sb.isPressed = false;
		if (dialog.sb.left <= mouse.x && dialog.sb.right >= mouse.x &&
			dialog.sb.top <= mouse.y && dialog.sb.bottom >= mouse.y)
			dialog.sb.isPressed = true;

		dialog.sb.posMax = dialog.sb.bottom - dialog.sb.length - 3;
		dialog.sb.range = dialog.sb.posMax - dialog.sb.posMin;
		dialog.sb.value = dialog.sb.pos - dialog.sb.posMin;

		pRenderTarget->DrawRectangle(dialog.sb, Brush, 2);

		dialog.sb.thumb.left = dialog.sb.left + 3;
		dialog.sb.thumb.right = dialog.sb.right - 3;
		dialog.sb.thumb.top = dialog.sb.pos;
		dialog.sb.thumb.bottom = dialog.sb.pos + dialog.sb.length;

		if (dialog.sb.isDragging) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
		else if (dialog.sb.isPressed) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
		else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));

		pRenderTarget->FillRectangle(dialog.sb.thumb, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	}
	
	// Fájl lista
	dialog.k = -1;
	WCHAR dirPrefix[] = L"<DIR>  ";
	WCHAR sorBuf[MAX_PATH] = { 0 };
	size_t prefixLen = wcslen(dirPrefix);

	size_t fileN = File_vector.size();
	size_t kOffset = 0;
	if (dialog.sb.isHover && dialog.sb.range > 0.0001f)
	{
		float rel = (dialog.sb.pos - dialog.sb.posMin) / dialog.sb.range;
		if (rel < 0) rel = 0;
		if (rel > 1) rel = 1;
		kOffset = (size_t)lround(dialog.out_N * rel);
		if (kOffset > (size_t)dialog.out_N) kOffset = dialog.out_N;
	}
	
	for (size_t i = 0; i < NN; i++)
	{
		if (kOffset + i >= fileN) break;

		rect.left = dialog.client.left + 10;
		rect.right = dialog.client.right - 20;
		rect.top = dialog.client.top + i * 20;
		rect.bottom = rect.top + 20;

		bool hover = (rect.left <= mouse.x && rect.right >= mouse.x &&
			rect.top < mouse.y && rect.bottom >= mouse.y);

		if (hover)
		{
			dialog.k = static_cast<int>(i);
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		}
		else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));

		const WIN32_FIND_DATAW &ffd = File_vector[kOffset + i];
		const WCHAR* fname = ffd.cFileName;
		size_t nameLen = wcslen(fname);
		//WCHAR *brrr = File_vector[kOffset + i].cFileName;
		const WCHAR* borzalom = L"CON";
		nameLen = wcslen(borzalom);
		if (fdini2) { OutputDebugStringW(borzalom); OutputDebugStringW(L"\n"); }
		pRenderTarget->DrawText(borzalom, (UINT32)nameLen, TF2, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
	fdini2 = false;
	// Hiba kijelzés
	if (fileN == 0 && dialog.lastEnumError != 0)
	{
		D2D1_RECT_F rr1 = dialog.client;
		rr1.bottom = rr1.top + 18;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::OrangeRed));
		const wchar_t* msg = (dialog.lastEnumError == ERROR_NOT_READY)
			? L"Meghajtó nem elérhető"
			: L"Hiba az olvasás során";
		pRenderTarget->DrawText(msg, (UINT32)wcslen(msg), TF2, rr1, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}

	// Edit mező
	dialog.edit.k = false;
	if (dialog.edit.left <= mouse.x && dialog.edit.right >= mouse.x &&
		dialog.edit.top <= mouse.y && dialog.edit.bottom >= mouse.y)
		dialog.edit.k = true;

	if (dialog.edit.kk) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	else if (dialog.edit.k) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));

	pRenderTarget->DrawRectangle(dialog.edit, Brush, 1);
	for (int i = 0; i < (int)dialog.edit.c.size(); i++)
		dialog.filepath[i] = dialog.edit.c[i];
	
	pRenderTarget->DrawText(dialog.edit.c.c_str(), static_cast<UINT32>(dialog.edit.c.length()), TF2, dialog.edit, Brush);

	// Mentés gomb
	save1.bottom = dialog.bottom - 10;
	save1.top = save1.bottom - 30;
	save1.left = dialog.client.left;
	save1.right = save1.left + 170;
	save1.t = L"Mentés alkatrészként";
	rrect.rect = save1;  rrect.radiusX = 5;  rrect.radiusY = 5;

	bool saveHover = (save1.left <= mouse.x && save1.right >= mouse.x &&
		save1.top < mouse.y && save1.bottom >= mouse.y);
	save1.k = saveHover;
	if (saveHover) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::LightGray));
	else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));

	pRenderTarget->FillRoundedRectangle(rrect, Brush);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
	pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	for (int i = 0; i < (int)save1.t.size(); i++) text[i] = save1.t[i];
	pRenderTarget->DrawText(text, (UINT32)save1.t.size(), TF1, save1, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

void MainWindow::Printdialog_rajzol()
{
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkBlue));
	pRenderTarget->FillRectangle(dialog_2, Brush);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawRectangle(dialog_2, Brush, 2);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	pRenderTarget->DrawLine(dialog_2.p1, dialog_2.p2, Brush, 2);

	std::vector<D2D1::ColorF> colors = {
		D2D1::ColorF(0.0f, 1.0f, 0.0f), 
		D2D1::ColorF(0.1f, 0.8f, 0.1f), 
		D2D1::ColorF(1.0f, 0.8f, 0.0f), 
		D2D1::ColorF(0.9f, 0.7f, 0.2f)  
	};

	if(dialog_2.ini)
	{
		// 20 elemű vegyes típusú teszt lista generálása a nyomtato vektorba
		/*nyomtato.clear();
		for (int i = 1; i <= 30; ++i) {
			Nyomtato p;
			p.name = L"Teszt nyomtató " + std::to_wstring(i);
			// 1: helyi, 2: helyi virtuális, 3: hálózati, 4: hálózati virtuális
			switch (i % 4) {
			case 1: p.tipus = std::byte{ 1 }; p.name += L" (helyi)"; break;
			case 2: p.tipus = std::byte{ 2 }; p.name += L" (helyi virtuális)"; break;
			case 3: p.tipus = std::byte{ 3 }; p.name += L" (hálózati)"; break;
			case 0: p.tipus = std::byte{ 4 }; p.name += L" (hálózati virtuális)"; break;
			}
			nyomtato.push_back(p);
		}*/
		
		size_t helyN = static_cast<size_t>(dialog_2.list.bottom - dialog_2.list.top) / 20;
		size_t N = nyomtato.size();
		Kiir((int)N, 100, 100);
		if (N == 0)
		{
			NN = 0;
			dialog_2.out_N = 0;
			dialog_2.sb.length = 0;
			dialog_2.sb.posMin = dialog_2.sb.posMax = dialog_2.sb.pos = dialog_2.sb.top;
			dialog_2.sb.range = 1;
		}
		else
		{
			if (helyN < N) { NN = helyN; dialog_2.sb.isHover = true; dialog_2.out_N = (int)(N - helyN); }
			else { NN = N; dialog_2.out_N = 0; }
			float arany = (float)helyN / (float)N;
			dialog_2.sb.length = arany * (dialog_2.list.bottom - dialog_2.list.top);
			dialog_2.sb.posMin = dialog_2.sb.pos = dialog_2.sb.top + 3;
		}
		dialog_2.ini = false;
	}
	//dialog_2.cs.v = true; //ideiglenes
	if (dialog_2.sb.isHover)
	{
		dialog_2.sb.isPressed = false;
		if (dialog_2.sb.left <= mouse.x && dialog_2.sb.right >= mouse.x &&
			dialog_2.sb.top <= mouse.y && dialog_2.sb.bottom >= mouse.y)
			dialog_2.sb.isPressed = true;

		dialog_2.sb.posMax = dialog_2.sb.bottom - dialog_2.sb.length - 3;
		dialog_2.sb.range = dialog_2.sb.posMax - dialog_2.sb.posMin;
		dialog_2.sb.value = dialog_2.sb.pos - dialog_2.sb.posMin;

		pRenderTarget->DrawRectangle(dialog_2.sb, Brush, 2);

		dialog_2.sb.thumb.left = dialog_2.sb.left + 3;
		dialog_2.sb.thumb.right = dialog_2.sb.right - 3;
		dialog_2.sb.thumb.top = dialog_2.sb.pos;
		dialog_2.sb.thumb.bottom = dialog_2.sb.pos + dialog_2.sb.length;

		if (dialog_2.sb.isDragging) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
		else if (dialog_2.sb.isPressed) Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
		else Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));

		pRenderTarget->FillRectangle(dialog_2.sb.thumb, Brush);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	}
	size_t kOffset = 0;
	if (dialog_2.sb.isHover && dialog_2.sb.range > 0.0001f)
	{
		float rel = (dialog_2.sb.pos - dialog_2.sb.posMin) / dialog_2.sb.range;
		if (rel < 0) rel = 0;
		if (rel > 1) rel = 1;
		kOffset = (size_t)lround(dialog_2.out_N * rel);
		if (kOffset > (size_t)dialog_2.out_N) kOffset = dialog_2.out_N;
	}
	for(size_t i=0; i<NN; i++)
	{
		rect.left = dialog_2.list.left + 10;
		rect.right = dialog_2.list.right - 20;
		rect.top = dialog_2.list.top + i * 20;
		rect.bottom = rect.top + 20;
		Brush->SetColor(colors[static_cast<int>(nyomtato[i+kOffset].tipus)-1]);
		UINT32 nameLen = (UINT32)nyomtato[i+kOffset].name.length();
		if (nyomtato[i + kOffset].alap)
		{
			Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
			std::wstring displayName = nyomtato[i + kOffset].name;
			//if (nyomtato[i + kOffset].alap)
			displayName = L"★ " + displayName;
			nameLen = static_cast<UINT32>(displayName.length());
			pRenderTarget->DrawText(displayName.c_str(), nameLen, TF2_dir, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		}
		else pRenderTarget->DrawText(nyomtato[i + kOffset].name.c_str(), nameLen, TF2, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
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
		for (size_t n = 0; n < hossz; n++) text[n] = ws[n];
		pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		size_t s = CUSTOM[ALAK_kk].size();
		int i = 0;
		while (s >= 1)
		{
			rect.top = BOX_CUSTOM.top + CUSTOM[ALAK_kk][i].y1;
			rect.bottom = BOX_CUSTOM.top + CUSTOM[ALAK_kk][i].y2;
			rect.left = BOX_CUSTOM.left;
			rect.right = BOX_CUSTOM.left + 60;
			ws = CUSTOM[ALAK_kk][i].t;
			hossz = ws.length();
			for (size_t n = 0; n < hossz; n++) text[n] = ws[n];
			if (CUSTOM_vector[i].sz)
			{
				Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
				pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
				rect.top = rect.top + 3;
				rect.left = BOX_CUSTOM.left + 70;
				rect.right = BOX_CUSTOM.right - 5;
				pRenderTarget->DrawRectangle(rect, Brush, 1);
				rect.top = rect.top - 2;
				for (size_t ii = 0; ii < edit.c.size(); ii++) text[ii] = edit.c[ii];
				pRenderTarget->DrawText(text, static_cast<UINT32>(edit.c.size()), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
			}
			else
			{
				if (CUSTOM_vector[i].k)
					Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
				else
					Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
				pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
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
	rect.left = static_cast<float>(grid.x1);
	rect.top = static_cast<float>(grid.y1);
	rect.right = static_cast<float>(grid.x2);
	rect.bottom = static_cast<float>(grid.y2);
	
	if (grid.sz)
	{
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
		pRenderTarget->DrawRectangle(rect, Brush, 2);
		for (size_t i = 0; i < edit.c.size(); i++) text[i] = edit.c[i];
		char w[10];
		for (int j = 0; j < 10; j++) w[j] = ' ';
		for (size_t j = 0; j < edit.c.size(); j++) w[j] = edit.c[j];
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
	for (size_t n = 0; n < hossz; n++) text[n] = origo.t[n];
	pRenderTarget->DrawText(text, static_cast<UINT32>(hossz), TF1, origo, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

void MainWindow::Origo_athelyez()
{
	float x1 = -xx;
	float y1 = -yy;
	for (size_t i = 0; i < VONAL_vector.size(); i++)
	{
		VONAL_vector[i].x1 += x1;
		VONAL_vector[i].x2 += x1;
		VONAL_vector[i].y1 += y1;
		VONAL_vector[i].y2 += y1;
	}
	for (size_t i = 0; i < ARC_vector.size(); i++)
	{
		ARC_vector[i].kpx += x1;
		ARC_vector[i].kpy += y1;
		ARC_vector[i].xk += x1;
		ARC_vector[i].yk += y1;
		ARC_vector[i].xv += x1;
		ARC_vector[i].yv += y1;
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
	for (size_t i = 0; i < POLIGON_vector.size(); i++)
	{
		for (size_t j = 0; j < POLIGON_vector[i].pont.size(); j++)
		{
			POLIGON_vector[i].pont[j].x += x1;
			POLIGON_vector[i].pont[j].y += y1;
		}
		SafeRelease(&POLIGON_vector[i].pg);
		for (size_t j = 0; j < POLIGON_vector[i].pont.size(); j++) pontok[j] = POLIGON_vector[i].pont[j];
		pFactory->CreatePathGeometry(&POLIGON_vector[i].pg);
		ID2D1GeometrySink* pSink;
		POLIGON_vector[i].pg->Open(&pSink);
		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
		pSink->BeginFigure(POLIGON_vector[i].pont[0], D2D1_FIGURE_BEGIN_FILLED);
		pSink->AddLines(pontok, static_cast<UINT32>(POLIGON_vector[i].pont.size()));
		pSink->AddLine(POLIGON_vector[i].pont[0]);
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pSink->Close();
		SafeRelease(&pSink);
	}
	for (size_t i = 0; i < EL_vector.size(); i++)
	{
		EL_vector[i].x += x1;
		EL_vector[i].y += y1;
	}
	for (size_t i = 0; i < SQ_vector.size(); i++)
	{
		SQ_vector[i].x += x1;
		SQ_vector[i].y += y1;
	}
	for (size_t i = 0; i < RR_vector.size(); i++)
	{
		RR_vector[i].x += x1;
		RR_vector[i].y += y1;
	}
	for (size_t i = 0; i < ELVIA_vector.size(); i++)
	{
		ELVIA_vector[i].x += x1;
		ELVIA_vector[i].y += y1;
	}
	for (size_t i = 0; i < SQVIA_vector.size(); i++)
	{
		SQVIA_vector[i].x += x1;
		SQVIA_vector[i].y += y1;
	}
	for (size_t i = 0; i < RRVIA_vector.size(); i++)
	{
		RRVIA_vector[i].x += x1;
		RRVIA_vector[i].y += y1;
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
	for (int i = 0; i < static_cast<int>(GC_vector.size()); i++)
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
	Kiir("X = ", static_cast<int>(xx), rect);
	rect.left = BOX_XY.left + 100;
	rect.right = BOX_XY.right;
	Kiir("Y = ", static_cast<int>(yy), rect);
}

void MainWindow::UpdateDialogContents()
{
	WCHAR base[MAX_PATH];
	if (dialog_path[0] == 0)
		swprintf_s(base, L"%c:\\", drivers[dialog.kkd].ch);
	else
		swprintf_s(base, L"%c:\\%s", drivers[dialog.kkd].ch, dialog_path);

	WCHAR pattern[MAX_PATH];
	swprintf_s(pattern, L"%s*.*", base);

	if (dialog.dirchange)
	{
		File_vector.clear();
		dialog.lastEnumError = 0;
		// Csak ha a meghajtó ready
		if (IsDriveReady(drivers[dialog.kkd].ch))
		{
			dialog.hFind = FindFirstFileW(pattern, &dialog.FindFileData);
			if (dialog.hFind != INVALID_HANDLE_VALUE)
			{
				do {
					if (wcscmp(dialog.FindFileData.cFileName, L".") == 0)
						continue;
					File_vector.push_back(dialog.FindFileData);
				} while (FindNextFileW(dialog.hFind, &dialog.FindFileData));
				FindClose(dialog.hFind);
			}
			else
			{
				dialog.lastEnumError = GetLastError();
			}
		}
		else
		{
			dialog.lastEnumError = ERROR_NOT_READY;
		}

		Microsoft::WRL::ComPtr<IDWriteTextLayout> layout;
		pDWriteFactory->CreateTextLayout(
			dialog.edit.c.c_str(),
			(UINT32)dialog.edit.c.length(),
			TF2,
			dialog.edit.right - dialog.edit.left,   // elérhető szélesség
			10000.0f,                               // nagy magasság, hogy elférjen
			&layout
		);

		DWRITE_TEXT_METRICS m = {};
		layout->GetMetrics(&m);

		// Sorok száma:
		UINT32 lines = (m.lineCount > 0) ? m.lineCount : 1;

		// Új magasság: a DirectWrite által számolt teljes magasság
		float newHeight = std::ceil(m.height);

		// (opcionálisan limitáld max N sorra)
		const UINT32 maxLines = 3; // pl. 3 sort engedünk
		if (lines > maxLines) {
			float perLine = m.height / lines;
			newHeight = std::ceil(perLine * maxLines);
		}

		dialog.edit.bottom = dialog.edit.top + newHeight;

	}

	if (dialog.ini)
	{
		dialog.sb.isHover = false;
		//size_t TF = 20;
		size_t fileN = File_vector.size();
		size_t helyN = (size_t)((dialog.client.bottom - dialog.client.top) / sorMag);

		if (fileN == 0)
		{
			NN = 0;
			dialog.out_N = 0;
			dialog.sb.length = 0;
			dialog.sb.posMin = dialog.sb.posMax = dialog.sb.pos = dialog.sb.top;
			dialog.sb.range = 1;
		}
		else
		{
			if (helyN < fileN) { NN = helyN; dialog.sb.isHover = true; dialog.out_N = (int)(fileN - helyN); }
			else { NN = fileN; dialog.out_N = 0; }
			float arany = (float)helyN / (float)fileN;
			dialog.sb.length = arany * (dialog.client.bottom - dialog.client.top);
			dialog.sb.posMin = dialog.sb.pos = dialog.sb.top + 3;

			if (fileN > 1)
			{
				if (dialogSortMode == DIALOG_SORT_DIR_FIRST)
				{
					std::sort(File_vector.begin(), File_vector.end(),
						[](const WIN32_FIND_DATAW &a, const WIN32_FIND_DATAW &b)
						{
							bool ad = (a.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
							bool bd = (b.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
							if (ad != bd) return ad > bd; // könyvtárak előre
							return _wcsicmp(a.cFileName, b.cFileName) < 0;
						});
				}
				else // DIALOG_SORT_MIXED
				{
					std::sort(File_vector.begin(), File_vector.end(),
						[](const WIN32_FIND_DATAW &a, const WIN32_FIND_DATAW &b)
						{
							return _wcsicmp(a.cFileName, b.cFileName) < 0;
						});
				}
			}
		}
		/*if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (dialogSortMode == DIALOG_SORT_DIR_FIRST)
			{
				// Régi: <DIR> előtag
				for (size_t n = 0; n < prefixLen; n++) sorBuf[n] = dirPrefix[n];
				for (size_t n = 0; n < nameLen && (n + prefixLen) < 255; n++)
					sorBuf[prefixLen + n] = fname[n];
				size_t total = prefixLen + nameLen;
				if (total > 255) total = 255;
				pRenderTarget->DrawText(sorBuf, (UINT32)total, TF2_dir, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
			}
			else
			{
				// Kevert mód: név + <DIR> utótag
				size_t maxLen = 255;
				size_t n = (nameLen > maxLen) ? maxLen : nameLen;
				for (size_t k = 0; k < n; ++k) sorBuf[k] = fname[k];
				const wchar_t tag[] = L"  <DIR>";
				size_t tagLen = wcslen(tag);
				size_t total = n;
				for (size_t k = 0; k < tagLen && total < maxLen; ++k) sorBuf[total++] = tag[k];
				pRenderTarget->DrawText(sorBuf, (UINT32)total, TF2_dir, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
			}
		}
		else
		{
			pRenderTarget->DrawText(fname, (UINT32)nameLen, TF2, rect, Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		}*/
		dialog.ini = false;
	}
}