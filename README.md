
# Galutinių studentų balų skaičiuoklė

C++ kalba parašyta penktoji programos versija, skaičiuojanti galutinius studentų balus pagal formulę

    Galutinis = 0.4 * namų darbai + 0.6 * egzaminas



## Naudotojo galimybės

 - Pasirinkti, kokį std konteinerį (vector, deque, list) naudoti darbui su duomenimis
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


## STD konteinerių *vector, deque* ir *list* naudojimo spartos palyginimas
Įrangos spec.: Intel i7 CPU @ 1.80 GHz, 16 GB RAM, SSD
Namų darbų kiekis: 8
Namų darbų skaičiavimo būdas: vidurkis
Rezultatų rūšiavimo būdas: pagal pavardę

**Duomenų skaitymas iš failų ir galutinių balų skaičiavimas:**

| Įrašų kiekis | std::vector | std::deque | std::list |
|--|--|--|--|
| 1000 | 0.01129s | 0.018851s | 0.021437s |
| 10000 | 0.172806s | 0.145858s | 0.155495s |
| 100000 | 1.00991s  | 1.08421s | 1.21618s |
| 1000000 | 10.5939s | 10.312s | 11.4773s |
| 10000000 | 97.1415s | 102.196s | 128.297s |

Efektyviausia duomenų skaitymui naudoti *vector* arba *deque* STD konteinerius, mažiausiai efektyvu - *list* konteinerį. Čia *vector* pakeitus *deque* konteineriu, tikėtina, kad sparta nekis, o jei *list* konteineriu, funkcijos darbas sulėtės.

**Duomenų rūšiavimas į dvi kategorijas:**
| Įrašų kiekis | std::vector | std::deque | std::list |
|--|--|--|--|
| 1000 | 0.004103s | 0.003279s | 0.001035s |
| 10000 | 0.035193s | 0.041735s | 0.012601s |
| 100000 | 0.484706s  | 0.536913s | 0.188799s |
| 1000000 | 6.82151s | 6.95582s | 2.06539s |
| 10000000 | 76.2613s | 77.3368s | 27.3425s |

Efektyviausia duomenų rūšiavimui naudoti *std::list* konteinerį, mažiausiai efektyvu - *std::deque* arba *std::vector* konteinerį. Čia *vector* pakeitus *deque* konteineriu, tikėtina, kad sparta nekis arba nežymiai sumažės, o jei *list* konteineriu, funkcijos darbas pagreitės.

## Programos diegimas ir naudojimas:

 1. Parsisiųsti programą iš [versijų puslapio](https://github.com/Naktis/final-grades/releases)
 2. Parsisiųsti ir įsidiegti C++ kompiliatorių (pvz. [GCC](https://gcc.gnu.org/))
 3. Atsidaryti terminalą ir jame įvesti programos vietą diske
 4. Sukompiliuoti programą, pvz
	- Jei naudojate *GCC* su *GNU Make*, įrašykite komandą`make`
	- Jei naudojate *GCC* be *GNU Make*, įrašykite: 
	
	`g++ -c main.cpp validation.cpp file.cpp funList.cpp funVector.cpp funDeque.cpp containers.cpp`
	
	`g++ -o main main.o validation.o file.o funList.o funVector.o funDeque.o containers.o`
5. Paleiskite programą su `./main` arba `main`
 
 
## v0.5 versijos patobulinimai:

 - Pridėta STL konteinerio pasirinkimo galimybė
 - Išpildytos galimybės duomenų saugojimui naudoti std::deque ir std::list konteinerius
 - Sumažintas struktūros narių kiekis efektyvesniam atminties naudojimui
 - Galutinių balų skaičiavimas vykdomas iškart perskaičius namų darbus
 - Programos kodas išskaidytas į daugiau mažesnių failų

------------
Augustina Šareikaitė

Informacinių sistemų inžinerija, I kursas, I grupė

Vilniaus universitetas
