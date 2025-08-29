// �J: seg�df�ggv�nyek a f�jl el�r�si utakhoz �s n�vhez
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
    // opcion�lis: trimmel�s
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

// M�DOS�TOTT: Save � k�l�n f�jl rajzoknak �s alkatr�szeknek
void MainWindow::Save(ment�s ment)
{
    std::wstring dirAlk, dirRajz;
    EnsureDataDirs(dirAlk, dirRajz);

    // n�v a dialog.edit.c-b�l (ASCII), biztons�gos�t�s
    std::string baseName = MakeSafeName(BytesToAscii(dialog.edit.c),
                                        ment == ment�s::rajz ? "Rajz" : "Alkatresz");

    std::wstring wfile;
    if (ment == ment�s::rajz)
        wfile = WJoin(dirRajz, std::wstring(baseName.begin(), baseName.end()) + L".twist");
    else
        wfile = WJoin(dirAlk, std::wstring(baseName.begin(), baseName.end()) + L".alk");

    std::ofstream f;
    f.open(wfile); // MSVC t�mogatja a wchar_t* path-ot
    if (!f.is_open()) { save = 88; return; }

    if (ment == ment�s::alkatr�sz)
    {
        // fejl�c az alkatr�sz n�vvel
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
        f << "K�r�v "
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

    if (ment == ment�s::alkatr�sz) f << "|\n";

    save = 66;
    f.close();
}

// �J: Load � k�l�n f�jl rajzoknak �s alkatr�szeknek
void MainWindow::Load(ment�s t�lt)
{
    bool alk = (t�lt == alkatr�sz);

    std::wstring dirAlk, dirRajz;
    EnsureDataDirs(dirAlk, dirRajz);

    // n�v beolvas�sa
    std::string baseName = BytesToAscii(dialog.edit.c);
    baseName = MakeSafeName(baseName, alk ? "Alkatresz" : "Rajz");

    std::wstring prefer;
    if (alk) prefer = WJoin(dirAlk, std::wstring(baseName.begin(), baseName.end()) + L".alk");
    else     prefer = WJoin(dirRajz, std::wstring(baseName.begin(), baseName.end()) + L".twist");

    std::ifstream f;
    f.open(prefer);
    if (!f.is_open())
    {
        // visszafel� kompatibilit�s
        if (alk) f.open("alkatr�szek.alkatr�sz");
        else     f.open("rajz.twist");
        if (!f.is_open()) { save = 99; return; }
    }

    int alk_sz = -1;
    std::string sor;
    char s[256], *a, *b, ss[256];
    ALKATR�SZ alkatresz;

    auto pushPart = [&]()
    {
        if (!alk) return;
        if (alkatresz.n�v.empty() &&
            VONAL_bet�lt.empty() && ARC_bet�lt.empty() && POLIGON_bet�lt.empty() &&
            EL_bet�lt.empty() && SQ_bet�lt.empty() && RR_bet�lt.empty() &&
            ELVIA_bet�lt.empty() && SQVIA_bet�lt.empty() && RRVIA_bet�lt.empty())
            return;

        if (VONAL_bet�lt.size())   alkatresz.v.insert(alkatresz.v.end(), VONAL_bet�lt.begin(), VONAL_bet�lt.end());
        if (ARC_bet�lt.size())     alkatresz.a.insert(alkatresz.a.end(), ARC_bet�lt.begin(), ARC_bet�lt.end());
        if (POLIGON_bet�lt.size()) alkatresz.p.insert(alkatresz.p.end(), POLIGON_bet�lt.begin(), POLIGON_bet�lt.end());
        if (EL_bet�lt.size())      alkatresz.ep.insert(alkatresz.ep.end(), EL_bet�lt.begin(), EL_bet�lt.end());
        if (SQ_bet�lt.size())      alkatresz.sp.insert(alkatresz.sp.end(), SQ_bet�lt.begin(), SQ_bet�lt.end());
        if (RR_bet�lt.size())      alkatresz.rp.insert(alkatresz.rp.end(), RR_bet�lt.begin(), RR_bet�lt.end());
        if (ELVIA_bet�lt.size())   alkatresz.ev.insert(alkatresz.ev.end(), ELVIA_bet�lt.begin(), ELVIA_bet�lt.end());
        if (SQVIA_bet�lt.size())   alkatresz.sv.insert(alkatresz.sv.end(), SQVIA_bet�lt.begin(), SQVIA_bet�lt.end());
        if (RRVIA_bet�lt.size())   alkatresz.rv.insert(alkatresz.rv.end(), RRVIA_bet�lt.begin(), RRVIA_bet�lt.end());

        Alkatr�sz.push_back(alkatresz);
        alkatresz.n�v.clear();
        alkatresz.v.clear(); alkatresz.a.clear(); alkatresz.p.clear();
        alkatresz.ep.clear(); alkatresz.sp.clear(); alkatresz.rp.clear();
        alkatresz.ev.clear(); alkatresz.sv.clear(); alkatresz.rv.clear();
        Bet�lt_clear();
    };

    if (f.is_open())
    {
        save = 55;
        Bet�lt_clear();

        while (std::getline(f, sor))
        {
            if (sor.empty()) continue;
            strncpy_s(s, sor.c_str(), _TRUNCATE);
            strncpy_s(ss, sor.c_str(), _TRUNCATE);
            a = strtok_s(s, " ", &b);

            if (ss[0] == '_')
            {
                // �j alkatr�sz blokk
                if (!alkatresz.n�v.empty()) pushPart();
                alk_sz++;
                alkatresz.n�v.clear();
                for (size_t i = 1; i < strlen(ss); ++i)
                {
                    if (ss[i] == ':') break;
                    alkatresz.n�v.push_back(ss[i]);
                }
                continue;
            }
            if (s[0] == '|') { pushPart(); continue; }

            // Vonal / K�r�v / Poligon / EL / SQ / RR / EV / SV / RV
            // (a te k�dod itt marad)
        }

        // f�jl v�ge: ha maradt nyitott alkatr�sz
        pushPart();

        if (!alk) bet�lt�s = true;
        f.close();
    }
    else save = 99;
}