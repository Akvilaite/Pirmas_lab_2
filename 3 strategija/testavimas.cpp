#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

#include "studentas.h"
#include "failai.h"
#include "rusiavimas.h"

using namespace std;
using namespace std::chrono;

static void GenerateTestFile(const string& filename, int n) {
    ofstream fout(filename);
    if (!fout) return;
    fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= 15; ++i) fout << left << setw(6) << ("ND" + to_string(i));
    fout << left << setw(6) << "Egz." << '\n';
    std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<int> dist(1, 10);
    for (int i = 1; i <= n; ++i) {
        fout << left << setw(15) << ("Vardas" + to_string(i))
            << left << setw(15) << ("Pavarde" + to_string(i));
        for (int j = 0; j < 15; ++j) fout << left << setw(6) << dist(rng);
        fout << left << setw(6) << dist(rng) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testsCount = 0;
    cout << "Kiek skirtingu testu (failu) norite atlikti? ";
    while (!(cin >> testsCount) || testsCount <= 0) {
        cout << "Iveskite teigiama sveika skaiciu: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    vector<int> sizes;
    sizes.reserve(testsCount);
    for (int i = 0; i < testsCount; ++i) {
        int s;
        cout << "Iveskite studentu kieki testui " << (i + 1) << ": ";
        while (!(cin >> s) || s <= 0) {
            cout << "Iveskite teigiama sveika skaiciu: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        sizes.push_back(s);
    }

    const int runs = 3;

    cout << '\n';
    // Header for visual separation
    cout << left << setw(40) << "Vektoriai:" << "List'ai:" << '\n';

    for (int size : sizes) {
        string filename = "stud" + to_string(size) + ".txt";
        GenerateTestFile(filename, size);

        // accumulators for averages
        double v_file_sum = 0.0, v_sort_sum = 0.0, v_out_sum = 0.0;
        double l_file_sum = 0.0, l_sort_sum = 0.0, l_out_sum = 0.0;

        for (int r = 0; r < runs; ++r) {
            // VECTOR RUN
            vector<Studentas> v;
            auto t0 = high_resolution_clock::now();
            v = Stud_from_file(filename);
            auto t1 = high_resolution_clock::now();
            double v_file = duration_cast<duration<double>>(t1 - t0).count();

            // prepare copy for manipulation
            vector<Studentas> vcopy = v;
            // measure sort + partition (we will sort by galVid descending and then call Strategija3)
            auto t2 = high_resolution_clock::now();
            sort(vcopy.begin(), vcopy.end(), [](const Studentas& a, const Studentas& b) {
                return a.galVid > b.galVid;
                });
            vector<Studentas> v_vargsiukai;
            Strategija3(vcopy, v_vargsiukai, 1); // kriterijus = 1 => pagal galVid
            auto t3 = high_resolution_clock::now();
            double v_sort = duration_cast<duration<double>>(t3 - t2).count();

            // measure output: write vargsiukai and kietiakai to temp files
            auto t4 = high_resolution_clock::now();
            Spausdinti(v_vargsiukai, "vargsiukai_temp.txt");
            Spausdinti(vcopy, "kietiakai_temp.txt");
            auto t5 = high_resolution_clock::now();
            double v_out = duration_cast<duration<double>>(t5 - t4).count();

            v_file_sum += v_file;
            v_sort_sum += v_sort;
            v_out_sum += v_out;

            // LIST RUN
            vector<Studentas> v2;
            auto u0 = high_resolution_clock::now();
            v2 = Stud_from_file(filename);
            auto u1 = high_resolution_clock::now();
            double l_file = duration_cast<duration<double>>(u1 - u0).count();

            list<Studentas> l(v2.begin(), v2.end());
            auto u2 = high_resolution_clock::now();
            l.sort([](const Studentas& a, const Studentas& b) {
                return a.galVid > b.galVid;
                });
            list<Studentas> l_vargsiukai;
            Strategija3(l, l_vargsiukai, 1);
            auto u3 = high_resolution_clock::now();
            double l_sort = duration_cast<duration<double>>(u3 - u2).count();

            auto u4 = high_resolution_clock::now();
            // Spausdinti expects a Container; we can pass list as well
            Spausdinti(l_vargsiukai, "vargsiukai_temp_list.txt");
            // if needed write kietiakai back to file with different name
            Spausdinti(l, "kietiakai_temp_list.txt");
            auto u5 = high_resolution_clock::now();
            double l_out = duration_cast<duration<double>>(u5 - u4).count();

            l_file_sum += l_file;
            l_sort_sum += l_sort;
            l_out_sum += l_out;
        }

        double v_file_avg = v_file_sum / runs;
        double v_sort_avg = v_sort_sum / runs;
        double v_out_avg = v_out_sum / runs;
        double v_total = v_file_avg + v_sort_avg + v_out_avg;

        double l_file_avg = l_file_sum / runs;
        double l_sort_avg = l_sort_sum / runs;
        double l_out_avg = l_out_sum / runs;
        double l_total = l_file_avg + l_sort_avg + l_out_avg;

        // Print formatted block as requested
        // Two columns: left = Vector, right = List
        cout << "\nSu " << size << ":" << setw(36 - to_string(size).length()) << "" << "Su " << size << ":\n";

        cout << left << setw(25) << "Failo nuskaitymas"
            << right << setw(10) << fixed << setprecision(5) << v_file_avg
            << "     "
            << left << setw(20) << "Failo nuskaitymas"
            << right << setw(10) << fixed << setprecision(5) << l_file_avg << '\n';

        cout << left << setw(25) << "Rusiavimas ir skirstymas"
            << right << setw(10) << fixed << setprecision(5) << v_sort_avg
            << "     "
            << left << setw(20) << "Rusiavimas ir skirstymas"
            << right << setw(10) << fixed << setprecision(5) << l_sort_avg << '\n';

        cout << left << setw(25) << "Rezultatu isvedimas"
            << right << setw(10) << fixed << setprecision(5) << v_out_avg
            << "     "
            << left << setw(20) << "Rezultatu isvedimas"
            << right << setw(10) << fixed << setprecision(5) << l_out_avg << '\n';

        cout << left << setw(25) << "Bendras laikas"
            << right << setw(10) << fixed << setprecision(5) << v_total
            << "     "
            << left << setw(20) << "Bendras laikas"
            << right << setw(10) << fixed << setprecision(5) << l_total << '\n';
    }

    cout << "\nTestavimas baigtas. Laikų vidurkiai apskaiciuoti ir atspausdinti.\n";
    return 0;
}
