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
#include <iostream>
#include <fstream>
#include <cstring>
#include "DPIScale.h"


LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
		{
			return -1;  // Fail CreateWindowEx.
		}
		DPIScale::Initialize(pFactory);
		eltolas.x = 0; eltolas.y = 0;
		nagyitas = 1;
		wheel = 0;
		ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
		MoveWindow(m_hwnd, 0, 0, ScreenWidth, ScreenHeight, 0);
		grid.i = 1;
		return 0;

	case WM_DESTROY:
		DiscardGraphicsResources();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		OnPaint();
		return 0;

	case WM_SIZE:
		Resize();
		return 0;

	case WM_LBUTTONDOWN:
		OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;

	case WM_LBUTTONUP:
		dialog.cs.kk = false;
		return 0;

	case WM_RBUTTONDOWN:
		OnRButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;

	case WM_MOUSEMOVE:
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;

	case WM_MOUSEWHEEL:
		OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
		return 0;

	case WM_KEYDOWN:
		if (!edit.sz && !dialog.edit.sz)
		{
			if (wParam == 0x4d) Save(rajz);		// 'M'
			if (wParam == 0x41) Save(alkatrész);// 'A'
			if (wParam == 0x4c) Load(rajz);		// 'L'
			if (wParam == 0x44) Load(alkatrész);// 'D'
			if (wParam == VK_DELETE && mode == _töröl) Töröl();
			if (wParam == VK_ESCAPE)  DestroyWindow(m_hwnd);
		}
		if (wParam == VK_ESCAPE)  DestroyWindow(m_hwnd);
		return 0;

	/*case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT)
		{
			//SetCursor(Cursor_system);
			return true;
		}
		break;*/

	case WM_COMMAND:
		if (!krv && !dialog.edit.sz)
		{
			vonalfolyamatban = false;
			for (int i = 0; i < alak_nevek.size(); i++) ALAK_vector[i].kk = false;
			switch (LOWORD(wParam))
			{
			case a_VONAL:
				alak = _vonal;
				ALAK_kk = 0;
				break;
			case a_KORIV:
				alak = _koriv;
				ALAK_kk = 1;
				break;
			case a_POLIGON:
				alak = _poligon;
				ALAK_kk = 2;
				break;
			case a_EL:
				alak = _el_pad;
				ALAK_kk = 3;
				break;
			case a_SQ:
				alak = _sq_pad;
				ALAK_kk = 4;
				break;
			case a_RR:
				alak = _rr_pad;
				ALAK_kk = 5;
				break;
			}
			return 0;
		}		
	case WM_CHAR:
		if (dialog.edit.sz)
		{
			if (wParam == VK_BACK) dialog.edit.c.pop_back();
			else
			{
				char w = wParam;
				//if (w > 65535) w -= 65536;				
				//if (isalnum(w) || w == 336 || w == 337 || w == 368 || w == 369) 
				if (isalnum(w)) dialog.edit.c.push_back(w);
				int2 = w;
			}
		}
		if (edit_sz)
		{
			switch (wParam)
			{
				case 0x30: if (edit.c.size() < 4) edit.c.push_back('0'); break;
				case 0x31: if (edit.c.size() < 4) edit.c.push_back('1'); break;
				case 0x32: if (edit.c.size() < 4) edit.c.push_back('2'); break;
				case 0x33: if (edit.c.size() < 4) edit.c.push_back('3'); break;
				case 0x34: if (edit.c.size() < 4) edit.c.push_back('4'); break;
				case 0x35: if (edit.c.size() < 4) edit.c.push_back('5'); break;
				case 0x36: if (edit.c.size() < 4) edit.c.push_back('6'); break;
				case 0x37: if (edit.c.size() < 4) edit.c.push_back('7'); break;
				case 0x38: if (edit.c.size() < 4) edit.c.push_back('8'); break;
				case 0x39: if (edit.c.size() < 4) edit.c.push_back('9'); break;
				case VK_BACK: if (edit.c.size() > 0) edit.c.pop_back(); break;
				case VK_RETURN: 
				{
					edit_sz = false;				
					if (edit.c.size() == 0) edit.c.push_back('1');
					if (grid.sz)
					{
						int h = edit.c.size();
						grid.c.clear();
						for (int n = 0; n < h; n++) grid.c.push_back(edit.c[n]);
						grid.sz = false;
						for (int j = 0; j < 10; j++) w[j] = ' ';
						for (int j = 0; j < h; j++) w[j] = grid.c[j];
						grid.i = stoi(w);
					}
					if (custom_sz)
					{
						int s = CUSTOM[ALAK_kk].size();
						int i = 0;
						while (s >= 1)
						{
							if (CUSTOM_vector[i].sz)
							{
								int h = edit.c.size();
								CUSTOM[ALAK_kk][i].c.clear();
								for (int n = 0; n < h; n++) CUSTOM[ALAK_kk][i].c.push_back(edit.c[n]);
								custom_sz = false;
								CUSTOM_vector[i].sz = false;
								for (int j = 0; j < 10; j++) w[j] = ' ';
								for (int j = 0; j < h; j++) w[j] = CUSTOM[ALAK_kk][i].c[j];
								CUSTOM[ALAK_kk][i].i = stoi(w);
							}
							i++;
							s--;
						}
						vonal_t[0] = CUSTOM[0][0].i;
						kör_t[0] = CUSTOM[1][0].i;
						EL_t[0] = CUSTOM[3][0].i; EL_t[1] = CUSTOM[3][1].i; EL_t[2] = CUSTOM[3][2].i;
						SQ_t[0] = CUSTOM[4][0].i; SQ_t[1] = CUSTOM[4][1].i; SQ_t[2] = CUSTOM[4][2].i;
						RR_t[0] = CUSTOM[5][0].i; RR_t[1] = CUSTOM[5][1].i; RR_t[2] = CUSTOM[5][2].i;
						RR_t[3] = CUSTOM[5][3].i; RR_t[4] = CUSTOM[5][4].i;
						EV_t[0] = CUSTOM[6][0].i; EV_t[1] = CUSTOM[6][1].i; EV_t[2] = CUSTOM[6][2].i;
						SV_t[0] = CUSTOM[7][0].i; SV_t[1] = CUSTOM[7][1].i; SV_t[2] = CUSTOM[7][2].i;
						RV_t[0] = CUSTOM[8][0].i; RV_t[1] = CUSTOM[8][1].i; RV_t[2] = CUSTOM[8][2].i;
						RV_t[3] = CUSTOM[8][3].i; RV_t[4] = CUSTOM[8][4].i;
					}
				} break;
			}				
		}
		else if (körfázis == 2 && wParam == VK_SPACE)
		{
			if (arc.i == D2D1_SWEEP_DIRECTION_CLOCKWISE) { arc.i = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE; }
			else { arc.i = D2D1_SWEEP_DIRECTION_CLOCKWISE; }
		}
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
