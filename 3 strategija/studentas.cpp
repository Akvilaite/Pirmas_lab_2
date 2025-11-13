#include "studentas.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

Studentas Stud_iv(int budas) {
    Studentas st;
    st.var = "Vardas";
    st.pav = "Pavarde";
    st.egz = 1;
    st.galVid = 1.0;
    st.galMed = 1.0;
    return st;
}
