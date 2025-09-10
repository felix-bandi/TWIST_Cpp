#include <Windows.h>
#include <commdlg.h>   // PRINTDLG, PrintDlg, PD_*
#include <wingdi.h>
#include <windowsx.h>
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


void MainWindow::OnLButtonDown(int X, int Y, DWORD flags)
{
	flo3 = 333;
	if (ALAK_k < 0 && GC_k < 0 && !grid.k && !BOX_CUSTOM_k && MODE_k < 0 && mode == _rajzol
		&& !origo.k && !origo.kk && SZINT_k < 0 && !XY_k && !list.BOX_k)

		if (ALAK_kk >= 0)
			switch (alak)
			{
			case _vonal:
				if (!vonalfolyamatban)
				{
					krv = true;
					vonalfolyamatban = true;
					pont.x = xx;  pont.y = yy;
				}
				else
				{
					vonal.x1 = pont.x;
					vonal.y1 = pont.y;
					vonal.x2 = xx;
					vonal.y2 = yy;
					vonal.v = static_cast<float>(vonal_t[0]);
					vonal.szint = SZINT_kk;
					vonal.alk = -1;
					vonal.blokk = 0;
					VONAL_vector.push_back(vonal);
					pont.x = xx;
					pont.y = yy;
				}
				break;
			case _koriv:
				if (!arcfolyamatban)
				{
					krv = true;
					arcfolyamatban = true;
					arc.kpx = xx; arc.kpy = yy;
					arc.i = D2D1_SWEEP_DIRECTION_CLOCKWISE;
					korfazis = ketto;
				}
				else
				{
					if (korfazis == ketto)
					{
						arc.xk = xx;
						arc.yk = yy;
						arc.rx = sqrt((arc.kpx - xx) * (arc.kpx - xx) + (arc.kpy - yy) * (arc.kpy - yy));
						arc.ry = arc.rx;
						arc.ksz = atan2((arc.kpx - arc.xk), (arc.kpy - arc.yk));
						korfazis = harom;
					}
					else if (korfazis == harom)
					{
						arc.xv = av.x;
						arc.yv = av.y;
						arc.vsz = atan2((arc.kpx - arc.xv), (arc.kpy - arc.yv));
						arc.v = static_cast<float>(kor_t[0]);
						arc.blokk = 0;
						arc.szint = SZINT_kk;
						arc.alk = -1;
						ARC_vector.push_back(arc);
						ARC_rajzol(ARC_vector);
						krv = false;
						arcfolyamatban = false;
						korfazis = egy;
					}
				}
				break;
			case _poligon:
				krv = true;
				polifolyamatban = true;
				pont.x = xx;  pont.y = yy;
				poligon.push_back(pont);
				break;
			case _el_pad:
				if (!EL_folyamatban)
				{
					krv = true;
					EL_folyamatban = true;
				}
				else
				{
					el.x = xx;
					el.y = yy;
					el.rx = static_cast<float>(EL_t[0]) / 2;
					el.ry = static_cast<float>(EL_t[1]) / 2;
					el.r = static_cast<float>(EL_t[2]) / 2;
					el.szint = SZINT_kk;
					el.blokk = 0;
					el.alk = -1;
					EL_vector.push_back(el);
				}
				break;
			case _sq_pad:
				if (!SQ_folyamatban)
				{
					krv = true;
					SQ_folyamatban = true;
				}
				else
				{
					sq.x = xx;
					sq.y = yy;
					sq.rx = static_cast<float>(SQ_t[0]) / 2;
					sq.ry = static_cast<float>(SQ_t[1]) / 2;
					sq.r = static_cast<float>(SQ_t[2]) / 2;
					sq.szint = SZINT_kk;
					sq.blokk = 0;
					sq.alk = -1;
					SQ_vector.push_back(sq);
				}
				break;
			case _rr_pad:
				if (!RR_folyamatban)
				{
					krv = true;
					RR_folyamatban = true;
				}
				else
				{
					rr.x = xx;
					rr.y = yy;
					rr.rx = static_cast<float>(RR_t[0]) / 2;
					rr.ry = static_cast<float>(RR_t[1]) / 2;
					rr.rrx = static_cast<float>(RR_t[2]);
					rr.rry = static_cast<float>(RR_t[3]);
					rr.r = static_cast<float>(RR_t[4]) / 2;
					rr.szint = SZINT_kk;
					rr.blokk = 0;
					rr.alk = -1;
					RR_vector.push_back(rr);
				}
				break;
			case _el_via:
				if (!EV_folyamatban)
				{
					krv = true;
					EV_folyamatban = true;
				}
				else
				{
					ev.x = xx;
					ev.y = yy;
					ev.rx = static_cast<float>(EV_t[0]) / 2;
					ev.ry = static_cast<float>(EV_t[1]) / 2;
					ev.r = static_cast<float>(EV_t[2]) / 2;
					ev.blokk = 0;
					ev.alk = -1;
					ELVIA_vector.push_back(ev);
				}
				break;
			case _sq_via:
				if (!SV_folyamatban)
				{
					krv = true;
					SV_folyamatban = true;
				}
				else
				{
					sv.x = xx;
					sv.y = yy;
					sv.rx = static_cast<float>(SQ_t[0]) / 2;
					sv.ry = static_cast<float>(SQ_t[1]) / 2;
					sv.r = static_cast<float>(SQ_t[2]) / 2;
					sv.blokk = 0;
					sv.alk = -1;
					SQVIA_vector.push_back(sv);
				}
				break;
			case _rr_via:
				if (!RV_folyamatban)
				{
					krv = true;
					RV_folyamatban = true;
				}
				else
				{
					rv.x = xx;
					rv.y = yy;
					rv.rx = static_cast<float>(RV_t[0]) / 2;
					rv.ry = static_cast<float>(RV_t[1]) / 2;
					rv.rrx = static_cast<float>(RV_t[2]);
					rv.rry = static_cast<float>(RV_t[3]);
					rv.r = static_cast<float>(RV_t[4]) / 2;
					rv.blokk = 0;
					rv.alk = -1;
					RRVIA_vector.push_back(rv);
				}
				break;
			}
		else if (list.kk >= 0 && !krv) { krv = true; }
		else if (list.kk >= 0 && krv) { alk_letesz(list.kk); }

	Blokk_szamol();

	if (ALAK_k >= 0 && !krv)
	{
		flo3 = 22;
		switch (ALAK_k)
		{
		case 0:
			alak = _vonal; flo3 = 0;
			break;
		case 1:
			alak = _koriv;
			break;
		case 2:
			alak = _poligon;
			break;
		case 3:
			alak = _el_pad;
			break;
		case 4:
			alak = _sq_pad;
			break;
		case 5:
			alak = _rr_pad;
			break;
		case 6:
			alak = _el_via;
			break;
		case 7:
			alak = _sq_via;
			break;
		case 8:
			alak = _rr_via;
			break;
		}
		ALAK_kk = ALAK_k;
		if (ALAK_kk >= 0) list.kk = -1;
		//int3 = ALAK_kk;
	}

	if (MODE_k >= 0 && !krv)
	{
		switch (MODE_k)
		{
		case 0:
			mode = _rajzol;
			break;
		case 1:
			mode = _torol;
			break;
		case 2:
			mode = _file;
			dialog.ini = true;
			dialog.dirchange = true;
			break;
		case 3:
			mode = _print;
			ny_kep = true;
			PRINTDLG pd = { 0 };
			pd.lStructSize = sizeof(pd);
			pd.hwndOwner = m_hwnd;
			pd.Flags = PD_RETURNDC;

			static DOCINFO di = { sizeof(DOCINFO), TEXT("Test Page : Printing...") };
			if (PrintDlg(&pd) == TRUE)
			{
				hdc = pd.hDC;
				SetMapMode(hdc, MM_HIENGLISH);
				int1 = GetDeviceCaps(hdc, HORZRES);  //nyomtatási terület X
				int2 = GetDeviceCaps(hdc, VERTRES);  //nyomtatási terület Y
				int3 = GetDeviceCaps(hdc, LOGPIXELSX);
				int4 = GetDeviceCaps(hdc, LOGPIXELSY);
				flo5 = float(int1) / float(int3) * 1000;
				flo6 = float(int2) / float(int4) * 1000;
				if (flo6 / flo5 > 1.4143f) flo6 = flo5 * 1.4143f;
				int5 = int(flo5);
				int6 = int(flo6);

				StartDoc(hdc, &di);
				StartPage(hdc);
				GetClientRect(m_hwnd, &rc);
				m_pDCRT->BindDC(hdc, &rc);
				//HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
				//HBRUSH B = CreateSolidBrush(RGB(255, 255, 255));
				//HPEN Pen = CreatePen(PS_SOLID, 250, RGB(0, 0, 0));
				Nyomtat();

				EndPage(hdc);
				EndDoc(hdc);
				RestoreDC(hdc, TRUE);
			}
			break;
		}
		MODE_kk = MODE_k;
	}

	if (FILE_k >= 0 && !krv)
	{
		switch (FILE_k)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
		FILE_kk = FILE_k;
	}

	if (SZINT_k >= 0 && !krv) { SZINT_kk = SZINT_k; }

	if (origo.k && !origo.kk && !krv) origo.kk = true;
	else if (origo.kk && !krv) Origo_athelyez();

	if (dialog.k >= 0) dialog.kk = dialog.k;
	if (dialog.kd >= 0) { dialog.kkd = dialog.kd; dialog.ini = true;  dialog.dirchange = true; kiv_drv = drivers[dialog.kkd].ch; }
	if (dialog.cs.k) { dialog.cs.kk = true; dialog.cs.pp = mouse.y - dialog.cs.p; }
	if (dialog.edit.k) { dialog.edit.kk = true; dialog.edit.sz = true; }

	if (list.k >= 0 && !krv) { list.kk = list.k; if (list.kk >= 0) ALAK_kk = -1; }
	//int3 = ALAK_kk;
	if (GC_k >= 0) GC_kk = GC_k;

	if (save1.k)
	{
		for (size_t i = 0; i < dialog.edit.c.size(); i++) dialog.edit.tt[i] = dialog.edit.c[i];
		Save(alkatresz);
		//dialog.v = false;
	}
	if (grid.k && edit_sz == false)
	{
		size_t h = grid.c.size();
		edit.c.clear();
		for (size_t i = 0; i < h; i++) edit.c.push_back(grid.c[i]);
		grid.sz = true;
		edit_sz = true;
	}
	if (BOX_CUSTOM_k && edit_sz == false)
	{
		size_t s = CUSTOM[ALAK_kk].size();
		int i = 0;
		while (s >= 1)
		{
			if (CUSTOM_vector[i].k)
			{
				size_t h = CUSTOM[ALAK_kk][i].c.size();
				edit.c.clear();
				for (size_t n = 0; n < h; n++) edit.c.push_back(CUSTOM[ALAK_kk][i].c[n]);
				CUSTOM_vector[i].sz = true;
				edit_sz = true;
				custom_sz = true;
			}
			i++;
			s--;
		}
	}
	InvalidateRect(m_hwnd, nullptr, FALSE);
}

void MainWindow::OnRButtonDown(int X, int Y, DWORD flags)
{
	krv = false; flo3 = -1;
	vonalfolyamatban = false;
	arcfolyamatban = false;
	EL_folyamatban = false;
	SQ_folyamatban = false;
	RR_folyamatban = false;
	EV_folyamatban = false;
	SV_folyamatban = false;
	RV_folyamatban = false;
	edit_sz = false;
	if (polifolyamatban)
	{
		polifolyamatban = false;
		poli.pont.clear();
		for (size_t i = 0; i < poligon.size(); i++) poli.pont.push_back(poligon[i]);
		poli.blokk = 0;
		poli.szint = SZINT_kk;
		poli.alk = -1;
		POLIGON_vector.push_back(poli);
		POLIGON_rajzol(POLIGON_vector);
		poligon.clear();
		Blokk_szamol();
	}
}

void MainWindow::OnMouseMove(int X, int Y, DWORD flags)
{
	//float Xf = static_cast<float>(X);
	//float Yf = static_cast<float>(Y);
	if (flags & MK_MBUTTON)
	{
		eltolas.x += (X - mouse.x) / nagyitas;
		eltolas.y += (Y - mouse.y) / nagyitas;
	}
	mouse.x = static_cast<FLOAT>(X); mouse.y = static_cast<FLOAT>(Y);	// képernyő koordináta X/Y
	xxx = mouse.x / nagyitas - eltolas.x;			// rajz kordináta X
	yyy = mouse.y / nagyitas - eltolas.y;			// rajz kordináta Y

	//xx = ((xxx + grid.i / 2) / grid.i) * grid.i;	// rajz kordináta grid: X
	//yy = ((yyy + grid.i / 2) / grid.i) * grid.i;	// rajz kordináta grid: Y
	if (grid.i > 0) {
		const float g = static_cast<float>(grid.i);
		// legközelebbi rácspontra
		xx = std::round(xxx / g) * g;
		yy = std::round(yyy / g) * g;
		// ha mindig lefelé szeretnéd:
		// xx = std::floor(xxx / g) * g;
		// yy = std::floor(yyy / g) * g;
	}
	else {
		xx = xxx;
		yy = yyy;
	}
	mouse_grid.x = (xx + eltolas.x) * nagyitas;		// képernyő kordináta grid: X
	mouse_grid.y = (yy + eltolas.y) * nagyitas;		// képernyő kordináta grid: Y

	InvalidateRect(m_hwnd, nullptr, FALSE);
	ALAK_keres();
	GC_keres();
	CUSTOM_keres();
	MODE_keres();
	FILE_keres();
	SZINT_keres();
	XY_keres();
	if (ALAK_k >= 0 || BOX_GC_k || grid.k || BOX_CUSTOM_k || MODE_k >= 0 || XY_k || SZINT_k >= 0 || origo.k || mode == _file || list.BOX_k) SetCursor(Cursor_1);
	else SetCursor(Cursor_system);
	if (dialog.cs.kk)
	{
		float f = mouse.y - dialog.cs.pp;
		if (dialog.cs.min <= f && dialog.cs.max >= f) dialog.cs.p = f;
	}
}

void MainWindow::OnMouseWheel(int d)
{
	if (!((wheel > 1000 and d > 0) or (wheel < -1000 and d < 0)))
	{
		if (d > 1) n_sz = 1.25f; else n_sz = 0.8f;
		wheel += d;
		D2D1_POINT_2F p;
		p.x = mouse.x / nagyitas - eltolas.x;
		p.y = mouse.y / nagyitas - eltolas.y;
		nagyitas *= n_sz;
		//nagyitas = 1.0f + double(wheel) / 1500;
		//nagyitas = 0.01 * pow(double(wheel + 1200),0.5);
		eltolas.x = mouse.x / nagyitas - p.x;
		eltolas.y = mouse.y / nagyitas - p.y;
		xx = mouse.x / nagyitas - eltolas.x;
		yy = mouse.y / nagyitas - eltolas.y;
		xx = ((xx + grid.i / 2) / grid.i) * grid.i;
		yy = ((yy + grid.i / 2) / grid.i) * grid.i;
		mouse_grid.x = (xx + eltolas.x) * nagyitas;
		mouse_grid.y = (yy + eltolas.y) * nagyitas;
	}
}
