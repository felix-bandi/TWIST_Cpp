#include "PrintHelpers.h"
#include <windows.h>
#include <winspool.h>
#include <vector>
#include <string>

void GetPrintersByType(std::vector<std::wstring>& localPrinters, std::vector<std::wstring>& networkPrinters)
{
    DWORD needed = 0, returned = 0;
    EnumPrintersW(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 2, nullptr, 0, &needed, &returned);
    if (needed == 0) return;

    std::vector<BYTE> buffer(needed);
    if (!EnumPrintersW(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 2, buffer.data(), needed, &needed, &returned))
        return;

    PRINTER_INFO_2W* printers = reinterpret_cast<PRINTER_INFO_2W*>(buffer.data());
    for (DWORD i = 0; i < returned; ++i)
    {
        if (printers[i].Attributes & PRINTER_ATTRIBUTE_NETWORK)
            networkPrinters.push_back(printers[i].pPrinterName);
        else
            localPrinters.push_back(printers[i].pPrinterName);
    }
}