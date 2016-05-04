#include <stdio.h>
#include <stdbool.h>

/* für Rückgabewert */
struct res {
    int P;
    int S;
};

struct res erathostenes(int N)
{
    /**
     * Das Feld numbers markiert die Primzahlen
     * Da markierte Zahlen keine Primzahlen sind, wird mit '0' markiert
     * Über den Index lässt sich die dahinterstehende Zahl ermitteln:
     * Index + 2 = Zahl
     * Zahl - 2 = Index
     */
    bool numbers[N - 1];
    for (int i = 0; i < N - 1; i++)
        numbers[i] = true;
    struct res result;
    result.P = 0;
    result.S = 0;

    for (int m = 2; m * m <= N; m++) {
        /* m ist möglicherweise Primzahl */
        if (numbers[m - 2])
            for (int i = m * m; i <= N; i++) {
                /* i somit keine Primzahl */
                if (i % m == 0) {
                    numbers[i - 2] = false;
                    /* es wurde eine Streichung vorgenommen */
                    result.S++;
                }
            }
    }
    for (int i = 0; i < N - 1; i++) {
        /* numbers[i] wahr -> Primzahl */
        if (numbers[i])
            result.P++;
    }
    return result;
}

int main(int argc, char **argv)
{
    printf("        N         P         S\n");
    int n = 2;
    struct res result;
    for (int i = 2; i <= 20; i++) {
        n *= 2;
        result = erathostenes(n);
        printf("%9d %9d %9d\n", n, result.P, result.S);
    }
    return 0;
}
