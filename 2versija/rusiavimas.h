#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include "studentas.h"
#include <vector>

// Studentų padalijimas į dvi grupes pagal pasirinktą kriterijų
void Rusiavimas(const std::vector<Studentas>& Grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus);

#endif
