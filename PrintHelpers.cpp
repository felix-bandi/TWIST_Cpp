#include "PrintHelpers.h"
#include <windows.h>
#include <winspool.h>
//#pragma comment(lib, "Winspool.lib")
#include <vector>
#include <string>
#include <cwctype>

std::vector<Nyomtato> nyomtato;

static std::wstring to_lower_copy(const std::wstring& s) {
    std::wstring out; out.reserve(s.size());
    for (wchar_t c : s) out.push_back(static_cast<wchar_t>(std::towlower(c)));
    return out;
}

static bool is_virtual_by_name(const std::wstring& name) {
    auto n = to_lower_copy(name);
    return n.find(L"pdf") != std::wstring::npos ||
        n.find(L"xps") != std::wstring::npos ||
        n.find(L"fax") != std::wstring::npos ||
        n.find(L"onenote") != std::wstring::npos;
}

// includeConnections=false → csak helyi; true → a felhasználói kapcsolatok is (lassabb lehet)
void GetPrintersByType(std::vector<Nyomtato>& ny, bool includeConnections = false)
{
    std::wstring defaultName;
    const bool haveDefault = GetDefaultPrinterName(defaultName);
    const DWORD flags = PRINTER_ENUM_LOCAL | (includeConnections ? PRINTER_ENUM_CONNECTIONS : 0);

    DWORD needed = 0, returned = 0;
    EnumPrintersW(flags, nullptr, 4, nullptr, 0, &needed, &returned);
    if (needed == 0) { ny.clear(); return; }

    std::vector<BYTE> buffer(needed);
    if (!EnumPrintersW(flags, nullptr, 4, buffer.data(), needed, &needed, &returned)) {
        ny.clear(); return;
    }

    auto* printers = reinterpret_cast<PRINTER_INFO_4W*>(buffer.data());
    ny.clear();
    ny.reserve(returned);

    for (DWORD i = 0; i < returned; ++i) 
    {
        const auto& pi = printers[i];
        Nyomtato p;
        p.name = pi.pPrinterName ? pi.pPrinterName : L"?----?";

        const bool isNet = (pi.Attributes & PRINTER_ATTRIBUTE_NETWORK) != 0
            || (pi.pServerName && *pi.pServerName); // szervernév → gyakran hálózati
        const bool isVirt = is_virtual_by_name(p.name); // INFO_4-ben csak név-heurisztika elérhető

        p.tipus = isNet ? (isVirt ? std::byte{ 4 } : std::byte{ 3 })
            : (isVirt ? std::byte{ 2 } : std::byte{ 1 });

        p.alap = haveDefault && (p.name == defaultName);
        ny.push_back(std::move(p));
    }
	AppendTypeToName(ny);
}
// 1) Segédfüggvény: default nyomtató neve
static bool GetDefaultPrinterName(std::wstring& out)
{
    DWORD need = 0;
    GetDefaultPrinterW(nullptr, &need);
    if (need == 0) return false;
    out.resize(need - 1); // need tartalmazza a záró nullát
    return GetDefaultPrinterW(out.data(), &need) != FALSE;
}

void AppendTypeToName(std::vector<Nyomtato>& nyomtatoList) {
    for (auto& printer : nyomtatoList) {
        switch (static_cast<int>(printer.tipus)) {
        case 1:
            printer.name += L" : (helyi)";
            break;
        case 2:
            printer.name += L" : (helyi virtuális)";
            break;
        case 3:
            printer.name += L" : (hálózati)";
            break;
        case 4:
            printer.name += L" : (hálózati virtuális)";
            break;
        default:
            printer.name += L" : (ismeretlen típus)";
            break;
        }
    }
}
/*void GetPrintersByType(std::vector<Nyomtato>& ny)
{
    DWORD needed = 0, returned = 0;
    EnumPrintersW(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 2, nullptr, 0, &needed, &returned);
    if (needed == 0) return;

    std::vector<BYTE> buffer(needed);
    if (!EnumPrintersW(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 2, buffer.data(), needed, &needed, &returned))
        return;

    PRINTER_INFO_2W* printers = reinterpret_cast<PRINTER_INFO_2W*>(buffer.data());
	ny.clear();
	ny.reserve(returned);
    for (DWORD i = 0; i < returned; ++i)
    {
        Nyomtato p;
        p.name = printers[i].pPrinterName ? printers[i].pPrinterName : L"";
       
		ny.push_back(p);
    }
}*/