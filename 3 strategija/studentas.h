#pragma once
#include <string>
#include <vector>
using namespace std;

struct Studentas {
    string var;
    string pav;
    vector<int> paz;
    int egz{ 0 };
    double galVid{ 0.0 };
    double galMed{ 0.0 };
};

Studentas Stud_iv(int budas);
