#include "failai.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<Studentas> Stud_from_file(const string& fname) {
    ifstream fd(fname);
    vector<Studentas> grupe;
    grupe.reserve(1000000);

    if (!fd) {
        cout << "Nepavyko atidaryti failo.\n";
        return grupe;
    }

    string eilute;
    getline(fd, eilute);

    while (getline(fd, eilute)) {
        if (eilute.empty()) continue;
        istringstream iss(eilute);
        Studentas st;
        iss >> st.var >> st.pav;

        string temp;
        vector<int> laik;
        bool klaida = false;

        while (iss >> temp) {
            try {
                int paz = stoi(temp);
                if (paz < 1 || paz > 10) throw invalid_argument("Neteisingas pazymys");
                laik.push_back(paz);
            }
            catch (...) {
                klaida = true;
                break;
            }
        }

        if (klaida || laik.empty()) continue;

        st.egz = laik.back();
        laik.pop_back();
        st.paz = move(laik);

        int sum = 0;
        for (int x : st.paz) sum += x;

        size_t n = st.paz.size();
        st.galVid = double(sum) / n * 0.4 + st.egz * 0.6;

        sort(st.paz.begin(), st.paz.end());
        double med = (n % 2 == 0) ?
            (st.paz[n / 2 - 1] + st.paz[n / 2]) / 2.0 :
            st.paz[n / 2];
        st.galMed = med * 0.4 + st.egz * 0.6;

        grupe.emplace_back(move(st));
    }

    return grupe;
}
