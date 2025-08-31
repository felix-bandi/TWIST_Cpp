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

void MainWindow::alk_krv_rajzol(int alk)
{
	ALKATRESZ a = Alkatresz[alk];
	for (int k = 0; k <= 1; k++)
	{
		if (a.v.size() > 0)
			for (size_t i = 0; i < a.v.size(); i++)
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
					pRenderTarget->DrawEllipse(ellipse, feher, 1);
					rx = ry = e.r * nagyitas;
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->FillEllipse(ellipse, fekete);
					pRenderTarget->DrawEllipse(ellipse, feher, 1);
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
					pRenderTarget->DrawRectangle(rect, feher);
					rx = ry = s.r * nagyitas;
					f1.x = (s.x + eltolas.x + xx) * nagyitas;
					f1.y = (s.y + eltolas.y + yy) * nagyitas;
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->FillEllipse(ellipse, fekete);
					pRenderTarget->DrawEllipse(ellipse, feher, 1);
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
					pRenderTarget->DrawRoundedRectangle(rrect, feher);
					rx = ry = r.r * nagyitas;
					f1.x = (r.x + eltolas.x + xx) * nagyitas;
					f1.y = (r.y + eltolas.y + yy) * nagyitas;
					ellipse = D2D1::Ellipse(f1, rx, ry);
					pRenderTarget->FillEllipse(ellipse, fekete);
					pRenderTarget->DrawEllipse(ellipse, feher, 1);
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
			pRenderTarget->DrawEllipse(ellipse, feher, 1);
			rx = ry = e.r * nagyitas;
			ellipse = D2D1::Ellipse(f1, rx, ry);
			pRenderTarget->FillEllipse(ellipse, fekete);
			pRenderTarget->DrawEllipse(ellipse, feher, 1);
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

void MainWindow::alk_letesz(int alk)
{
	ALKATRESZ a = Alkatresz[alk];
	if (a.v.size() > 0)
		for (int i = 0; i < a.v.size(); i++)
		{
			vonal.x1 = a.v[i].x1 + xx;
			vonal.y1 = a.v[i].y1 + yy;
			vonal.x2 = a.v[i].x2 + xx;
			vonal.y2 = a.v[i].y2 + yy;
			vonal.v = a.v[i].v;
			vonal.szint = a.v[i].szint;
			vonal.alk = alk_sz;
			vonal.blokk = 0;
			VONAL_vector.push_back(vonal);
		}
	if (a.a.size() > 0)
		for (int i = 0; i < a.a.size(); i++)
		{
			arc.alk = alk_sz;
			arc.blokk = 0;
			arc.i = a.a[i].i;
			arc.kpx = a.a[i].kpx + xx;
			arc.kpy = a.a[i].kpy + yy;
			arc.ksz = a.a[i].ksz;
			arc.rx = a.a[i].rx;
			arc.ry = a.a[i].ry;
			arc.s = a.a[i].s;
			arc.szint = a.a[i].szint;
			arc.v = a.a[i].v;
			arc.vsz = a.a[i].vsz;
			arc.xk = a.a[i].xk + xx;
			arc.yk = a.a[i].yk + yy;
			arc.xv = a.a[i].xv + xx;
			arc.yv = a.a[i].yv + yy;
			ARC_vector.push_back(arc);
			ARC_rajzol(ARC_vector);
		}
	if (a.p.size() > 0)
		for (int i = 0; i < a.p.size(); i++)
		{
			poli.alk = alk_sz;
			poli.szint = a.p[i].szint;
			poli.blokk = a.p[i].blokk;
			poli.pont.clear();
			for (int j = 0; j < a.p[i].pont.size(); j++)
			{
				p.x = a.p[i].pont[j].x + xx;
				p.y = a.p[i].pont[j].y + yy;
				poli.pont.push_back(p);
				pontok[j] = p;
			}
			POLIGON_vector.push_back(poli);
			POLIGON_rajzol(POLIGON_vector);
			poligon.clear();
		}
	if (a.ep.size() > 0)
		for (int i = 0; i < a.ep.size(); i++)
		{
			el.x = a.ep[i].x + xx;
			el.y = a.ep[i].y + yy;
			el.rx = a.ep[i].rx;
			el.ry = a.ep[i].ry;
			el.r = a.ep[i].r;
			el.szint = a.ep[i].szint;
			el.blokk = 0;
			el.alk = alk_sz;
			EL_vector.push_back(el);
		}
	if (a.sp.size() > 0)
		for (int i = 0; i < a.sp.size(); i++)
		{
			sq.x = a.sp[i].x + xx;
			sq.y = a.sp[i].y + yy;
			sq.rx = a.sp[i].rx;
			sq.ry = a.sp[i].ry;
			sq.r = a.sp[i].r;
			sq.szint = a.sp[i].szint;
			sq.blokk = a.sp[i].blokk;
			sq.alk = alk_sz;
			SQ_vector.push_back(sq);
		}
	if (a.rp.size() > 0)
		for (int i = 0; i < a.rp.size(); i++)
		{
			rr.x = a.rp[i].x + xx;
			rr.y = a.rp[i].y + yy;
			rr.rx = a.rp[i].rx;
			rr.ry = a.rp[i].ry;
			rr.rrx = a.rp[i].rrx;
			rr.rry = a.rp[i].rry;
			rr.r = a.rp[i].r;
			rr.szint = a.rp[i].szint;
			rr.blokk = 0;
			rr.alk = alk_sz;
			RR_vector.push_back(rr);
		}
	if (a.ev.size() > 0)
		for (int i = 0; i < a.ev.size(); i++)
		{
			ev.x = a.ev[i].x + xx;
			ev.y = a.ev[i].y + yy;
			ev.rx = a.ev[i].rx;
			ev.ry = a.ev[i].ry;
			ev.r = a.ev[i].r;
			ev.blokk = 0;
			ev.alk = alk_sz;
			ELVIA_vector.push_back(ev);
		}
	if (a.sv.size() > 0)
		for (int i = 0; i < a.sv.size(); i++)
		{
			sv.x = a.sv[i].x + xx;
			sv.y = a.sv[i].y + yy;
			sv.rx = a.sv[i].rx;
			sv.ry = a.sv[i].ry;
			sv.r = a.sv[i].r;
			sv.blokk = 0;
			sv.alk = alk_sz;
			SQVIA_vector.push_back(sv);
		}
	if (a.rv.size() > 0)
		for (int i = 0; i < a.rv.size(); i++)
		{
			rv.x = a.rv[i].x + xx;
			rv.y = a.rv[i].y + yy;
			rv.rx = a.rv[i].rx;
			rv.ry = a.rv[i].ry;
			rv.rrx = a.rv[i].rrx;
			rv.rry = a.rv[i].rry;
			rv.r = a.rv[i].r;
			rv.blokk = 0;
			rv.alk = alk_sz;
			RRVIA_vector.push_back(rv);
		}
	alk_sz++;
}