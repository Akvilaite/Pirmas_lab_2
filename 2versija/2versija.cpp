#include <iostream>
#include <vector>
#include "studentas.h"
#include "failai.h"
#include "rusiavimas.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Studentas> Grupe;
    srand(time(0));

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

    if (budas == 4) {
        string fname;
        cout << "Iveskite failo pavadinima: ";
        cin >> fname;
        Grupe = Stud_from_file(fname);
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

    Spausdinti(vargsiukai, "vargsiukai.txt");
    Spausdinti(kietiakiai, "kietiakiai.txt");
    cout << "Rezultatai issaugoti i failus.\n";
    return 0;
}
