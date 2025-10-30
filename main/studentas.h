#pragma once
#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct Studentas {
    std::string var;
    std::string pav;
    std::vector<int> paz;
    int egz = 0;
    double galVid = 0.0;
    double galMed = 0.0;
};

Studentas Stud_iv(int budas);

#endif