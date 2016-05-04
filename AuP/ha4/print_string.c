#include <stdio.h>
#include <stdbool.h>

/*
 * Markierung für Löschung im String,
 * ascii-Wert 127 (DEL) dürfte als Platzhalter ok sein
 */
#define MARK 127

/*
 * Hilfsfunktionen
 */

int readInt()
{
    int number;
    scanf("%d", &number);
    return number;
}

int evalWord(char string[], int i)
{
    int count = 0;
    for (int k = i; string[k] != ' ' && string[k] != 0 && string[k] != MARK; k++) {
        count++;
    }
    return count;
}

void printWord(char string[], int i)
{
    for (int k = i; string[k] != ' ' && string[k] != 0 && string[k] != MARK; k++) {
        putchar(string[k]);
    }
}

/*
 * für Aufgabe a
 */

int countWords(char string[])
{
    int i = 0;
    int count = 0;
    for (i = 0; string[i] != 0; i++) {
        /* immer ein <SPACE> zwischen Wörtern */
        if (string[i] == ' ') {
            count ++;
        }
    }
    /* Wort <SPACE> Wort ==> es gibt immer ein Wort mehr als Leerzeichen */
    return count + 1;
}

/*
 * für Aufgabe b
 */

int wordWrap(char string[], int b)
{
    int lineLength = 0;
    int wordLength = 0;
    int newLineLength = 0;
    for (int i = 0; string[i] != 0; i++) {
        if ((string[i] >= 'a' && string[i] <= 'z')
                || (string[i] >= 'A' && string[i] <= 'Z')
                /* ASCII 39 --> Apostroph ' */
                || (string[i] == 39)) {
            wordLength = evalWord(string, i);
            newLineLength = lineLength + wordLength;
            /*
             * in der Beispielausgabe wurde hier wohl >= und > verwechselt
            /* --> dort gibt es Zeilen mit 71/21 statt 70/20 Spalten
             */
            if (newLineLength >= b) {
                printf("\n");
                lineLength = 0;
            }
            printWord(string, i);
            printf(" ");
            lineLength += wordLength + 1;
            i += wordLength;
        }
    }
    printf("\n");
    return 0;
}

/*
 * für Aufgabe c
 */

int markWord(char string[], int c)
{
    int i = 0;
    int count = 0;
    if (c > 1) {
        for (i = 0; string[i] != 0; i++) {
            if (string[i] == ' ' && count + 2 < c) {
                count++;
            } else if (string[i] == ' ' && count + 2 == c) {
                do {
                    putchar(string[i]);
                    string[i] = MARK;
                    i++;
                } while (string[i] != ' ' && string[i] != 0);
                return 0;
            }
        }
    } else {  // c == 1
        do {
            putchar(string[i]);
            string[i] = MARK;
            i++;
        } while (string[i] != ' ' && string[i] != 0);
        if (string[i] == ' ') {
            string[i] = MARK;
            i++;
        }
        return 0;
    }
    printf("\n");
    return 0;
}

int main()
{
    char string[] = {"to be or not to be, that is the question: whether 'tis nobler in the mind to suffer the slings and arrows of outrageous fortune, or to take arms against a sea of troubles, and by opposing, end them? to die: to sleep; no more; and by a sleep to say we end the heartache and the thousand natural shocks that flesh is heir to, 'tis a consummation devoutly to be wish'd. to die, to sleep; to sleep: perchance to dream: ay, there's the rub; for in that sleep of death what dreams may come when we have shuffled off this mortal coil, must give us pause: there's the respect that makes calamity of so long life; for who would bear the whips and scorns of time, the oppressor's wrong, the proud man's contumely, the pangs of despised love, the law's delay, the insolence of office and the spurns that patient merit of the unworthy takes, when he himself might his quietus make with a bare bodkin?"};
//  char string[] = {"dies ist ein test."};
//  char string[] = {"zwanzigzeichenlange wort."};
    int count;
    int b;
    int c;
    for (count = countWords(string); count > 0; count--) {
        printf("Geben Sie die Ausgabebreite ein (20-80): ");
        b = readInt();
        printf("\n");
        if (b > 80 || b < 20) {
            printf("Falsche Zahl\n");
        } else {
            wordWrap(string, b);
            printf("\n");
        }
        printf("Das wievielte Wort soll gelöscht werden (1 - %d)? ", count);
        c = readInt();
        printf("\n");
        if (c < 1 || c > count) {
            printf("Falsche Zahl\n");
        } else {
            printf("Das zu löschende Wort heißt:");
            markWord(string, c);
            printf("\n\n");
        }
    }
    return 0;
}
