#ifndef _SRC_MATRIX_H_
#define _SRC_MATRIX_H_

#include <stdlib.h>

#define ACCURACY 1e-8

#define OK 0 //OK
#define INCORRECT 1 //Ошибка, некорректная матрица
#define ERR 2 // Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

//EQ RESULTS
#define SUCCESS 1
#define FAILURE 0

typedef struct s21_matrix_struct {
    double** matrix;
    int rows;
    int columns;
} s21_matrix_t;

int s21_create_matrix(int rows, int columns, s21_matrix_t *result);
int s21_eq_matrix(s21_matrix_t *A, s21_matrix_t *B);
int s21_sum_matrix(s21_matrix_t *A, s21_matrix_t *B, s21_matrix_t *result);
int s21_sub_matrix(s21_matrix_t *A, s21_matrix_t *B, s21_matrix_t *result);
int s21_mult_number(s21_matrix_t *A, double number, s21_matrix_t *result);
int s21_mult_matrix(s21_matrix_t *A, s21_matrix_t *B, s21_matrix_t *result);
int s21_transpose(s21_matrix_t *A, s21_matrix_t *result);
int s21_calc_complements(s21_matrix_t *A, s21_matrix_t *result);
int s21_determinant(s21_matrix_t *A, double *result);
int s21_inverse_matrix(s21_matrix_t *A, s21_matrix_t *result);
void s21_remove_matrix(s21_matrix_t *A);

#endif  // _SRC_MATRIX_H_