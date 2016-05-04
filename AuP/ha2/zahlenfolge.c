#include <stdio.h>

int readInt()
{
    int number;
    scanf("%d", &number);
    return number;
}

int ziffernanzahl(int n)
{
    if (n < 0)
        n = -n;
    int restzahl = n;
    int anzahl = 0;
    while (restzahl > 0) {
        restzahl = restzahl / 10;
        anzahl = anzahl + 1;
    }
    return anzahl;
}

int main()
{
    printf("Zahlenfolge: ");
    int zahl = readInt();
    int zahlalt = zahl;
    int zaehler = 0;

    int summe = zahlalt;
    int minimum = zahlalt;
    int maximum = zahlalt;

    int maxziffern = ziffernanzahl(zahlalt);
    int ziffern;

    int durchschnitt;
    int minimumdifferenz;
    int maximumdifferenz;
    int groesstedifferenz;

    while (zahl != 0) {
        zahl = readInt();
        summe = summe + zahl;
        zaehler = zaehler + 1;
        // damit nicht die 0 am Ende für Vergleiche herangezogen wird
        if (zahl != 0) {
            if (zahl < minimum)
                minimum = zahl;
            if (zahl > maximum)
                maximum = zahl;
        }
        ziffern = ziffernanzahl(zahl);
        if (ziffern > maxziffern)
            maxziffern = ziffern;
        zahlalt = zahl;
    }

    durchschnitt = summe / zaehler;
    minimumdifferenz = durchschnitt - minimum;
    maximumdifferenz = maximum - durchschnitt;
    if (maximumdifferenz > minimumdifferenz)
        groesstedifferenz = maximumdifferenz;
    else
        groesstedifferenz = minimumdifferenz;

    printf("Mittelwert der Folge: %d", durchschnitt);
    printf("\nGrößte Abweichung zum Mittelwert: %d", groesstedifferenz);
    printf("\nMaximale Ziffernanzahl: %d", maxziffern);
    printf("\n");

    /* Spaltenindex */
    int i = 0;
    /* Zeilenindex */
    int j = 0;
    while (j <= 25) {
        if (j % maxziffern == 0) {
            while (i <= 50) {
                if (i % maxziffern == 0)
                    printf("*");
                else
                    printf(" ");
                i = i + 1;
            }
            printf("\n");
            i = 0;
        } else {
            printf("\n");
            i = 0;
        }
        j = j + 1;
    }
    return 0;
}

