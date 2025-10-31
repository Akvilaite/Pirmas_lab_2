# V03 specifikacijos:

<pre>
CPU Intel Core i9-12900H, 12-oji karta, 14 branduolių (6 P + 8 E), 20 gijų, 2.5 GHz bazinis dažnis, iki 5.0 GHz
RAM 16 GB DDR5-4800 MHz, 2× 8 GB 
SSD - 1 TB PCIe Gen 4 NVMe M.2 SSD 
<pre>
  
#Vidurkiai: 
  
<pre>  
su 1000 eilučių greičiau veikė listai, o su 10 000 000 eilučių - vektoriai. Testuota buvo po 3 kartus skirtingais laikais.

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
