#pragma once
#include "studentas.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <functional>
using namespace std;

template <typename Container>
void Rikiuoti(Container& Grupe) {
    int pasirinkimas;
    cout << "\nPasirinkite pagal ka rikiuoti studentus:\n";
    cout << "1 - Pagal varda/pavarde\n";
    cout << "2 - Pagal galutini vidurki\n";
    cout << "3 - Pagal galutine mediana\n";

    while (!(cin >> pasirinkimas) || pasirinkimas < 1 || pasirinkimas > 3) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    function<bool(const Studentas&, const Studentas&)> comp;

    if (pasirinkimas == 1) {
        comp = [](const Studentas& a, const Studentas& b) {
            if (a.var == b.var) return a.pav < b.pav;
            return a.var < b.var;
            };
    }
    else if (pasirinkimas == 2) {
        comp = [](const Studentas& a, const Studentas& b) {
            return a.galVid > b.galVid;
            };
    }
    else {
        comp = [](const Studentas& a, const Studentas& b) {
            return a.galMed > b.galMed;
            };
    }

    using Iter = decltype(begin(Grupe));
    using Cat = typename iterator_traits<Iter>::iterator_category;
    constexpr bool is_random_access = is_same<Cat, random_access_iterator_tag>::value;

    if constexpr (is_random_access)
        sort(Grupe.begin(), Grupe.end(), comp);
    else
        Grupe.sort(comp);
}

template <typename Container>
void Strategija2(Container& studentai, Container& vargsiukai, int kriterijus) {
    if constexpr (is_same<Container, vector<Studentas>>::value) {
        auto it = remove_if(studentai.begin(), studentai.end(), [&](const Studentas& s) {
            double val = (kriterijus == 1 ? s.galVid : s.galMed);
            if (val < 5.0) {
                vargsiukai.push_back(s);
                return true;
            }
            return false;
            });
        studentai.erase(it, studentai.end());
    }
    else {
        for (auto it = studentai.begin(); it != studentai.end();) {
            double val = (kriterijus == 1 ? it->galVid : it->galMed);
            if (val < 5.0) {
                vargsiukai.push_back(*it);
                it = studentai.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

template <typename Container>
void Strategija3(Container& studentai, Container& vargsiukai, int kriterijus) {
    auto pred = [&](const Studentas& s) {
        double val = (kriterijus == 1 ? s.galVid : s.galMed);
        return val >= 5.0;
        };

    if constexpr (is_same_v<Container, vector<Studentas>>) {
        auto it = partition(studentai.begin(), studentai.end(), pred);
        move(it, studentai.end(), back_inserter(vargsiukai));
        studentai.erase(it, studentai.end());
    }
    else if constexpr (is_same_v<Container, list<Studentas>>) {
        auto it = partition(studentai.begin(), studentai.end(), pred);
        vargsiukai.splice(vargsiukai.end(), studentai, it, studentai.end());
    }
}
