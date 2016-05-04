#include <stdio.h>

/* für Aufgabenteil a) */
int alteRoemischeZahl(int n)
{
    while (n >= 1000) {
        printf("M");
        n = n - 1000;
    }
    while (n >= 500) {
        printf("D");
        n = n - 500;
    }
    while (n >= 100) {
        printf("C");
        n = n - 100;
    }
    while (n >= 50) {
        printf("L");
        n = n - 50;
    }
    while (n >= 10) {
        printf("X");
        n = n - 10;
    }
    while (n >= 5) {
        printf("V");
        n = n - 5;
    }
    while (n >= 1) {
        printf("I");
        n = n - 1;
    }
    printf("\n");
    return 0;
}

/* für Aufgabenteil b) */
int neueRoemischeZahl(int n)
{
    /*
     * n ist die Summe aus k1*1000, k2*900, k3*500, k4*400, k5*100, k6*90, 
     * k7*50, k8*40, k9*10, k10*9, k11*5, k12*4, k13*1
     *
     * Dabei können k1 (mit der Bedingung in der main-Funktion), k5, k9 und k13 
     * nicht größer als 3 und die anderen k's nicht größer als 1 sein
     */

    int k1 = n / 1000;
    n = n % 1000;
    int k2 = n / 900;
    n = n % 900;
    int k3 = n / 500;
    n = n % 500;
    int k4 = n / 400;
    n = n % 400;
    int k5 = n / 100;
    n = n % 100;
    int k6 = n / 90;
    n = n % 90;
    int k7 = n / 50;
    n = n % 50; 
    int k8 = n / 40;
    n = n % 40;
    int k9 = n / 10;
    n = n % 10;
    int k10 = n / 9;
    n = n % 9;
    int k11 = n / 5;
    n = n % 5;
    int k12 = n / 4;
    n = n % 4;
    int k13 = n / 1;
    n = n % 1;
    while (k1 > 0) {
        printf("M");
        k1 = k1 - 1;
    }
    while (k2 > 0) {
        printf("CM");
        k2 = k2 - 1;  
    }
    while (k3 > 0) {
        printf("D");
        k3 = k3 - 1;
    }
    while (k4 > 0) {
        printf("CD");
        k4 = k4 - 1;
    }
    while (k5 > 0) {
        printf("C");
        k5 = k5 - 1;
    }
    while (k6 > 0) {
        printf("XC");
        k6 = k6 - 1;
    }
    while (k7 > 0) {
        printf("L");
        k7 = k7 - 1;
    }
    while (k8 > 0) {
        printf("XL");
        k8 = k8 - 1;
    }
    while (k9 > 0) {
        printf("X");
        k9 = k9 - 1;
    }
    while (k10 > 0) {
        printf("IX");
        k10 = k10 - 1;
    }
    while (k11 > 0) {
        printf("V");
        k11 = k11 - 1;
    }
    while (k12 > 0) {
        printf("IV");
        k12 = k12 - 1;
    }
    while (k13 > 0) {
        printf("I");
        k13 = k13 - 1;
    }
    printf("\n");
    return 0;
}

/* für Aufgabenteil c) */
int readInt()
{
    int number;
    scanf("%d", &number);
    return number;
}

int main()
{
    printf("Geben Sie eine natürliche Zahl < 4000 ein  : ");
    int n = readInt();

    if (n >= 4000) {
        printf("Die Zahl muss kleiner als 4000 sein!\n");
        return 0;
    }
    if (n <= 0) {
        printf("Die Zahl muss eine natürliche Zahl sein!\n");
        return 0;
    }

    /* %4d, damit die Doppelpunkte untereinander aufgereiht sind */
    printf("Die Zahl %4d im altrömischen System lautet: ", n);
    alteRoemischeZahl(n);
    printf("Die Zahl %4d im neurömischen System lautet: ", n);
    neueRoemischeZahl(n);
    return 0;
}
