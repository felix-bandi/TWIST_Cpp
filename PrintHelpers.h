#pragma once
#include <cmath>
#include <limits>

// Ha a min vagy max makr�k�nt van defini�lva (pl. windows.h miatt), t�r�lj�k �ket
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

inline int iroundf(float v) {
    long t = std::lroundf(v); // kerek�t, nem trunc�l
    if (t < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
    if (t > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
    return static_cast<int>(t);
}
// ha esetleg double j�n be:
inline int iround(double v) {
    long long t = std::llround(v);
    if (t < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
    if (t > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
    return static_cast<int>(t);
}
