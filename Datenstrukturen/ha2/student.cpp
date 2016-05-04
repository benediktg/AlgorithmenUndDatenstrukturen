#include <stdio.h>
#include "hilfsfunktionen.hpp"
#include "student.hpp"

void addStudent(student **body, int number, int *stCount)
{
    int index = 0;
    while (body[index] && body[index]->number < number)
        /* zur einzufügenden Stelle vorrücken */
        index++;
    for (int i = 998; i >= index; i--)
        /* Platz schaffen für einzufügendes Element */
        body[i + 1] = body[i];
    student *temp = new student;
    temp = readStudent(number);
    body[index] = temp;
    /* es wurde ein Element hinzugefügt */
    (*stCount)++;
    return;
}

bool searchStudent(student **body, int value, int *stCount)
{
    int upper = *stCount - 1;
    int lower = 0;
    /* für binäre Suche */
    int mid;
    if (body[0]) {
        while (lower <= upper) {
            mid = lower + ((upper - lower) / 2);
            if (body[mid]->number == value) { // Mitte gleich gesucht
                return true;
            } else if (body[mid]->number < value) { // Mitte kleiner als gesucht
                lower = mid + 1;
            } else { // Mitte größer als gesucht
                upper = mid - 1;
            }
        }
        return false;
    } else {
        /* leeres Verwaltungsfeld */
        return false;
    }
}

void deleteStudent(student **body, int number, int *stCount)
{
    int index = 0;
    while (body[index]->number < number)
        /* zur zu löschenden Stelle vorrücken */
        index++;
    delete body[index];
    for (int i = index; i < 999; i++)
        /* damit keine Lücken auftreten */
        body[i] = body[i + 1];
    body[999] = 0;
    /* es wurde ein Element gelöscht */
    (*stCount)--;
    return;
}
