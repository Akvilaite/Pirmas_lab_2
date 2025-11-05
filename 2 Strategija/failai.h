#pragma once
#include "studentas.h"
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>

std::vector<Studentas> Stud_from_file(const std::string& fname);
void GeneruotiFaila();

template <typename Container>
void Spausdinti(const Container& Grupe, const std::string& out_file) {
    std::ofstream fout(out_file);
    if (!fout) return;

    fout << std::left << std::setw(15) << "Vardas"
        << std::left << std::setw(20) << "Pavarde"
        << std::right << std::setw(20) << "Galutinis (Vid.)"
        << std::right << std::setw(20) << "Galutinis (Med.)" << '\n';
    fout << std::string(75, '-') << '\n';

    for (const auto& st : Grupe) {
        fout << std::left << std::setw(15) << st.var
            << std::left << std::setw(20) << st.pav
            << std::right << std::setw(20) << std::fixed << std::setprecision(2) << st.galVid
            << std::right << std::setw(20) << std::fixed << std::setprecision(2) << st.galMed
            << '\n';
    }
}
