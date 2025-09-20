#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <functional>
#include <string_view>

// (A projektedben már létezik.)
std::wstring NormalizePath(const std::wstring& s);

namespace TWIST
{
	// Mentési eredmények
	enum class SaveResult {
		Ok = 0,
		CreateBaseFailed,
		InvalidName,       // névben elválasztó / path
		TempCreateFailed,
		WriteFailed,
		FlushFailed,
		RotateFailed,
		ReplaceFailed
	};

	// Fix bázis: ".\\Rajzok" – relatív az aktuális munkakönyvtárhoz.
	// Létrehozza, ha nincs; true ha a mappa létezik/használható.
	bool EnsureRajzokBase();

	// Biztonságos összerakás: csak fájlnév (nincs '\\' vagy '/'), kiterjesztés .twist
	// Visszaadja: ".\\Rajzok\\<nev>.twist"
	std::wstring MakeTwistPath(const std::wstring& baseNameNoExt);

	// Visszaadja a kapcsolódó bak/tmp neveket ugyanabban a mappában.
	std::wstring MakeBak1(const std::wstring& twistPath);   // *.twist.bak
	std::wstring MakeBak2(const std::wstring& twistPath);   // *.twist.bak2
	std::wstring MakeBak3(const std::wstring& twistPath);   // *.twist.bak3
	std::wstring MakeTmp(const std::wstring& twistPath);   // *.twist.tmp

	// 1) Egyszerű mentés pufferből (.tmp -> rotáció -> csere)
	SaveResult SaveTwistWithBackups(const std::wstring& baseNameNoExt,
		const void* data, size_t size);

	// 2) Mentés callbackkel: a callback a .tmp fájl HANDLE-jére írjon (true = siker)
	using WriterFn = std::function<bool(HANDLE hTmp)>;
	SaveResult SaveTwistWithBackups(const std::wstring& baseNameNoExt,
		const WriterFn& writer);

	// Visszaállítás: a legfrissebb elérhető .bak -> .twist
	// Előtte az aktuális .twist-ből készít .bak-ot (rotációval), hogy vissza lehessen lépni.
	SaveResult RestoreFromBak(const std::wstring& baseNameNoExt);

	// Segéd: hibakód -> emberi rövid leírás
	const wchar_t* ToString(SaveResult r);
}
