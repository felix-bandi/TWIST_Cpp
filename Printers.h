#pragma once
#include <windows.h>
#include <winspool.h>
#include <string>
#include <vector>

struct PrinterInfo {
    std::wstring name;
    std::wstring driver;
    std::wstring port;
    DWORD        status = 0;
    bool         isDefault = false;
};

inline std::vector<PrinterInfo> GetAllPrinters()
{
    // 1) Alapértelmezett nyomtató neve
    DWORD need = 0;
    std::wstring defName;
    GetDefaultPrinterW(nullptr, &need);
    if (need) {
        defName.resize(need);
        if (GetDefaultPrinterW(defName.data(), &need) && !defName.empty() && defName.back() == L'\0')
            defName.pop_back(); // trailing NUL le
    }

    // 2) Összes helyi + kapcsolat (hálózati) nyomtató
    DWORD flags = PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS;
    DWORD bytesNeeded = 0, count = 0;
    EnumPrintersW(flags, nullptr, 2, nullptr, 0, &bytesNeeded, &count); // méretkérés

    std::vector<BYTE> buf(bytesNeeded);
    std::vector<PrinterInfo> out;
    if (bytesNeeded == 0) return out;

    if (!EnumPrintersW(flags, nullptr, 2, buf.data(), bytesNeeded, &bytesNeeded, &count))
        return out;

    auto* pi2 = reinterpret_cast<PRINTER_INFO_2W*>(buf.data());
    out.reserve(count);
    for (DWORD i = 0; i < count; ++i) {
        PrinterInfo p;
        if (pi2[i].pPrinterName) p.name = pi2[i].pPrinterName;
        if (pi2[i].pDriverName)  p.driver = pi2[i].pDriverName;
        if (pi2[i].pPortName)    p.port = pi2[i].pPortName;
        p.status = pi2[i].Status;
        p.isDefault = (!defName.empty() && _wcsicmp(p.name.c_str(), defName.c_str()) == 0);
        out.push_back(std::move(p));
    }
    return out;
}
#pragma once
