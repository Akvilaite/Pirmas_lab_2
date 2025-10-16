#ifndef FAILAI_H
#define FAILAI_H

#include <string>
#include <vector>
#include "studentas.h"

std::vector<Studentas> Stud_from_file(const std::string& fname);
void Spausdinti(const std::vector<Studentas>& Grupe, const std::string& out_file);
void GeneruotiFaila();

#endif

