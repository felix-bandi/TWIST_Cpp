#include "RajzMentes.h"
#include <shlwapi.h>
#include <string_view>
#pragma comment(lib, "Shlwapi.lib")

namespace {
	inline bool HasSlash(const std::wstring& s) {
		return s.find(L'\\') != std::wstring::npos || s.find(L'/') != std::wstring::npos;
	}
	inline std::wstring EnsureExtTwist(std::wstring name) {
		if (name.size() >= 6) {
			std::wstring ext = name.substr(name.size() - 6);
			for (auto& ch : ext) ch = (wchar_t)towlower(ch);
			if (ext == L".twist") return name;
		}
		return name + L".twist";
	}
	inline bool CreateDirIfMissing(const std::wstring& path) {
		DWORD attr = GetFileAttributesW(path.c_str());
		if (attr != INVALID_FILE_ATTRIBUTES) {
			return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}
		return CreateDirectoryW(path.c_str(), nullptr) != 0;
	}
	inline bool FileExists(const std::wstring& p) {
		DWORD attr = GetFileAttributesW(p.c_str());
		return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
	}
	inline bool MoveReplace(const std::wstring& from, const std::wstring& to) {
		// REPLACE_EXISTING + WRITE_THROUGH a biztonság kedvéért
		return MoveFileExW(from.c_str(), to.c_str(),
			MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH) != 0;
	}
	inline bool DeleteIfExists(const std::wstring& p) {
		if (!FileExists(p)) return true;
		return DeleteFileW(p.c_str()) != 0;
	}
	inline bool RotateBakTriplet(const std::wstring& twistPath) {
		const auto b1 = TWIST::MakeBak1(twistPath);
		const auto b2 = TWIST::MakeBak2(twistPath);
		const auto b3 = TWIST::MakeBak3(twistPath);

		// töröld a legrégebbit
		if (!DeleteIfExists(b3)) return false;
		// b2 -> b3
		if (FileExists(b2) && !MoveReplace(b2, b3)) return false;
		// b1 -> b2
		if (FileExists(b1) && !MoveReplace(b1, b2)) return false;
		return true;
	}
}

namespace TWIST
{
	bool EnsureRajzokBase() {
		std::wstring base = L".\\Rajzok";
		// Ha van NormalizePath, használjuk (nem kötelező)
		base = NormalizePath(base);
		return CreateDirIfMissing(base);
	}

	std::wstring MakeTwistPath(const std::wstring& baseNameNoExt) {
		if (baseNameNoExt.empty() || HasSlash(baseNameNoExt))
			return std::wstring(); // invalid
		std::wstring path = L".\\Rajzok\\";
		path += baseNameNoExt;
		path = EnsureExtTwist(path);
		return NormalizePath(path);
	}

	std::wstring MakeBak1(const std::wstring& twistPath) { return twistPath + L".bak"; }
	std::wstring MakeBak2(const std::wstring& twistPath) { return twistPath + L".bak2"; }
	std::wstring MakeBak3(const std::wstring& twistPath) { return twistPath + L".bak3"; }
	std::wstring MakeTmp(const std::wstring& twistPath) { return twistPath + L".tmp"; }

	static SaveResult DoRotateAndSwap(const std::wstring& twistPath, const std::wstring& tmpPath) {
		// 1) rotáció
		if (!RotateBakTriplet(twistPath))
			return SaveResult::RotateFailed;

		// 2) aktuális -> .bak (ha létezik)
		const auto b1 = MakeBak1(twistPath);
		if (FileExists(twistPath)) {
			if (!MoveReplace(twistPath, b1))
				return SaveResult::RotateFailed;
		}

		// 3) tmp -> twist (csere)
		if (!MoveReplace(tmpPath, twistPath))
			return SaveResult::ReplaceFailed;

		return SaveResult::Ok;
	}

	static SaveResult WriteTmpFromBuffer(const std::wstring& tmpPath, const void* data, size_t size) {
		HANDLE h = CreateFileW(tmpPath.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
		if (h == INVALID_HANDLE_VALUE)
			return SaveResult::TempCreateFailed;

		SaveResult res = SaveResult::Ok;
		DWORD written = 0;
		const BYTE* p = static_cast<const BYTE*>(data);
		size_t left = size;
		while (left > 0) {
			DWORD chunk = (left > 1 << 20) ? (1 << 20) : (DWORD)left;
			if (!WriteFile(h, p, chunk, &written, nullptr) || written != chunk) {
				res = SaveResult::WriteFailed;
				break;
			}
			p += chunk;
			left -= chunk;
		}
		if (res == SaveResult::Ok) {
			if (!FlushFileBuffers(h))
				res = SaveResult::FlushFailed;
		}
		CloseHandle(h);
		return res;
	}

	SaveResult SaveTwistWithBackups(const std::wstring& baseNameNoExt,
		const void* data, size_t size)
	{
		if (!EnsureRajzokBase())
			return SaveResult::CreateBaseFailed;

		if (baseNameNoExt.empty() || HasSlash(baseNameNoExt))
			return SaveResult::InvalidName;

		const auto twistPath = MakeTwistPath(baseNameNoExt);
		if (twistPath.empty())
			return SaveResult::InvalidName;

		const auto tmpPath = MakeTmp(twistPath);

		// 1) tmp megírás
		if (auto r = WriteTmpFromBuffer(tmpPath, data, size); r != SaveResult::Ok) {
			DeleteIfExists(tmpPath);
			return r;
		}
		// 2) rotáció + csere
		auto rr = DoRotateAndSwap(twistPath, tmpPath);
		// takarítás (hibánál is próbáljuk törölni a tmp-t)
		DeleteIfExists(tmpPath);
		return rr;
	}

	TWIST::SaveResult TWIST::SaveTwistWithBackups(const std::wstring& baseNameNoExt,
		const WriterFn& writer)
	{
		if (!EnsureRajzokBase())
			return SaveResult::CreateBaseFailed;

		if (baseNameNoExt.empty() || HasSlash(baseNameNoExt))
			return SaveResult::InvalidName;

		const auto twistPath = MakeTwistPath(baseNameNoExt);
		if (twistPath.empty())
			return SaveResult::InvalidName;

		const auto tmpPath = MakeTmp(twistPath);

		// 1) tmp létrehozás
		HANDLE h = CreateFileW(tmpPath.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
		if (h == INVALID_HANDLE_VALUE)
			return SaveResult::TempCreateFailed;

		bool ok = false;
		// Írás C++ try/catch-csel, hogy mindig zárjunk
		try {
			ok = writer ? writer(h) : false;
		}
		catch (...) {
			CloseHandle(h);
			DeleteIfExists(tmpPath);
			return SaveResult::WriteFailed;
		}

		BOOL flushed = FlushFileBuffers(h);
		CloseHandle(h);

		if (!ok) {
			DeleteIfExists(tmpPath);
			return SaveResult::WriteFailed;
		}
		if (!flushed) {
			DeleteIfExists(tmpPath);
			return SaveResult::FlushFailed;
		}

		// 2) rotáció + csere
		auto rr = DoRotateAndSwap(twistPath, tmpPath);
		DeleteIfExists(tmpPath);
		return rr;
	}


	SaveResult RestoreFromBak(const std::wstring& baseNameNoExt)
	{
		if (!EnsureRajzokBase())
			return SaveResult::CreateBaseFailed;

		if (baseNameNoExt.empty() || HasSlash(baseNameNoExt))
			return SaveResult::InvalidName;

		const auto twistPath = MakeTwistPath(baseNameNoExt);
		const auto b1 = MakeBak1(twistPath);
		const auto b2 = MakeBak2(twistPath);
		const auto b3 = MakeBak3(twistPath);

		// melyik .bak érhető el?
		std::wstring src;
		if (FileExists(b1)) src = b1;
		else if (FileExists(b2)) src = b2;
		else if (FileExists(b3)) src = b3;
		else return SaveResult::ReplaceFailed; // nincs mit visszaállítani

		// Mentsük el az aktuális .twist-et, hogy legyen visszaút
		if (!RotateBakTriplet(twistPath))
			return SaveResult::RotateFailed;
		if (FileExists(twistPath) && !MoveReplace(twistPath, b1))
			return SaveResult::RotateFailed;

		// .bak -> .twist
		if (!MoveReplace(src, twistPath))
			return SaveResult::ReplaceFailed;

		return SaveResult::Ok;
	}

	const wchar_t* ToString(SaveResult r) {
		switch (r) {
		case SaveResult::Ok:                return L"Ok";
		case SaveResult::CreateBaseFailed:  return L"Nem hozható létre a .\\Rajzok mappa";
		case SaveResult::InvalidName:       return L"Érvénytelen fájlnév (ne tartalmazzon útvonalat)";
		case SaveResult::TempCreateFailed:  return L"Nem hozható létre ideiglenes fájl";
		case SaveResult::WriteFailed:       return L"Írási hiba";
		case SaveResult::FlushFailed:       return L"FlushFileBuffers hiba";
		case SaveResult::RotateFailed:      return L".bak rotáció hiba";
		case SaveResult::ReplaceFailed:     return L"Csere/átnevezés hiba";
		default:                            return L"Ismeretlen hiba";
		}
	}
}
