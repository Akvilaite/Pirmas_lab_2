#include "rusiavimas.h"
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <iterator>
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

    std::function<bool(const Studentas&, const Studentas&)> comp;

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

    using Iter = decltype(std::begin(Grupe));
    using Cat = typename std::iterator_traits<Iter>::iterator_category;
    constexpr bool is_random_access = std::is_same<Cat, std::random_access_iterator_tag>::value;

    if constexpr (is_random_access) {
        std::sort(Grupe.begin(), Grupe.end(), comp);
    }
    else {
        Grupe.sort(comp);
    }
}

template void Rikiuoti(std::vector<Studentas>&);
template void Rikiuoti(std::list<Studentas>&);
