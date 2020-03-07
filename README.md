
# Galutinių studentų balų skaičiuoklė

C++ kalba parašyta ketvirtoji programos versija, skaičiuojanti galutinius studentų balus pagal formulę

    Galutinis = 0.4 * namų darbai + 0.6 * egzaminas



## Naudotojo galimybės

 - Pasirinkti duomenų failų generavimą
 - Pasirinkti, ar studento duomenis skaityti iš failo, ar generuoti atsitiktinai, ar įvesti ranka
 - Įvesti skaitomo duomenų failo pavadinimą
 - Pasirinkti, ar namų darbų balu bus laikomas jų vidurkis, ar mediana
 - Pasirinkti rezultatų rūšiavimo būdą
 
 Jei pasirenkamas balų generavimas arba įvedimas ranka, suteikiama galimybė
 - Įvesti studento vardą, pavardę
 - Įvesti/generuoti egzamino ir namų darbų balus
 - Namų darbų įvedimo/generavimo metu nuspręsti, kiek jų bus įvesta/sugeneruota
 - Įvedus vieno studento duomenis pasirinkti, ar reikia įvesti daugiau studentų duomenų


## Spartos analizė
Įrangos spec.: Intel i7 CPU @ 1.80 GHz, 16 GB RAM, SSD
Namų darbų kiekis: 5
Namų darbų skaičiavimo būdas: mediana
Rezultatų rūšiavimo būdas: pagal galutinį balą
| Įrašų kiekis | Generavimas | Skaitymas | Studentų grupavimas | Laimingųjų išvedimas | Nelaimingųjų išvedimas |
|--|--|--|--|--|--|
| 1000 | 0.013964s | 0.014863s | 0.006256s | 0.011687s | 0.007499s |
| 10000 | 0.09877s | 0.116621s | 0.058854s | 0.045761s | 0.037535s |
| 100000 | 0.5758s  | 0.797398s | 0.794526s | 0.374608s | 0.250596s |
| 1000000 | 6.13948s | 7.47853s | 9.2707s | 3.87893s | 2.78709s|
| 10000000 | 73.6627s | 74.0929s | 109.75s | 37.5145s | 25.6109s |


## Programos diegimas ir naudojimas:

 1. Parsisiųsti programą iš [versijų puslapio](https://github.com/Naktis/final-grades/releases)
 2. Parsisiųsti ir įsidiegti C++ kompiliatorių (pvz. [GCC](https://gcc.gnu.org/))
 3. Atsidaryti terminalą ir jame įvesti programos vietą diske
 4. Sukompiliuoti programą, pvz
	- Jei naudojate *GCC* su *GNU Make*, įrašykite komandą`make`
	- Jei naudojate *GCC* be *GNU Make*, įrašykite: 
	`g++ -c main.cpp functions.cpp`
	`g++ -o main main.o functions.o`
5. Paleiskite programą su `./main` arba `main`
 
 
## Patobulinimai nuo v0.3 versijos:

 - Pridėtas 5 duomenų failų, sudarytų iš: 1000, 10000, 100000, 1000000, 10000000 įrašų, generavimas
 - Pridėtas studentų rūšiavimas pagal galutinius balus
 - Studentai padalyti į dvi kategorijas pagal galutinius balus (nepažangūs su <5 balu ir pažangūs su aukštesniu balu)
 - Abiejų kategorijų rezultatai išvedami į skirtingus .txt formato failus
 - Duomenys skaitomi ir įrašomi ne po vieną elementą, bet po eilutę spartesniam programos veikimui
 - Efektyviau naudojama atmintis rezervuojant talpą vektoriams
 - Matuojamas failo generavimo, skaitymo, studentų grupavimo, duomenų įrašymo į failą laikas

------------
Augustina Šareikaitė

Informacinių sistemų inžinerija, I kursas, I grupė

Vilniaus universitetas
