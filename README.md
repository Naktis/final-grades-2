# Galutinių studentų balų skaičiuoklė

C++ kalba sukurta programa, skaičiuojanti galutinius studentų balus pagal formulę

    Galutinis = 0.4 * namų darbai + 0.6 * egzaminas



## Naudotojo galimybės

 - Pasirinkti, kokį STL konteinerį (vector, deque, list) naudoti darbui su duomenimis
 - Pasirinkti duomenų failų generavimą
 - Pasirinkti, ar studento duomenis skaityti iš failo, ar generuoti atsitiktinai, ar įvesti ranka
 - Įvesti skaitomo duomenų failo pavadinimą
 - Pasirinkti, ar namų darbų balu bus laikomas jų vidurkis, ar mediana
 - Pasirinkti rezultatų rūšiavimo būdą (pagal vardą, pavardę ar galutinį balą)
 - Pasirinkti, ar naudoti programą spartinančius algoritmus su *std::vector* konteineriu
 - Pasirinkti studentų rūšiavimui naudojamų naujų konteinerių kiekį - 1 arba 2
 
 Jei pasirenkamas balų generavimas arba įvedimas ranka, suteikiama galimybė
 - Įvesti studento vardą, pavardę
 - Įvesti/generuoti egzamino ir namų darbų balus
 - Namų darbų įvedimo/generavimo metu nuspręsti, kiek jų bus įvesta/sugeneruota
 - Įvedus vieno studento duomenis pasirinkti, ar reikia įvesti daugiau studentų duomenų


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
6. Pasirinkite norimus programos darbo parametrus pagal nurodymus ekrane

### Naudojimosi programa pavyzdys

```
C:...>make
g++    -c -o validation.o validation.cpp
g++    -c -o file.o file.cpp
g++    -c -o funList.o funList.cpp
g++    -c -o funVector.o funVector.cpp
g++    -c -o funDeque.o funDeque.cpp
g++    -c -o containers.o containers.cpp
g++ -o main main.cpp validation.o file.o funList.o funVector.o funDeque.o containers.o

C:...>main
Pasirinkite konteineri darbui su duomenimis:
std::vector:    v
std::list:      l
std::deque:     d
v

Pasirinkite studentu skirstymo i kategorijas strategija:
Kurti du naujus konteinerius:   1
Kurti viena nauja konteineri:   2
2

Ar norite generuoti naujus duomenu failus? (t/n)
t

Duomenu failu generavimo trukme:
kursiokai1000.txt - 0.005546s
kursiokai10000.txt - 0.034645s
kursiokai100000.txt - 0.311169s
kursiokai1000000.txt - 3.22537s
kursiokai10000000.txt - 32.727s

Pasirinkite studentu balu ivesties buda:
Skaitymas is failo:       f
Atsitiktinis generavimas: g
Rankinis ivedimas:        r
f

Pasirinkite rezultatu rusiavimo buda:
Abeceliskai pagal varda:        v
Abeceliskai pagal pavarde:      p
Pagal galutini bala:            b
p

Pasirinkite namu darbu skaiciavimo buda:
Mediana:        m
Vidurkis:       v
v

Ar norite naudoti studentu skirstyma spartinancius algoritmus? (t/n)
t

Iveskite failo varda formatu failo_pav.txt
kursiokai1000000.txt

Failo skaitymas uztruko: 3.89256s
Studentu skirstymas uztruko: 0.355778s
Programos pabaiga

C:...>
```

-------------------------------------

# Versijos

## [v1.0](https://github.com/Naktis/final-grades/releases/tag/v1.0)
### Patobulinimai
 - Pridėta galimybė rūšiuoti studentus kuriant du naujus konteinerius
 - Išmatuota, kaip keičiasi studentų rūšiavimo laikas naudojant 1 arba 2 naujus konteinerius
 - Panaudoti nauji STL algoritmai studentų rūšiavimo optimizavimui
 - Išmatuota, kaip keičiasi studentų rūšiavimo laikas naudojant ir nenaudojant optimizavimo algoritmus

### Spartos analizė // Studentų grupavimo strategijos

**1 strategija:** kuriami 2 nauji konteineriai, senojo turinys ištrinamas

**2 strategija:** kuriamas 1 naujas konteineris, nukopijuota dalis iš senojo konteinerio ištrinama

| Įrašų kiekis | 1 / vector | 2 / vector | 1 / deque | 2 / deque | 1 / list | 2 / list |
|--|--|--|--|--|--|--|
| 100000 | 0.030344s | 0.020395s | 0.05098s | 0.026147s | 0.120206s | 0.051861s |
| 1000000 | 0.234283s  | 0.21658s | 0.429966s | 0.247034s | 0.998865s | 0.586527s |
| 10000000 | 2.36117s | 2.26438s | 3.98602s | 2.79122s | 9.75742s | 6.02634s |

Pasitelkiant 2 strategiją dalyba vyksta greičiau. Tai geriausiai atsispindi naudojant std::deque ir std:: list konteinerius, kai laikas pakeitus strategiją sumažėja beveik perpus.

### Spartos analizė // Grupavimą spartinantys algoritmai su *std::vector*

**Paprasta dalyba**: studentai surūšiuojami galutinių balų didėjimo tvarka, randama pirmo studento, turinčio didesnį nei 5 balą, vieta, toliau žingsniai vykdomi pagal 2 strategiją

**Optimizuota dalyba**: studentų grupės paskirstomos su *std::partition*, toliau žingsniai vykdomi pagal 2 strategiją
| Įrašų kiekis | Paprasta dalyba | Optimizuota dalyba |
|--|--|--|
| 10000 | 0.612445s | 0.065684s |
| 1000000 | 6.63175s | 0.54386s |
| 10000000 | 82.2365s | 6.30857s |

Pagal gautus rezultatus, papildomi algoritmai optimizavimui panaudoti sėkmingai, nes visur juos panaudojus dalybos laikas sutrumpėja ~10 kartų.

## [v0.5](https://github.com/Naktis/final-grades/releases/tag/v0.5.1)
### Patobulinimai
 - Pridėta STL konteinerio pasirinkimo galimybė
 - Išpildytos galimybės duomenų saugojimui naudoti std::deque ir std::list konteinerius
 - Sumažintas struktūros narių kiekis efektyvesniam atminties naudojimui
 - Galutinių balų skaičiavimas vykdomas iškart perskaičius namų darbus
 - Programos kodas išskaidytas į daugiau mažesnių failų

### Spartos analizė // *Vector, deque* ir *list*  konteineriai

**Duomenų skaitymas iš failų ir galutinių balų skaičiavimas:**

| Įrašų kiekis | std::vector | std::deque | std::list |
|--|--|--|--|
| 1000 | 0.01129s | 0.018851s | 0.021437s |
| 10000 | 0.172806s | 0.145858s | 0.155495s |
| 100000 | 1.00991s  | 1.08421s | 1.21618s |
| 1000000 | 10.5939s | 10.312s | 11.4773s |
| 10000000 | 97.1415s | 102.196s | 128.297s |

Efektyviausia duomenų skaitymui naudoti *vector* arba *deque* STD konteinerius, mažiausiai efektyvu - *list* konteinerį. Čia *vector* pakeitus *deque* konteineriu, tikėtina, kad sparta nekis, o jei *list* konteineriu, funkcijos darbas sulėtės.

**Duomenų rūšiavimas pagal galutinį balą ir dalyba į dvi kategorijas:**
| Įrašų kiekis | std::vector | std::deque | std::list |
|--|--|--|--|
| 1000 | 0.004103s | 0.003279s | 0.001035s |
| 10000 | 0.035193s | 0.041735s | 0.012601s |
| 100000 | 0.484706s  | 0.536913s | 0.188799s |
| 1000000 | 6.82151s | 6.95582s | 2.06539s |
| 10000000 | 76.2613s | 77.3368s | 27.3425s |

Efektyviausia duomenų rūšiavimui naudoti *std::list* konteinerį, mažiausiai efektyvu - *std::deque* arba *std::vector* konteinerį. Čia *vector* pakeitus *deque* konteineriu, tikėtina, kad sparta nekis arba nežymiai sumažės, o jei *list* konteineriu, funkcijos darbas pagreitės.

**Bendra trukmė**
| Įrašų kiekis | std::vector | std::deque | std::list |
|--|--|--|--|
| 1000 | 0.015393s | 0.02213s | 0.022472‬s |
| 10000 | 0.207999s | 0.187593s | 0.168096s |
| 100000 | 0.494616s  | 1.621013s | 1.404979s |
| 1000000 | 17.41541s | 17.26782s | 13.54269s |
| 10000000 | 173.4028s | 179.5328s | 155.6395s |

Sudėjus duomenų skaitymo ir rūšiavimo rezultatus, efektyviausia programoje naudoti *std::list* konteinerį. Čia *std::vector* pakeitus *std::deque* konteineriu, sparta gali nežymiai sumažėti, o su *std::list* - padidėti.


## [v0.4](https://github.com/Naktis/final-grades/releases/tag/v0.4)
### Patobulinimai
 - Pridėtas 5 duomenų failų, sudarytų iš: 1000, 10000, 100000, 1000000, 10000000 įrašų, generavimas
 - Pridėtas studentų rūšiavimas pagal galutinius balus
 - Studentai padalyti į dvi kategorijas pagal galutinius balus (nepažangūs su <5 balu ir pažangūs su aukštesniu balu)
 - Abiejų kategorijų rezultatai išvedami į skirtingus .txt formato failus
 - Duomenys skaitomi ir įrašomi ne po vieną elementą, bet po eilutę spartesniam programos veikimui
 - Efektyviau naudojama atmintis rezervuojant talpą vektoriams
 - Matuojamas failo generavimo, skaitymo, studentų grupavimo, duomenų įrašymo į failą laikas

### Spartos analizė
Įrangos spec. (čia ir vėliau): Intel i7 CPU @ 1.80 GHz, 16 GB DDR3 RAM, 1 TB SSD

| Įrašų kiekis | Generavimas | Skaitymas | Studentų grupavimas | Laimingųjų išvedimas į failą | Nelaimingųjų išvedimas į failą|
|--|--|--|--|--|--|
| 1000 | 0.013964s | 0.014863s | 0.006256s | 0.011687s | 0.007499s |
| 10000 | 0.09877s | 0.116621s | 0.058854s | 0.045761s | 0.037535s |
| 100000 | 0.5758s  | 0.797398s | 0.794526s | 0.374608s | 0.250596s |
| 1000000 | 6.13948s | 7.47853s | 9.2707s | 3.87893s | 2.78709s|
| 10000000 | 73.6627s | 74.0929s | 109.75s | 37.5145s | 25.6109s |

## [v0.3](https://github.com/Naktis/final-grades/releases/tag/v0.3)
 - Duomenų struktūrai ir funkcijoms sukurti antraštiniai (*header*) failai, funkcijos perkeltos į atskirą *.cpp* failą.
 - Pridėtas išimčių valdymas darbui su failais (tikrinimas, ar atidaromas failas egzistuoja ir ar duomenų įrašymas į failą buvo sėkmingas). Įvesties tikrinimui naudojamos jau sukurtos funkcijos.
 - Pridėtas make komandų naudojimas, aprašytas *makefile*
 - Optimizuotas įvesties kartojimas po nesėkmingos įvesties, panaudojant funkcijos šabloną
## [v0.2](https://github.com/Naktis/final-grades/releases/tag/v0.2)
 - Pridėtas duomenų skaitymas ir rašymas į failą
 - Pakeistas skaičių generavimas iš funkcijos `rand()` į bibliotekos `<random>` generatorių naudojimą
 - Quicksort algoritmas pakeistas funkcija `sort()`  iš `<algorithm>`
 - Laiko matavimui naudojama ne `<ctime>`, bet `<chrono>` biblioteka
 - Rezultatai surūšiuojami pagal vardus abėcėliškai didėjant

## [v0.1](https://github.com/Naktis/final-grades/releases/tag/v0.1)
- Pradinė programos versija, realizuota naudojant C - masyvus ir vektorius
------------
Augustina Šareikaitė

Informacinių sistemų inžinerija, I kursas, I grupė

Vilniaus universitetas
