#include "failai.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<Studentas> Stud_from_file(const string& fname) {
    ifstream fd(fname);
    vector<Studentas> grupe;
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

        vector<int> laik;
        int val;
        while (iss >> val) laik.push_back(val);
        if (laik.size() < 2) continue;

        st.egz = laik.back();
        laik.pop_back();
        st.paz = laik;

        int sum = 0;
        for (int x : st.paz) sum += x;
        double vid = double(sum) / st.paz.size();
        st.galVid = vid * 0.4 + st.egz * 0.6;

        sort(st.paz.begin(), st.paz.end());
        double med = (st.paz.size() % 2 == 0)
            ? (st.paz[st.paz.size() / 2 - 1] + st.paz[st.paz.size() / 2]) / 2.0
            : st.paz[st.paz.size() / 2];
        st.galMed = med * 0.4 + st.egz * 0.6;

        grupe.push_back(st);
    }

    return grupe;
}

void GeneruotiFaila() {
    int n;
    cout << "Iveskite studentu kieki: ";
    cin >> n;

    string filename = "studentai" + to_string(n) + ".txt";
    ofstream fout(filename);
    if (!fout) {
        cerr << "Nepavyko sukurti failo!\n";
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= 15; i++)
        fout << left << setw(6) << ("ND" + to_string(i));
    fout << left << setw(6) << "Egz." << endl;

    for (int i = 1; i <= n; i++) {
        fout << left << setw(15) << ("Vardas" + to_string(i))
            << left << setw(15) << ("Pavarde" + to_string(i));
        for (int j = 0; j < 15; j++)
            fout << left << setw(6) << (rand() % 10 + 1);
        fout << left << setw(6) << (rand() % 10 + 1) << endl;
    }

    cout << "Failas '" << filename << "' sugeneruotas.\n";
}
