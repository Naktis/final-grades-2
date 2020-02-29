
# Galutinių studentų balų skaičiuoklė

C++ kalba parašyta trečioji programos versija, skaičiuojanti galutinius studentų balus pagal formulę

    Galutinis = 0.4 * namų darbai + 0.6 * egzaminas



## Naudotojo galimybės

 - Pasirinkti, ar studento duomenis skaityti iš failo, ar generuoti atsitiktinai, ar įvesti ranka
 - Pasirinkti, ar namų darbų balu bus laikomas jų vidurkis, ar mediana
 
 Jei pasirenkamas balų generavimas arba įvedimas ranka, suteikima galimybė
 - Įvesti studento vardą, pavardę
 - Įvesti/generuoti egzamino ir namų darbų balus
 - Namų darbų įvedimo/generavimo metu nuspręsti, kiek jų bus įvesta/sugeneruota
 - Įvedus vieno studento duomenis pasirinkti, ar reikia įvesti daugiau studentų duomenų

## Programos diegimas ir naudojimas:

 1. Parsisiųsti programą iš [versijų puslapio](https://github.com/Naktis/final-grades/releases)
 2. Parsisiųsti ir įsidiegti C++ kompiliatorių (pvz. [GCC](https://gcc.gnu.org/))
 3. Atsidaryti terminalą ir jame įvesti programos vietą diske
 4. Sukompiliuoti programą (Jei naudojate GCC, įrašykite `make`)
 5. Paleiskite programą su `./main` arba `main`
 
## Patobulinimai nuo v0.2 versijos:

 - Duomenų struktūrai ir funkcijoms sukurti antraštiniai (*header*) failai, funkcijos perkeltos į atskirą *.cpp* failą.
 - Pridėtas išimčių valdymas darbui su failais (tikrinimas, ar atidaromas failas egzistuoja ir ar duomenų įrašymas į failą buvo sėkmingas). Įvesties tikrinimui naudojamos jau sukurtos funkcijos.
 - Pridėtas make komandų naudojimas, aprašytas *makefile*
 - Optimizuotas įvesties kartojimas po nesėkmingos įvesties, panaudojant funkcijos šabloną

------------
Augustina Šareikaitė

Informacinių sistemų inžinerija, I kursas, I grupė

Vilniaus universitetas
