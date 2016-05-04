#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix(const int M, const int N);
    ~Matrix();
    void set(int *a);
    void out();
    void trp();
    void add(Matrix &m);
    void mul(Matrix &m);
    bool sym();
    bool ort();
    int getM();
    int getN();
    int getElem(int i, int j);
    void setElem(int i, int j, int value);

    /* Hilfsmethoden */
    Matrix *copy();
    Matrix *operator*(Matrix &r);

private:
    int M;
    int N;
    int **matr;
};

#endif
