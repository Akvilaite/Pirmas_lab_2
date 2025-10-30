#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <type_traits>
#include "studentas.h"
#include "failai.h"
#include "rusiavimas.h"

using namespace std;
using namespace std::chrono;

// Bendrinė šabloninė funkcija, kur visa logika
template <typename Container>
void VykdytiPrograma() {
    auto startProgram = high_resolution_clock::now();
    srand(time(0));

    double failoLaikas = 0.0;
    double rusiavimoLaikas = 0.0;
    double isvedimoLaikas = 0.0;

    Container Grupe;

    int budas;
    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Zinomas pazymiu skaicius\n";
    cout << "2 - Nezinomas pazymiu skaicius (ENTER x2)\n";
    cout << "3 - Generuoti pazymius\n";
    cout << "4 - Nuskaityti duomenis is failo\n";
    cout << "5 - Sugeneruoti nauja faila\n";

    while (!(cin >> budas) || budas < 1 || budas > 5) {
        cout << "Neteisingas pasirinkimas: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (budas == 5) {
        GeneruotiFaila();
        return;
    }

    if (budas == 4) {
        string fname;
        cout << "Iveskite failo pavadinima: ";
        cin >> fname;

        auto start = high_resolution_clock::now();
        Grupe = Stud_from_file<Container>(fname);
        auto end = high_resolution_clock::now();

        failoLaikas = duration_cast<duration<double>>(end - start).count();
    }
    else {
        int n;
        cout << "Kiek studentu grupeje: ";
        cin >> n;
        for (int i = 0; i < n; ++i)
            Grupe.push_back(Stud_iv(budas));
    }

    if (Grupe.empty()) {
        cout << "Nerasta duomenu!\n";
        return;
    }

    auto startR = high_resolution_clock::now();
    Rikiuoti(Grupe);

    int kriterijus;
    cout << "\nPasirinkite kriteriju studentu dalinimui:\n";
    cout << "1 - Pagal vidurki\n";
    cout << "2 - Pagal mediana\n";
    cin >> kriterijus;

    Container vargsiukai, kietiakiai;
    for (const auto& st : Grupe) {
        double val = (kriterijus == 1 ? st.galVid : st.galMed);
        if (val < 5.0) vargsiukai.push_back(st);
        else kietiakiai.push_back(st);
    }

    auto endR = high_resolution_clock::now();
    rusiavimoLaikas = duration_cast<duration<double>>(endR - startR).count();

    auto startI = high_resolution_clock::now();
    Spausdinti(vargsiukai, "vargsiukai.txt");
    Spausdinti(kietiakiai, "kietiakiai.txt");
    auto endI = high_resolution_clock::now();

    isvedimoLaikas = duration_cast<duration<double>>(endI - startI).count();

    auto endProgram = high_resolution_clock::now();
    double bendrasLaikas = duration_cast<duration<double>>(endProgram - startProgram).count();

    cout << "\n===== LAIKO MATAVIMAI =====\n";
    cout << "Failo nuskaitymo laikas: " << failoLaikas << " s\n";
    cout << "Rusiavimo i vargsiukus/kietiakus laikas: " << rusiavimoLaikas << " s\n";
    cout << "Rezultatu isvedimo i failus laikas: " << isvedimoLaikas << " s\n";
    cout << "---------------------------------\n";
    cout << "Bendras programos veikimo laikas: " << bendrasLaikas << " s\n";
    cout << "===========================\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Pasirinkite konteineri:\n";
    cout << "1 - std::vector\n";
    cout << "2 - std::list\n";

    int pasirinkimas;
    while (!(cin >> pasirinkimas) || pasirinkimas < 1 || pasirinkimas > 2) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (pasirinkimas == 1) {
        cout << "\nNaudojamas konteineris: std::vector\n";
        VykdytiPrograma<vector<Studentas>>();
    }
    else {
        cout << "\nNaudojamas konteineris: std::list\n";
        VykdytiPrograma<list<Studentas>>();
    }

    return 0;
}
