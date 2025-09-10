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
#undef M_PI
#undef M_PI_2
#define M_PI    3.14159265358979323846f
#define M_PI_2  1.57079632679489661923f
#include <wrl.h>
using Microsoft::WRL::ComPtr;

/*void MainWindow::ARC_rajzol()
{
	int i = ARC_vector.size() - 1;
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
}*/
/*void MainWindow::ARC_rajzol(vector<ARC>& ARC)
{
	if (ARC.empty()) return; // üres védelem
	int i = ARC.size() - 1;
	pFactory->CreatePathGeometry(&ARC[i].pg);
	ID2D1GeometrySink* pSink;
	ARC[i].pg->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	ak.x = ARC[i].xk;
	ak.y = ARC[i].yk;
	av.x = ARC[i].xv;
	av.y = ARC[i].yv;
	meret.width = ARC[i].rx;
	meret.height = ARC[i].ry;
	pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
	pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, ARC[i].i, ARC[i].s));
	pSink->EndFigure(D2D1_FIGURE_END_OPEN);
	pSink->Close();
	SafeRelease(&pSink);
}*/


void MainWindow::ARC_rajzol(std::vector<ARC>& ARC)
{
	if (ARC.empty()) return;
	size_t i = ARC.size() - 1;

	ComPtr<ID2D1PathGeometry> pg;
	if (FAILED(pFactory->CreatePathGeometry(&pg))) return;

	ComPtr<ID2D1GeometrySink> sink;
	if (FAILED(pg->Open(&sink))) return;

	sink->SetFillMode(D2D1_FILL_MODE_WINDING);

	const auto startPt = D2D1::Point2F(ARC[i].xk, ARC[i].yk);
	const auto endPt = D2D1::Point2F(ARC[i].xv, ARC[i].yv);
	const auto arcSize = D2D1::SizeF(ARC[i].rx, ARC[i].ry);
	sink->BeginFigure(startPt, D2D1_FIGURE_BEGIN_HOLLOW);
	sink->AddArc(D2D1::ArcSegment(endPt, arcSize, 0.0f, ARC[i].i, ARC[i].s));
	sink->EndFigure(D2D1_FIGURE_END_OPEN);
	if (FAILED(sink->Close())) return;

	ARC[i].pg = pg.Detach();
}

/*void MainWindow::ARC_rajzol_betölt()
{
	int i = ARC_betölt.size() - 1;
	pFactory->CreatePathGeometry(&ARC_betölt[i].pg);
	ID2D1GeometrySink* pSink;
	ARC_betölt[i].pg->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	ak.x = ARC_betölt[i].xk;
	ak.y = ARC_betölt[i].yk;
	av.x = ARC_betölt[i].xv;
	av.y = ARC_betölt[i].yv;
	meret.width = ARC_betölt[i].rx;
	meret.height = ARC_betölt[i].ry;
	pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
	pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, ARC_betölt[i].i, ARC_betölt[i].s));
	pSink->EndFigure(D2D1_FIGURE_END_OPEN);
	pSink->Close();
	SafeRelease(&pSink);
}*/
void MainWindow::ARC_rajzol_2() // FIXME: 2felkoros 
{
	SafeRelease(&pPathGeometry_2);
	pFactory->CreatePathGeometry(&pPathGeometry_2);
	ID2D1GeometrySink* pSink;
	pPathGeometry_2->Open(&pSink);
	ak.x = arc.xk;
	ak.y = arc.yk;
	arc.vsz = atan2((arc.kpx - xx), (arc.kpy - yy));
	float szt = (arc.i == D2D1_SWEEP_DIRECTION_CLOCKWISE) ? (arc.ksz - arc.vsz) : (arc.vsz - arc.ksz);
	if (szt < 0) szt += 2 * M_PI;
	arc.s = (szt <= (float)M_PI) ? D2D1_ARC_SIZE_SMALL : D2D1_ARC_SIZE_LARGE;
	av.x = arc.kpx - sin(arc.vsz) * arc.rx;
	av.y = arc.kpy - cos(arc.vsz) * arc.ry;
	meret.width = arc.rx;
	meret.height = arc.ry;
	if (majdnem(ak, av))
	{
		D2D1_POINT_2F start = D2D1::Point2F(arc.kpx + rx, arc.kpy);
		D2D1_POINT_2F mid = D2D1::Point2F(arc.kpx - rx, arc.kpy);
		D2D1_POINT_2F end = start;
		pSink->BeginFigure(start, D2D1_FIGURE_BEGIN_HOLLOW);
		pSink->AddArc(D2D1::ArcSegment(
			mid,
			D2D1::SizeF(rx, ry),
			0.0f,
			D2D1_SWEEP_DIRECTION_CLOCKWISE,
			D2D1_ARC_SIZE_LARGE));

		pSink->AddArc(D2D1::ArcSegment(
			end,
			D2D1::SizeF(rx, ry),
			0.0f,
			D2D1_SWEEP_DIRECTION_CLOCKWISE,
			D2D1_ARC_SIZE_LARGE));
	}
	else
	{
		pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
		pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, arc.i, arc.s));
	}
	pSink->EndFigure(D2D1_FIGURE_END_OPEN);
	pSink->Close();
	SafeRelease(&pSink);
}
/*void MainWindow::ARC_rajzol_2()
{
	SafeRelease(&pPathGeometry_2);
	pFactory->CreatePathGeometry(&pPathGeometry_2);
	ID2D1GeometrySink* pSink;
	pPathGeometry_2->Open(&pSink);
	ak.x = arc.xk;
	ak.y = arc.yk;
	arc.vsz = atan2((arc.kpx - xx), (arc.kpy - yy));
	if (arc.i == D2D1_SWEEP_DIRECTION_CLOCKWISE) { szt = arc.ksz - arc.vsz; }
	else { szt = arc.vsz - arc.ksz; }
	if (szt < 0) szt += 2 * M_PI;
	if (szt <= M_PI) { arc.s = D2D1_ARC_SIZE_SMALL; }
	else if (szt > M_PI) { arc.s = D2D1_ARC_SIZE_LARGE; }
	av.x = arc.kpx - sin(arc.vsz) * arc.rx;
	av.y = arc.kpy - cos(arc.vsz) * arc.ry;
	meret.width = arc.rx;
	meret.height = arc.ry;
	pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
	pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, arc.i, arc.s));
	pSink->EndFigure(D2D1_FIGURE_END_OPEN);
	pSink->Close();
	SafeRelease(&pSink);
}*/

void MainWindow::POLIGON_rajzol(vector<POLI> &POLI)
{
	size_t i = POLI.size() - 1;
	pFactory->CreatePathGeometry(&POLI[i].pg);
	ID2D1GeometrySink* pSink;
	POLI[i].pg->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	pSink->BeginFigure(POLI[i].pont[0], D2D1_FIGURE_BEGIN_FILLED);
	pSink->AddLines(pontok, static_cast<UINT32>(POLI[i].pont.size()));
	pSink->AddLine(POLI[i].pont[0]);
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pSink->Close();
	SafeRelease(&pSink);
}

/*void MainWindow::POLIGON_rajzol_betölt()
{
	int i = POLIGON_betölt.size() - 1;
	for (int j = 0; j < POLIGON_betölt[i].pont.size(); j++) pontok[j] = POLIGON_betölt[i].pont[j];
	pFactory->CreatePathGeometry(&POLIGON_betölt[i].pg);
	ID2D1GeometrySink* pSink;
	POLIGON_betölt[i].pg->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	pSink->BeginFigure(POLIGON_betölt[i].pont[0], D2D1_FIGURE_BEGIN_FILLED);
	pSink->AddLines(pontok, POLIGON_betölt[i].pont.size());
	pSink->AddLine(POLIGON_betölt[i].pont[0]);
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pSink->Close();
	SafeRelease(&pSink);
}*/

void MainWindow::POLIGON_rajzol_T()
{
	SafeRelease(&pPathGeometry_5);
	pFactory->CreatePathGeometry(&pPathGeometry_5);
	ID2D1GeometrySink* pSink;
	pPathGeometry_5->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	for (size_t i = 0; i < Talalat[5].size(); i++)
	{
		for (size_t j = 0; j < POLIGON_vector[Talalat[5][i]].pont.size(); j++) pontok[j] = POLIGON_vector[Talalat[5][i]].pont[j];
		pSink->BeginFigure(POLIGON_vector[Talalat[5][i]].pont[0], D2D1_FIGURE_BEGIN_FILLED);
		pSink->AddLines(pontok, static_cast<UINT32>(POLIGON_vector[Talalat[5][i]].pont.size()));
		pSink->AddLine(POLIGON_vector[Talalat[5][i]].pont[0]);
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	}
	pSink->Close();
	SafeRelease(&pSink);
}

void MainWindow::POLIGON_rajzol_2()
{
	for (size_t i = 0; i < count; i++) pontok[i] = poligon[i];
	SafeRelease(&pPathGeometry_4);
	pFactory->CreatePathGeometry(&pPathGeometry_4);
	ID2D1GeometrySink* pSink;
	pPathGeometry_4->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	pSink->BeginFigure(poligon[0], D2D1_FIGURE_BEGIN_FILLED);
	pSink->AddLines(pontok, static_cast<UINT32>(count));
	pSink->AddLine(D2D1::Point2F(xx, yy));
	pSink->AddLine(poligon[0]);
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pSink->Close();
	SafeRelease(&pSink);
}

void MainWindow::VONAL_rajzol()
{
	for (size_t i = 0; i < VONAL_vector.size(); i++)
		if (VONAL_vector[i].szint == sz[kk])
		{
			pont0.x = (VONAL_vector[i].x1 + eltolas.x) * nagyitas;
			pont0.y = (VONAL_vector[i].y1 + eltolas.y) * nagyitas;
			pont1.x = (VONAL_vector[i].x2 + eltolas.x) * nagyitas;
			pont1.y = (VONAL_vector[i].y2 + eltolas.y) * nagyitas;
			pRenderTarget->DrawLine(pont0, pont1, bv[sz[kk]][kk], VONAL_vector[i].v * nagyitas, pStrokeStyle);
		}
}

void MainWindow::EL_rajzol()
{
	for (size_t i = 0; i < EL_vector.size(); i++)
		if (EL_vector[i].szint == sz[kk])
		{
			hely.x = (EL_vector[i].x + eltolas.x) * nagyitas;
			hely.y = (EL_vector[i].y + eltolas.y) * nagyitas;
			rx = EL_vector[i].rx * nagyitas;
			ry = EL_vector[i].ry * nagyitas;
			ellipse = D2D1::Ellipse(hely, rx, ry);
			//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
			pRenderTarget->FillEllipse(ellipse, bp[sz[kk]][kk]);
			//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
			//pRenderTarget->DrawEllipse(ellipse, Brush, 1);
		}
}

void MainWindow::SQ_rajzol()
{
	for (size_t i = 0; i < SQ_vector.size(); i++)
		if (SQ_vector[i].szint == sz[kk])
		{
			rect.left = (SQ_vector[i].x - SQ_vector[i].rx + eltolas.x) * nagyitas;
			rect.top = (SQ_vector[i].y - SQ_vector[i].ry + eltolas.y) * nagyitas;
			rect.right = (SQ_vector[i].x + SQ_vector[i].rx + eltolas.x) * nagyitas;
			rect.bottom = (SQ_vector[i].y + SQ_vector[i].ry + eltolas.y) * nagyitas;
			//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
			pRenderTarget->FillRectangle(rect, bp[sz[kk]][kk]);
			//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
			//pRenderTarget->DrawRectangle(rect, Brush, 1);
		}
}

void MainWindow::RR_rajzol()
{
	for (size_t i = 0; i < RR_vector.size(); i++)
		if (RR_vector[i].szint == sz[kk])
		{
			rect.left = (RR_vector[i].x - RR_vector[i].rx + eltolas.x) * nagyitas;
			rect.top = (RR_vector[i].y - RR_vector[i].ry + eltolas.y) * nagyitas;
			rect.right = (RR_vector[i].x + RR_vector[i].rx + eltolas.x) * nagyitas;
			rect.bottom = (RR_vector[i].y + RR_vector[i].ry + eltolas.y) * nagyitas;
			rrect.rect = rect;  rrect.radiusX = RR_vector[i].rrx * nagyitas;  rrect.radiusY = RR_vector[i].rry * nagyitas;
			//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
			pRenderTarget->FillRoundedRectangle(rrect, bp[sz[kk]][kk]);
			//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
			//pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);
		}
}
void MainWindow::EV_rajzol()
{
	for (size_t i = 0; i < ELVIA_vector.size(); i++)
	{
		hely.x = (ELVIA_vector[i].x + eltolas.x) * nagyitas;
		hely.y = (ELVIA_vector[i].y + eltolas.y) * nagyitas;
		rx = ELVIA_vector[i].rx * nagyitas;
		ry = ELVIA_vector[i].ry * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Cyan));
		pRenderTarget->FillEllipse(ellipse, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
		//pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	}
}

void MainWindow::SV_rajzol()
{
	for (size_t i = 0; i < SQVIA_vector.size(); i++)
	{
		rect.left = (SQVIA_vector[i].x - SQVIA_vector[i].rx + eltolas.x) * nagyitas;
		rect.top = (SQVIA_vector[i].y - SQVIA_vector[i].ry + eltolas.y) * nagyitas;
		rect.right = (SQVIA_vector[i].x + SQVIA_vector[i].rx + eltolas.x) * nagyitas;
		rect.bottom = (SQVIA_vector[i].y + SQVIA_vector[i].ry + eltolas.y) * nagyitas;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Cyan));
		pRenderTarget->FillRectangle(rect, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
		//pRenderTarget->DrawRectangle(rect, Brush, 1);
	}
}

void MainWindow::RV_rajzol()
{
	for (size_t i = 0; i < RRVIA_vector.size(); i++)
	{
		rect.left = (RRVIA_vector[i].x - RRVIA_vector[i].rx + eltolas.x) * nagyitas;
		rect.top = (RRVIA_vector[i].y - RRVIA_vector[i].ry + eltolas.y) * nagyitas;
		rect.right = (RRVIA_vector[i].x + RRVIA_vector[i].rx + eltolas.x) * nagyitas;
		rect.bottom = (RRVIA_vector[i].y + RRVIA_vector[i].ry + eltolas.y) * nagyitas;
		rrect.rect = rect;  rrect.radiusX = RRVIA_vector[i].rrx * nagyitas;  rrect.radiusY = RRVIA_vector[i].rry * nagyitas;
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Cyan));
		pRenderTarget->FillRoundedRectangle(rrect, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
		//pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);
	}
}
void MainWindow::EL_lyuk_rajzol()
{
	for (size_t i = 0; i < EL_vector.size(); i++)
	{
		hely.x = (EL_vector[i].x + eltolas.x) * nagyitas;
		hely.y = (EL_vector[i].y + eltolas.y) * nagyitas;
		rx = EL_vector[i].r * nagyitas;
		ry = EL_vector[i].r * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		pRenderTarget->FillEllipse(ellipse, Brush);
	}
}

void MainWindow::SQ_lyuk_rajzol()
{
	for (size_t i = 0; i < SQ_vector.size(); i++)
	{
		hely.x = (SQ_vector[i].x + eltolas.x) * nagyitas;
		hely.y = (SQ_vector[i].y + eltolas.y) * nagyitas;
		rx = SQ_vector[i].r * nagyitas;
		ry = SQ_vector[i].r * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		pRenderTarget->FillEllipse(ellipse, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));
		//pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	};
}

void MainWindow::RR_lyuk_rajzol()
{
	for (size_t i = 0; i < RR_vector.size(); i++)
	{
		hely.x = (RR_vector[i].x + eltolas.x) * nagyitas;
		hely.y = (RR_vector[i].y + eltolas.y) * nagyitas;
		rx = RR_vector[i].r * nagyitas;
		ry = RR_vector[i].r * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		pRenderTarget->FillEllipse(ellipse, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));
		//pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	};
}
void MainWindow::EV_lyuk_rajzol()
{
	for (size_t i = 0; i < ELVIA_vector.size(); i++)
	{
		hely.x = (ELVIA_vector[i].x + eltolas.x) * nagyitas;
		hely.y = (ELVIA_vector[i].y + eltolas.y) * nagyitas;
		rx = ELVIA_vector[i].r * nagyitas;
		ry = ELVIA_vector[i].r * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		pRenderTarget->FillEllipse(ellipse, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));
		//pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	};
}

void MainWindow::SV_lyuk_rajzol()
{
	for (size_t i = 0; i < SQVIA_vector.size(); i++)
	{
		hely.x = (SQVIA_vector[i].x + eltolas.x) * nagyitas;
		hely.y = (SQVIA_vector[i].y + eltolas.y) * nagyitas;
		rx = SQVIA_vector[i].r * nagyitas;
		ry = SQVIA_vector[i].r * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		pRenderTarget->FillEllipse(ellipse, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));
		//pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	};
}

void MainWindow::RV_lyuk_rajzol()
{
	for (size_t i = 0; i < RRVIA_vector.size(); i++)
	{
		hely.x = (RRVIA_vector[i].x + eltolas.x) * nagyitas;
		hely.y = (RRVIA_vector[i].y + eltolas.y) * nagyitas;
		rx = RRVIA_vector[i].r * nagyitas;
		ry = RRVIA_vector[i].r * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		pRenderTarget->FillEllipse(ellipse, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Goldenrod));
		//pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	};
}

void MainWindow::Talalat_rajzol()
{
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	for (size_t i = 0; i < Talalat[0].size(); i++)
	{
		pont0.x = (VONAL_vector[Talalat[0][i]].x1 + eltolas.x) * nagyitas;
		pont0.y = (VONAL_vector[Talalat[0][i]].y1 + eltolas.y) * nagyitas;
		pont1.x = (VONAL_vector[Talalat[0][i]].x2 + eltolas.x) * nagyitas;
		pont1.y = (VONAL_vector[Talalat[0][i]].y2 + eltolas.y) * nagyitas;
		pRenderTarget->DrawLine(pont0, pont1, Brush, VONAL_vector[Talalat[0][i]].v * nagyitas, pStrokeStyle);
	}
	for (size_t i = 0; i < Talalat[1].size(); i++)
	{
		hely.x = (EL_vector[Talalat[1][i]].x + eltolas.x) * nagyitas;
		hely.y = (EL_vector[Talalat[1][i]].y + eltolas.y) * nagyitas;
		rx = EL_vector[Talalat[1][i]].rx * nagyitas;
		ry = EL_vector[Talalat[1][i]].ry * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		pRenderTarget->FillEllipse(ellipse, Brush);
		pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	}
	for (size_t i = 0; i < Talalat[2].size(); i++)
	{
		rect.left = (SQ_vector[Talalat[2][i]].x - SQ_vector[Talalat[2][i]].rx + eltolas.x) * nagyitas;
		rect.top = (SQ_vector[Talalat[2][i]].y - SQ_vector[Talalat[2][i]].ry + eltolas.y) * nagyitas;
		rect.right = (SQ_vector[Talalat[2][i]].x + SQ_vector[Talalat[2][i]].rx + eltolas.x) * nagyitas;
		rect.bottom = (SQ_vector[Talalat[2][i]].y + SQ_vector[Talalat[2][i]].ry + eltolas.y) * nagyitas;
		pRenderTarget->FillRectangle(rect, Brush);
		pRenderTarget->DrawRectangle(rect, Brush, 1);
	}
	for (size_t i = 0; i < Talalat[3].size(); i++)
	{
		rect.left = (RR_vector[Talalat[3][i]].x - RR_vector[Talalat[3][i]].rx + eltolas.x) * nagyitas;
		rect.top = (RR_vector[Talalat[3][i]].y - RR_vector[Talalat[3][i]].ry + eltolas.y) * nagyitas;
		rect.right = (RR_vector[Talalat[3][i]].x + RR_vector[Talalat[3][i]].rx + eltolas.x) * nagyitas;
		rect.bottom = (RR_vector[Talalat[3][i]].y + RR_vector[Talalat[3][i]].ry + eltolas.y) * nagyitas;
		rrect.rect = rect;  rrect.radiusX = RR_vector[Talalat[3][i]].rrx * nagyitas;  rrect.radiusY = RR_vector[Talalat[3][i]].rry * nagyitas;
		pRenderTarget->FillRoundedRectangle(rrect, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
		pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);
	}
	sc = D2D1::Matrix3x2F::Scale(nagyitas, nagyitas, D2D1::Point2F(0, 0));
	tr = D2D1::Matrix3x2F::Translation(nagyitas * eltolas.x, nagyitas * eltolas.y);
	pRenderTarget->SetTransform(sc * tr);
	for (size_t i = 0; i < Talalat[4].size(); i++)
	{
		pRenderTarget->DrawGeometry(ARC_vector[Talalat[4][i]].pg, Brush, ARC_vector[Talalat[4][i]].v, pStrokeStyle);
	}
	for (size_t i = 0; i < Talalat[5].size(); i++)
	{
		pRenderTarget->FillGeometry(POLIGON_vector[Talalat[5][i]].pg, Brush);
	}
	//pRenderTarget->FillGeometry(pPathGeometry_5, Brush);
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	for (size_t i = 0; i < Talalat[6].size(); i++)
	{
		hely.x = (ELVIA_vector[Talalat[6][i]].x + eltolas.x) * nagyitas;
		hely.y = (ELVIA_vector[Talalat[6][i]].y + eltolas.y) * nagyitas;
		rx = ELVIA_vector[Talalat[6][i]].rx * nagyitas;
		ry = ELVIA_vector[Talalat[6][i]].ry * nagyitas;
		ellipse = D2D1::Ellipse(hely, rx, ry);
		pRenderTarget->FillEllipse(ellipse, Brush);
		pRenderTarget->DrawEllipse(ellipse, Brush, 1);
	}
	for (size_t i = 0; i < Talalat[7].size(); i++)
	{
		rect.left = (SQVIA_vector[Talalat[7][i]].x - SQVIA_vector[Talalat[7][i]].rx + eltolas.x) * nagyitas;
		rect.top = (SQVIA_vector[Talalat[7][i]].y - SQVIA_vector[Talalat[7][i]].ry + eltolas.y) * nagyitas;
		rect.right = (SQVIA_vector[Talalat[7][i]].x + SQVIA_vector[Talalat[7][i]].rx + eltolas.x) * nagyitas;
		rect.bottom = (SQVIA_vector[Talalat[7][i]].y + SQVIA_vector[Talalat[7][i]].ry + eltolas.y) * nagyitas;
		pRenderTarget->FillRectangle(rect, Brush);
		pRenderTarget->DrawRectangle(rect, Brush, 1);
	}
	for (size_t i = 0; i < Talalat[8].size(); i++)
	{
		rect.left = (RRVIA_vector[Talalat[8][i]].x - RRVIA_vector[Talalat[8][i]].rx + eltolas.x) * nagyitas;
		rect.top = (RRVIA_vector[Talalat[8][i]].y - RRVIA_vector[Talalat[8][i]].ry + eltolas.y) * nagyitas;
		rect.right = (RRVIA_vector[Talalat[8][i]].x + RRVIA_vector[Talalat[8][i]].rx + eltolas.x) * nagyitas;
		rect.bottom = (RRVIA_vector[Talalat[8][i]].y + RRVIA_vector[Talalat[8][i]].ry + eltolas.y) * nagyitas;
		rrect.rect = rect;  rrect.radiusX = RRVIA_vector[Talalat[8][i]].rrx * nagyitas;  rrect.radiusY = RRVIA_vector[Talalat[8][i]].rry * nagyitas;
		pRenderTarget->FillRoundedRectangle(rrect, Brush);
		//Brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkCyan));
		pRenderTarget->DrawRoundedRectangle(rrect, Brush, 1);
	}
}

