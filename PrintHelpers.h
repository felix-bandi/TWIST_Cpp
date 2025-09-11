#pragma once
#include <cmath>
#include <limits>
#include <vector>
#include <string>
// Ha a min vagy max makróként van definiálva (pl. windows.h miatt), töröljük őket
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

inline int iroundf(float v) {
    long t = std::lroundf(v); // kerekít, nem truncál
    if (t < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
    if (t > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
    return static_cast<int>(t);
}
// ha esetleg double jön be:
inline int iround(double v) {
    long long t = std::llround(v);
    if (t < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
    if (t > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
    return static_cast<int>(t);
}

// Lekérdezi az összes elérhető nyomtató nevét, külön helyi és hálózati csoportba
void GetPrintersByType(std::vector<std::wstring>& localPrinters, std::vector<std::wstring>& networkPrinters);