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

    if (budas == 4) {
        string fname;
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
            if (budas != 4) {
                cout << "Objekto saugojimo adresas (laikinas objektas): " << &st << "\n";
            }

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

    auto startR = high_resolution_clock::now();

    int kriterijus;
    cout << "\nPasirinkite kriteriju studentu dalinimui:\n";
    cout << "1 - Pagal vidurki\n";
    cout << "2 - Pagal mediana\n";
    while (!(cin >> kriterijus) || (kriterijus != 1 && kriterijus != 2)) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    vector<Studentas> vargsiukai, kietiakai;

    if (konteinerisTipas == 1) {
        Rikiuoti(vGrupe);
        for (const auto& st : vGrupe) {
            double val = (kriterijus == 1 ? st.galVid : st.galMed);
            if (val < 5.0) vargsiukai.push_back(st);
            else kietiakai.push_back(st);
        }
    }
    else {
        Rikiuoti(lGrupe);
        for (const auto& st : lGrupe) {
            double val = (kriterijus == 1 ? st.galVid : st.galMed);
            if (val < 5.0) vargsiukai.push_back(st);
            else kietiakai.push_back(st);
        }
    }

    auto endR = high_resolution_clock::now();
    rusiavimoLaikas = duration_cast<duration<double>>(endR - startR).count();

    auto startI = high_resolution_clock::now();
    Spausdinti(vargsiukai, "vargsiukai.txt");
    Spausdinti(kietiakai, "kietiakai.txt");
    auto endI = high_resolution_clock::now();
    isvedimoLaikas = duration_cast<duration<double>>(endI - startI).count();

    double bendrasLaikas = failoLaikas + rusiavimoLaikas + isvedimoLaikas;

    cout << "\n===== LAIKO MATAVIMAI =====\n";
    cout << "Failo nuskaitymo laikas: " << failoLaikas << " s\n";
    cout << "Rusiavimo ir skirstymo laikas: " << rusiavimoLaikas << " s\n";
    cout << "Rezultatu isvedimo i failus laikas: " << isvedimoLaikas << " s\n";
    cout << "---------------------------------\n";
    cout << "Bendras programos veikimo laikas: " << bendrasLaikas << " s\n";
    cout << "===========================\n";

    cout << "\nRezultatai issaugoti i failus.\n";

    cout << "\n===== OBJEKTŲ ADRESAI KONTEINERYJE =====\n";
    if (konteinerisTipas == 1) {
        for (const auto& st : vGrupe) {
            cout << "Vector objektas: " << &st << "\n";
        }
    }
    else {
        for (const auto& st : lGrupe) {
            cout << "List objektas: " << &st << "\n";
        }
    }

    return 0;
}
