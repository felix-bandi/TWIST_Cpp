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

void MainWindow::Torol()
{
	BOOLEAN t;

	VONAL_v.clear();
	for (int i = 0; i < static_cast<int>(VONAL_vector.size()); i++)
	{
		t = false;
		for (int k = 0; k < static_cast<int>(Talalat[0].size()); k++) if (i == Talalat[0][k]) t = true;
		if (!t) VONAL_v.push_back(VONAL_vector[i]); 
	}
	VONAL_vector.clear();
	for (size_t i = 0; i < VONAL_v.size(); i++) VONAL_vector.push_back(VONAL_v[i]);

	EL_v.clear();
	for (int i = 0; i < static_cast<int>(EL_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[1].size(); k++) if (i == Talalat[1][k]) t = true;
		if (!t) EL_v.push_back(EL_vector[i]);
	}
	EL_vector.clear();
	for (size_t i = 0; i < EL_v.size(); i++) EL_vector.push_back(EL_v[i]);

	SQ_v.clear();
	for (int i = 0; i < static_cast<int>(SQ_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[2].size(); k++) if (i == Talalat[2][k]) t = true;
		if (!t) SQ_v.push_back(SQ_vector[i]);
	}
	SQ_vector.clear();
	for (size_t i = 0; i < SQ_v.size(); i++) SQ_vector.push_back(SQ_v[i]);

	RR_v.clear();
	for (int i = 0; i < static_cast<int>(RR_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[3].size(); k++) if (i == Talalat[3][k]) t = true;
		if (!t) RR_v.push_back(RR_vector[i]);
	}
	RR_vector.clear();
	for (size_t i = 0; i < RR_v.size(); i++) RR_vector.push_back(RR_v[i]);

	ARC_v.clear();
	for (int i = 0; i < static_cast<int>(ARC_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[4].size(); k++) if (i == Talalat[4][k]) t = true;
		if (!t) ARC_v.push_back(ARC_vector[i]); else SafeRelease(&ARC_vector[i].pg);
	}
	ARC_vector.clear();
	for (size_t i = 0; i < ARC_v.size(); i++) ARC_vector.push_back(ARC_v[i]);

	POLIGON_v.clear();
	for (int i = 0; i < static_cast<int>(POLIGON_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[5].size(); k++) if (i == Talalat[5][k]) t = true;
		if (!t) POLIGON_v.push_back(POLIGON_vector[i]); else SafeRelease(&POLIGON_vector[i].pg);
	}
	POLIGON_vector.clear();
	for (size_t i = 0; i < POLIGON_v.size(); i++) POLIGON_vector.push_back(POLIGON_v[i]);

	ELVIA_v.clear();
	for (int i = 0; i < static_cast<int>(ELVIA_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[6].size(); k++) if (i == Talalat[6][k]) t = true;
		if (!t) ELVIA_v.push_back(ELVIA_vector[i]);
	}
	ELVIA_vector.clear();
	for (size_t i = 0; i < ELVIA_v.size(); i++) ELVIA_vector.push_back(ELVIA_v[i]);

	SQVIA_v.clear();
	for (int i = 0; i < static_cast<int>(SQVIA_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[7].size(); k++) if (i == Talalat[7][k]) t = true;
		if (!t) SQVIA_v.push_back(SQVIA_vector[i]);
	}
	SQVIA_vector.clear();
	for (size_t i = 0; i < SQVIA_v.size(); i++) SQVIA_vector.push_back(SQVIA_v[i]);

	RRVIA_v.clear();
	for (int i = 0; i < static_cast<int>(RRVIA_vector.size()); i++)
	{
		t = false;
		for (size_t k = 0; k < Talalat[8].size(); k++) if (i == Talalat[8][k]) t = true;
		if (!t) RRVIA_v.push_back(RRVIA_vector[i]);
	}
	RRVIA_vector.clear();
	for (size_t i = 0; i < RRVIA_v.size(); i++) RRVIA_vector.push_back(RRVIA_v[i]);
	Blokk_szamol();
}