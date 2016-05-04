#include <stdio.h>
#include "include/Matrix.hpp"
#include "include/hilfsfunktionen.hpp"

Matrix::Matrix(const int M, const int N)
{
    this->M = M;
    this->N = N;
    matr = new int*[M];
    for (int i = 0; i < M; i++) {
        matr[i] = new int[N];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < M; i++) {
        delete [] matr[i];
        matr[i] = 0;
    }
    delete [] matr;
    matr = 0;
}

int Matrix::getM()
{
    return M;
}

int Matrix::getN()
{
    return N;
}

int Matrix::getElem(int i, int j)
{
    return matr[i][j];
}

void Matrix::setElem(int i, int j, int value)
{
    matr[i][j] = value;
}

void Matrix::out()
{
    int value;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            value = getElem(i, j);
            printf("%4d ", value);
        }
        printf("\n\n");
    }
}

void Matrix::set(int *a)
{
    for (int i = 0, k = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            setElem(i, j, a[k]);
            k++;
        }
    }
}

void Matrix::add(Matrix &m)
{
    if (this->M != m.getM() || this->N != m.getN()) {
        printf("Addition wegen ungleicher Höhe oder Breite der Matrizen nicht möglich.\n");
    } else {
        for (int i = 0; i < this->M; i++) {
            for (int j = 0; j < this->N; j++) {
                this->setElem(i, j, (this->getElem(i, j) + m.getElem(i, j)));
            }
        }
    }
}

void Matrix::mul(Matrix &m)
{
    if (this->N != m.getM()) {
        printf("Multiplikation wegen ungleicher Breite der 1. und Höhe der 2. Matrix nicht möglich.\n"
               "Keine Ausgabe.\n\n");
    } else {
        /* durch Operatorüberladung unten definiert */
        Matrix *result = *this * m;
        result->out();
        delete result;
    }
}

void Matrix::trp()
{
    /* Hilfsmatrix, um sich die Werte zu merken */
    Matrix *notrp = this->copy();

    /* alte Matrix löschen */
    for (int i = 0; i < notrp->M; i++) {
        delete [] matr[i];
        matr[i] = 0;
    }
    delete [] matr;

    /* neue Matrix anlegen */
    int tmp = M;
    M = N;
    N = tmp;
    matr = new int*[M];
    for (int i = 0; i < M; i++) {
        matr[i] = new int[N];
    }

    /* neue Matrix mit Werten versehen */
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matr[i][j] = notrp->getElem(j, i);
        }
    }

    delete notrp;
}

bool Matrix::sym()
{
    if (M != N) {
        printf("Symmetrietest durch nichtquadratische Matrix falsch.\n");
        return false;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i; j < M; j++) {
            /* Elemente mit vertauschten Indizes müssen gleich sein */
            if (getElem(i, j) != getElem(j, i))
                return false;
        }
    }
    return true;
}

bool Matrix::ort()
{
    Matrix *notrp = this->copy();
    trp();

    /* untransponierte mit transponierter Matrix multiplizieren */
    Matrix *result = *notrp * *this;

    delete notrp;
    notrp = 0;

    /* Test auf Einheitsmatrix */
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if ((i != j && result->getElem(i, j) != 0) || (i == j && result->getElem(i, j) != 1)) {
                delete result;
                result = 0;
                return false;
            }
        }
    }
    delete result;
    result = 0;
    return true;
}

/*
 * Hilfsmethoden
 */

/* tiefes Kopieren */
Matrix *Matrix::copy()
{
    Matrix *result = new Matrix(this->M, this->N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            result->setElem(i, j, this->getElem(i, j));
        }
    }
    return result;
}

/* Matrixmultiplikation */
Matrix *Matrix::operator*(Matrix &r)
{
    Matrix *result = new Matrix(this->M, r.getN());
    int sum;
    for (int i = 0; i < this->M; i++) {
        for (int j = 0; j < r.getN(); j++) {
            sum = 0;
            for (int k = 0; k < this->N; k++) {
                sum += this->getElem(i, k) * r.getElem(k, j);
            }
            result->setElem(i, j, sum);
        }
    }
    return result;
}
