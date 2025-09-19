#include <string>
#include <vector>
#include <algorithm>
#include <cwctype>

static inline bool is_slash(wchar_t c) noexcept { return c == L'\\' || c == L'/'; }

std::wstring NormalizePath(std::wstring_view in, bool keepTrailingSlash = false)
{
    if (in.empty()) return std::wstring();

    // 1) másolat + elválasztók egységesítése
    std::wstring s(in);
    std::replace(s.begin(), s.end(), L'/', L'\\');

    // 2) extended / device prefixek kezelése: \\?\  vagy  \\.\ 
    const std::wstring kExt1 = L"\\\\?\\";
    const std::wstring kExt2 = L"\\\\.\\";
    bool hasExtended = false;
    std::wstring prefix;

    if (s.rfind(kExt1, 0) == 0) { hasExtended = true; prefix = kExt1; s.erase(0, kExt1.size()); }
    else if (s.rfind(kExt2, 0) == 0) { hasExtended = true; prefix = kExt2; s.erase(0, kExt2.size()); }

    // 3) Ha extended: csak minimális tisztítás (ne bontsuk fel . és .. szerint, hogy ne sértsük a szemantikát)
    if (hasExtended) {
        // többszörös '\' tömörítése a prefix UTÁN
        std::wstring out; out.reserve(prefix.size() + s.size());
        out += prefix;
        bool lastWasSlash = false;
        for (wchar_t ch : s) {
            if (ch == L'\\') {
                if (!lastWasSlash) out.push_back(L'\\');
                lastWasSlash = true;
            }
            else {
                out.push_back(ch);
                lastWasSlash = false;
            }
        }
        return out;
    }

    // 4) UNC vagy meghajtós?
    bool isUNC = false;
    std::wstring root;     // "C:\", vagy "\\server\share"
    size_t startIdx = 0;

    if (s.rfind(L"\\\\", 0) == 0) {
        isUNC = true;
        // Szedd ki a szerver és share komponenseket
        size_t i = 2; // átugorjuk a leading "\\"
        auto nextComp = [&](size_t from)->std::pair<std::wstring, size_t> {
            size_t j = from;
            while (j < s.size() && s[j] != L'\\') ++j;
            return { s.substr(from, j - from), j };
            };
        auto [server, p1] = nextComp(i);
        std::wstring share;
        if (p1 < s.size() && s[p1] == L'\\') ++p1;
        if (p1 <= s.size()) {
            auto [shareTmp, p2] = nextComp(p1);
            share = shareTmp; startIdx = p2;
            if (startIdx < s.size() && s[startIdx] == L'\\') ++startIdx;
        }
        // Ha nincs rendes UNC gyökér, kezeld „üres” gyökérként
        if (!server.empty() && !share.empty()) {
            root = L"\\\\" + server + L"\\" + share;
        }
        else {
            root = L"\\\\"; // degenerált UNC; tartjuk, amit lehet
        }
    }
    else if (s.size() >= 2 && std::iswalpha(s[0]) && s[1] == L':') {
        // meghajtós útvonal
        wchar_t drive = s[0];
        root.assign({ drive, L':', L'\\' });
        startIdx = 2;
        if (startIdx < s.size() && s[startIdx] == L'\\') ++startIdx;
    }

    // 5) Komponensek tokenizálása és normalizálása (., ..)
    std::vector<std::wstring> comps;
    size_t i = startIdx;
    while (i < s.size()) {
        // ugord át a többszörös '\'-t
        while (i < s.size() && s[i] == L'\\') ++i;
        if (i >= s.size()) break;
        size_t j = i;
        while (j < s.size() && s[j] != L'\\') ++j;
        std::wstring comp = s.substr(i, j - i);
        i = j;

        if (comp == L"." || comp.empty()) {
            // kihagy
            continue;
        }
        if (comp == L"..") {
            if (!comps.empty()) {
                comps.pop_back();
            }
            else {
                // relatív útvonalnál a vezető „..” megőrizhető; abszolútnál/UNC-nál nem mehetünk feljebb
                if (root.empty()) comps.emplace_back(L"..");
            }
            continue;
        }
        comps.emplace_back(std::move(comp));
    }

    // 6) Összerakás
    std::wstring out;
    if (!root.empty()) {
        out = root;
    }
    // Ha root üres és az input relatív volt, akkor nincs leading '\'
    for (size_t k = 0; k < comps.size(); ++k) {
        if (!out.empty() && out.back() != L'\\') out.push_back(L'\\');
        else if (out.empty() && isUNC) out = L"\\\\"; // degenerált UNC folytatásához
        out += comps[k];
    }

    // 7) Trailing szabály
    auto isRootPath = [&]() -> bool {
        if (isUNC) {
            // UNC gyökér: \\server\share
            return !root.empty() && out.size() == root.size();
        }
        // meghajtó gyökér: "C:\"
        return (!root.empty() && out == root);
        };

    if (keepTrailingSlash) {
        if (!out.empty() && out.back() != L'\\' && !isRootPath()) out.push_back(L'\\');
    }
    else {
        // gyökér kivételével töröljük a záró '\'-t
        if (!isRootPath() && !out.empty() && out.back() == L'\\') out.pop_back();
    }

    // Speciális eset: ha semmi komponens nincs és nincs root → üres marad
    if (out.empty() && !root.empty()) out = root;

    return out;
}
