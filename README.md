Proiect  - Intersecție Semaforizată [Strada 20 Decembrie]
Acest proiect implementează un sistem de control al semafoarelor pentru o intersecție semaforizată, având trei sensuri de mers: sud, est și nord, reprezentate de săgeți de culori roșie, portocalie și verde, respectiv.

Descriere
Există opt stâlpi cu semafoare pentru pietoni/șoferi:

Stâlpul 1: Semafor galben intermitent pentru mașini.
Stâlpul 2: Strict pentru pietonii ce vin din direcția nord.
Stâlpul 3: Strict pentru pietonii ce vin din direcția sud.
Stâlpul 4: Două semafoare, unul pentru pietonii ce vin din direcția est și unul pentru mașinile ce vin din direcția nord.
Stâlpul 5: Trei semafoare, unul pentru pietonii ce vin din direcția sud, altul pentru pietonii ce vin din direcția vest și altul pentru mașinile ce vin din direcția est.
Stâlpul 6: Două semafoare, unul pentru pietonii ce vin din direcția nord, altul pentru pietonii ce vin din direcția vest.
Stâlpul 7: Strict pentru pietonii ce vin din direcția est.
Stâlpul 8: Semafor pentru mașinile ce vin din direcția sud.
Sistemul poate fi controlat prin trimiterea de caractere pe monitorul serial din Arduino IDE, având următoarele stări activate:

Starea 1 (caracterul 'N'): Modul normal.
Starea 2 (caracterul 'B'): Modul intermitent (blinking).
Starea 3 (caracterul 'D'): Modul de diagnoză.
Utilizare
Pentru a controla sistemul, urmați instrucțiunile de mai jos:

Starea 1 (Normal)
Trimiterea caracterului 'N' pe monitorul serial activează modul normal.
În acest mod, toate semafoarele funcționează conform programării.
Starea 2 (Blinking)
Trimiterea caracterului 'B' pe monitorul serial activează modul intermitent.
În acest mod, toate semafoarele au culoarea galbenă intermitentă, cu o latență de 1 secundă aprins și 1 secundă stins.
Starea 3 (Diagnoză)
Trimiterea caracterului 'D' pe monitorul serial activează modul de diagnoză.
În acest mod, toate semafoarele sunt oprite.
Pentru a controla semafoarele în modul de diagnoză, se pot trimite următoarele comenzi:
'R': Activează toate semafoarele cu culoarea roșie.
'G': Activează toate semafoarele cu culoarea galbenă.
'V': Activează toate semafoarele cu culoarea verde.
'T': Semafoarele încep să se aprindă și să se stingă cu o latență de 1 secundă, folosind ultima culoare setată.
'S': Oprește toate semafoarele.
'X': Semafoarele trec prin toate culorile la fiecare 2 secunde.
Implementare
Codul implementat pentru acest proiect poate fi găsit în fișierul cod.ino.


![Schema_circuit](https://github.com/Linu03/numerical_calculators_project/assets/163161692/fc6e410e-8ef8-4f3e-8256-894f3e78c5ad)
