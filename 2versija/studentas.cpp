#include "studentas.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        for (int i = 0; i < n; i++) {
            int laik;
            cout << i + 1 << ": ";
            while (!(cin >> laik) || laik < 1 || laik > 10) {
                cout << "Netinkamas pazymys. Bandykite dar karta: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                int laik = stoi(line);
                if (laik < 1 || laik > 10) throw invalid_argument("Blogas intervalas");
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    n = st.paz.size();
    if (n > 0) {
        st.galVid = double(sum) / n * 0.4 + st.egz * 0.6;
        sort(st.paz.begin(), st.paz.end());
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