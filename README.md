# V03 specifikacijos:

<pre>
CPU Intel Core i9-12900H, 12-oji karta, 14 branduolių (6 P + 8 E), 20 gijų, 2.5 GHz bazinis dažnis, iki 5.0 GHz
RAM 16 GB DDR5-4800 MHz, 2× 8 GB 
SSD - 1 TB PCIe Gen 4 NVMe M.2 SSD 
<pre>


# programos paleidimas
</pre>
1. Atsisiųsti v1.0 release failus
2. atsidarius Pirmas_lab_2 pasirinkti, kurią strategiją naudosime.
3. Atidaryti .sln failą per Visual studio
4. rekomenduoju naudoti c++17 versiją
5. paleisti programą Realease x64 metodu.
   
Paleidus programą:
Pasirinkite, ar norite įvesti duomenis ranka, ar nuskaityti iš failo.
Įveskite studentų duomenis (vardas, pavardė, pažymiai, egzaminas).
Programa automatiškai:
suskaičiuos vidurkius ir medianas,
išrūšiuos studentus pagal pasirinktą strategiją (pvz. 3 strategija),
atskirs „vargšiukus“,
išves rezultatus ekrane ir į failus.
</pre>
  
#Vidurkiai: 
  
<pre>  
Bendros įžvalgos
2strategija buvo greitesnė už 1.
Su mažais duomenų kiekiais (1000 eilučių) greičiau veikė list konteineris.

Su labai dideliais duomenų kiekiais (10 000 000 eilučių) efektyvesnis buvo vector konteineris.

Tai rodo, kad konteinerio pasirinkimas priklauso nuo duomenų masto: list pranašesnis mažesnėse apimtose, vector – didelėse.


# Pirmas_lab_2

## 1 strategija

<pre>
Vektoriai:                                List'ai:
Su 1000:                                  Su 1000:
Failo nuskaitymas     0.01135             Failo nuskaitymas     0.00804
Rūšiavimas ir skirstymas  1.85156         Rūšiavimas ir skirstymas  1.56665
Rezultatų išvedimas   0.09685             Rezultatų išvedimas   0.01833
Bendras laikas        1.95977             Bendras laikas        1.59302

Su 10 000:                                Su 10 000:
Failo nuskaitymas     0.09059             Failo nuskaitymas     0.08155
Rūšiavimas ir skirstymas  1.36175         Rūšiavimas ir skirstymas  2.37754
Rezultatų išvedimas   0.06081             Rezultatų išvedimas   0.04845
Bendras laikas        1.51315             Bendras laikas        2.50754

Su 100 000:                               Su 100 000:
Failo nuskaitymas     0.74772             Failo nuskaitymas     0.74102
Rūšiavimas ir skirstymas  2.21302         Rūšiavimas ir skirstymas  2.19679
Rezultatų išvedimas   0.25155             Rezultatų išvedimas   0.22546
Bendras laikas        3.21230             Bendras laikas        3.16326

Su 1 000 000:                             Su 1 000 000:
Failo nuskaitymas     7.41286             Failo nuskaitymas     7.34436
Rūšiavimas ir skirstymas  5.78897         Rūšiavimas ir skirstymas  7.85784
Rezultatų išvedimas   2.10004             Rezultatų išvedimas   2.06584
Bendras laikas        15.3019             Bendras laikas        17.268

Su 10 000 000:                            Su 10 000 000:
Failo nuskaitymas     74.8043             Failo nuskaitymas     76.347
Rūšiavimas ir skirstymas  18.0287         Rūšiavimas ir skirstymas  22.384
Rezultatų išvedimas   21.3821             Rezultatų išvedimas   21.331
Bendras laikas        114.215             Bendras laikas        120.063
</pre>


## 2 strategija

<pre>
Vektoriai:                                List'ai:
Su 1000:                                  Su 1000:
Failo nuskaitymas     0.00970             Failo nuskaitymas     0.00744
Skirstymas            0.00014             Skirstymas            0.00009
Rezultatų išvedimas   0.02020             Rezultatų išvedimas   0.01946
Bendras laikas        0.03701             Bendras laikas        0.02765

Su 10 000:                                Su 10 000:
Failo nuskaitymas     0.06628             Failo nuskaitymas     0.07150
Skirstymas            0.00151             Skirstymas            0.00096
Rezultatų išvedimas   0.03266             Rezultatų išvedimas   0.03075
Bendras laikas        0.09979             Bendras laikas        0.10321

Su 100 000:                               Su 100 000:
Failo nuskaitymas     0.77957             Failo nuskaitymas     0.77369
Skirstymas            0.01949             Skirstymas            0.02137
Rezultatų išvedimas   0.27716             Rezultatų išvedimas   0.34920
Bendras laikas        1.08288             Bendras laikas        1.15406

Su 1 000 000:                             Su 1 000 000:
Failo nuskaitymas     7.75270             Failo nuskaitymas     6.69168
Skirstymas            0.20482             Skirstymas            0.23783
Rezultatų išvedimas   2.41117             Rezultatų išvedimas   2.37864
Bendras laikas        10.3694             Bendras laikas        9.1026

Su 10 000 000:                            Su 10 000 000:
Failo nuskaitymas     66.0902             Failo nuskaitymas     60.8914
Skirstymas            2.1401              Skirstymas            2.5079
Rezultatų išvedimas   17.9058             Rezultatų išvedimas   18.0184
Bendras laikas        86.1361             Bendras laikas        81.4177
</pre>


# 3 strategija

<pre>
Vektoriai:                                   List'ai:
Su 1000:                                     Su 1000:
Failo nuskaitymas        0.01190             Failo nuskaitymas        0.01426
Rūšiavimas ir skirstymas 0.00024             Rūšiavimas ir skirstymas 0.00013
Rezultatų išvedimas      0.02664             Rezultatų išvedimas      0.01612
Bendras laikas           0.03878             Bendras laikas           0.03051

Su 10 000:                                   Su 10 000:
Failo nuskaitymas        0.10644             Failo nuskaitymas        0.10793
Rūšiavimas ir skirstymas 0.00242             Rūšiavimas ir skirstymas 0.00165
Rezultatų išvedimas      0.04277             Rezultatų išvedimas      0.04761
Bendras laikas           0.15163             Bendras laikas           0.15719

Su 100 000:                                  Su 100 000:
Failo nuskaitymas        1.04658             Failo nuskaitymas        1.04903
Rūšiavimas ir skirstymas 0.02732             Rūšiavimas ir skirstymas 0.02918
Rezultatų išvedimas      0.31476             Rezultatų išvedimas      0.35502
Bendras laikas           1.38866             Bendras laikas           1.43324

Su 1 000 000:                                Su 1 000 000:
Failo nuskaitymas        7.39874             Failo nuskaitymas        7.33834
Rūšiavimas ir skirstymas 0.09767             Rūšiavimas ir skirstymas 0.26995
Rezultatų išvedimas      2.12998             Rezultatų išvedimas      2.30696
Bendras laikas           9.62639             Bendras laikas           9.91524

Su 10 000 000:                               Su 10 000 000:
Failo nuskaitymas        63.8519             Failo nuskaitymas        64.7622
Rūšiavimas ir skirstymas 1.10497             Rūšiavimas ir skirstymas 1.98137
Rezultatų išvedimas      16.3334             Rezultatų išvedimas      15.6772
Bendras laikas           81.2903             Bendras laikas           82.4207
</pre>

