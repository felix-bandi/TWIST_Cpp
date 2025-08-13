#pragma once

#include "basewin.h"
#include "resource.h"
#include "Struct.h"
#include <wincodec.h>

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class MainWindow : public BaseWindow<MainWindow>
{
	HCURSOR                 Cursor_system = LoadCursor(NULL, NULL), Cursor_1 = LoadCursor(NULL, IDC_ARROW);
	ID2D1Factory*			pFactory;
	ID2D1HwndRenderTarget*	pRenderTarget;
	ID2D1DCRenderTarget*	m_pDCRT;
	ID2D1SolidColorBrush	*Brush, *bv[2][2], *bp[2][2], *fekete, *feh�r, *cyan;
	IDWriteFactory*			pDWriteFactory;
	IDWriteTextFormat		*TF1, *TF2, *TF2_dir;
	ID2D1StrokeStyle*		pStrokeStyle;
	ID2D1PathGeometry*		pPathGeometry;
	ID2D1PathGeometry*		pPathGeometry_2;
	ID2D1PathGeometry*		pPathGeometry_3;
	ID2D1PathGeometry*		pPathGeometry_4;
	ID2D1PathGeometry*		pPathGeometry_5;
	D2D1_ELLIPSE			ellipse;
	D2D1_RECT_F				rect;
	vector<D2D1_RECT_F>		Blokk;
	D2D1_ROUNDED_RECT		rrect;
	ALAK					alak = _vonal;
	MODE					mode = _rajzol;
	k�rf�zis				k�rf�zis = egy;
	vector<VONAL>				VONAL_vector, VONAL_v, VONAL_bet�lt, Vonal_alkatr�sz;
	vector<ARC>					ARC_vector, ARC_v, ARC_bet�lt, ARC_alkatr�sz;
	vector<POLI>				POLIGON_vector, POLIGON_v, POLIGON_bet�lt, POLIGON_alkatr�sz;
	vector<D2D1_POINT_2F>		P;
	vector<EL_PAD>				EL_vector, EL_v, EL_bet�lt, EL_alkatr�sz;
	vector<SQ_PAD>				SQ_vector, SQ_v, SQ_bet�lt, SQ_alkatr�sz;
	vector<RR_PAD>				RR_vector, RR_v, RR_bet�lt, RR_alkatr�sz;
	vector<EL_VIA>				ELVIA_vector, ELVIA_v, ELVIA_bet�lt, ELVIA_alkatr�sz;
	vector<SQ_VIA>				SQVIA_vector, SQVIA_v, SQVIA_bet�lt, SQVIA_alkatr�sz;
	vector<RR_VIA>				RRVIA_vector, RRVIA_v, RRVIA_bet�lt, RRVIA_alkatr�sz;
	vector<ALKATR�SZ>			Alkatr�sz;
	vector<GOMB>			ALAK_vector, CUSTOM_vector, gt, MODE_vector, SZINT_vector, FILE_vector;
	vector<vector<GOMB>>	CUSTOM;	
	vector<GC>				GC_vector;
	vector<wstring>			alak_nevek = { L"Vonal", L"K�r�v", L"Poligon", L"EL_pad", L"SQ_pad", L"RR_pad", L"EL_via", L"SQ_via", L"RR_via" };
	vector<wstring>			mode_nevek = { L"Rajzol�s", L"T�rl�s", L"File", L"Print"};
	vector<wstring>			szint_nevek = { L"Top", L"Bottom" };
	vector<wstring>			file_nevek = { L"Ment�s", L"Alkatr�sz ment�s", L"Bet�lt�s", L"Bet�lt�s �j blokkba" };
	wstring					ws;
	wstring					ws_vonal[1] = { L"Width" }; int vonal_t[1] = { 40 };
	wstring					ws_k�r[1] = { L"Width" };   int k�r_t[1] = { 40 };
	wstring					ws_poli[1];
	wstring					ws_EL[3] = { L"dx", L"dy", L"d" }; int EL_t[3] = { 80, 80, 20 };
	wstring					ws_SQ[3] = { L"dx", L"dy", L"d" }; int SQ_t[3] = { 80, 80, 20 };
	wstring					ws_RR[5] = { L"Width", L"Height", L"rx", L"ry", L"d"}; int RR_t[5] = { 80, 80, 20, 20, 20 };
	wstring					ws_EV[3] = { L"dx", L"dy", L"d" }; int EV_t[3] = { 80, 80, 20 };
	wstring					ws_SV[3] = { L"dx", L"dy", L"d" }; int SV_t[3] = { 80, 80, 20 };
	wstring					ws_RV[5] = { L"Width", L"Height", L"rx", L"ry", L"d" }; int RV_t[5] = { 80, 80, 20, 20, 20 };
	vector<int>				tali;
	vector<vector<int>>		Tal�lat;
	D2D1_POINT_2F			pont, pont0, pont1;
	VONAL					vonal;
	ARC						arc;
	vector<D2D1_POINT_2F>	poligon, Poligon_2;
	vector<float>			sz�gek;
	POLI					poli;
	EL_PAD					el; EL_VIA ev;
	SQ_PAD					sq; SQ_VIA sv;
	RR_PAD					rr; RR_VIA rv;
	GOMB					gomb, edit, grid, origo;
	//GOMB_1					File_gomb;
	vector<GOMB_2>			drivers; GOMB_2 driver, save1, save2, load;
	vector<WIN32_FIND_DATA>	File_vector;
	GC						gc;
	WCHAR					text[MAX_PATH], kiv_drv, dialog_path[260];
	DWORD					dialog_last_click_time = 0;
	RECT					rc, BOX_GC, BOX_XY, BOX_ALAK, BOX_CUSTOM, BOX_MODE, BOX_SZINT, BOX_FILE;
	D2D1_MATRIX_3X2_F		sc, tr, sc_alk, tr_alk;
	HDC						hdc;
	// ReSharper disable once IdentifierTypo
	BOOLEAN krv = false, vonalfolyamatban = false, arcfolyamatban = false, polifolyamatban = false;
	BOOLEAN EL_folyamatban = false, SQ_folyamatban = false, RR_folyamatban = false, BOX_GC_k = false, BOX_CUSTOM_k = false;
	BOOLEAN EV_folyamatban = false, SV_folyamatban = false, RV_folyamatban = false, ny_k�p = false;
	BOOLEAN edit_k = false, edit_t = false, edit_sz = false, custom_sz = false, bet�lt�s = false, vanrajz = false, XY_k=false;
	POINT ablak;
	POINT* eger;
	float r, rx, rrx, ry, rry, nagyitas, n_sz, dx, dy, sz�g = 1.0;
	int xe, ye, xxx, yyy, xx, yy, x, y, wheel, count, metsz, sz_sz, NN = 0, sz[2], kk;
	int ALAK_k = -1, ALAK_kk = 0, GC_k = -1, GC_kk = 0, hossz, MODE_k = -1, MODE_kk = 0, SZINT_k = -1, SZINT_kk = 0, alk_sz = 0;
	int FILE_k = -1, FILE_kk = -1, dialog_last_click_index = -1;
	D2D1_POINT_2F eltolas, hely, ak, av, f, m, p, mouse_grid, p1, p2, p3, p4, f1, f2, mouse;
	D2D1_SIZE_F meret;
	D2D1_POINT_2F pontok[100];
	char w[10];
	float vv = 10, szt, save=77, d, alfa, alfa_, beta, gamma, h, h_, delta, delta_, sz_max, flo1=0, flo2=0, flo3=0;
	//int vonal_d = 40, arc_v = 40, EL_pad_dx = 40, EL_pad_dy = 40, EL_pad_d = 10, SQ_pad_dx = 40, SQ_pad_dy = 40, SQ_pad_d = 10;
	//int RR_pad_dx = 40, RR_pad_dy = 40, RR_pad_rx = 10, RR_pad_ry = 10, RR_pad_d = 10;
public: 
	int ScreenWidth, ScreenHeight, int1=0, int2=0, int3=0, int4=0, int5=0, int6=0;
	float flo5 = 0, flo6 = 0;
	Dialog dialog;
	List list, list2;
	

	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();
	void    Resize();
	void    OnLButtonDown(int pixelX, int pixelY, DWORD flags);
	void    OnRButtonDown(int pixelX, int pixelY, DWORD flags);
	void    OnMouseMove(int pixelX, int pixelY, DWORD flags);
	void	OnMouseWheel(int d);
	void	Kiir(boolean v, int x, int y);
	void	Kiir(int v, int x, int y);
	void	Kiir(int v, D2D1_RECT_F t);
	void	Kiir(const char* s, int v, D2D1_RECT_F t);
	void	Kiir(const char* s, float v, int x, int y);
	void	Kiir(const char* s, D2D1_RECT_F t);
	void	XY_init();
	void	XY_rajzol();
	void	XY_keres();
	void	EL_rajzol();
	void	EL_keres();
	void	EL_lyuk_rajzol();
	void	SQ_rajzol();
	void	SQ_keres();
	void	SQ_lyuk_rajzol();
	void	RR_rajzol();
	void	RR_keres();
	void	RR_lyuk_rajzol();
	void	EV_rajzol();
	void	EV_keres();
	void	EV_lyuk_rajzol();
	void	SV_rajzol();
	void	SV_keres();
	void	SV_lyuk_rajzol();
	void	RV_rajzol();
	void	RV_keres();
	void	RV_lyuk_rajzol();
	void	VONAL_rajzol();
	void	VONAL_keres();
	//void	ARC_rajzol();
	void	ARC_rajzol(vector<ARC> &ARC);
	void	ARC_rajzol_2();
	//void	ARC_rajzol_bet�lt();
	void	ARC_keres();
	void	POLIGON_rajzol(vector<POLI> &POLI);
	void	POLIGON_rajzol_2();
	void	POLIGON_rajzol_T();
	//void	POLIGON_rajzol_bet�lt();
	void	POLIGON_keres();
	void	ALAK_init();
	void	ALAK_rajzol();
	void	ALAK_keres();
	void	CUSTOM_init();
	void	CUSTOM_rajzol();
	void	CUSTOM_keres();
	void	GC_init();
	void	GC_rajzol();
	void	GC_keres();
	void	Cursor_rajzol();
	void	GRID_init();
	void	GRID_rajzol();
	void	ORIGO_rajzol();
	void	ORIGO_init();
	void	Origo_�thelyez();
	void	Tal�lat_rajzol();
	void	Save(ment�s);
	void	Load(ment�s);
	void	MODE_init();
	void	MODE_rajzol();
	void	MODE_keres();
	void	SZINT_init();
	void	SZINT_rajzol();
	void	SZINT_keres();
	void	T�r�l();
	void	Bet�lt_clear();
	void	Filedialog_init();
	void	Filedialog_rajzol();
	void	List_init();
	void	List_rajzol();
	//void	List_keres();
	void	List2_init();
	void	List2_rajzol();
	void	FILE_init();
	void	FILE_rajzol();
	void	FILE_keres();
	void	Blokk_szamol();
	void	alk_krv_rajzol(int alk);
	void	alk_letesz(int alk);
	void	Nyomtat();
	void	UpdateDialogContents();

public:

	MainWindow() : pFactory(NULL), pRenderTarget(NULL), Brush(NULL)
	{
	}

	PCWSTR  ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	enum DialogSortMode { DIALOG_SORT_DIR_FIRST = 0, DIALOG_SORT_MIXED = 1 };
	DialogSortMode dialogSortMode = DIALOG_SORT_DIR_FIRST;
};
