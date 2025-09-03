#include "Types.h"
#include <vector>
#include <Windows.h>
#pragma once
#include "Precision.h"

enum ALAK
{
	_vonal,
	_koriv,
	_poligon,
	_el_pad,
	_sq_pad,
	_rr_pad,
	_el_via,
	_sq_via,
	_rr_via,
	_alkatresz
};

enum MODE
{
	_torol,
	_rajzol,
	_file,
	_print
};

enum korfazis
{
	egy,
	ketto,
	harom
};

enum mentes
{
	rajz,
	alkatresz
};

struct VONAL
{
	float x1=0;
	float y1=0;
	float x2=0;
	float y2=0;
	float v=0;
	int szint=0;
	int alk=0;
	int blokk=0;
};

struct ARC
{
	Real xk=0;
	Real yk=0;
	Real xv=0;
	Real yv=0;
	Real rx=0;
	Real ry=0;
	Real kpx=0;
	Real kpy=0;
	Real ksz=0;
	Real vsz=0;
	Real v=0;
	D2D1_SWEEP_DIRECTION i=D2D1_SWEEP_DIRECTION_CLOCKWISE;
	D2D1_ARC_SIZE s=D2D1_ARC_SIZE_SMALL;
	ID2D1PathGeometry* pg=nullptr;
	int szint=0;
	int alk=0;
	int blokk=0;
};

struct POLI
{
    vector<D2D1_POINT_2F> pont;
    ID2D1PathGeometry* pg = nullptr;
    int szint = 0;
    int alk = 0;
    int blokk = 0;
};

struct EL_PAD
{
	float x=0;
	float y=0;
	float rx=0;
	float ry=0;
	float r=0;
	int szint=0;
	int alk=0;
	int blokk=0;
};

struct SQ_PAD
{
	float x=0;
	float y=0;
	float rx=0;
	float ry=0;
	float r=0;
	int szint=0;
	int alk=0;
	int blokk=0;
};

struct RR_PAD
{
	float x=0;
	float y=0;
	float rx=0;
	float ry=0;
	float rrx=0;
	float rry=0;
	float r=0;
	int szint=0;
	int alk=0;
	int blokk=0;
};

struct EL_VIA
{
	float x=0;
	float y=0;
	float rx=0;
	float ry=0;
	float r=0;
	int alk=0;
	int blokk=0;
};

struct SQ_VIA
{
	float x=0;
	float y=0;
	float rx=0;
	float ry=0;
	float r=0;
	int alk=0;
	int blokk=0;
};

struct RR_VIA
{
	float x=0;
	float y=0;
	float rx=0;
	float ry=0;
	float rrx=0;
	float rry=0;
	float r=0;
	int alk=0;
	int blokk=0;
};

struct ALKATRESZ
{
	vector<char> nev;
	vector<VONAL> v;
	vector<ARC> a;
	vector<POLI> p;
	vector<EL_PAD> ep;
	vector<SQ_PAD> sp;
	vector<RR_PAD> rp;
	vector<EL_VIA> ev;
	vector<SQ_VIA> sv;
	vector<RR_VIA> rv;
};

struct GOMB:D2D1_RECT_F
{
	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	boolean k = false;
	boolean kk = false;
	boolean sz = false;
	wstring t;
	vector<char> c;
	int i = 0;
	GOMB() { top = 0; left = 0; bottom = 0; right = 0; }
};

struct GOMB_1
{
	D2D1_RECT_F r;
	boolean k=false;
	boolean kk=false;
	wstring t;
};

struct GOMB_2:D2D1_RECT_F
{
	char ch = '\0'; // Initialize to null character
	wstring t;
	WCHAR tt[MAX_PATH] = { 0 }; // Initialize all elements to zero
	boolean k = false; // Initialize to false
	GOMB_2() { top = 0; left = 0; bottom = 0; right = 0; }
};

struct EDIT :D2D1_RECT_F
{
    boolean sz = false, k = false, kk = false; // Initialize all boolean members to false
    vector<u8> c;
    u8 tt[MAX_PATH] = { 0 }; // Initialize all elements to zero
	EDIT() { top = 0; left = 0; bottom = 0; right = 0; } // Default constructor initializing rectangle members to zero
};

struct EDIT_W : D2D1_RECT_F
{
    boolean sz=false;
    boolean k=false;
    boolean kk=false;
    std::wstring c;
    WCHAR tt[MAX_PATH];
    EDIT_W()
        : sz(false), k(false), kk(false), c(), tt{0}
    {
        top = 0; left = 0; bottom = 0; right = 0;
    }
};

struct VEZ_C
{
	int x1=0, x2=0, x3=0;
	int y1=0, y2=0;
};

struct GC
{
	float x=0;
	float y=0;
	float r=0;
};

struct Talalat
{
	int a=0;
	int i=0;
};

struct Csuszka :D2D1_RECT_F
{
	float min=0, max=0, range=0;
	float p=0, pp=0, value=0;
	float length=0;
	float sz=0;
	BOOLEAN v=false, k=false, kk=false;
	D2D1_RECT_F bar;
	Csuszka() { top = 0; left = 0; bottom = 0; right = 0; }
};

struct Dialog :D2D1_RECT_F
{
	size_t kkd = 0;
	int k = 0, kk = 0, out_N = 0, kd = 0;
	Csuszka cs = {};
	BOOLEAN ini = FALSE, dirchange = FALSE;
	WIN32_FIND_DATA FindFileData = {}; // Initialize to zero
	HANDLE hFind = nullptr;
	WCHAR filepath[MAX_PATH] = { 0 };
	vector<WCHAR[MAX_PATH]> path;
	D2D1_RECT_F client = {};
	EDIT edit;
	D2D1_POINT_2F p1 = {}, p2 = {};
	DWORD lastEnumError = 0; 
	Dialog() { top = 0; left = 0; bottom = 0; right = 0; }	
};

struct List :D2D1_RECT_F
{
	int k=0, kk=0, out_N=0, kd=0, kkd=0;
	Csuszka cs = {};
	boolean BOX_k=false;
	List() { top = 0; left = 0; bottom = 0; right = 0; BOX_k = false; }	
};

struct Lista :D2D1_RECT_F
{
	Lista() { top = 0; left = 0; bottom = 0; right = 0; }	
};