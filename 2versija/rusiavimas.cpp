#include "rusiavimas.h"
#include <algorithm>

void Rusiavimas(const std::vector<Studentas>& Grupe,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai,
    int kriterijus)
{
    for (const auto& st : Grupe) {
        double kriterijaus_reiksme = (kriterijus == 1) ? st.galVid : st.galMed;
        if (kriterijaus_reiksme < 5.0)
            vargsiukai.push_back(st);
        else
            kietiakiai.push_back(st);
    }
}
