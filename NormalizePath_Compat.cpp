// NormalizePath_compat.cpp  — kompatibilitási overload a régi hívásokhoz
#include <string>
#include <string_view>

// Az ÚJ függvény deklarációja (már valahol definiálva van):
std::wstring NormalizePath(std::wstring_view in, bool keepTrailingSlash = false);

// A RÉGI szignatúra pótlása (definíció!):
std::wstring NormalizePath(const std::wstring& in)
{
    return NormalizePath(std::wstring_view(in), false);
}
