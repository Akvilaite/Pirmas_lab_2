#pragma once
#include "studentas.h"
#include <string>
#include <vector>
#include <list>

std::vector<Studentas> Stud_from_file(const std::string& fname);

template <typename Container>
void Spausdinti(const Container& Grupe, const std::string& out_file);

void GeneruotiFaila();

