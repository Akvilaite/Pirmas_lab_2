#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::sort;
using std::ifstream;
using std::getline;
using std::istringstream;

struct Studentas {
    string var;
    string pav;
    vector<int> paz;
    int egz;
    double galVid;
    double galMed;
};

Studentas Stud_iv(int budas);
vector<Studentas> Stud_from_file(string fname);

int main() {
    srand(time(0));
    vector<Studentas> Grupe;

    int budas;
    cout << "Pasirinkite pazymiu ivedimo buda:\n";
    cout << "1 - zinomas pazymiu skaicius\n";
    cout << "2 - nezinomas pazymiu skaicius (baigti ENTER x2)\n";
    cout << "3 - generuoti pazymius ir egzamina\n";
    cout << "4 - nuskaityti duomenis is failo\n";
    cin >> budas;
    //failo pavadinimas cia!
    if (budas == 4) {
        Grupe = Stud_from_file("C:/Users/akvil/OneDrive/Desktop/koduxai/objektinis/1 uzduotis/vo2/pasibandymai/generav/studentai1000000.txt");
        ;
    }
    else {
        cout << "Kiek studentu grupeje: ";
        int m;
        cin >> m;
        for (int z = 0; z < m; z++)
            Grupe.push_back(Stud_iv(budas));
    }

    sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b) {
        if (a.var == b.var)
            return a.pav > b.pav;
        return a.var > b.var;
        });

    cout << left << setw(15) << "Vardas"
        << left << setw(20) << "Pavarde"
        << right << setw(20) << "Galutinis (Vid.)"
        << right << setw(20) << "Galutinis (Med.)"
        << endl;

    cout << std::string(75, '-') << endl;

    for (auto& Past : Grupe) {
        cout << left << setw(15) << Past.var
            << left << setw(20) << Past.pav
            << right << setw(20) << fixed << setprecision(2) << Past.galVid
            << right << setw(20) << fixed << setprecision(2) << Past.galMed
            << endl;
    }
}

Studentas Stud_iv(int budas) {
    Studentas pirmas;
    cout << "\n--- Naujas studentas ---\n";
    cout << "Vardas: ";
    cin >> pirmas.var;
    cout << "Pavarde: ";
    cin >> pirmas.pav;

    int sum = 0;
    int n = 0;

    if (budas == 1) {
        cout << "Kiek pazymiu turi " << pirmas.var << " " << pirmas.pav << ": ";
        cin >> n;
        for (int a = 0; a < n; a++) {
            int laik_paz;
            cout << a + 1 << ": ";
            cin >> laik_paz;
            pirmas.paz.push_back(laik_paz);
            sum += laik_paz;
        }
    }
    else if (budas == 2) {
        cout << "Iveskite pazymius (baigti ENTER x2):" << endl;
        cin.ignore();
        string line;
        int tuscios = 0;
        while (true) {
            std::getline(cin, line);
            if (line.empty()) {
                tuscios++;
                if (tuscios >= 2) break;
                else continue;
            }
            tuscios = 0;
            int laik_paz = std::stoi(line);
            pirmas.paz.push_back(laik_paz);
            sum += laik_paz;
        }
        n = pirmas.paz.size();
    }
    else if (budas == 3) {
        cout << "Kiek pazymiu sugeneruoti " << pirmas.var << " " << pirmas.pav << ": ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            int laik_paz = rand() % 10 + 1;
            pirmas.paz.push_back(laik_paz);
            sum += laik_paz;
        }
        pirmas.egz = rand() % 10 + 1;
        cout << "Sugeneruoti pazymiai: ";
        for (auto x : pirmas.paz) cout << x << " ";
        cout << " | Egz: " << pirmas.egz << endl;
    }

    if (budas != 3) {
        cout << "Iveskite egzamino paz.: ";
        cin >> pirmas.egz;
    }

    n = pirmas.paz.size();
    if (n > 0) {
        pirmas.galVid = double(sum) / double(n) * 0.4 + pirmas.egz * 0.6;
        sort(pirmas.paz.begin(), pirmas.paz.end());
        double med;
        if (n % 2 == 0)
            med = (pirmas.paz[n / 2 - 1] + pirmas.paz[n / 2]) / 2.0;
        else
            med = pirmas.paz[n / 2];
        pirmas.galMed = med * 0.4 + pirmas.egz * 0.6;
    }
    else {
        pirmas.galVid = pirmas.egz * 0.6;
        pirmas.galMed = pirmas.egz * 0.6;
    }

    return pirmas;
}

vector<Studentas> Stud_from_file(string fname) {
    ifstream fd(fname);
    vector<Studentas> grupe;
    if (!fd) {
        cout << "Nepavyko atidaryti failo: " << fname << endl;
        return grupe;
    }

    string header;
    getline(fd, header);

    while (getline(fd, header)) {
        if (header.empty()) continue;

        istringstream iss(header);
        Studentas st;
        iss >> st.var >> st.pav;

        int paz;
        vector<int> laik;
        while (iss >> paz) {
            laik.push_back(paz);
        }

        if (laik.empty()) continue;

        st.egz = laik.back();
        laik.pop_back();

        st.paz = laik;

        int sum = 0;
        for (int x : st.paz) sum += x;

        st.galVid = (double)sum / st.paz.size() * 0.4 + st.egz * 0.6;

        sort(st.paz.begin(), st.paz.end());
        double med;
        if (st.paz.size() % 2 == 0)
            med = (st.paz[st.paz.size() / 2 - 1] + st.paz[st.paz.size() / 2]) / 2.0;
        else
            med = st.paz[st.paz.size() / 2];
        st.galMed = med * 0.4 + st.egz * 0.6;

        grupe.push_back(st);
    }

    return grupe;
}

