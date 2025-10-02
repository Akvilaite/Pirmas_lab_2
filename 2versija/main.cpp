#include <iostream>
#include <algorithm>
#include "studentas.h"
#include "failai.h"
#include "rezultatai.h"
#include "rusiavimas.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(static_cast<unsigned>(time(0)));

    vector<Studentas> Grupe;

    int budas;
    cout << "Pasirinkite pazymiu ivedimo buda:\n";
    cout << "1 - zinomas pazymiu skaicius\n";
    cout << "2 - nezinomas pazymiu skaicius (baigti ENTER x2)\n";
    cout << "3 - generuoti pazymius ir egzamina\n";
    cout << "4 - nuskaityti duomenis is failo\n";
    while (!(cin >> budas) || budas < 1 || budas > 4) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (budas == 4) {
        string failoVardas = "studentai.txt"; // pakeiskite pagal poreikį
        Grupe = Stud_from_file(failoVardas);
    }
    else {
        cout << "Kiek studentu grupeje: ";
        int m;
        while (!(cin >> m) || m <= 0) {
            cout << "Netinkamas skaicius. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        for (int z = 0; z < m; ++z)
            Grupe.push_back(Stud_iv(budas));
    }

    sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b) {
        if (a.var == b.var)
            return a.pav < b.pav;
        return a.var < b.var;
        });

    int kriterijus;
    cout << "\nPasirinkite kriteriju studentu dalinimui:\n";
    cout << "1 - pagal vidurki (galVid)\n";
    cout << "2 - pagal mediana (galMed)\n";
    while (!(cin >> kriterijus) || (kriterijus != 1 && kriterijus != 2)) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    Rusiavimas(Grupe, vargsiukai, kietiakiai, kriterijus);

    Spausdinti(vargsiukai, "vargsiukai.txt");
    Spausdinti(kietiakiai, "kietiakiai.txt");

    cout << "Rezultatai issaugoti i failus: vargsiukai.txt ir kietiakiai.txt\n";
    cout << "Vargsiuku skaicius: " << vargsiukai.size()
        << ", Kietiakiu skaicius: " << kietiakiai.size() << "\n";

    return 0;
}
