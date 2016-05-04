#include <stdio.h>
#include "include/hilfsfunktionen.hpp"

int readInt(FILE *input)
{
    int number;
    fscanf(input, "%d", &number);
    return number;
}
