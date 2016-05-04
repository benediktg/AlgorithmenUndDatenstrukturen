#include <stdio.h>
#include "include/readInt.hpp"

int readInt(FILE *input)
{
    int number;
    fscanf(input, "%d", &number);
    return number;
}
