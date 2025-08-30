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
#include <iostream>
#include <fstream>
#include <cstring>
#include <wincodec.h>
/*void MainWindow::Save_alkatresz()
{
	ofstream alkatresz("alkatreszek.alk", ios::app);
	if(alkatresz.is_open())
	{
		
	}
}*/

void MainWindow::Save(mentes ment)
{
	boolean a = false;
	std::wofstream f;
	switch (ment)
	{
	case mentes::rajz:
		f.open(L"rajz.twist");
		break;
	case mentes::alkatresz:
		f.open(L"alkatrészek.alkatrész", std::ios::app);
		a = true;
			break;
	}
	
	if (f.is_open())
	{
		if (a)
		{
			//f << "/n";
			std::wstring name;
			for (size_t i = 0; i < MAX_PATH && dialog.edit.tt[i] != 0; ++i) {
				name += static_cast<wchar_t>(dialog.edit.tt[i]);
			}
			f << L"_" << name.c_str() << L":\n";
			///f << "_" << dialog.edit.tt << ":\n";
		}
		for (int i = 0; i < VONAL_vector.size(); i++)
		{
			f << "Vonal ";
			f << VONAL_vector[i].x1 << " ";
			f << VONAL_vector[i].y1 << " ";
			f << VONAL_vector[i].x2 << " ";
			f << VONAL_vector[i].y2 << " ";
			f << VONAL_vector[i].v << " ";
			f << VONAL_vector[i].szint << " ";
			f << "\n";
		}
		for (int i = 0; i < ARC_vector.size(); i++)
		{
			f << "Koriv ";
			f << ARC_vector[i].i << " ";
			f << ARC_vector[i].kpx << " ";
			f << ARC_vector[i].kpy << " ";
			f << ARC_vector[i].ksz << " ";
			f << ARC_vector[i].rx << " ";
			f << ARC_vector[i].ry << " ";
			f << ARC_vector[i].s << " ";
			f << ARC_vector[i].szint << " ";
			f << ARC_vector[i].v << " ";
			f << ARC_vector[i].vsz << " ";
			f << ARC_vector[i].xk << " ";
			f << ARC_vector[i].xv << " ";
			f << ARC_vector[i].yk << " ";
			f << ARC_vector[i].yv << " ";
			f << "\n";
		}
		for (int i = 0; i < POLIGON_vector.size(); i++)
		{
			f << "Poligon ";
			f << POLIGON_vector[i].szint << " ";
			f << POLIGON_vector[i].pont.size() << " ";
			for (int p = 0; p < POLIGON_vector[i].pont.size(); p++)
			{
				f << POLIGON_vector[i].pont[p].x << " ";
				f << POLIGON_vector[i].pont[p].y << " ";
			}
			f << "\n";
		}
		for (int i = 0; i < EL_vector.size(); i++)
		{
			f << "EL ";
			f << EL_vector[i].r << " ";
			f << EL_vector[i].rx << " ";
			f << EL_vector[i].ry << " ";
			f << EL_vector[i].szint << " ";
			f << EL_vector[i].x << " ";
			f << EL_vector[i].y << " ";
			f << "\n";
		}
		for (int i = 0; i < SQ_vector.size(); i++)
		{
			f << "SQ ";
			f << SQ_vector[i].r << " ";
			f << SQ_vector[i].rx << " ";
			f << SQ_vector[i].ry << " ";
			f << SQ_vector[i].szint << " ";
			f << SQ_vector[i].x << " ";
			f << SQ_vector[i].y << " ";
			f << "\n";
		}
		for (int i = 0; i < RR_vector.size(); i++)
		{
			f << "RR ";
			f << RR_vector[i].r << " ";
			f << RR_vector[i].rx << " ";
			f << RR_vector[i].ry << " ";
			f << RR_vector[i].rrx << " ";
			f << RR_vector[i].rry << " ";
			f << RR_vector[i].szint << " ";
			f << RR_vector[i].x << " ";
			f << RR_vector[i].y << " ";
			f << "\n";
		}
		for (int i = 0; i < ELVIA_vector.size(); i++)
		{
			f << "EV ";
			f << ELVIA_vector[i].r << " ";
			f << ELVIA_vector[i].rx << " ";
			f << ELVIA_vector[i].ry << " ";
			f << ELVIA_vector[i].x << " ";
			f << ELVIA_vector[i].y << " ";
			f << "\n";
		}
		for (int i = 0; i < SQVIA_vector.size(); i++)
		{
			f << "SV ";
			f << SQVIA_vector[i].r << " ";
			f << SQVIA_vector[i].rx << " ";
			f << SQVIA_vector[i].ry << " ";
			f << SQVIA_vector[i].x << " ";
			f << SQVIA_vector[i].y << " ";
			f << "\n";
		}
		for (int i = 0; i < RRVIA_vector.size(); i++)
		{
			f << "RV ";
			f << RRVIA_vector[i].r << " ";
			f << RRVIA_vector[i].rx << " ";
			f << RRVIA_vector[i].ry << " ";
			f << RRVIA_vector[i].rrx << " ";
			f << RRVIA_vector[i].rry << " ";
			f << RRVIA_vector[i].x << " ";
			f << RRVIA_vector[i].y << " ";
			f << "\n";
		}
		if (a) f << "|\n";
		save = 66;
		f.close();
	}
	else save = 88;
}

void MainWindow::Load(mentes tölt)
{
	boolean alk = false;
	std::wifstream f;
	if(tölt==rajz)
	{
		f.open(L"rajz.twist");
	}
	if(tölt==alkatresz)
	{
		f.open(L"alkatrészek.alkatrész");
		alk = true;
	}
	int alk_sz = -1;
	std::wstring wsor;
	char s[1000], *a, *b, ss[1000];
	ALKATRESZ alkatresz;

	if (f.is_open())
	{
		save = 55;
		Betolt_clear();
		while (f.good())
		{
			getline(f, wsor);
			std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
			std::string sor = conv.to_bytes(wsor);
			strncpy_s(s, sizeof(s), sor.c_str(), sizeof(s) - 1);
			strncpy_s(ss, sizeof(ss), sor.c_str(), sizeof(ss) - 1);
			a = strtok_s(s, " ", &b);
			if (ss[0] == '_')
			{
				alk_sz++;
				for (int i = 1; i < std::strlen(ss); i++) alkatresz.nev.push_back(ss[i]);
				save = 111;
			}
			if(s[0] == 'V')
			{
				a = strtok_s(NULL, " ", &b);
				vonal.x1 = atof(a);
				a = strtok_s(NULL, " ", &b);
				vonal.y1 = atof(a);
				a = strtok_s(NULL, " ", &b);
				vonal.x2 = atof(a);
				a = strtok_s(NULL, " ", &b);
				vonal.y2 = atof(a);
				a = strtok_s(NULL, " ", &b);
				vonal.v = atof(a);
				a = strtok_s(NULL, " ", &b);
				vonal.szint = atoi(a);
				VONAL_betolt.push_back(vonal);
				//save = 40;
			}
			if (s[0] == 'K')
			{
				a = strtok_s(NULL, " ", &b);
				if (atoi(a) == 1) arc.i = D2D1_SWEEP_DIRECTION_CLOCKWISE; else arc.i = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
				a = strtok_s(NULL, " ", &b);
				arc.kpx = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.kpy = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.ksz = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.rx = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.ry = atof(a);
				a = strtok_s(NULL, " ", &b);
				if (atoi(a) == 0) arc.s = D2D1_ARC_SIZE_SMALL; else arc.s = D2D1_ARC_SIZE_LARGE;
				a = strtok_s(NULL, " ", &b);
				arc.szint = atoi(a);
				a = strtok_s(NULL, " ", &b);
				arc.v = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.vsz = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.xk = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.xv = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.yk = atof(a);
				a = strtok_s(NULL, " ", &b);
				arc.yv = atof(a);
				ARC_betolt.push_back(arc);
				ARC_rajzol(ARC_betolt);
				//save = 41;
			}
			if (s[0] == 'P')
			{
				poli.pont.clear();
				//pontok.
				save = 0;
				a = strtok_s(NULL, " ", &b);
				poli.szint = atoi(a);
				a = strtok_s(NULL, " ", &b);
				int k = atoi(a);
				for (int p = 0; p < k; p++)
				{
					a = strtok_s(NULL, " ", &b);
					pont.x = atof(a);
					a = strtok_s(NULL, " ", &b);
					pont.y = atof(a);
					poli.pont.push_back(pont);
					save++;
				}
				for (int i = 0; i < poli.pont.size(); i++) pontok[i] = poli.pont[i];
				POLIGON_betolt.push_back(poli);
				POLIGON_rajzol(POLIGON_betolt);
				//save = 40;
			}
			if (s[0] == 'E' && s[1] == 'L')
			{
				save++;
				a = strtok_s(NULL, " ", &b);
				el.r = atof(a);
				a = strtok_s(NULL, " ", &b);
				el.rx = atof(a);
				a = strtok_s(NULL, " ", &b);
				el.ry = atof(a);
				a = strtok_s(NULL, " ", &b);
				el.szint = atoi(a);
				a = strtok_s(NULL, " ", &b);
				el.x = atof(a);
				a = strtok_s(NULL, " ", &b);
				el.y = atof(a);
				EL_betolt.push_back(el);
			}//save = 50;
			
			if (s[0] == 'S' && s[1] == 'Q')
			{
				a = strtok_s(NULL, " ", &b);
				sq.r = atof(a);
				a = strtok_s(NULL, " ", &b);
				sq.rx = atof(a);
				a = strtok_s(NULL, " ", &b);
				sq.ry = atof(a);
				a = strtok_s(NULL, " ", &b);
				sq.szint = atoi(a);
				a = strtok_s(NULL, " ", &b);
				sq.x = atof(a);
				a = strtok_s(NULL, " ", &b);
				sq.y = atof(a);
				SQ_betolt.push_back(sq);
			}
			if (s[0] == 'R' && s[1] == 'R')
			{
				a = strtok_s(NULL, " ", &b);
				rr.r = atof(a);
				a = strtok_s(NULL, " ", &b);
				rr.rx = atof(a);
				a = strtok_s(NULL, " ", &b);
				rr.ry = atof(a);
				a = strtok_s(NULL, " ", &b);
				rr.rrx = atof(a);
				a = strtok_s(NULL, " ", &b);
				rr.rry = atof(a);
				a = strtok_s(NULL, " ", &b);
				rr.szint = atoi(a);
				a = strtok_s(NULL, " ", &b);
				rr.x = atof(a);
				a = strtok_s(NULL, " ", &b);
				rr.y = atof(a);
				RR_betolt.push_back(rr);
			}
			if (s[0] == 'E' && s[1] == 'V')
			{
				a = strtok_s(NULL, " ", &b);
				ev.r = atof(a);
				a = strtok_s(NULL, " ", &b);
				ev.rx = atof(a);
				a = strtok_s(NULL, " ", &b);
				ev.ry = atof(a);
				a = strtok_s(NULL, " ", &b);
				ev.x = atof(a);
				a = strtok_s(NULL, " ", &b);
				ev.y = atof(a);
				ELVIA_betolt.push_back(ev);
			}
			if (s[0] == 'S' && s[1] == 'V')
			{
				a = strtok_s(NULL, " ", &b);
				sv.r = atof(a);
				a = strtok_s(NULL, " ", &b);
				sv.rx = atof(a);
				a = strtok_s(NULL, " ", &b);
				sv.ry = atof(a);
				a = strtok_s(NULL, " ", &b);
				sv.x = atof(a);
				a = strtok_s(NULL, " ", &b);
				sv.y = atof(a);
				SQVIA_betolt.push_back(sv);
			}
			if (s[0] == 'R' && s[1] == 'V')
			{
				a = strtok_s(NULL, " ", &b);
				rv.r = atof(a);
				a = strtok_s(NULL, " ", &b);
				rv.rx = atof(a);
				a = strtok_s(NULL, " ", &b);
				rv.ry = atof(a);
				a = strtok_s(NULL, " ", &b);
				rv.rrx = atof(a);
				a = strtok_s(NULL, " ", &b);
				rv.rry = atof(a);
				a = strtok_s(NULL, " ", &b);
				rv.x = atof(a);
				a = strtok_s(NULL, " ", &b);
				rv.y = atof(a);
				RRVIA_betolt.push_back(rv);
			}
			if (alk && s[0]=='|')
			{
				if (VONAL_betolt.size() > 0) for (int i = 0; i < VONAL_betolt.size(); i++)     alkatresz.v.push_back(VONAL_betolt[i]);
				if (ARC_betolt.size() > 0)   for (int i = 0; i < ARC_betolt.size(); i++)       alkatresz.a.push_back(ARC_betolt[i]);
				if (POLIGON_betolt.size() > 0)
				{
					for (int i = 0; i < POLIGON_betolt.size(); i++)
					{
						poli.pont.clear();
						for (int p = 0; p < POLIGON_betolt[i].pont.size(); p++) poli.pont.push_back(POLIGON_betolt[i].pont[p]);
						poli.pg = POLIGON_betolt[i].pg;
						poli.szint = POLIGON_betolt[i].szint;
						alkatresz.p.push_back(POLIGON_betolt[i]);
					}
				}
				if (EL_betolt.size() > 0)    for (int i = 0; i < EL_betolt.size(); i++)    alkatresz.ep.push_back(EL_betolt[i]);
				if (SQ_betolt.size() > 0)    for (int i = 0; i < SQ_betolt.size(); i++)    alkatresz.sp.push_back(SQ_betolt[i]);
				if (RR_betolt.size() > 0)    for (int i = 0; i < RR_betolt.size(); i++)    alkatresz.rp.push_back(RR_betolt[i]);
				if (ELVIA_betolt.size() > 0) for (int i = 0; i < ELVIA_betolt.size(); i++) alkatresz.ev.push_back(ELVIA_betolt[i]);
				if (SQVIA_betolt.size() > 0) for (int i = 0; i < SQVIA_betolt.size(); i++) alkatresz.sv.push_back(SQVIA_betolt[i]);
				if (RRVIA_betolt.size() > 0) for (int i = 0; i < RRVIA_betolt.size(); i++) alkatresz.rv.push_back(RRVIA_betolt[i]);
				Alkatresz.push_back(alkatresz);
				alkatresz.nev.clear();
				alkatresz.v.clear();
				alkatresz.a.clear();
				alkatresz.p.clear();
				alkatresz.ep.clear();
				alkatresz.sp.clear();
				alkatresz.rp.clear();
				alkatresz.ev.clear();
				alkatresz.sv.clear();
				alkatresz.rv.clear();
				Betolt_clear();
			}
		}
		
		if (!alk) betoltes = true;
		f.close();
		//save = 33;
	}
	else save = 99;
	wchar_t exePath[MAX_PATH];
	GetModuleFileNameW(nullptr, exePath, MAX_PATH);
	std::wstring root(exePath);
	size_t pos = root.find_last_of(L"\\/");
	if (pos != std::wstring::npos) root.erase(pos); // Debug/Release mappa
	pos = root.find_last_of(L"\\/");
	if (pos != std::wstring::npos) root.erase(pos); // Projekt fõkönyvtár
	std::wstring alkDir = root + L"\\Alkatreszek";
	std::wstring rajzDir = root + L"\\Rajzok";
}