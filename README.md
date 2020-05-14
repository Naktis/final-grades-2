# Galutinių studentų balų skaičiuoklė

C++ kalba sukurta programa, skaičiuojanti galutinius studentų balus pagal formulę

    Galutinis = 0.4 * namų darbai + 0.6 * egzaminas



## Naudotojo galimybės

 - Pasirinkti kiekvieno programos etapo trukmes matavimą
 - Pasirinkti, ar studento duomenis skaityti iš failo, ar generuoti atsitiktinai, ar įvesti ranka
 - Pasirinkti, ar namų darbų balu bus laikomas jų vidurkis, ar mediana
 - Pasirinkti rezultatų rūšiavimo būdą (pagal vardą, pavardę ar galutinį balą)
 - Pasirinkti duomenų failų generavimą
 - Pasirinkti, ar skaityti visus 5 sugeneruotus failus, ar tik vieną
 - Įvesti skaitomo duomenų failo pavadinimą
 
 Jei pasirenkamas balų generavimas arba įvedimas ranka, suteikiama galimybė
 - Įvesti studento vardą, pavardę
 - Įvesti/generuoti egzamino ir namų darbų balus
 - Namų darbų įvedimo/generavimo metu nuspręsti, kiek jų bus įvesta/sugeneruota
 - Įvedus vieno studento duomenis pasirinkti, ar reikia įvesti daugiau studentų duomenų


## Programos diegimas ir naudojimas:

 1. Parsisiųsti programą iš versijų puslapio arba nuorodų apačioje
 2. Parsisiųsti ir įsidiegti C++ kompiliatorių (pvz. [GCC](https://gcc.gnu.org/))
 3. Atsidaryti terminalą ir jame įvesti programos vietą diske, pasirinkti *src* aplanką
 4. Sukompiliuoti programą, pvz
	- Jei naudojate *GCC* su *GNU Make*, įrašykite komandą`make`
	- Jei naudojate *GCC* be *GNU Make*, įrašykite: 
	
	`g++ -c main.cpp validation.cpp iodata.cpp modification.cpp utility.cpp student.cpp`
	
	`g++ -o main main.o validation.o iodata.o modification.o utility.o student.o`
	
1. Paleiskite programą su `./main` (unix) arba `main` (windows)
2. Pasirinkite norimus programos darbo parametrus pagal nurodymus terminale

### Diegimo ir naudojimosi programa pavyzdys

```
C:...\src>make
g++    -c -o validation.o validation.cpp
g++    -c -o iodata.o iodata.cpp
g++    -c -o modification.o modification.cpp
g++    -c -o utility.o utility.cpp
g++    -c -o student.o student.cpp
g++ -O2 -o main main.cpp validation.o iodata.o modification.o utility.o student.o

C:...\src>main
Ar norite matuoti kiekvieno programos etapo trukme? (t/n)
t

Pasirinkite studentu balu ivesties buda:
Skaitymas is failo:       f
Atsitiktinis generavimas: g
Rankinis ivedimas:        r
f

Pasirinkite namu darbu skaiciavimo buda:
Mediana:        m
Vidurkis:       v
v

Pasirinkite rezultatu rusiavimo buda:
Abeceliskai pagal varda:        v
Abeceliskai pagal pavarde:      p
Pagal galutini bala:            b
p

Ar norite generuoti naujus duomenu failus? (t/n)
t

Duomenu failu generavimo trukme:
kursiokai1000.txt - 0.00985s
kursiokai10000.txt - 0.067339s
kursiokai100000.txt - 0.519941s
kursiokai1000000.txt - 5.26319s
kursiokai10000000.txt - 49.5392s

Kiek failu norite perskaityti? (t/n)
Visus sugeneruotus:     5
Tik viena:              1
1

Iveskite failo varda formatu failo_pav.txt
kursiokai100000.txt

kursiokai100000.txt failo skaitymas uztruko:    0.55751s
Studentu grupavimas uztruko:                    0.041899s
Rezultatu rusiavimas uztruko:                   0.7889s
Pazangiuju rezultatu irasymas uztruko:          0.327126s
Nepazangiuju rezultatu irasymas uztruko:        0.218417s
Is viso:                                        1.97372s

Programos pabaiga

C:...\src>
```

## Programos failų turinys:
 - *main.cpp* : pagrindinė funkcija, naudotojo pageidaujamų parametrų pasirinkimas
 - *validation.cpp + validation.h* : funkcijos, tikrinančios naudotojo įvestus duomenis
 - *utility.cpp + utility.h* : funkcija, kurianti studentų vektorių, kviečianti laiko matavimo, duomenų skaitymo, modifikavimo ir rašymo funkcijas
 - *iodata.cpp + iodata.h* : funkcijos, skaitančios ir įrašančios duomenis
 - *modification.cpp + modification.h* : funkcijos, modifikuojančios duomenis (galutinio balo skaičiavimas, duomenų grupavimas ir rūšiavimas)
 - *person.h* : abstrakti bazinė žmogaus duomenų klasė
 - *student.h + student.cpp* : studento duomenų klasė, padaryta *person* klasės pagrindu, ir jos funkcijos
 - *timer.h* : laikmačio klasė
 - *test.cpp* + *catch.hpp* : *unit* testai ir *Catch* framework

-------------------------------------

# Versijos
## [v2.0](https://github.com/Naktis/final-grades-2/releases/tag/v2.0)
### Patobulinimai
 - Sugeneruota [Doxygen](http://www.doxygen.nl/index.html) dokumentacija
 - Sukurti ir sėkmingai įveikti *unit* testai su [Catch](https://github.com/catchorg/Catch2) framework
 - Peroranizuoti failai: .cpp, .h ir makefile perkelti į atskirą aplanką

### *Unit testing*
 [Testais](/src/test.cpp) patikrinta, ar tinkamai veikia:
 - *Student* klasės palyginimo operatorius ==
 - Studentų vardų, pavardžių ir galutinių balų lyginimas
 - *Student* klasės *Copy assignment* operatorius
 - Studentų galutinių balų +, -, / operatoriai
 - Vidurkio skaičiavimas
 - Medianos skaičiavimas
 - Galutinio balo skaičiavimas
  
  ![test results](https://i.imgur.com/qArVeaq.jpg "Rezultatai")

## [v1.5](https://github.com/Naktis/final-grades-2/releases/tag/v1.5)
### Patobulinimai
 - Sukurta abstrakti bazinė *person* klasė
 - *Student* klasė paversta *person* klasės išvestine klase
 - Duomenų grupavimo strategijos ir naujų konteinerių kiekio pasirinkimai pakeisti optimaliausiais, atsižvelgiant į ankstesnių versijų analizes

## [v1.2](https://github.com/Naktis/final-grades-2/releases/tag/v1.2)
### Patobulinimai
 - Studento klasei sukurtas copy-konstruktorius ir copy-assignment operatorius
 - Perkrauti +, -, /, ==, >> ir << operatoriai
 - Perkrauti operatoriai pritaikyti seniau sukurtose funkcijose
 - Programos optimizacijai panaikintos std::list ir std::deque realizacijos, atitinkamai reorganizuotas kodas
 - Platesniam pritaikomumui rūšiavime naudotos *lambda* funkcijos pakeistos *Student* klasės funkcijomis

## [v1.1](https://github.com/Naktis/final-grades-2/releases/tag/v1.1)
### Patobulinimai
 - Studento duomenis sauganti struktūra pakeista į klasę
 - Sukurti klasės metodai, leidžiantys gauti arba pakeisti klasės apsaugotus duomenis

### Spartos analizė // *Struct* ir *class* realizacijų spartos palyginimas
Įrangos spec. (čia ir toliau): Intel i7 CPU @ 1.80 GHz, 16 GB DDR3 RAM, 1 TB SSD

Programos parametrai (čia ir toliau): naudojamas vektoriaus konteineris, skirstant sudentus kuriamas vienas naujas konteineris ir darbą spartinantys STL spartinantys algoritmai.

| Studentų kiekis | Struct   | Class    |
| --------------- | -------- | -------- |
| 100000          | 1.32942s | 1.97372s |
| 1000000         | 13.5805s | 20.396s  |
| 10000000        | 141.079s | 209.019s |

Programos, realizuotos su *class*, veikimo trukmė su visais studentų kiekiais viršija *struct* realizacijos veikimo trukmę. Jai įtaką gali daryti tai, kad *struct* realizacijoje studentų duomenys yra vieši, o *class* - privatūs, todėl jiems pasiekti ir keisti naudojami atitinkami metodai, kurie kaip papildomi veiksmai prailgina veikimo trukmę.

### Spartos analizė // Kompiliavimo vėliavėlių palyginimas
#### Programos veikimo trukmė

| Studentų kiekis | O0       | O1       | O2       | O3       |
| --------------- | -------- | -------- | -------- | -------- |
| 100000          | 2.2816s  | 1.5117s  | 1.60508s | 1.60542s |
| 1000000         | 22.1502s | 15.7225s | 14.8622s | 14.8566s |
| 10000000        | 225.638s | 156.761s | 152.472s | 152.388s |


Optimizavimo vėliavėlės padidino programos veikimo spartą su visais testuotais duomenų kiekiais. Efektyviausios programai - O2 ir O3 vėliavėlės.

#### Vykdomojo failo .exe dydis baitais

| Failo formatas | O0      | O1      | O2      | O3      |
| -------------- | ------- | ------- | ------- | ------- |
| .exe           | 593 678 | 293 496 | 324 697 | 326 919 |

Visos optimizavimo vėliavėlės sumažino .exe failo dydį. Mažiausias failo dydis pasiektas naudojant O2 vėliavėlę.

Ankstesnės versijos aprašytos [čia](https://github.com/Naktis/final-grades/blob/master/README.md).
------------
Augustina Šareikaitė

Informacinių sistemų inžinerija, I kursas, I grupė

Vilniaus universitetas
