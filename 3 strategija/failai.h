#pragma once
#include "studentas.h"
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>
using namespace std;

vector<Studentas> Stud_from_file(const string& fname);
void GeneruotiFaila();

template <typename Container>
void Spausdinti(const Container& Grupe, const string& out_file) {
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
            << right << setw(20) << fixed << setprecision(2) << st.galMed << '\n';
    }
}

