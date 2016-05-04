#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// liefert Zufallszahl zwischen 0 und 1
double Zufallszahl()
{
    double r = rand();
    return r / RAND_MAX;
}

// ... hier stehen Ihre Lösungen der Aufgaben a) und b)
double Gewinn(double einsatz, int zahl, int runden)
{
    // Vorbedingungsprüfung
    // 0.0005 wegen Gleitkommaarithmetik
    if (einsatz < 0.0005 || zahl < 0 || runden <= 0) {
        printf("Fehlerhafte Eingaben\n");
        return 0;
    }
    double gewinn = 0;
    double zufall;

    for (int i = 0; i < runden; i++) {
        gewinn -= einsatz;
        zufall = Zufallszahl();
        // Wahrscheinlichkeit 1/37
        if (zufall < (double)1 / 37)
            gewinn += einsatz * 36;
    }
    return gewinn;
}

int GewinneMillion(double basiseinsatz)
{
    // Vorbedingungsprüfung
    // 0.0005 wegen Gleitkommaarithmetik
    if (basiseinsatz < 0.0005) {
        printf("Fehlerhafte Eingaben\n");
        return 0;
    }
    double gewinn = 0;
    double zufall;
    int glueck = 0;
    int glueckmax = glueck;
    int pech = 0;
    int pechmax = pech;
    int runden = 0;
    double einsatz = basiseinsatz;
    double einsatzmax = basiseinsatz;

    while (gewinn < 1000000) {
        runden++;
        gewinn -= einsatz;
        zufall = Zufallszahl();
        if (zufall < (double)18 / 37) {
            glueck++;
            if (pech > 0) {
                if (pech > pechmax)
                    pechmax = pech;
                pech = 0;
            }
            gewinn += einsatz * 2;
            if (einsatz > einsatzmax)
                einsatzmax = einsatz;
            einsatz = basiseinsatz;
        } else {
            pech++;
            if (glueck > 0) {
                if (glueck > glueckmax)
                    glueckmax = glueck;
                glueck = 0;
            }
            einsatz *= 2;
        }
    }
    printf("%10.2f   |%8d|%9d      |%8d     |%15.2f   |%10.2f\n",
           basiseinsatz, runden, glueckmax, pechmax, einsatzmax, gewinn);
    return 0;
}

int main()
{
    // Initialisierung des Zufallszahlengenerators
    srand((int)time(0));
    // ... hier stehen Ihre Lösungen der Aufgaben c) und d)
    for (int zahl = 0; zahl <= 36; zahl++) {
        printf("Der Gewinn für die Zahl %2d beträgt %7.2f\n",
               zahl, Gewinn(11.11, zahl, 37));
    }
    printf("\n",
           "Basiseinsatz | Runden | Glückssträhne | Pechsträhne | Höchster Einsatz | Gewinn\n",
           "-------------+--------+---------------+-------------+------------------+----------\n");
    double einsatz = 0.75;
    while (einsatz < 100000) {
        GewinneMillion(einsatz);
        einsatz *= 2;
    }
    return 0;
}
