#include "rusiavimas.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Rikiuoti(vector<Studentas>& Grupe) {
    int pasirinkimas;
    cout << "\nPasirinkite pagal ka rikiuoti studentus:\n";
    cout << "1 - Pagal varda/pavarde\n";
    cout << "2 - Pagal galutini vidurki\n";
    cout << "3 - Pagal galutine mediana\n";
    while (!(cin >> pasirinkimas) || pasirinkimas < 1 || pasirinkimas > 3) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (pasirinkimas == 1)
        sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b) {
        if (a.var == b.var) return a.pav < b.pav;
        return a.var < b.var;
            });
    else if (pasirinkimas == 2)
        sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.galVid > b.galVid;
            });
    else
        sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.galMed > b.galMed;
            });
}
