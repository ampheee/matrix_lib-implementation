#include "lib_matrix.h"

int lib_create_matrix(int rows, int columns, matrix_t *result) {
    int res = OK;
    if (rows < 1 || columns < 1) {
        res = INCORRECT;
    } else {
        result->columns = columns;
        result->rows = rows;
        result->matrix = (double **) malloc(sizeof(double *) * rows);
        if (result->matrix != NULL) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = (double *) malloc(sizeof(double) * columns);
            }
        }
    }
    return res;
}
int lib_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = OK;
    if (!isIncorrect(A) && !isIncorrect(B)) {
        if (A->columns == B->columns && A->rows == B->rows) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    if (fabs(A->matrix[i][j] - B->matrix[i][j]) > lib_EPS) {
                        res = FAILURE;
                    }
                }
            }
        } else {
            res = FAILURE;
        }
    } else {
        res = FAILURE;
    }
    return res;
}
int lib_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (!isIncorrect(A) && !isIncorrect(B)) {
        if (A->columns == B->columns && A->rows == B->rows) {
            res = lib_create_matrix(A->rows, B->columns, result);
            if (res == OK) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                    }
                }
            }
        } else { 
            res = ERR;
        }
    } else {
        res = INCORRECT;
    }
    return res;
}

int lib_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (!isIncorrect(A) && !isIncorrect(B)) {
        if (A->columns == B->columns && A->rows == B->rows) {
            res = lib_create_matrix(A->rows, B->columns, result);
            if (res == OK) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                    }
                }
            }
        } else { 
            res = ERR;
        }
    } else {
        res = INCORRECT;
    }
    return res;
}

int lib_mult_number(matrix_t *A, double number, matrix_t *result) {
    int res = OK;
    if (!isIncorrect(A)) {
        res = lib_create_matrix(A->columns, A->rows, result);
        if (res == OK) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        }
    } else {
        res = INCORRECT;
    }
    return res;
}
int lib_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (!isIncorrect(A) && !isIncorrect(B)) {
        if (A->columns == B->rows) {
            res = lib_create_matrix(A->rows, B->columns, result);
            if (res == OK) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < B->columns; j++) {
                        int sum = 0;
                        for (int k = 0; k < A->columns; k++) {
                            sum += A->matrix[i][k] * B->matrix[k][j];
                        }
                        result->matrix[i][j] = sum;
                    }
                }
            }
        } else {
            res = ERR;
        }
    } else {
        res = INCORRECT;
    }
    return res;
}

int lib_transpose(matrix_t *A, matrix_t *result) {
    int res = OK;
    if (!isIncorrect(A)) {
        res = lib_create_matrix(A->columns, A->rows, result);
        if (res == OK) {
            for (int i = 0; i < A->columns; i++) {
                for (int j = 0; j < A->rows; j++) {
                    result->matrix[j][i] = A->matrix[i][j];
                }
            }
        }
    } else {
        res = INCORRECT;
    }
    return res;
}
int lib_calc_complements(matrix_t *A, matrix_t *result) {
    int res = OK;
    if (!isIncorrect(A)) {
        res = lib_create_matrix(A->rows, A->columns, result);
        if (res == OK) {
            for (int i = 0; i < A->columns; i++) {
                for (int j = 0; j < A->rows; i++) {
                    double MinorRes;
                    matrix_t MinorMatrix;
                    res = GetMinor(i, j, A, &MinorMatrix);
                    if (res == OK) {
                        res = lib_determinant(&MinorMatrix, &MinorRes);
                        if (res == OK) {
                            result->matrix[i][j] = pow(-1, i + j) * MinorRes;
                        }
                    }
                    lib_remove_matrix(&MinorMatrix);
                }
            }
        }

    }
    return res;
}

int lib_determinant(matrix_t *A, double *result) {
    int res = OK;
    if (!isIncorrect(A)) {
        if (A->columns == A->rows) {
            if (A->columns == 1) {
                *result = A->matrix[0][0];
            }
            *result = determinantRecur(A);
        } else {
            res = ERR;
        }
    } else {
        res = INCORRECT;
    }
    return res;
}


// Найти определитель (детерминант) матрицы A. Если определитель ≠ 0, то обратная матрица существует. Если определитель = 0, то обратная матрица не существует.
// Найти матрицу миноров M.
// Из матрицы M найти матрицу алгебраических дополнений C*.
// Транспонировать матрицу (поменяем местами строки со столбцами) C*, получить матрицу C*T.
// По формуле найти обратную матрицу.
// A^-1 = C*T / det A
int lib_inverse_matrix(matrix_t *A, matrix_t *result) {
    int res = OK;
    if(!isIncorrect(A)) {
        double deter;
        lib_determinant(A, &deter);
        if (deter != 0) {
            matrix_t complements;
            res = lib_calc_complements(A, &complements);
            if (res == OK) {
                matrix_t transposed;
                res = lib_transpose(&complements, &transposed);
                if (res == OK) {
                    res = lib_create_matrix(A->rows, A->columns, result);
                    if (res == OK) {
                        lib_mult_number(&transposed, 1./deter, result);
                    }
                }
                lib_remove_matrix(&transposed);
            }
            lib_remove_matrix(&complements);
        } else {
            res = ERR;
        }
    } else {
        res = INCORRECT;
    }
    return res;
}

void lib_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++) {
        if (A->matrix[i]) {
            free(A->matrix[i]);
        }
    }
    free(A->matrix);
    if (A->columns != 0) {
        A->columns = 0;
    }
    if (A->rows != 0) {
        A->rows = 0;
    }
    A = NULL;
}

//utility-funcs

int GetMinor(int xRow, int yColumn, matrix_t *Matrix,  matrix_t *tempMatrix) {
    int res = INCORRECT;
    if (Matrix->matrix != NULL) {
        res = lib_create_matrix(Matrix->rows - 1, Matrix->columns - 1, tempMatrix);
        if (res == OK) {
            int minor_i, minor_j;
            for (int i = 0; i < Matrix->rows; i++) {
                minor_i = i;
                if (i > xRow) {
                    minor_i -= 1;
                }
                for (int j = 0; j < Matrix->columns; j++) {
                    minor_j = j;
                    if (j > yColumn) {
                        minor_j -= 1;
                    }
                    if (i != xRow && j != yColumn) {
                        tempMatrix->matrix[minor_i][minor_j] = Matrix->matrix[i][j];
                    }
                }
            }
        }
    }
    return res;
}

double determinantRecur(matrix_t *A) {
    double res;
    if (A->columns == 2 && A->rows == A->columns) {
        res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else {
        for (int i = 0; i < A->columns; i ++) {
            matrix_t temp;
            GetMinor(0, i, A, &temp);
            if (i % 2 == 0) {   
                res += A->matrix[0][i] * determinantRecur(&temp);
            } else {
                res -= A->matrix[0][i] * determinantRecur(&temp);
            }
            lib_remove_matrix(&temp);
        }
    }
    return res;
}

int isIncorrect(matrix_t *Matrix) {
    int res = INCORRECT;
    if (Matrix != NULL && Matrix->matrix != NULL && Matrix->columns >= 1 && Matrix->rows >= 1) {
        res = OK;
    }
    return res;
}