#pragma once
#include "basewin.h"
#include "resource.h"
#include "Struct.h"
#include <wincodec.h>
#include <Windows.h>
#include <cstring>

inline bool majdnem(const D2D1_POINT_2F& a, const D2D1_POINT_2F& b, float eps = 1e-3f)
{
	return (std::fabs(a.x - b.x) < eps) &&
		(std::fabs(a.y - b.y) < eps);
}

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = nullptr;
	}
}

inline HCURSOR CreateEmptyCursor()
{
	BYTE andMask[128]; memset(andMask, 0xFF, sizeof(andMask)); // háttér megtartása
	BYTE xorMask[128]; memset(xorMask, 0x00, sizeof(xorMask)); // semmi rajzolás
	return CreateCursor(GetModuleHandle(nullptr), 16, 16, 32, 32, andMask, xorMask);
}

class MainWindow : public BaseWindow<MainWindow>
{
	HCURSOR                 Cursor_system = CreateEmptyCursor(), Cursor_1 = LoadCursor(nullptr, IDC_ARROW);
	ID2D1Factory*			pFactory;
	ID2D1HwndRenderTarget*	pRenderTarget;
	ID2D1DCRenderTarget*	m_pDCRT;
	ID2D1SolidColorBrush	*Brush, *bv[2][2], *bp[2][2], *fekete, *feher, *cyan;
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
	korfazis				korfazis = egy;
	vector<VONAL>				VONAL_vector, VONAL_v, VONAL_betolt, Vonal_alkatresz;
	vector<ARC>					ARC_vector, ARC_v, ARC_betolt, ARC_alkatresz;
	vector<POLI>				POLIGON_vector, POLIGON_v, POLIGON_betolt, POLIGON_alkatresz;
	vector<D2D1_POINT_2F>		P;
	vector<EL_PAD>				EL_vector, EL_v, EL_betolt, EL_alkatresz;
	vector<SQ_PAD>				SQ_vector, SQ_v, SQ_betolt, SQ_alkatresz;
	vector<RR_PAD>				RR_vector, RR_v, RR_betolt, RR_alkatresz;
	vector<EL_VIA>				ELVIA_vector, ELVIA_v, ELVIA_betolt, ELVIA_alkatresz;
	vector<SQ_VIA>				SQVIA_vector, SQVIA_v, SQVIA_betolt, SQVIA_alkatresz;
	vector<RR_VIA>				RRVIA_vector, RRVIA_v, RRVIA_betolt, RRVIA_alkatresz;
	vector<ALKATRESZ>			Alkatresz;
	vector<GOMB>			ALAK_vector, CUSTOM_vector, gt, MODE_vector, SZINT_vector, FILE_vector;
	vector<vector<GOMB>>	CUSTOM;	
	vector<GC>				GC_vector;	
	vector<wstring>			alak_nevek = { L"Vonal", L"Körív", L"Poligon", L"EL_pad", L"SQ_pad", L"RR_pad", L"EL_via", L"SQ_via", L"RR_via" };
	vector<wstring>			mode_nevek = { L"Rajzolás", L"Törlés", L"File", L"Print"};
	vector<wstring>			szint_nevek = { L"Top", L"Bottom" };
	vector<wstring>			file_nevek = { L"Mentés", L"Alkatrész mentés", L"Betöltés", L"Betöltés új blokkba" };
	wstring					ws;
	wstring					ws_vonal[1] = { L"Width" }; int vonal_t[1] = { 40 };
	wstring					ws_kor[1] = { L"Width" };   int kor_t[1] = { 40 };
	wstring					ws_poli[1];
	wstring					ws_EL[3] = { L"dx", L"dy", L"d" }; int EL_t[3] = { 80, 80, 20 };
	wstring					ws_SQ[3] = { L"dx", L"dy", L"d" }; int SQ_t[3] = { 80, 80, 20 };
	wstring					ws_RR[5] = { L"Width", L"Height", L"rx", L"ry", L"d"}; int RR_t[5] = { 80, 80, 20, 20, 20 };
	wstring					ws_EV[3] = { L"dx", L"dy", L"d" }; int EV_t[3] = { 80, 80, 20 };
	wstring					ws_SV[3] = { L"dx", L"dy", L"d" }; int SV_t[3] = { 80, 80, 20 };
	wstring					ws_RV[5] = { L"Width", L"Height", L"rx", L"ry", L"d" }; int RV_t[5] = { 80, 80, 20, 20, 20 };
	vector<size_t>				tali;
	vector<vector<size_t>>		Talalat;
	D2D1_POINT_2F			pont, pont0, pont1;
	VONAL					vonal;
	ARC						arc;
	vector<D2D1_POINT_2F>	poligon, Poligon_2;
	vector<float>			szogek;
	POLI					poli;
	EL_PAD					el; EL_VIA ev;
	SQ_PAD					sq; SQ_VIA sv;
	RR_PAD					rr; RR_VIA rv;
	GOMB					gomb, edit, grid, origo;
	//GOMB_1					File_gomb;
	vector<GOMB_2>			drivers; GOMB_2 driver, save1, save2, load;
	vector<WIN32_FIND_DATA>	File_vector;
	GC						gc;
	WCHAR					text[MAX_PATH], kiv_drv, dialog_path[MAX_PATH];
	RECT					rc{};
	D2D1_RECT_F				BOX_GC{}, BOX_XY{}, BOX_ALAK{}, BOX_CUSTOM{}, BOX_MODE{}, BOX_SZINT{}, BOX_FILE{};
	D2D1_MATRIX_3X2_F		sc, tr, sc_alk, tr_alk;
	HDC						hdc;
	// ReSharper disable once IdentifierTypo
	bool krv = false, vonalfolyamatban = false, arcfolyamatban = false, polifolyamatban = false;
	bool EL_folyamatban = false, SQ_folyamatban = false, RR_folyamatban = false, BOX_GC_k = false, BOX_CUSTOM_k = false;
	bool EV_folyamatban = false, SV_folyamatban = false, RV_folyamatban = false, ny_kep = false;
	bool edit_k = false, edit_t = false, edit_sz = false, custom_sz = false, betoltes = false, vanrajz = false, XY_k=false;
	//POINT ablak;
	POINT* eger;
	float rx, rrx, ry, rry, nagyitas, n_sz;
	float xx, xxx, yy, yyy;
	int xe, ye, wheel, metsz, sz_sz, sz[2], kk;
	size_t hossz, count, NN=0;
	int ALAK_k = -1, ALAK_kk = 0, GC_k = -1, GC_kk = 0, MODE_k = -1, MODE_kk = 0, SZINT_k = -1, SZINT_kk = 0, alk_sz = 0;
	int FILE_k = -1, FILE_kk = -1, dialog_last_click_index = -1;
	D2D1_POINT_2F eltolas, hely, ak, av, mouse_grid, p1, p2, p3, p4, f1, f2, mouse;
	D2D1_SIZE_F meret;
	D2D1_POINT_2F pontok[100], ablak;
	
	double alfa, alfa_, beta, gamma, h_;
	float vv = 10, szt, save=77, delta, delta_, sz_max, flo1=0, flo2=0, flo3=0;
	//int vonal_d = 40, arc_v = 40, EL_pad_dx = 40, EL_pad_dy = 40, EL_pad_d = 10, SQ_pad_dx = 40, SQ_pad_dy = 40, SQ_pad_d = 10;
	//int RR_pad_dx = 40, RR_pad_dy = 40, RR_pad_rx = 10, RR_pad_ry = 10, RR_pad_d = 10;
public: 
	int ScreenWidth, ScreenHeight, int1=0, int2=0, int3=0, int4=0, int5=0, int6=0;
	float flo5 = 0, flo6 = 0;
	Dialog dialog;
	Dialog_2 dialog_2;
	List list, list2;
	

	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();
	void    Resize();
	void    OnLButtonDown(int pixelX, int pixelY, DWORD flags);
	void    OnRButtonDown(int pixelX, int pixelY, DWORD flags);
	void    OnMouseMove(int pixelX, int pixelY, DWORD flags);
	void	OnMouseWheel(int d);
	void	Kiir(bool v, float x, float y);
	void	Kiir(int v, float x, float y);
	void	Kiir(int v, D2D1_RECT_F t);
	void	Kiir(const char* s, int v, D2D1_RECT_F t);
	void	Kiir(const char* s, float v, float x, float y);
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
	//void	ARC_rajzol_betölt();
	void	ARC_keres();
	void	POLIGON_rajzol(vector<POLI> &POLI);
	void	POLIGON_rajzol_2();
	void	POLIGON_rajzol_T();
	//void	POLIGON_rajzol_betölt();
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
	void	Origo_athelyez();
	void	Talalat_rajzol();
	void	Save(mentes);
	void	Load(mentes);
	void	MODE_init();
	void	MODE_rajzol();
	void	MODE_keres();
	void	SZINT_init();
	void	SZINT_rajzol();
	void	SZINT_keres();
	void	Torol();
	void	Betolt_clear();
	void	Filedialog_init();
	void	Filedialog_rajzol();
	void	Printdialog_init();
	void	Printdialog_rajzol();
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

	MainWindow() 
		: pFactory(nullptr)
		, pRenderTarget(nullptr)
		, Brush(nullptr)
		, ScreenWidth(0)          // Initialize ScreenWidth
		, ScreenHeight(0)         // Initialize ScreenHeight
	{
	}

	PCWSTR  ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	enum DialogSortMode { DIALOG_SORT_DIR_FIRST = 0, DIALOG_SORT_MIXED = 1 };
	DialogSortMode dialogSortMode = DIALOG_SORT_DIR_FIRST;
};
