#include <stdio.h>
#include "hilfsfunktionen.hpp"
#include "student.hpp"

int readInt()
{
    int number;
    scanf("%d", &number);
    return number;
}

/* aus Übung 3, Felder(2), Aufgabe 2 entnommen */
char *readString()
{
    char c;
    int count = 0;
    char *string_old = 0;
    char *string_new = 0;

    do {
        c = getchar();
        string_new = new char[count + 1];
        for (int i = 0; i < count; i++)
            string_new[i] = string_old[i];
        string_new[count] = c;
        count++;
        delete[] string_old;
        string_old = string_new;
    } while (c != '\n');
    return string_new;
}

student *readStudent(int number)
{
    int tempNumber = number;
    student *newstudent = new student;

    char *trash = new char;
    /* zum Abfangen eines überflüssigen '\n'-Zeichens */
    *trash = getchar();
    /* damit der Name eingelesen werden kann */
    delete trash;
    trash = 0;

    char *tempName;
    do {
        printf("Namen eingeben: ");
        tempName = readString();
    } while (tempName[0] == '\n');  // zur Vermeidung eines leeren Strings als Name
    int templCount = 0;
    char *string[30];
    char *tempLecture[30] = {0};
    for (int i = 0; i < 30; i++) {
        printf("%2d. Lehrveranstaltung von 30 angeben: ", i + 1);
        string[i] = readString();
        if (string[i][0] != '\n') {
            tempLecture[templCount] = string[i];
            templCount++;
        } else if (string[i][0] == '\n') {
            /* zur Vermeidung von unnötigen Eingabeaufforderungen */
            break;
        }
    }
    if (templCount == 0)
        tempLecture[30] = 0;
    newstudent->number = tempNumber;
    newstudent->name = tempName;
    newstudent->lecture = tempLecture;
    newstudent->lCount = templCount;
    return newstudent;
}
