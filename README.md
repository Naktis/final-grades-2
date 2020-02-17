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
| 3 studentai, atsitiktinis generavimas, mediana |:heavy_check_mark:| :heavy_check_mark: |
| 12 studentų, atsitiktinis generavimas, vidurkis | :heavy_check_mark: | :heavy_check_mark: |
| 1 studentas, atsitiktinis generavimas, vidurkis |:heavy_check_mark:  | :heavy_check_mark: |
| Įvedant balus įvedamas ne skaičius | :heavy_check_mark: | :heavy_check_mark: |
| Taip/ne pasirinkimo vietoje įvesta ne 't' arba 'n' | :heavy_check_mark: | :heavy_check_mark: |
| 4 studentai, 0 namų darbų, vidurkis| :heavy_check_mark: | :heavy_check_mark: |
| 2 studentai, 0 namų darbų, mediana | :heavy_check_mark: | :heavy_check_mark: |
| Vardas įvestas su netinkamu elementu (ne raide) | :heavy_check_mark: | :heavy_check_mark: |
| 2 studentai, rankinė įvestis, mediana | :heavy_check_mark: | :heavy_check_mark: |
| 3 studentai, rankinė įvestis, vidurkis | :heavy_check_mark: | :heavy_check_mark: |

------------
Augustina Šareikaitė

Informacinių sistemų inžinerija, I kursas, I grupė

Vilniaus universitetas
