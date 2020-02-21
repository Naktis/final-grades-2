# Galutinių studentų balų skaičiuoklė v.1

C++ kalba parašyta pirminė programos versija, skaičiuojanti galutinius studentų balus pagal formulę

***Galutinis = 0.4 * namų darbai + 0.6 * egzaminas***

Programos naudotojas gali:

 - Įvesti studento vardą, pavardę, egzamino ir namų darbų balus
 - Namų darbų įvedimo metu nuspręsti, kiek jų bus įvesta
 - Pasirinkti, ar atsitiktinai generuoti namų darbų ir egzamino balus, ar juos įvesti ranka
 - Įvedus vieno studento duomenis nuspręsti, ar įvesti daugiau studentų duomenų
 - Pasirinkti, ar namų darbai bus laikomi jų vidurkiu ar mediana

Programa realizuota naudojant C-masyvus (*array.cpp*) ir vektorius (*vector.cpp*).


## Testavimas

| Atlikti testai | array.cpp | vector.cpp |
|--|--|--|
| Įvestas balas nėra skaičius | *Įvesties kartojimas* | *Įvesties kartojimas* |
| Įvestas balas yra neigiamas skaičius | *Įvesties kartojimas* | *Įvesties kartojimas* 
| Įvestas balas yra didesnis už 10 | *Įvesties kartojimas* | *Įvesties kartojimas* |
| Taip/ne pasirinkimo vietoje įvesta ne 't' arba 'n' | *Įvesties kartojimas* | *Įvesties kartojimas* |
| Įvestame varde yra neleidžiamų simbolių (ne raidė) | *Įvesties kartojimas* | *Įvesties kartojimas* |
| 3 studentai, atsitiktinis generavimas, mediana | *Rezultatai teisingi* | *Rezultatai teisingi* |
| 12 studentų, atsitiktinis generavimas, vidurkis | *Rezultatai teisingi* | *Rezultatai teisingi* |
| 1 studentas, atsitiktinis generavimas, vidurkis | *Rezultatai teisingi*  | *Rezultatai teisingi* |
| 4 studentai, 0 namų darbų, vidurkis| *Rezultatai teisingi* |*Rezultatai teisingi* |
| 2 studentai, 0 namų darbų, mediana | *Rezultatai teisingi* | *Rezultatai teisingi* |
| 2 studentai, rankinė įvestis, mediana | *Rezultatai teisingi* | *Rezultatai teisingi* |
| 3 studentai, rankinė įvestis, vidurkis | *Rezultatai teisingi* | *Rezultatai teisingi* |


------------
Augustina Šareikaitė

Informacinių sistemų inžinerija, I kursas, I grupė

Vilniaus universitetas
