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
#include "PrintHelpers.h"

void MainWindow::Nyomtat()
{
	int x0, y0, x1, y1;
	POINT p[100] = {};

	for (size_t i = 0; i < VONAL_vector.size(); i++)
		if (VONAL_vector[i].szint == 0)
		{
			HPEN Pen = CreatePen(PS_SOLID, iroundf(VONAL_vector[i].v), RGB(0, 0, 0));
			SelectObject(hdc, Pen);
			x0 = iroundf(VONAL_vector[i].x1);
			y0 = -iroundf(VONAL_vector[i].y1);
			MoveToEx(hdc, x0, y0, NULL);
			x0 = iroundf(VONAL_vector[i].x2);
			y0 = -iroundf(VONAL_vector[i].y2);
			LineTo(hdc, x0, y0);
			DeleteObject(Pen);
		}
	for (size_t i = 0; i < ARC_vector.size(); i++)
		if (ARC_vector[i].szint == 0)
		{
			x0 = iroundf(ARC_vector[i].kpx - ARC_vector[i].rx);
			y0 = iroundf(ARC_vector[i].kpy - ARC_vector[i].ry);
			x1 = iroundf(ARC_vector[i].kpx + ARC_vector[i].rx);
			y1 = iroundf(ARC_vector[i].kpy + ARC_vector[i].ry);
			SetArcDirection(hdc, ARC_vector[i].i == D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE ? AD_COUNTERCLOCKWISE : AD_CLOCKWISE);
			HPEN Pen = CreatePen(PS_SOLID, iroundf(ARC_vector[i].v), RGB(0, 0, 0));
			Arc(hdc, x0, -y0, x1, -y1, iroundf(ARC_vector[i].xk), -iroundf(ARC_vector[i].yk),
				iroundf(ARC_vector[i].xv), -iroundf(ARC_vector[i].yv));

			DeleteObject(Pen);
		}
	HPEN Pen = CreatePen(PS_NULL, 1, 1);
	SelectObject(hdc, Pen);
	HBRUSH Brush_ny = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Brush_ny);
	for (size_t i = 0; i < POLIGON_vector.size(); i++)
		if (POLIGON_vector[i].szint == 0)
		{
			size_t c = POLIGON_vector[i].pont.size();
			for (size_t j = 0; j < c; j++)
			{
				p[j].x = iroundf(POLIGON_vector[i].pont[j].x);
				p[j].y = -iroundf(POLIGON_vector[i].pont[j].y);

			}
			Polygon(hdc, p, static_cast<int>(c));
		}
	for (size_t i = 0; i < EL_vector.size(); i++)
		if (EL_vector[i].szint == 0)
		{
			x0 = iroundf(EL_vector[i].x - EL_vector[i].rx);
			y0 = -iroundf(EL_vector[i].y - EL_vector[i].ry);
			x1 = iroundf(EL_vector[i].x + EL_vector[i].rx);
			y1 = -iroundf(EL_vector[i].y + EL_vector[i].ry);
			Ellipse(hdc, x0, y0, x1, y1);
		}
	for (size_t i = 0; i < SQ_vector.size(); i++)
		if (SQ_vector[i].szint == 0)
		{
			x0 = iroundf(SQ_vector[i].x - SQ_vector[i].rx);
			y0 = -iroundf(SQ_vector[i].y - SQ_vector[i].ry);
			x1 = iroundf(SQ_vector[i].x + SQ_vector[i].rx);
			y1 = -iroundf(SQ_vector[i].y + SQ_vector[i].ry);
			Rectangle(hdc, x0, y0, x1, y1);
		}
	for (size_t i = 0; i < RR_vector.size(); i++)
		if (RR_vector[i].szint == 0)
		{
			x0 = iroundf(RR_vector[i].x - RR_vector[i].rx);
			y0 = -iroundf(RR_vector[i].y - RR_vector[i].ry);
			x1 = iroundf(RR_vector[i].x + RR_vector[i].rx);
			y1 = -iroundf(RR_vector[i].y + RR_vector[i].ry);
			RoundRect(hdc, x0, y0, x1, y1, iroundf(RR_vector[i].rrx), iroundf(RR_vector[i].rry));
		}
	for (size_t i = 0; i < ELVIA_vector.size(); i++)
	{
		x0 = iroundf(ELVIA_vector[i].x - ELVIA_vector[i].rx);
		y0 = -iroundf(ELVIA_vector[i].y - ELVIA_vector[i].ry);
		x1 = iroundf(ELVIA_vector[i].x + ELVIA_vector[i].rx);
		y1 = -iroundf(ELVIA_vector[i].y + ELVIA_vector[i].ry);
		Ellipse(hdc, x0, y0, x1, y1);
	}
	for (size_t i = 0; i < SQVIA_vector.size(); i++)
	{
		x0 = iroundf(SQVIA_vector[i].x - SQVIA_vector[i].rx);
		y0 = -iroundf(SQVIA_vector[i].y - SQVIA_vector[i].ry);
		x1 = iroundf(SQVIA_vector[i].x + SQVIA_vector[i].rx);
		y1 = -iroundf(SQVIA_vector[i].y + SQVIA_vector[i].ry);
		Rectangle(hdc, x0, y0, x1, y1);
	}
	for (size_t i = 0; i < RRVIA_vector.size(); i++)
	{
		x0 = iroundf(RRVIA_vector[i].x - RRVIA_vector[i].rx);
		y0 = -iroundf(RRVIA_vector[i].y - RRVIA_vector[i].ry);
		x1 = iroundf(RRVIA_vector[i].x + RRVIA_vector[i].rx);
		y1 = -iroundf(RRVIA_vector[i].y + RRVIA_vector[i].ry);
		RoundRect(hdc, x0, y0, x1, y1, iroundf(RRVIA_vector[i].rrx), iroundf(RRVIA_vector[i].rry));
	}
	DeleteObject(Brush_ny);

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
	for (size_t i = 0; i < EL_vector.size(); i++)
		if (EL_vector[i].szint == 0)
		{
			x0 = iroundf(EL_vector[i].x - EL_vector[i].r);
			y0 = -iroundf(EL_vector[i].y - EL_vector[i].r);
			x1 = iroundf(EL_vector[i].x + EL_vector[i].r);
			y1 = -iroundf(EL_vector[i].y + EL_vector[i].r);
			Ellipse(hdc, x0, y0, x1, y1);
		}
	for (size_t i = 0; i < SQ_vector.size(); i++)
		if (SQ_vector[i].szint == 0)
		{
			x0 = iroundf(SQ_vector[i].x - SQ_vector[i].r);
			y0 = -iroundf(SQ_vector[i].y - SQ_vector[i].r);
			x1 = iroundf(SQ_vector[i].x + SQ_vector[i].r);
			y1 = -iroundf(SQ_vector[i].y + SQ_vector[i].r);
			Ellipse(hdc, x0, y0, x1, y1);
		}
	for (size_t i = 0; i < RR_vector.size(); i++)
		if (RR_vector[i].szint == 0)
		{
			x0 = iroundf(RR_vector[i].x - RR_vector[i].r);
			y0 = -iroundf(RR_vector[i].y - RR_vector[i].r);
			x1 = iroundf(RR_vector[i].x + RR_vector[i].r);
			y1 = -iroundf(RR_vector[i].y + RR_vector[i].r);
			Ellipse(hdc, x0, y0, x1, y1);
		}
	for (size_t i = 0; i < ELVIA_vector.size(); i++)
	{
		x0 = iroundf(ELVIA_vector[i].x - ELVIA_vector[i].r);
		y0 = -iroundf(ELVIA_vector[i].y - ELVIA_vector[i].r);
		x1 = iroundf(ELVIA_vector[i].x + ELVIA_vector[i].r);
		y1 = -iroundf(ELVIA_vector[i].y + ELVIA_vector[i].r);
		Ellipse(hdc, x0, y0, x1, y1);
	}
	for (size_t i = 0; i < SQVIA_vector.size(); i++)
	{
		x0 = iroundf(SQVIA_vector[i].x - SQVIA_vector[i].r);
		y0 = -iroundf(SQVIA_vector[i].y - SQVIA_vector[i].r);
		x1 = iroundf(SQVIA_vector[i].x + SQVIA_vector[i].r);
		y1 = -iroundf(SQVIA_vector[i].y + SQVIA_vector[i].r);
		Ellipse(hdc, x0, y0, x1, y1);
	}
	for (size_t i = 0; i < RRVIA_vector.size(); i++)
	{
		x0 = iroundf(RRVIA_vector[i].x - RRVIA_vector[i].r);
		y0 = -iroundf(RRVIA_vector[i].y - RRVIA_vector[i].r);
		x1 = iroundf(RRVIA_vector[i].x + RRVIA_vector[i].r);
		y1 = -iroundf(RRVIA_vector[i].y + RRVIA_vector[i].r);
		Ellipse(hdc, x0, y0, x1, y1);
	}
	DeleteObject(Pen);
	DeleteObject(B);
}