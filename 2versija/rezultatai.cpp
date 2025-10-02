#include "rezultatai.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

void Spausdinti(const vector<Studentas>& Grupe, const string& out_file) {
    ofstream fout(out_file);
    if (!fout) return;

    fout << left << setw(15) << "Vardas"
        << left << setw(20) << "Pavarde"
        << right << setw(20) << "Galutinis (Vid.)"
        << right << setw(20) << "Galutinis (Med.)" << '\n';

    fout << string(75, '-') << '\n';

    for (const auto& st : Grupe) {
        fout << left << setw(15) << st.var
            << left << setw(20) << st.pav
            << right << setw(20) << fixed << setprecision(2) << st.galVid
            << right << setw(20) << fixed << setprecision(2) << st.galMed
            << '\n';
    }

    fout.close();
}