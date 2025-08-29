// ÚJ: segédfüggvények a fájl elérési utakhoz és névhez
static std::wstring GetAppRoot()
{
    wchar_t buf[MAX_PATH];
    DWORD n = GetModuleFileNameW(nullptr, buf, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) return L".";
    std::wstring p(buf, buf + n);
    size_t pos = p.find_last_of(L"\\/");
    if (pos != std::wstring::npos) p.erase(pos);
    return p;
}

static void EnsureDataDirs(std::wstring& dirAlk, std::wstring& dirRajz)
{
    auto root = GetAppRoot();
    dirAlk = root + L"\\Alkatresz";
    dirRajz = root + L"\\Rajzok";
    CreateDirectoryW(dirAlk.c_str(), nullptr);
    CreateDirectoryW(dirRajz.c_str(), nullptr);
}

static std::string BytesToAscii(const std::vector<byte>& v)
{
    std::string s; s.reserve(v.size());
    for (auto b : v) if (b >= 32 && b < 127) s.push_back((char)b);
    return s;
}

static std::string MakeSafeName(std::string name, const char* defName)
{
    if (name.empty()) name = defName;
    const char* bad = "<>:\"/\\|?*";
    for (char& c : name)
        if (strchr(bad, c) || (unsigned char)c < 32) c = '_';
    // opcionális: trimmelés
    while (!name.empty() && (name.back() == ' ' || name.back() == '.')) name.pop_back();
    if (name.empty()) name = defName;
    return name;
}

static std::wstring WJoin(const std::wstring& dir, const std::wstring& file)
{
    if (dir.empty()) return file;
    if (!dir.empty() && (dir.back() == L'\\' || dir.back() == L'/')) return dir + file;
    return dir + L"\\" + file;
}

// MÓDOSÍTOTT: Save – külön fájl rajzoknak és alkatrészeknek
void MainWindow::Save(mentés ment)
{
    std::wstring dirAlk, dirRajz;
    EnsureDataDirs(dirAlk, dirRajz);

    // név a dialog.edit.c-bõl (ASCII), biztonságosítás
    std::string baseName = MakeSafeName(BytesToAscii(dialog.edit.c),
                                        ment == mentés::rajz ? "Rajz" : "Alkatresz");

    std::wstring wfile;
    if (ment == mentés::rajz)
        wfile = WJoin(dirRajz, std::wstring(baseName.begin(), baseName.end()) + L".twist");
    else
        wfile = WJoin(dirAlk, std::wstring(baseName.begin(), baseName.end()) + L".alk");

    std::ofstream f;
    f.open(wfile); // MSVC támogatja a wchar_t* path-ot
    if (!f.is_open()) { save = 88; return; }

    if (ment == mentés::alkatrész)
    {
        // fejléc az alkatrész névvel
        f << "_" << baseName << ":\n";
    }

    for (int i = 0; i < (int)VONAL_vector.size(); i++)
    {
        f << "Vonal "
          << VONAL_vector[i].x1 << ' '
          << VONAL_vector[i].y1 << ' '
          << VONAL_vector[i].x2 << ' '
          << VONAL_vector[i].y2 << ' '
          << VONAL_vector[i].v  << ' '
          << VONAL_vector[i].szint << '\n';
    }
    for (int i = 0; i < (int)ARC_vector.size(); i++)
    {
        f << "Körív "
          << ARC_vector[i].i   << ' '
          << ARC_vector[i].kpx << ' '
          << ARC_vector[i].kpy << ' '
          << ARC_vector[i].ksz << ' '
          << ARC_vector[i].rx  << ' '
          << ARC_vector[i].ry  << ' '
          << ARC_vector[i].s   << ' '
          << ARC_vector[i].szint << ' '
          << ARC_vector[i].v   << ' '
          << ARC_vector[i].vsz << ' '
          << ARC_vector[i].xk  << ' '
          << ARC_vector[i].xv  << ' '
          << ARC_vector[i].yk  << ' '
          << ARC_vector[i].yv  << '\n';
    }
    for (int i = 0; i < (int)POLIGON_vector.size(); i++)
    {
        f << "Poligon "
          << POLIGON_vector[i].szint << ' '
          << POLIGON_vector[i].pont.size() << ' ';
        for (int p = 0; p < (int)POLIGON_vector[i].pont.size(); p++)
            f << POLIGON_vector[i].pont[p].x << ' ' << POLIGON_vector[i].pont[p].y << ' ';
        f << '\n';
    }
    for (int i = 0; i < (int)EL_vector.size(); i++)
    {
        f << "EL "
          << EL_vector[i].r  << ' '
          << EL_vector[i].rx << ' '
          << EL_vector[i].ry << ' '
          << EL_vector[i].szint << ' '
          << EL_vector[i].x  << ' '
          << EL_vector[i].y  << '\n';
    }
    for (int i = 0; i < (int)SQ_vector.size(); i++)
    {
        f << "SQ "
          << SQ_vector[i].r  << ' '
          << SQ_vector[i].rx << ' '
          << SQ_vector[i].ry << ' '
          << SQ_vector[i].szint << ' '
          << SQ_vector[i].x  << ' '
          << SQ_vector[i].y  << '\n';
    }
    for (int i = 0; i < (int)RR_vector.size(); i++)
    {
        f << "RR "
          << RR_vector[i].r   << ' '
          << RR_vector[i].rx  << ' '
          << RR_vector[i].ry  << ' '
          << RR_vector[i].rrx << ' '
          << RR_vector[i].rry << ' '
          << RR_vector[i].szint << ' '
          << RR_vector[i].x   << ' '
          << RR_vector[i].y   << '\n';
    }
    for (int i = 0; i < (int)ELVIA_vector.size(); i++)
        f << "EV " << ELVIA_vector[i].r << ' ' << ELVIA_vector[i].rx << ' ' << ELVIA_vector[i].ry << ' '
          << ELVIA_vector[i].x << ' ' << ELVIA_vector[i].y << '\n';
    for (int i = 0; i < (int)SQVIA_vector.size(); i++)
        f << "SV " << SQVIA_vector[i].r << ' ' << SQVIA_vector[i].rx << ' ' << SQVIA_vector[i].ry << ' '
          << SQVIA_vector[i].x << ' ' << SQVIA_vector[i].y << '\n';
    for (int i = 0; i < (int)RRVIA_vector.size(); i++)
        f << "RV " << RRVIA_vector[i].r << ' ' << RRVIA_vector[i].rx << ' ' << RRVIA_vector[i].ry << ' '
          << RRVIA_vector[i].rrx << ' ' << RRVIA_vector[i].rry << ' '
          << RRVIA_vector[i].x << ' ' << RRVIA_vector[i].y << '\n';

    if (ment == mentés::alkatrész) f << "|\n";

    save = 66;
    f.close();
}

// ÚJ: Load – külön fájl rajzoknak és alkatrészeknek
void MainWindow::Load(mentés tölt)
{
    bool alk = (tölt == alkatrész);

    std::wstring dirAlk, dirRajz;
    EnsureDataDirs(dirAlk, dirRajz);

    // név beolvasása
    std::string baseName = BytesToAscii(dialog.edit.c);
    baseName = MakeSafeName(baseName, alk ? "Alkatresz" : "Rajz");

    std::wstring prefer;
    if (alk) prefer = WJoin(dirAlk, std::wstring(baseName.begin(), baseName.end()) + L".alk");
    else     prefer = WJoin(dirRajz, std::wstring(baseName.begin(), baseName.end()) + L".twist");

    std::ifstream f;
    f.open(prefer);
    if (!f.is_open())
    {
        // visszafelé kompatibilitás
        if (alk) f.open("alkatrészek.alkatrész");
        else     f.open("rajz.twist");
        if (!f.is_open()) { save = 99; return; }
    }

    int alk_sz = -1;
    std::string sor;
    char s[256], *a, *b, ss[256];
    ALKATRÉSZ alkatresz;

    auto pushPart = [&]()
    {
        if (!alk) return;
        if (alkatresz.név.empty() &&
            VONAL_betölt.empty() && ARC_betölt.empty() && POLIGON_betölt.empty() &&
            EL_betölt.empty() && SQ_betölt.empty() && RR_betölt.empty() &&
            ELVIA_betölt.empty() && SQVIA_betölt.empty() && RRVIA_betölt.empty())
            return;

        if (VONAL_betölt.size())   alkatresz.v.insert(alkatresz.v.end(), VONAL_betölt.begin(), VONAL_betölt.end());
        if (ARC_betölt.size())     alkatresz.a.insert(alkatresz.a.end(), ARC_betölt.begin(), ARC_betölt.end());
        if (POLIGON_betölt.size()) alkatresz.p.insert(alkatresz.p.end(), POLIGON_betölt.begin(), POLIGON_betölt.end());
        if (EL_betölt.size())      alkatresz.ep.insert(alkatresz.ep.end(), EL_betölt.begin(), EL_betölt.end());
        if (SQ_betölt.size())      alkatresz.sp.insert(alkatresz.sp.end(), SQ_betölt.begin(), SQ_betölt.end());
        if (RR_betölt.size())      alkatresz.rp.insert(alkatresz.rp.end(), RR_betölt.begin(), RR_betölt.end());
        if (ELVIA_betölt.size())   alkatresz.ev.insert(alkatresz.ev.end(), ELVIA_betölt.begin(), ELVIA_betölt.end());
        if (SQVIA_betölt.size())   alkatresz.sv.insert(alkatresz.sv.end(), SQVIA_betölt.begin(), SQVIA_betölt.end());
        if (RRVIA_betölt.size())   alkatresz.rv.insert(alkatresz.rv.end(), RRVIA_betölt.begin(), RRVIA_betölt.end());

        Alkatrész.push_back(alkatresz);
        alkatresz.név.clear();
        alkatresz.v.clear(); alkatresz.a.clear(); alkatresz.p.clear();
        alkatresz.ep.clear(); alkatresz.sp.clear(); alkatresz.rp.clear();
        alkatresz.ev.clear(); alkatresz.sv.clear(); alkatresz.rv.clear();
        Betölt_clear();
    };

    if (f.is_open())
    {
        save = 55;
        Betölt_clear();

        while (std::getline(f, sor))
        {
            if (sor.empty()) continue;
            strncpy_s(s, sor.c_str(), _TRUNCATE);
            strncpy_s(ss, sor.c_str(), _TRUNCATE);
            a = strtok_s(s, " ", &b);

            if (ss[0] == '_')
            {
                // új alkatrész blokk
                if (!alkatresz.név.empty()) pushPart();
                alk_sz++;
                alkatresz.név.clear();
                for (size_t i = 1; i < strlen(ss); ++i)
                {
                    if (ss[i] == ':') break;
                    alkatresz.név.push_back(ss[i]);
                }
                continue;
            }
            if (s[0] == '|') { pushPart(); continue; }

            // Vonal / Körív / Poligon / EL / SQ / RR / EV / SV / RV
            // (a te kódod itt marad)
        }

        // fájl vége: ha maradt nyitott alkatrész
        pushPart();

        if (!alk) betöltés = true;
        f.close();
    }
    else save = 99;
}