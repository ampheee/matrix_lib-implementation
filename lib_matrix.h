#ifndef _SRC_MATRIX_H_
#define _SRC_MATRIX_H_

#include <stdlib.h>
#include <math.h>

#define lib_EPS 1E-7

#define OK 0 //OK
#define INCORRECT 1 //Ошибка, некорректная матрица
#define ERR 2 // Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

//EQ RESULTS
#define SUCCESS 1
#define FAILURE 0


typedef struct matrix_t {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int lib_create_matrix(int rows, int columns, matrix_t *result);
int lib_eq_matrix(matrix_t *A, matrix_t *B);
int lib_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int lib_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int lib_mult_number(matrix_t *A, double number, matrix_t *result);
int lib_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int lib_transpose(matrix_t *A, matrix_t *result);
int lib_calc_complements(matrix_t *A, matrix_t *result);
int lib_determinant(matrix_t *A, double *result);
int lib_inverse_matrix(matrix_t *A, matrix_t *result);
void lib_remove_matrix(matrix_t *A);


int isIncorrect(matrix_t *Matrix);
int GetMinor(int xRow, int yColumn, matrix_t *Matrix,  matrix_t *tempMatrix);
double determinantRecur(matrix_t *A);
#endif  // _SRC_MATRIX_H_