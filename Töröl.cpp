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

void MainWindow::Töröl()
{
	BOOLEAN t;
	int s;

	s = VONAL_vector.size();
	VONAL_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[0].size(); k++) if (i == Találat[0][k]) t = true;
		if (!t) VONAL_v.push_back(VONAL_vector[i]); 
	}
	VONAL_vector.clear();
	for (int i = 0; i < VONAL_v.size(); i++) VONAL_vector.push_back(VONAL_v[i]);

	s = EL_vector.size();
	EL_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[1].size(); k++) if (i == Találat[1][k]) t = true;
		if (!t) EL_v.push_back(EL_vector[i]);
	}
	EL_vector.clear();
	for (int i = 0; i < EL_v.size(); i++) EL_vector.push_back(EL_v[i]);

	s = SQ_vector.size();
	SQ_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[2].size(); k++) if (i == Találat[2][k]) t = true;
		if (!t) SQ_v.push_back(SQ_vector[i]);
	}
	SQ_vector.clear();
	for (int i = 0; i < SQ_v.size(); i++) SQ_vector.push_back(SQ_v[i]);

	s = RR_vector.size();
	RR_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[3].size(); k++) if (i == Találat[3][k]) t = true;
		if (!t) RR_v.push_back(RR_vector[i]);
	}
	RR_vector.clear();
	for (int i = 0; i < RR_v.size(); i++) RR_vector.push_back(RR_v[i]);

	s = ARC_vector.size();
	ARC_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[4].size(); k++) if (i == Találat[4][k]) t = true;
		if (!t) ARC_v.push_back(ARC_vector[i]); else SafeRelease(&ARC_vector[i].pg);
	}
	ARC_vector.clear();
	for (int i = 0; i < ARC_v.size(); i++) ARC_vector.push_back(ARC_v[i]);

	s = POLIGON_vector.size();
	POLIGON_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[5].size(); k++) if (i == Találat[5][k]) t = true;
		if (!t) POLIGON_v.push_back(POLIGON_vector[i]); else SafeRelease(&POLIGON_vector[i].pg);
	}
	POLIGON_vector.clear();
	for (int i = 0; i < POLIGON_v.size(); i++) POLIGON_vector.push_back(POLIGON_v[i]);

	s = ELVIA_vector.size();
	ELVIA_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[6].size(); k++) if (i == Találat[6][k]) t = true;
		if (!t) ELVIA_v.push_back(ELVIA_vector[i]);
	}
	ELVIA_vector.clear();
	for (int i = 0; i < ELVIA_v.size(); i++) ELVIA_vector.push_back(ELVIA_v[i]);

	s = SQVIA_vector.size();
	SQVIA_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[7].size(); k++) if (i == Találat[7][k]) t = true;
		if (!t) SQVIA_v.push_back(SQVIA_vector[i]);
	}
	SQVIA_vector.clear();
	for (int i = 0; i < SQVIA_v.size(); i++) SQVIA_vector.push_back(SQVIA_v[i]);

	s = RRVIA_vector.size();
	RRVIA_v.clear();
	for (int i = 0; i < s; i++)
	{
		t = false;
		for (int k = 0; k < Találat[8].size(); k++) if (i == Találat[8][k]) t = true;
		if (!t) RRVIA_v.push_back(RRVIA_vector[i]);
	}
	RRVIA_vector.clear();
	for (int i = 0; i < RRVIA_v.size(); i++) RRVIA_vector.push_back(RRVIA_v[i]);
	Blokk_szamol();
}