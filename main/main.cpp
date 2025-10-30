#include <iostream>
#include <vector>
#include <chrono>
#include "studentas.h"
#include "failai.h"
#include "rusiavimas.h"

using namespace std;
using namespace std::chrono;

int main() {
    ios::sync_with_stdio(false);

    // 🕒 Bendro veikimo pradžia
    auto startProgram = high_resolution_clock::now();

    vector<Studentas> Grupe;
    srand(time(0));

    double failoLaikas = 0.0;
    double rusiavimoLaikas = 0.0;
    double isvedimoLaikas = 0.0;

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
        return 0;
    }

    // === 1. FAILO NUSKAITYMO LAIKAS ===
    if (budas == 4) {
        string fname;
        cout << "Iveskite failo pavadinima: ";
        cin >> fname;

        auto start = high_resolution_clock::now();
        Grupe = Stud_from_file(fname);
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
        return 0;
    }

    // === 2. RUSIAVIMO LAIKAS ===
    auto startR = high_resolution_clock::now();

    Rikiuoti(Grupe);

    int kriterijus;
    cout << "\nPasirinkite kriteriju studentu dalinimui:\n";
    cout << "1 - Pagal vidurki\n";
    cout << "2 - Pagal mediana\n";
    cin >> kriterijus;

    vector<Studentas> vargsiukai, kietiakiai;
    for (const auto& st : Grupe) {
        double val = (kriterijus == 1 ? st.galVid : st.galMed);
        if (val < 5.0) vargsiukai.push_back(st);
        else kietiakiai.push_back(st);
    }

    auto endR = high_resolution_clock::now();
    rusiavimoLaikas = duration_cast<duration<double>>(endR - startR).count();

    // === 3. ISVEDIMO LAIKAS ===
    auto startI = high_resolution_clock::now();
    Spausdinti(vargsiukai, "vargsiukai.txt");
    Spausdinti(kietiakiai, "kietiakiai.txt");
    auto endI = high_resolution_clock::now();

    isvedimoLaikas = duration_cast<duration<double>>(endI - startI).count();

    // 🕒 Bendro veikimo pabaiga
    double bendrasLaikas = failoLaikas+rusiavimoLaikas+isvedimoLaikas;

    // === 4. ISVEDIMAS PABAIGOJE ===
    cout << "\n===== LAIKO MATAVIMAI =====\n";
    cout << "Failo nuskaitymo laikas: " << failoLaikas << " s\n";
    cout << "Rusiavimo i vargsiukus/kietiakus laikas: " << rusiavimoLaikas << " s\n";
    cout << "Rezultatu isvedimo i failus laikas: " << isvedimoLaikas << " s\n";
    cout << "---------------------------------\n";
    cout << "Bendras programos veikimo laikas: " << bendrasLaikas << " s\n";
    cout << "===========================\n";

    cout << "\nRezultatai issaugoti i failus.\n";
    return 0;
}
