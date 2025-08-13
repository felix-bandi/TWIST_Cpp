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

void MainWindow::Nyomtat()
{
	int x, y, x1, y1;
	POINT p[100];

	for (int i = 0; i < VONAL_vector.size(); i++)
		if (VONAL_vector[i].szint == 0)
		{
			HPEN Pen = CreatePen(PS_SOLID, VONAL_vector[i].v, RGB(0, 0, 0));
			SelectObject(hdc, Pen);
			x = round(VONAL_vector[i].x1);
			y = -round(VONAL_vector[i].y1);
			MoveToEx(hdc, x, y, NULL);
			x = round(VONAL_vector[i].x2);
			y = -round(VONAL_vector[i].y2);
			LineTo(hdc, x, y);
			DeleteObject(Pen);
		}
	for (int i = 0; i < ARC_vector.size(); i++)
		if (ARC_vector[i].szint == 0)
		{
			x = ARC_vector[i].kpx - ARC_vector[i].rx;
			y = ARC_vector[i].kpy - ARC_vector[i].ry;
			x1 = ARC_vector[i].kpx + ARC_vector[i].rx;
			y1 = ARC_vector[i].kpy + ARC_vector[i].ry;
			SetArcDirection(hdc, AD_CLOCKWISE);
			if (ARC_vector[i].i == D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE) SetArcDirection(hdc, AD_COUNTERCLOCKWISE);
			HPEN Pen = CreatePen(PS_SOLID, ARC_vector[i].v, RGB(0, 0, 0));
			Arc(hdc, x, -y, x1, -y1, ARC_vector[i].xk, -ARC_vector[i].yk, ARC_vector[i].xv, -ARC_vector[i].yv);
			DeleteObject(Pen);
		}
	HPEN Pen = CreatePen(PS_NULL, 1, 1);
	SelectObject(hdc, Pen);
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Brush);
	for (int i = 0; i < POLIGON_vector.size(); i++)
		if (POLIGON_vector[i].szint == 0)
		{
			int c = POLIGON_vector[i].pont.size();
			for (int j = 0; j < c; j++)
			{
				p[j].x = (LONG)(POLIGON_vector[i].pont[j].x);
				p[j].y = -(LONG)(POLIGON_vector[i].pont[j].y);
			}
			Polygon(hdc, p, c);
		}
	for (int i = 0; i < EL_vector.size(); i++)
		if (EL_vector[i].szint == 0)
		{
			x = round(EL_vector[i].x - EL_vector[i].rx);
			y = -round(EL_vector[i].y - EL_vector[i].ry);
			x1 = round(EL_vector[i].x + EL_vector[i].rx);
			y1 = -round(EL_vector[i].y + EL_vector[i].ry);
			Ellipse(hdc, x, y, x1, y1);
		}
	for (int i = 0; i < SQ_vector.size(); i++)
		if (SQ_vector[i].szint == 0)
		{
			x = round(SQ_vector[i].x - SQ_vector[i].rx);
			y = -round(SQ_vector[i].y - SQ_vector[i].ry);
			x1 = round(SQ_vector[i].x + SQ_vector[i].rx);
			y1 = -round(SQ_vector[i].y + SQ_vector[i].ry);
			Rectangle(hdc, x, y, x1, y1);
		}
	for (int i = 0; i < RR_vector.size(); i++)
		if (RR_vector[i].szint == 0)
		{
			x = round(RR_vector[i].x - RR_vector[i].rx);
			y = -round(RR_vector[i].y - RR_vector[i].ry);
			x1 = round(RR_vector[i].x + RR_vector[i].rx);
			y1 = -round(RR_vector[i].y + RR_vector[i].ry);
			RoundRect(hdc, x, y, x1, y1, RR_vector[i].rrx, RR_vector[i].rry);
		}
	for (int i = 0; i < ELVIA_vector.size(); i++)
	{
		x = round(ELVIA_vector[i].x - ELVIA_vector[i].rx);
		y = -round(ELVIA_vector[i].y - ELVIA_vector[i].ry);
		x1 = round(ELVIA_vector[i].x + ELVIA_vector[i].rx);
		y1 = -round(ELVIA_vector[i].y + ELVIA_vector[i].ry);
		Ellipse(hdc, x, y, x1, y1);
	}
	for (int i = 0; i < SQVIA_vector.size(); i++)
	{
		x = round(SQVIA_vector[i].x - SQVIA_vector[i].rx);
		y = -round(SQVIA_vector[i].y - SQVIA_vector[i].ry);
		x1 = round(SQVIA_vector[i].x + SQVIA_vector[i].rx);
		y1 = -round(SQVIA_vector[i].y + SQVIA_vector[i].ry);
		Rectangle(hdc, x, y, x1, y1);
	}
	for (int i = 0; i < RRVIA_vector.size(); i++)
	{
		x = round(RRVIA_vector[i].x - RRVIA_vector[i].rx);
		y = -round(RRVIA_vector[i].y - RRVIA_vector[i].ry);
		x1 = round(RRVIA_vector[i].x + RRVIA_vector[i].rx);
		y1 = -round(RRVIA_vector[i].y + RRVIA_vector[i].ry);
		RoundRect(hdc, x, y, x1, y1, RRVIA_vector[i].rrx, RRVIA_vector[i].rry);
	}
	DeleteObject(Brush);

	/*LineTo(hdc, int5 - 1, 0);
	LineTo(hdc, int5 - 1, -int6 + 1);
	LineTo(hdc, 0, -int6 + 1);
	LineTo(hdc, 0, 0);
	MoveToEx(hdc, 1000, -1000, NULL);
	SelectObject(hdc, Brush);
	RoundRect(hdc, 200, -200, 800, -800, 100, 100);
	SelectObject(hdc, B);
	Ellipse(hdc, 450, -450, 550, -550);
	SelectObject(hdc, Pen);
	LineTo(hdc, 2000, -2000);*/

	HBRUSH B = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, B);
	for (int i = 0; i < EL_vector.size(); i++)
		if (EL_vector[i].szint == 0)
		{
			x = round(EL_vector[i].x - EL_vector[i].r);
			y = -round(EL_vector[i].y - EL_vector[i].r);
			x1 = round(EL_vector[i].x + EL_vector[i].r);
			y1 = -round(EL_vector[i].y + EL_vector[i].r);
			Ellipse(hdc, x, y, x1, y1);
		}
	for (int i = 0; i < SQ_vector.size(); i++)
		if (SQ_vector[i].szint == 0)
		{
			x = round(SQ_vector[i].x - SQ_vector[i].r);
			y = -round(SQ_vector[i].y - SQ_vector[i].r);
			x1 = round(SQ_vector[i].x + SQ_vector[i].r);
			y1 = -round(SQ_vector[i].y + SQ_vector[i].r);
			Ellipse(hdc, x, y, x1, y1);
		}
	for (int i = 0; i < RR_vector.size(); i++)
		if (RR_vector[i].szint == 0)
		{
			x = round(RR_vector[i].x - RR_vector[i].r);
			y = -round(RR_vector[i].y - RR_vector[i].r);
			x1 = round(RR_vector[i].x + RR_vector[i].r);
			y1 = -round(RR_vector[i].y + RR_vector[i].r);
			Ellipse(hdc, x, y, x1, y1);
		}
	for (int i = 0; i < ELVIA_vector.size(); i++)
	{
		x = round(ELVIA_vector[i].x - ELVIA_vector[i].r);
		y = -round(ELVIA_vector[i].y - ELVIA_vector[i].r);
		x1 = round(ELVIA_vector[i].x + ELVIA_vector[i].r);
		y1 = -round(ELVIA_vector[i].y + ELVIA_vector[i].r);
		Ellipse(hdc, x, y, x1, y1);
	}
	for (int i = 0; i < SQVIA_vector.size(); i++)
	{
		x = round(SQVIA_vector[i].x - SQVIA_vector[i].r);
		y = -round(SQVIA_vector[i].y - SQVIA_vector[i].r);
		x1 = round(SQVIA_vector[i].x + SQVIA_vector[i].r);
		y1 = -round(SQVIA_vector[i].y + SQVIA_vector[i].r);
		Ellipse(hdc, x, y, x1, y1);
	}
	for (int i = 0; i < RRVIA_vector.size(); i++)
	{
		x = round(RRVIA_vector[i].x - RRVIA_vector[i].r);
		y = -round(RRVIA_vector[i].y - RRVIA_vector[i].r);
		x1 = round(RRVIA_vector[i].x + RRVIA_vector[i].r);
		y1 = -round(RRVIA_vector[i].y + RRVIA_vector[i].r);
		Ellipse(hdc, x, y, x1, y1);
	}
	DeleteObject(Pen);
	DeleteObject(B);
}