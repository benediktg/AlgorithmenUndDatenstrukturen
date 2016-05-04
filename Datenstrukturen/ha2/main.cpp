#include <stdio.h>
#include "student.hpp"
#include "hilfsfunktionen.hpp"

int main()
{
    char c;
    char *s;
    int number;
    student **body = new student*[1000];
    for (int i = 0; i < 1000; i++) {
        body[i] = 0;
    }
    int *stCount = new int(0);

    printf(
        "Studentenverwaltung\n"
        "===================\n"
        "Auswahlmenü:\n"
        "A - Anlegen eines neuen Studenten und der bisher belegten Lehrveranstaltungen\n"
        "S - Suchen eines Studenten\n"
        "L - Löschen eines Studenten\n"
        "E - Programmende\n"
    );
    while (true) {
        printf(">> ");
        s = readString();
        c = s[0];
        if (c == 'a' || c == 'A' || c == 's' || c == 'S' || c == 'l' || c == 'L') {
            printf("Matrikelnummer: ");
            number = readInt();
            while (number < 1 || number > 999999) {
                printf("Nummer außerhalb des Bereichs, erneute Eingabe: ");
                number = readInt();
            }
        }
        if (c == 'A' || c == 'a') {
            if (!searchStudent(body, number, stCount)) {
                addStudent(body, number, stCount);
                printf("Student %d hinzugefügt\n", number);
            } else {
                printf("Student %d bereits vorhanden\n", number);
            }
        } else if (c == 'S' || c == 's') {
            if (searchStudent(body, number, stCount))
                printf("Student %d vorhanden\n", number);
            else
                printf("Student %d nicht vorhanden\n", number);
        } else if (c == 'L' || c == 'l') {
            if (searchStudent(body, number, stCount)) {
                deleteStudent(body, number, stCount);
                printf("Student %d gelöscht\n", number);
            } else {
                printf("Student %d nicht vorhanden\n", number);
            }
        } else if (c == 'E' || c == 'e') {
            delete[] body;
            body = 0;
            delete stCount;
            stCount = 0;
            return 0;
        }
    }
}
