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

void MainWindow::alk_krv_rajzol(int alk)
{
	ALKATRÉSZ a = Alkatrész[alk];
	for (int k = 0; k <= 1; k++)
	{
		if (a.v.size() > 0)
			for (int i = 0; i < a.v.size(); i++)
				if (a.v[i].szint == sz[k])
				{
					VONAL v = a.v[i];
					rx = v.v / 2 * nagyitas;
					ry = v.v / 2 * nagyitas;
					f1.x = (v.x1 + eltolas.x + xx) * nagyitas;
					f1.y = (v.y1 + eltolas.y + yy) * nagyitas;
					f2.x = (v.x2 + eltolas.x + xx) * nagyitas;
					f2.y = (v.y2 + eltolas.y + yy) * nagyitas;
					pRenderTarget->DrawLine(f1, f2, bv[sz[k]][k], v.v * nagyitas, pStrokeStyle);
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->DrawEllipse(ellipse, Brush, 1);
					ellipse = D2D1::Ellipse(f2, rx, ry);
					pRenderTarget->DrawEllipse(ellipse, Brush, 1);
					double a = f2.y - f1.y;
					double b = f2.x - f1.x;
					double c = sqrt(a * a + b * b);
					p1.x = f1.x - a * rx / c;
					p1.y = f1.y + b * ry / c;
					p2.x = f2.x - a * rx / c;
					p2.y = f2.y + b * ry / c;
					pRenderTarget->DrawLine(p1, p2, Brush, 1.0, pStrokeStyle);
					p1.x = f1.x + a * rx / c;
					p1.y = f1.y - b * ry / c;
					p2.x = f2.x + a * rx / c;
					p2.y = f2.y - b * ry / c;
					pRenderTarget->DrawLine(p1, p2, Brush, 1.0, pStrokeStyle);
				}
		p1.x = eltolas.x + xx;
		p1.y = eltolas.y + yy;
		sc_alk = D2D1::Matrix3x2F::Scale(nagyitas, nagyitas, D2D1::Point2F(0, 0));
		tr_alk = D2D1::Matrix3x2F::Translation(nagyitas * p1.x, nagyitas * p1.y);
		pRenderTarget->SetTransform(sc_alk * tr_alk);
		if (a.a.size() > 0)
			for (int i = 0; i < a.a.size(); i++)
				if (a.a[i].szint == sz[k])
				{
					pRenderTarget->DrawGeometry(a.a[i].pg, bv[sz[k]][k], a.a[i].v, pStrokeStyle);
				}
		if (a.p.size()>0)
			for(int i=0;i<a.p.size();i++)
				if (a.p[i].szint == sz[k])
				{
					pRenderTarget->FillGeometry(a.p[i].pg, bv[sz[k]][k]);
				}
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		if (a.ep.size() > 0)
			for (int i = 0; i < a.ep.size(); i++)
				if (a.ep[i].szint == sz[k])
				{
					EL_PAD e = a.ep[i];
					f1.x = (e.x + eltolas.x + xx) * nagyitas;
					f1.y = (e.y + eltolas.y + yy) * nagyitas;
					rx = e.rx * nagyitas;  ry = e.ry * nagyitas;
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->FillEllipse(ellipse, bp[sz[k]][k]);
					pRenderTarget->DrawEllipse(ellipse, fehér, 1);
					rx = ry = e.r * nagyitas;
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->FillEllipse(ellipse, fekete);
					pRenderTarget->DrawEllipse(ellipse, fehér, 1);
				}
		if (a.sp.size() > 0)
			for (int i = 0; i < a.sp.size(); i++)
				if (a.sp[i].szint == sz[k])
				{
					SQ_PAD s = a.sp[i];
					rx = s.rx * nagyitas;  ry = s.ry * nagyitas;
					rect.left = (s.x - s.rx + eltolas.x + xx) * nagyitas;
					rect.right = (s.x + s.rx + eltolas.x + xx) * nagyitas;
					rect.top = (s.y - s.ry + eltolas.y + yy) * nagyitas;
					rect.bottom = (s.y + s.ry + eltolas.y + yy) * nagyitas;
					pRenderTarget->FillRectangle(rect, bp[sz[k]][k]);
					pRenderTarget->DrawRectangle(rect, fehér);
					rx = ry = s.r * nagyitas;
					f1.x = (s.x + eltolas.x + xx) * nagyitas;
					f1.y = (s.y + eltolas.y + yy) * nagyitas;
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->FillEllipse(ellipse, fekete);
					pRenderTarget->DrawEllipse(ellipse, fehér, 1);
				}
		if (a.rp.size() > 0)
			for (int i = 0; i < a.rp.size(); i++)
				if (a.rp[i].szint == sz[k])
				{
					RR_PAD r = a.rp[i];
					rx = r.rx * nagyitas;  ry = r.ry * nagyitas;
					rect.left = (r.x - r.rx + eltolas.x + xx) * nagyitas;
					rect.right = (r.x + r.rx + eltolas.x + xx) * nagyitas;
					rect.top = (r.y - r.ry + eltolas.y + yy) * nagyitas;
					rect.bottom = (r.y + r.ry + eltolas.y + yy) * nagyitas;
					rrect.rect = rect;
					rrect.radiusX = r.rrx * nagyitas;  rrect.radiusY = r.rry * nagyitas;
					pRenderTarget->FillRoundedRectangle(rrect, bp[sz[k]][k]);
					pRenderTarget->DrawRoundedRectangle(rrect, fehér);
					rx = ry = r.r * nagyitas;
					f1.x = (r.x + eltolas.x + xx) * nagyitas;
					f1.y = (r.y + eltolas.y + yy) * nagyitas;
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->FillEllipse(ellipse, fekete);
					pRenderTarget->DrawEllipse(ellipse, fehér, 1);
				}
	}
	if (a.ev.size() > 0)
		for (int i = 0; i < a.ev.size(); i++)
		{
			EL_VIA e = a.ev[i];
			f1.x = (e.x + eltolas.x + xx) * nagyitas;
			f1.y = (e.y + eltolas.y + yy) * nagyitas;
			rx = e.rx * nagyitas;  ry = e.ry * nagyitas;
			ellipse = D2D1::Ellipse(f1, rx, ry);
			pRenderTarget->FillEllipse(ellipse, cyan);
			pRenderTarget->DrawEllipse(ellipse, fehér, 1);
			rx = ry = e.r * nagyitas;
			ellipse = D2D1::Ellipse(f1, rx, ry);
			pRenderTarget->FillEllipse(ellipse, fekete);
			pRenderTarget->DrawEllipse(ellipse, fehér, 1);
		}
	if (a.sv.size() > 0)
		for (int i = 0; i < a.sv.size(); i++)
		{
			SQ_VIA s = a.sv[i];
			rx = s.rx * nagyitas;  ry = s.ry * nagyitas;
			rect.left = (s.x - s.rx + eltolas.x + xx) * nagyitas;
			rect.right = (s.x + s.rx + eltolas.x + xx) * nagyitas;
			rect.top = (s.y - s.ry + eltolas.y + yy) * nagyitas;
			rect.bottom = (s.y + s.ry + eltolas.y + yy) * nagyitas;
			pRenderTarget->FillRectangle(rect, cyan);
			pRenderTarget->DrawRectangle(rect, Brush);
			rx = ry = s.r * nagyitas;
			f1.x = (s.x + eltolas.x + xx) * nagyitas;
			f1.y = (s.y + eltolas.y + yy) * nagyitas;
			ellipse = D2D1::Ellipse(f1, rx, ry);
			pRenderTarget->FillEllipse(ellipse, fekete);
			pRenderTarget->DrawEllipse(ellipse, Brush, 1);
		}
	if (a.rv.size() > 0)
		for (int i = 0; i < a.rv.size(); i++)
		{
			RR_VIA r = a.rv[i];
			rx = r.rx * nagyitas;  ry = r.ry * nagyitas;
			rect.left = (r.x - r.rx + eltolas.x + xx) * nagyitas;
			rect.right = (r.x + r.rx + eltolas.x + xx) * nagyitas;
			rect.top = (r.y - r.ry + eltolas.y + yy) * nagyitas;
			rect.bottom = (r.y + r.ry + eltolas.y + yy) * nagyitas;
			rrect.rect = rect;
			rrect.radiusX = r.rrx * nagyitas;  rrect.radiusY = r.rry * nagyitas;
			pRenderTarget->FillRoundedRectangle(rrect, cyan);
			pRenderTarget->DrawRoundedRectangle(rrect, Brush);
			rx = ry = r.r * nagyitas;
			f1.x = (r.x + eltolas.x + xx) * nagyitas;
			f1.y = (r.y + eltolas.y + yy) * nagyitas;
			ellipse = D2D1::Ellipse(f1, rx, ry);
			pRenderTarget->FillEllipse(ellipse, fekete);
			pRenderTarget->DrawEllipse(ellipse, Brush, 1);
		}
}