#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <cstdlib>

#include "studentas.h"
#include "failai.h"
#include "rusiavimas.h"

using namespace std;
using namespace std::chrono;

int main() {
    ios::sync_with_stdio(false);
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Pasirinkite konteinerio tipa:\n";
    cout << "1 - std::vector\n";
    cout << "2 - std::list\n";
    int konteinerisTipas;
    while (!(cin >> konteinerisTipas) || (konteinerisTipas != 1 && konteinerisTipas != 2)) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    double failoLaikas = 0.0;
    double rusiavimoLaikas = 0.0;
    double isvedimoLaikas = 0.0;

    cout << "\nPasirinkite veiksma:\n";
    cout << "1 - Zinomas pazymiu skaicius\n";
    cout << "2 - Nezinomas pazymiu skaicius (ENTER x2)\n";
    cout << "3 - Generuoti pazymius\n";
    cout << "4 - Nuskaityti duomenis is failo\n";
    cout << "5 - Sugeneruoti nauja faila\n";

    int budas;
    while (!(cin >> budas) || budas < 1 || budas > 5) {
        cout << "Neteisingas pasirinkimas: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (budas == 5) {
        GeneruotiFaila();
        return 0;
    }

    vector<Studentas> vGrupe;
    list<Studentas> lGrupe;
    string fname;

    if (budas == 4) {
        cout << "Iveskite failo pavadinima: ";
        cin >> fname;

        auto start = high_resolution_clock::now();
        vGrupe = Stud_from_file(fname);
        auto end = high_resolution_clock::now();
        failoLaikas = duration_cast<duration<double>>(end - start).count();

        if (konteinerisTipas == 2) {
            lGrupe.assign(vGrupe.begin(), vGrupe.end());
            vGrupe.clear();
        }
    }
    else {
        int n;
        cout << "Kiek studentu grupeje: ";
        while (!(cin >> n) || n <= 0) {
            cout << "Netinkamas skaicius. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        for (int i = 0; i < n; ++i) {
            Studentas st = Stud_iv(budas);
            if (konteinerisTipas == 1)
                vGrupe.push_back(st);
            else
                lGrupe.push_back(st);
        }
    }

    if ((konteinerisTipas == 1 && vGrupe.empty()) || (konteinerisTipas == 2 && lGrupe.empty())) {
        cout << "Nerasta duomenu!\n";
        return 0;
    }

    if (konteinerisTipas == 1) {
        std::transform(vGrupe.begin(), vGrupe.end(), vGrupe.begin(), [](Studentas& s) {
            s.galVid = SkaiciuotiVidurki(s.namuDarbai);
            s.galMed = SkaiciuotiMediana(s.namuDarbai);
            return s;
            });
    }
    else {
        std::transform(lGrupe.begin(), lGrupe.end(), lGrupe.begin(), [](Studentas& s) {
            s.galVid = SkaiciuotiVidurki(s.namuDarbai);
            s.galMed = SkaiciuotiMediana(s.namuDarbai);
            return s;
            });
    }


    int kriterijus;
    cout << "\nPasirinkite kriteriju studentu dalinimui:\n";
    cout << "1 - Pagal vidurki\n";
    cout << "2 - Pagal mediana\n";
    while (!(cin >> kriterijus) || (kriterijus != 1 && kriterijus != 2)) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (konteinerisTipas == 1) {
        vector<Studentas> vargsiukai;

        Rikiuoti(vGrupe);

        auto startR = high_resolution_clock::now();
        Strategija3(vGrupe, vargsiukai, kriterijus);
        auto endR = high_resolution_clock::now();
        rusiavimoLaikas = duration_cast<duration<double>>(endR - startR).count();

        auto startI = high_resolution_clock::now();
        Spausdinti(vargsiukai, "vargsiukai.txt");
        if (budas == 4) Spausdinti(vGrupe, fname);
        auto endI = high_resolution_clock::now();
        isvedimoLaikas = duration_cast<duration<double>>(endI - startI).count();
    }
    else {
        list<Studentas> vargsiukai;

        Rikiuoti(lGrupe);

        auto startR = high_resolution_clock::now();
        Strategija3(lGrupe, vargsiukai, kriterijus);
        auto endR = high_resolution_clock::now();
        rusiavimoLaikas = duration_cast<duration<double>>(endR - startR).count();

        auto startI = high_resolution_clock::now();
        Spausdinti(vargsiukai, "vargsiukai.txt");
        if (budas == 4) Spausdinti(lGrupe, fname);
        auto endI = high_resolution_clock::now();
        isvedimoLaikas = duration_cast<duration<double>>(endI - startI).count();
    }

    double bendrasLaikas = failoLaikas + rusiavimoLaikas + isvedimoLaikas;

    cout << "\n===== LAIKO MATAVIMAI =====\n";
    cout << "Failo nuskaitymo laikas: " << failoLaikas << " s\n";
    cout << "Skirstymo i vargsiukus laikas: " << rusiavimoLaikas << " s\n";
    cout << "Rezultatu isvedimo i faila laikas: " << isvedimoLaikas << " s\n";
    cout << "---------------------------------\n";
    cout << "Bendras programos veikimo laikas: " << bendrasLaikas << " s\n";
    cout << "===========================\n";

    cout << "\nRezultatai issaugoti i faila: vargsiukai.txt\n";
    if (budas == 4) cout << "Atnaujintas failas: " << fname << " (liko tik kietiakai)\n";

    return 0;
}
