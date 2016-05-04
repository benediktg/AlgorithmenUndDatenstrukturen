#include <stdio.h>
#include "include/Matrix.hpp"
#include "include/hilfsfunktionen.hpp"

int main(int argc, char **argv)
{
    if (argc > 3)
        printf("Mehr Argumente als nötig angegeben.\n");
    if (argc < 3) {
        printf("Zu wenige Argumente, bitte 2 Argumente angeben.\n");
        return 0;
    }

    FILE *file1 = fopen(argv[1], "r");
    int M1 = readInt(file1);
    int N1 = readInt(file1);
    int mat1[M1 * N1];
    for (int i = 0; i < M1 * N1; i++) {
        mat1[i] = readInt(file1);
    }
    fclose(file1);

    FILE *file2 = fopen(argv[2], "r");
    int M2 = readInt(file2);
    int N2 = readInt(file2);
    int mat2[M2 * N2];
    for (int i = 0; i < M2 * N2; i++) {
        mat2[i] = readInt(file2);
    }
    fclose(file2);

    Matrix *matrix1 = new Matrix(M1, N1);
    matrix1->set(mat1);
    Matrix *matrix2 = new Matrix(M2, N2);
    matrix2->set(mat2);

    printf("Matrix 1:\n");
    matrix1->out();
    printf("Matrix 2:\n");
    matrix2->out();

    printf("Matrixaddition M1=M1+M2:\n");
    matrix1->add(*matrix2);
    matrix1->out();

    printf("Matrixmultiplikation M2*M1:\n");
    matrix2->mul(*matrix1);

    printf("Matrixtransposition M1=M1^T:\n");
    matrix1->trp();
    matrix1->out();

    printf("Symmetrietest M2:\n");
    if (matrix2->sym())
        printf("Matrix 2 ist symmetrisch.\n\n");
    else
        printf("Matrix 2 ist nicht symmetrisch.\n\n");

    printf("Orthogonalitätstest M1:\n");
    if (matrix1->ort())
        printf("Matrix 1 ist orthogonal.\n\n");
    else
        printf("Matrix 1 ist nicht orthogonal.\n\n");

    delete matrix1;
    matrix1 = 0;
    delete matrix2;
    matrix2 = 0;
    return 0;
}
