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
//#include <time.h>
using namespace std;
#include "TWIST_Cpp.h"

void MainWindow::VONAL_keres()
{
	boolean tl;
	tali.clear();
	for (int i = 0; i < VONAL_vector.size(); i++)
	{
		tl = false;
		alfa = atan2((VONAL_vector[i].x1 - VONAL_vector[i].x2), (VONAL_vector[i].y1 - VONAL_vector[i].y2)) + M_PI;
		beta = atan2((VONAL_vector[i].x1 - xx), (VONAL_vector[i].y1 - yy)) + M_PI;
		alfa_ = atan2((VONAL_vector[i].x2 - VONAL_vector[i].x1), (VONAL_vector[i].y2 - VONAL_vector[i].y1)) + M_PI;
		gamma = atan2((VONAL_vector[i].x2 - xx), (VONAL_vector[i].y2 - yy)) + M_PI;
		alfa = alfa - beta;
		if (alfa > M_PI) alfa -= 2 * M_PI;
		if (alfa < -M_PI) alfa += 2 * M_PI;
		alfa_ = alfa_ - gamma;
		if (alfa_ > M_PI) alfa_ -= 2 * M_PI;
		if (alfa_ < -M_PI) alfa_ += 2 * M_PI;
		h = sqrt((VONAL_vector[i].x1 - xx) * (VONAL_vector[i].x1 - xx) + (VONAL_vector[i].y1 - yy) * (VONAL_vector[i].y1 - yy));
		h_ = sqrt((VONAL_vector[i].x2 - xx) * (VONAL_vector[i].x2 - xx) + (VONAL_vector[i].y2 - yy) * (VONAL_vector[i].y2 - yy));
		if (alfa<M_PI_2 && alfa>-M_PI_2 && alfa_<M_PI_2 && alfa_>-M_PI_2)
		{
			if (VONAL_vector[i].v > sin(abs(alfa)) * h * 2) tl = true;
		}
		if (tl || VONAL_vector[i].v > 2 * h || VONAL_vector[i].v > 2 * h_) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::EL_keres()
{
	tali.clear();
	for (int i = 0; i < EL_vector.size(); i++)
	{
		hely.x = EL_vector[i].x;
		hely.y = EL_vector[i].y;
		rx = EL_vector[i].rx;
		ry = EL_vector[i].ry;
		if (rx >= ry) {
			d = sqrt(rx * rx - ry * ry);
			f1.x = hely.x + d; f1.y = hely.y;
			f2.x = hely.x - d; f2.y = hely.y;
		}
		else {
			d = sqrt(ry * ry - rx * rx);
			f1.x = hely.x; f1.y = hely.y + d;
			f2.x = hely.x; f2.y = hely.y - d;
		}
		if ((sqrt((xx - f1.x) * (xx - f1.x) + (yy - f1.y) * (yy - f1.y))
			+
			sqrt((xx - f2.x) * (xx - f2.x) + (yy - f2.y) * (yy - f2.y))) <= (2 * max(rx, ry))) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::SQ_keres()
{
	tali.clear();
	for (int i = 0; i < SQ_vector.size(); i++)
	{
		hely.x = SQ_vector[i].x;
		hely.y = SQ_vector[i].y;
		rx = SQ_vector[i].rx;
		ry = SQ_vector[i].ry;
		if ((hely.x - rx) < xx && (hely.x + rx) > xx && (hely.y - ry) < yy && (hely.y + ry) > yy) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::RR_keres()
{
	tali.clear();
	for (int i = 0; i < RR_vector.size(); i++)
	{
		hely.x = RR_vector[i].x;
		hely.y = RR_vector[i].y;
		rx = RR_vector[i].rx;
		ry = RR_vector[i].ry;
		if ((hely.x - rx) < xx && (hely.x + rx) > xx && (hely.y - ry) < yy && (hely.y + ry) > yy) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::EV_keres()
{
	tali.clear();
	for (int i = 0; i < ELVIA_vector.size(); i++)
	{
		hely.x = ELVIA_vector[i].x;
		hely.y = ELVIA_vector[i].y;
		rx = ELVIA_vector[i].rx;
		ry = ELVIA_vector[i].ry;
		if (rx >= ry) {
			d = sqrt(rx * rx - ry * ry);
			f1.x = hely.x + d; f1.y = hely.y;
			f2.x = hely.x - d; f2.y = hely.y;
		}
		else {
			d = sqrt(ry * ry - rx * rx);
			f1.x = hely.x; f1.y = hely.y + d;
			f2.x = hely.x; f2.y = hely.y - d;
		}
		if ((sqrt((xx - f1.x) * (xx - f1.x) + (yy - f1.y) * (yy - f1.y))
			+
			sqrt((xx - f2.x) * (xx - f2.x) + (yy - f2.y) * (yy - f2.y))) <= (2 * max(rx, ry))) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::SV_keres()
{
	tali.clear();
	for (int i = 0; i < SQVIA_vector.size(); i++)
	{
		hely.x = SQVIA_vector[i].x;
		hely.y = SQVIA_vector[i].y;
		rx = SQVIA_vector[i].rx;
		ry = SQVIA_vector[i].ry;
		if ((hely.x - rx) < xx && (hely.x + rx) > xx && (hely.y - ry) < yy && (hely.y + ry) > yy) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::RV_keres()
{
	tali.clear();
	for (int i = 0; i < RRVIA_vector.size(); i++)
	{
		hely.x = RRVIA_vector[i].x;
		hely.y = RRVIA_vector[i].y;
		rx = RRVIA_vector[i].rx;
		ry = RRVIA_vector[i].ry;
		if ((hely.x - rx) < xx && (hely.x + rx) > xx && (hely.y - ry) < yy && (hely.y + ry) > yy) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::POLIGON_keres()
{
    tali.clear();
    for (int i = 0; i < POLIGON_vector.size(); i++)
    {
        int n = POLIGON_vector[i].pont.size();
        int crossings = 0;
        float px = xx, py = yy;
        for (int j = 0; j < n; j++)
        {
            float x1 = POLIGON_vector[i].pont[j].x;
            float y1 = POLIGON_vector[i].pont[j].y;
            float x2 = POLIGON_vector[i].pont[(j + 1) % n].x;
            float y2 = POLIGON_vector[i].pont[(j + 1) % n].y;
            // Ellenõrizzük, hogy a vízszintes sugár metszi-e az élt
            if (((y1 > py) != (y2 > py))) {
                float intersectX = (x2 - x1) * (py - y1) / (y2 - y1 + 1e-12f) + x1;
                if (intersectX > px) crossings++;
            }
        }
        if (crossings % 2 == 1) {
            tali.push_back(i);
        }
    }
    Talalat.push_back(tali);
    POLIGON_rajzol_T();
}

void MainWindow::ARC_keres()
{
	float r, dx, dy, sz, d, ksz, vsz;
	boolean f1, f2, f3, f4;
	tali.clear();
	for (int i = 0; i < ARC_vector.size(); i++)
	{
		dx = ARC_vector[i].kpx - xx; dy = ARC_vector[i].kpy - yy;
		r = sqrt(dx * dx + dy * dy);
		if (r >= (ARC_vector[i].rx - ARC_vector[i].v / 2) && r <= (ARC_vector[i].rx + ARC_vector[i].v / 2)) f1 = true; else f1 = false;
		d = ARC_vector[i].ksz + M_PI;
		ksz = -M_PI;
		vsz = ARC_vector[i].vsz - d;
		if (vsz < ksz) vsz += 2 * M_PI;
		sz = atan2(dx, dy) - d; //flo1 = atan2(dx, dy);
		if (sz < -M_PI) sz += 2 * M_PI;
		if (sz > M_PI) sz -= 2 * M_PI;
		if (sz > ksz && sz < vsz) f2 = true; else f2 = false;
		if (ARC_vector[i].i == D2D1_SWEEP_DIRECTION_CLOCKWISE) f2 = ~f2;
		h = sqrt((ARC_vector[i].xk - xx) * (ARC_vector[i].xk - xx) + (ARC_vector[i].yk - yy) * (ARC_vector[i].yk - yy));
		h_ = sqrt((ARC_vector[i].xv - xx) * (ARC_vector[i].xv - xx) + (ARC_vector[i].yv - yy) * (ARC_vector[i].yv - yy));
		if (h < ARC_vector[i].v / 2) f3 = true; else f3 = false;
		if (h_ < ARC_vector[i].v / 2) f4 = true; else f4 = false;
		if (f1 && f2 || f3 || f4) tali.push_back(i);
	}
	Talalat.push_back(tali);
}

void MainWindow::ALAK_keres()
{
	ALAK_k = -1;
	for (size_t i = 0; i < ALAK_vector.size(); i++)
	{
		if ((BOX_ALAK.left <= mouse.x) && (BOX_ALAK.right >= mouse.x) &&
			((ALAK_vector[i].y1 + BOX_ALAK.top) <= mouse.y) && ((ALAK_vector[i].y2 + BOX_ALAK.top) >= mouse.y))
			ALAK_k = i;
	}
}

void MainWindow::MODE_keres()
{
	MODE_k = -1;
	for (int i = 0; i < MODE_vector.size(); i++)
	{
		if ((BOX_MODE.left <= mouse.x) && (BOX_MODE.right >= mouse.x) &&
			((MODE_vector[i].y1 + BOX_MODE.top) <= mouse.y) && ((MODE_vector[i].y2 + BOX_MODE.top) >= mouse.y))
			MODE_k = i;
	}
}

void MainWindow::FILE_keres()
{
	FILE_k = -1;
	for (int i = 0; i < FILE_vector.size(); i++)
	{
		if ((BOX_FILE.left <= mouse.x) && (BOX_FILE.right >= mouse.x) &&
			((FILE_vector[i].y1 + BOX_FILE.top) <= mouse.y) && ((FILE_vector[i].y2 + BOX_FILE.top) >= mouse.y))
			FILE_k = i;
	}
}

void MainWindow::SZINT_keres()
{
	SZINT_k = -1;
	int mx = mouse.x - BOX_SZINT.left;
	int my = mouse.y - BOX_SZINT.top;
	for (int i = 0; i < SZINT_vector.size(); i++)
	{
		if (SZINT_vector[i].x1 <= mx && SZINT_vector[i].x2 >= mx && SZINT_vector[i].y1 <= my && SZINT_vector[i].y2 >= my)
			SZINT_k = i;
	}
}

void MainWindow::XY_keres()
{
	XY_k = false;
	if (BOX_XY.left <= mouse.x && BOX_XY.right >= mouse.x && BOX_XY.top <= mouse.y && BOX_XY.bottom >= mouse.y) XY_k = true;
}

void MainWindow::CUSTOM_keres()
{
	grid.k = false;
	if ((grid.x1 <= mouse.x) && (grid.x2 >= mouse.x) && (grid.y1 <= mouse.y) && (grid.y2 >= mouse.y)) grid.k = true;
	origo.k = false;
	if ((origo.left <= mouse.x) && (origo.right >= mouse.x) && (origo.top <= mouse.y) && (origo.bottom >= mouse.y)) origo.k = true;
	BOX_CUSTOM_k = false;
	if ((BOX_CUSTOM.left <= mouse.x) && (BOX_CUSTOM.right >= mouse.x) &&
		(BOX_CUSTOM.top <= mouse.y) && (BOX_CUSTOM.bottom >= mouse.y))
	{
		BOX_CUSTOM_k = true;
		for (int i = 0; i < CUSTOM_vector.size(); i++)
			if (((CUSTOM_vector[i].y1 + BOX_CUSTOM.top + 3) <= mouse.y) && ((CUSTOM_vector[i].y2 + BOX_CUSTOM.top) >= mouse.y))
				CUSTOM_vector[i].k = true;
			else CUSTOM_vector[i].k = false;
	}
	else for (int i = 0; i < CUSTOM_vector.size(); i++) CUSTOM_vector[i].k = false;
}

void MainWindow::GC_keres()
{
	BOX_GC_k = false; GC_k = -1;
	if ((BOX_GC.left <= mouse.x) && (BOX_GC.right >= mouse.x) &&
		(BOX_GC.top <= mouse.y) && (BOX_GC.bottom >= mouse.y))
	{
		BOX_GC_k = true;
		for (size_t i = 0; i < GC_vector.size(); i++)
		{
			dx = mouse.x - GC_vector[i].x - BOX_GC.left;
			dy = mouse.y - GC_vector[i].y - BOX_GC.top;
			if (GC_vector[i].r >= sqrt(dx * dx + dy * dy))
				GC_k = i;
		}
	}
}

void MainWindow::Blokk_szamol()
{
	VONAL v;
	float ksz, vsz, kpx, kpy, r, va, xk, yk, xv, yv;
	vanrajz = false;
	for (int k = 0; k < VONAL_vector.size(); k++)
		if (VONAL_vector[k].blokk == 0)
		{
			rect.bottom = max(VONAL_vector[k].y1, VONAL_vector[k].y2) + VONAL_vector[k].v / 2;
			rect.top = min(VONAL_vector[k].y1, VONAL_vector[k].y2) - VONAL_vector[k].v / 2;
			rect.right = max(VONAL_vector[k].x1, VONAL_vector[k].x2) + VONAL_vector[k].v / 2;
			rect.left = min(VONAL_vector[k].x1, VONAL_vector[k].x2) - VONAL_vector[k].v / 2;
			vanrajz = true;
		}
	for (int k = 0; k < ARC_vector.size(); k++)
		if (ARC_vector[k].blokk == 0)
		{
			rect.bottom = max(ARC_vector[k].yk, ARC_vector[k].yv) + ARC_vector[k].v / 2;
			rect.top = min(ARC_vector[k].yk, ARC_vector[k].yv) - ARC_vector[k].v / 2;
			rect.right = max(ARC_vector[k].xk, ARC_vector[k].xv) + ARC_vector[k].v / 2;
			rect.left = min(ARC_vector[k].xk, ARC_vector[k].xv) - ARC_vector[k].v / 2;
			vanrajz = true;
		}
	for (int k = 0; k < POLIGON_vector.size(); k++)
		if (POLIGON_vector[k].blokk == 0)
		{
			rect.bottom = POLIGON_vector[k].pont[0].y;
			rect.top = POLIGON_vector[k].pont[0].y;
			rect.right = POLIGON_vector[k].pont[0].x;
			rect.left = POLIGON_vector[k].pont[0].x;
			vanrajz = true;
		}
	for (int k = 0; k < EL_vector.size(); k++)
		if (EL_vector[k].blokk == 0)
		{
			rect.bottom = EL_vector[k].y + EL_vector[k].ry;
			rect.top = EL_vector[k].y - EL_vector[k].ry;
			rect.right = EL_vector[k].x + EL_vector[k].rx;
			rect.left = EL_vector[k].x - EL_vector[k].rx;
			vanrajz = true;
		}
	for (int k = 0; k < SQ_vector.size(); k++)
		if (SQ_vector[k].blokk == 0)
		{
			rect.bottom = SQ_vector[k].y + SQ_vector[k].ry;
			rect.top = SQ_vector[k].y - SQ_vector[k].ry;
			rect.right = SQ_vector[k].x + SQ_vector[k].rx;
			rect.left = SQ_vector[k].x - SQ_vector[k].rx;
			vanrajz = true;
		}
	for (int k = 0; k < RR_vector.size(); k++)
		if (RR_vector[k].blokk == 0)
		{
			rect.bottom = RR_vector[k].y + RR_vector[k].ry;
			rect.top = RR_vector[k].y - RR_vector[k].ry;
			rect.right = RR_vector[k].x + RR_vector[k].rx;
			rect.left = RR_vector[k].x - RR_vector[k].rx;
			vanrajz = true;
		}
	for (int k = 0; k < ELVIA_vector.size(); k++)
		if (ELVIA_vector[k].blokk == 0)
		{
			rect.bottom = ELVIA_vector[k].y + ELVIA_vector[k].ry;
			rect.top = ELVIA_vector[k].y - ELVIA_vector[k].ry;
			rect.right = ELVIA_vector[k].x + ELVIA_vector[k].rx;
			rect.left = ELVIA_vector[k].x - ELVIA_vector[k].rx;
			vanrajz = true;
		}
	for (int k = 0; k < SQVIA_vector.size(); k++)
		if (SQVIA_vector[k].blokk == 0)
		{
			rect.bottom = SQVIA_vector[k].y + SQVIA_vector[k].ry;
			rect.top = SQVIA_vector[k].y - SQVIA_vector[k].ry;
			rect.right = SQVIA_vector[k].x + SQVIA_vector[k].rx;
			rect.left = SQVIA_vector[k].x - SQVIA_vector[k].rx;
			vanrajz = true;
		}
	for (int k = 0; k < RRVIA_vector.size(); k++)
		if (RRVIA_vector[k].blokk == 0)
		{
			rect.bottom = RRVIA_vector[k].y + RRVIA_vector[k].ry;
			rect.top = RRVIA_vector[k].y - RRVIA_vector[k].ry;
			rect.right = RRVIA_vector[k].x + RRVIA_vector[k].rx;
			rect.left = RRVIA_vector[k].x - RRVIA_vector[k].rx;
			vanrajz = true;
		}
	if (Blokk.size() > 0)
	{
		Blokk[0].bottom = rect.bottom;
		Blokk[0].top = rect.top;
		Blokk[0].right = rect.right;
		Blokk[0].left = rect.left;
	}
	if (vanrajz && Blokk.size() == 0) Blokk.push_back(rect);
	for (int i = 0; i < Blokk.size(); i++)
	{
		if (vanrajz)
		{
			BOOLEAN k1, k2, k3, k4;
			float vsz2, sz;
			for (int j = 0; j < VONAL_vector.size(); j++)
				if (VONAL_vector[j].blokk == i)
				{
					v = VONAL_vector[j];
					if (Blokk[i].bottom < (v.y1 + v.v / 2)) Blokk[i].bottom = v.y1 + v.v / 2;
					if (Blokk[i].bottom < (v.y2 + v.v / 2)) Blokk[i].bottom = v.y2 + v.v / 2;
					if (Blokk[i].right < (v.x1 + v.v / 2)) Blokk[i].right = v.x1 + v.v / 2;
					if (Blokk[i].right < (v.x2 + v.v / 2)) Blokk[i].right = v.x2 + v.v / 2;
					if (Blokk[i].top > (v.y1 - v.v / 2)) Blokk[i].top = v.y1 - v.v / 2;
					if (Blokk[i].top > (v.y2 - v.v / 2)) Blokk[i].top = v.y2 - v.v / 2;
					if (Blokk[i].left > (v.x1 - v.v / 2)) Blokk[i].left = v.x1 - v.v / 2;
					if (Blokk[i].left > (v.x2 - v.v / 2)) Blokk[i].left = v.x2 - v.v / 2;
				}
			for (int j = 0; j < ARC_vector.size(); j++)
				if (ARC_vector[j].blokk == i)
				{
					ksz = ARC_vector[j].ksz;
					vsz = ARC_vector[j].vsz;
					kpx = ARC_vector[j].kpx;
					kpy = ARC_vector[j].kpy;
					r = ARC_vector[j].rx;
					va = ARC_vector[j].v / 2;
					xk = ARC_vector[j].xk;
					yk = ARC_vector[j].yk;
					xv = ARC_vector[j].xv;
					yv = ARC_vector[j].yv;
					k1 = k2 = k3 = k4 = false;
					if (ARC_vector[j].i)
					{
						if (vsz < ksz) vsz2 = vsz; else vsz2 = vsz - 2 * M_PI;
						if (ksz > -M_PI_2) sz = -M_PI_2; else sz = -2 * M_PI - M_PI_2;
						if (vsz2 < sz) k1 = true;
						if (ksz > 0) sz = 0; else sz = -2 * M_PI;
						if (vsz2 < sz) k2 = true;
						if (ksz > M_PI_2) sz = M_PI_2; else sz = -2 * M_PI + M_PI_2;
						if (vsz2 < sz) k3 = true;
						if (vsz2 < -M_PI) k4 = true;
					}
					else
					{
						if (vsz > ksz) vsz2 = vsz; else vsz2 = vsz + 2 * M_PI;
						if (ksz < -M_PI_2) sz = -M_PI_2; else sz = 2 * M_PI - M_PI_2;
						if (vsz2 > sz) k1 = true;
						if (ksz < 0) sz = 0; else sz = 2 * M_PI;
						if (vsz2 > sz) k2 = true;
						if (ksz < M_PI_2) sz = M_PI_2; else sz = 2 * M_PI + M_PI_2;
						if (vsz2 > sz) k3 = true;
						if (vsz2 > -M_PI) k4 = true;
					}
					if (k1 && Blokk[i].right < (kpx + r + va)) Blokk[i].right = kpx + r + va;
					if (k2 && Blokk[i].top > (kpy - r - va)) Blokk[i].top = kpy - r - va;
					if (k3 && Blokk[i].left > (kpx - r - va)) Blokk[i].left = kpx - r - va;
					if (k4 && Blokk[i].bottom < (kpy + r + va)) Blokk[i].bottom = kpy + r + va;

					if (Blokk[i].right < (max(xk, xv) + va)) Blokk[i].right = max(xk, xv) + va;
					if (Blokk[i].top > (min(yk, yv) - va)) Blokk[i].top = min(yk, yv) - va;
					if (Blokk[i].left > (min(xk, xv) - va)) Blokk[i].left = min(xk, xv) - va;
					if (Blokk[i].bottom < (max(yk, yv) + va)) Blokk[i].bottom = max(yk, yv) + va;
				}
			for (int j = 0; j < POLIGON_vector.size(); j++)
				if (POLIGON_vector[j].blokk == i)
					for (int k = 0; k < POLIGON_vector[j].pont.size(); k++)
					{
						if (Blokk[i].bottom < POLIGON_vector[j].pont[k].y)Blokk[i].bottom = POLIGON_vector[j].pont[k].y;
						if (Blokk[i].top > POLIGON_vector[j].pont[k].y)Blokk[i].top = POLIGON_vector[j].pont[k].y;
						if (Blokk[i].right < POLIGON_vector[j].pont[k].x)Blokk[i].right = POLIGON_vector[j].pont[k].x;
						if (Blokk[i].left > POLIGON_vector[j].pont[k].x)Blokk[i].left = POLIGON_vector[j].pont[k].x;
					}
			for (int j = 0; j < EL_vector.size(); j++)
				if (EL_vector[j].blokk == i)
				{
					if (Blokk[i].bottom < EL_vector[j].y + EL_vector[j].ry) Blokk[i].bottom = EL_vector[j].y + EL_vector[j].ry;
					if (Blokk[i].top > EL_vector[j].y - EL_vector[j].ry) Blokk[i].top = EL_vector[j].y - EL_vector[j].ry;
					if (Blokk[i].right < EL_vector[j].x + EL_vector[j].rx) Blokk[i].right = EL_vector[j].x + EL_vector[j].rx;
					if (Blokk[i].left > EL_vector[j].x - EL_vector[j].rx) Blokk[i].left = EL_vector[j].x - EL_vector[j].rx;
				}
			for (int j = 0; j < SQ_vector.size(); j++)
				if (SQ_vector[j].blokk == i)
				{
					if (Blokk[i].bottom < SQ_vector[j].y + SQ_vector[j].ry) Blokk[i].bottom = SQ_vector[j].y + SQ_vector[j].ry;
					if (Blokk[i].top > SQ_vector[j].y - SQ_vector[j].ry) Blokk[i].top = SQ_vector[j].y - SQ_vector[j].ry;
					if (Blokk[i].right < SQ_vector[j].x + SQ_vector[j].rx) Blokk[i].right = SQ_vector[j].x + SQ_vector[j].rx;
					if (Blokk[i].left > SQ_vector[j].x - SQ_vector[j].rx) Blokk[i].left = SQ_vector[j].x - SQ_vector[j].rx;
				}
			for (int j = 0; j < RR_vector.size(); j++)
				if (RR_vector[j].blokk == i)
				{
					if (Blokk[i].bottom < RR_vector[j].y + RR_vector[j].ry) Blokk[i].bottom = RR_vector[j].y + RR_vector[j].ry;
					if (Blokk[i].top > RR_vector[j].y - RR_vector[j].ry) Blokk[i].top = RR_vector[j].y - RR_vector[j].ry;
					if (Blokk[i].right < RR_vector[j].x + RR_vector[j].rx) Blokk[i].right = RR_vector[j].x + RR_vector[j].rx;
					if (Blokk[i].left > RR_vector[j].x - RR_vector[j].rx) Blokk[i].left = RR_vector[j].x - RR_vector[j].rx;
				}
			for (int j = 0; j < ELVIA_vector.size(); j++)
				if (ELVIA_vector[j].blokk == i)
				{
					if (Blokk[i].bottom < ELVIA_vector[j].y + ELVIA_vector[j].ry) Blokk[i].bottom = ELVIA_vector[j].y + ELVIA_vector[j].ry;
					if (Blokk[i].top > ELVIA_vector[j].y - ELVIA_vector[j].ry) Blokk[i].top = ELVIA_vector[j].y - ELVIA_vector[j].ry;
					if (Blokk[i].right < ELVIA_vector[j].x + ELVIA_vector[j].rx) Blokk[i].right = ELVIA_vector[j].x + ELVIA_vector[j].rx;
					if (Blokk[i].left > ELVIA_vector[j].x - ELVIA_vector[j].rx) Blokk[i].left = ELVIA_vector[j].x - ELVIA_vector[j].rx;
				}
			for (int j = 0; j < SQVIA_vector.size(); j++)
				if (SQVIA_vector[j].blokk == i)
				{
					if (Blokk[i].bottom < SQVIA_vector[j].y + SQVIA_vector[j].ry) Blokk[i].bottom = SQVIA_vector[j].y + SQVIA_vector[j].ry;
					if (Blokk[i].top > SQVIA_vector[j].y - SQVIA_vector[j].ry) Blokk[i].top = SQVIA_vector[j].y - SQVIA_vector[j].ry;
					if (Blokk[i].right < SQVIA_vector[j].x + SQVIA_vector[j].rx) Blokk[i].right = SQVIA_vector[j].x + SQVIA_vector[j].rx;
					if (Blokk[i].left > SQVIA_vector[j].x - SQVIA_vector[j].rx) Blokk[i].left = SQVIA_vector[j].x - SQVIA_vector[j].rx;
				}
			for (int j = 0; j < RRVIA_vector.size(); j++)
				if (RRVIA_vector[j].blokk == i)
				{
					if (Blokk[i].bottom < RRVIA_vector[j].y + RRVIA_vector[j].ry) Blokk[i].bottom = RRVIA_vector[j].y + RRVIA_vector[j].ry;
					if (Blokk[i].top > RRVIA_vector[j].y - RRVIA_vector[j].ry) Blokk[i].top = RRVIA_vector[j].y - RRVIA_vector[j].ry;
					if (Blokk[i].right < RRVIA_vector[j].x + RRVIA_vector[j].rx) Blokk[i].right = RRVIA_vector[j].x + RRVIA_vector[j].rx;
					if (Blokk[i].left > RRVIA_vector[j].x - RRVIA_vector[j].rx) Blokk[i].left = RRVIA_vector[j].x - RRVIA_vector[j].rx;
				}
		}
	}
}