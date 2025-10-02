#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include "studentas.h"
#include <vector>

void Rusiavimas(const std::vector<Studentas>& Grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus);

#endif
