#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <limits>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::cin;
using std::cout;

struct Studentas {
    string var;
    string pav;
    vector<int> paz;
    int egz = 0;
    double galVid = 0.0;
    double galMed = 0.0;
};

Studentas Stud_iv(int budas);
vector<Studentas> Stud_from_file(const string& fname);
void Spausdinti(const vector<Studentas>& Grupe, const string& out_file = "rezultatai.txt");

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    srand(static_cast<unsigned>(time(0)));

    vector<Studentas> Grupe;

    int budas;
    cout << "Pasirinkite pazymiu ivedimo buda:\n";
    cout << "1 - zinomas pazymiu skaicius\n";
    cout << "2 - nezinomas pazymiu skaicius (baigti ENTER x2)\n";
    cout << "3 - generuoti pazymius ir egzamina\n";
    cout << "4 - nuskaityti duomenis is failo\n";
    while (!(cin >> budas) || budas < 1 || budas > 4) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (budas == 4) {
        string failoVardas = "C://Users//akvil//OneDrive//Desktop//koduxai//objektinis//1 uzduotis//vo2//pasibandymai//generav//studentai10000.txt";
        Grupe = Stud_from_file(failoVardas);
    }
    else {
        cout << "Kiek studentu grupeje: ";
        int m;
        while (!(cin >> m) || m <= 0) {
            cout << "Netinkamas skaicius. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        for (int z = 0; z < m; ++z)
            Grupe.push_back(Stud_iv(budas));
    }

   
    std::sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b) {
        if (a.var == b.var)
            return a.pav < b.pav;
        return a.var < b.var;
        });

    int kriterijus;
    cout << "\nPasirinkite kriteriju studentu dalinimui:\n";
    cout << "1 - pagal vidurki (galVid)\n";
    cout << "2 - pagal mediana (galMed)\n";
    while (!(cin >> kriterijus) || (kriterijus != 1 && kriterijus != 2)) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    for (const auto& st : Grupe) {
        double kriterijaus_reiksme = (kriterijus == 1) ? st.galVid : st.galMed;
        if (kriterijaus_reiksme < 5.0)
            vargsiukai.push_back(st);
        else
            kietiakiai.push_back(st);
    }

    Spausdinti(vargsiukai, "vargsiukai.txt");
    Spausdinti(kietiakiai, "kietiakiai.txt");

    cout << "Rezultatai issaugoti i failus: vargsiukai.txt ir kietiakiai.txt\n";

    return 0;
}

Studentas Stud_iv(int budas) {
    Studentas st;
    cout << "\n--- Naujas studentas ---\n";
    cout << "Vardas: ";
    cin >> st.var;
    cout << "Pavarde: ";
    cin >> st.pav;

    int sum = 0;
    int n = 0;

    if (budas == 1) {
        cout << "Kiek pazymiu turi " << st.var << " " << st.pav << ": ";
        while (!(cin >> n) || n <= 0) {
            cout << "Netinkamas skaicius. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        for (int i = 0; i < n; i++) {
            int laik;
            cout << i + 1 << ": ";
            while (!(cin >> laik) || laik < 1 || laik > 10) {
                cout << "Netinkamas pazymys. Bandykite dar karta: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            st.paz.push_back(laik);
            sum += laik;
        }
    }
    else if (budas == 2) {
        cout << "Iveskite pazymius (baigti ENTER x2):\n";
        cin.ignore();
        string line;
        int tuscios = 0;
        while (true) {
            getline(cin, line);
            if (line.empty()) {
                tuscios++;
                if (tuscios >= 2) break;
                continue;
            }
            tuscios = 0;
            try {
                int laik = std::stoi(line);
                if (laik < 1 || laik > 10) throw std::invalid_argument("Blogas intervalas");
                st.paz.push_back(laik);
                sum += laik;
            }
            catch (...) {
                cout << "Netinkama ivestis, ignoruojama.\n";
            }
        }
    }
    else if (budas == 3) {
        cout << "Kiek pazymiu sugeneruoti: ";
        while (!(cin >> n) || n <= 0) {
            cout << "Netinkamas skaicius. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        for (int i = 0; i < n; i++) {
            int laik = rand() % 10 + 1;
            st.paz.push_back(laik);
            sum += laik;
        }
        st.egz = rand() % 10 + 1;
        cout << "Sugeneruoti pazymiai: ";
        for (auto x : st.paz) cout << x << " ";
        cout << "| Egz: " << st.egz << "\n";
    }

    if (budas != 3) {
        cout << "Iveskite egzamino pazymi: ";
        while (!(cin >> st.egz) || st.egz < 1 || st.egz > 10) {
            cout << "Netinkamas egzamino pazymys. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    n = st.paz.size();
    if (n > 0) {
        st.galVid = double(sum) / n * 0.4 + st.egz * 0.6;
        std::sort(st.paz.begin(), st.paz.end());
        double med = (n % 2 == 0) ?
            (st.paz[n / 2 - 1] + st.paz[n / 2]) / 2.0 :
            st.paz[n / 2];
        st.galMed = med * 0.4 + st.egz * 0.6;
    }
    else {
        st.galVid = st.egz * 0.6;
        st.galMed = st.egz * 0.6;
    }

    return st;
}

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
                int paz = std::stoi(temp);
                if (paz < 1 || paz > 10) throw std::invalid_argument("Neteisingas pazymys");
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
        st.paz = std::move(laik);

        int sum = 0;
        for (int x : st.paz) sum += x;

        size_t n = st.paz.size();
        st.galVid = double(sum) / n * 0.4 + st.egz * 0.6;

        std::sort(st.paz.begin(), st.paz.end());
        double med = (n % 2 == 0) ?
            (st.paz[n / 2 - 1] + st.paz[n / 2]) / 2.0 :
            st.paz[n / 2];
        st.galMed = med * 0.4 + st.egz * 0.6;

        grupe.emplace_back(std::move(st));
    }

    return grupe;
}

void Spausdinti(const vector<Studentas>& Grupe, const string& out_file) {
    ofstream fout(out_file);
    if (!fout) return;

    fout << left << setw(15) << "Vardas"
        << left << setw(20) << "Pavarde"
        << right << setw(20) << "Galutinis (Vid.)"
        << right << setw(20) << "Galutinis (Med.)" << '\n';

    fout << std::string(75, '-') << '\n';

    for (const auto& st : Grupe) {
        fout << left << setw(15) << st.var
            << left << setw(20) << st.pav
            << right << setw(20) << fixed << setprecision(2) << st.galVid
            << right << setw(20) << fixed << setprecision(2) << st.galMed
            << '\n';
    }

    fout.close();
}
