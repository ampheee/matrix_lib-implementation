#include "matrix.h"

int s21_create_matrix(int rows, int columns, s21_matrix_t *result) {
    int res = OK;
    result->matrix = (double **) malloc(sizeof(double *) * rows);
    if (result->matrix != NULL) {
        for (size_t i = 0; i < rows; i++) {
            *(&result->matrix[i]) = (double *) malloc(sizeof(double) * columns);
            if (*result->matrix != NULL) {
                res = INCORRECT;
                break;
            }
        }
    } else {
        res = INCORRECT;
    }
    return res;
}
int s21_eq_matrix(s21_matrix_t *A, s21_matrix_t *B) {
    int res = OK;
    if (A->columns == B->columns && A->rows == B->rows) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (A->matrix[i][j] - B->matrix[i][j] > ACCURACY) {
                    res = FAILURE;
                }
            }
        }
    } else {
        res = FAILURE;
    }
    return res;
}
int s21_sum_matrix(s21_matrix_t *A, s21_matrix_t *B, s21_matrix_t *result) {
    int res = OK;
    return res;
}
int s21_sub_matrix(s21_matrix_t *A, s21_matrix_t *B, s21_matrix_t *result) {
    int res = OK;
    return res;
}
int s21_mult_number(s21_matrix_t *A, double number, s21_matrix_t *result) {
    int res = OK;
    return res;
}
int s21_mult_matrix(s21_matrix_t *A, s21_matrix_t *B, s21_matrix_t *result) {
    int res = OK;
    return res;
}
int s21_transpose(s21_matrix_t *A, s21_matrix_t *result) {
    int res = OK;
    return res;
}
int s21_calc_complements(s21_matrix_t *A, s21_matrix_t *result) {
    int res = OK;
    return res;
}
int s21_determinant(s21_matrix_t *A, double *result) {
    int res = OK;
    return res;
}
int s21_inverse_matrix(s21_matrix_t *A, s21_matrix_t *result) {
    int res = OK;
    return res;
}
void s21_remove_matrix(s21_matrix_t *A);
