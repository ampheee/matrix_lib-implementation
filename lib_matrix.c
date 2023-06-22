#include "lib_matrix.h"

int lib_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows < 1 || columns < 1) {
    res = INCORRECT;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
      }
    }
  }
  return res;
}
int lib_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
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
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
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
            double sum = 0;
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
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
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
  res = lib_create_matrix(A->rows, A->columns, result);
  if (!isIncorrect(A) && A->columns == A->rows) {
    if (A->rows == 1) result->matrix = A->matrix;
    if (A->rows == 2) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor;
          getMinor(A, &minor, i, j);
          result->matrix[i][j] = pow(-1, i + j) * minor.matrix[0][0];
          lib_remove_matrix(&minor);
        }
      }
    }
    if (A->rows >= 3) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor;
          getMinor(A, &minor, i, j);
          result->matrix[i][j] = pow(-1, i + j) * determinantRecur(&minor);
          lib_remove_matrix(&minor);
        }
    }
  } else {
    res = ERR;
  }
  return res;
}

int lib_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (!isIncorrect(A)) {
    if (A->columns == A->rows) {
      *result = determinantRecur(A);
    } else {
      res = ERR;
    }
  } else {
    res = INCORRECT;
  }
  return res;
}

// Найти определитель (детерминант) матрицы A. Если определитель ≠ 0, то
// обратная матрица существует. Если определитель = 0, то обратная матрица не
// существует. Найти матрицу миноров M. Из матрицы M найти матрицу
// алгебраических дополнений C*. Транспонировать матрицу (поменяем местами
// строки со столбцами) C*, получить матрицу C*T. По формуле найти обратную
// матрицу. A^-1 = C*T / det A

int lib_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  double det = 0;
  matrix_t adjust = {0};
  matrix_t transposed = {0};
  if (!isIncorrect(A)) {
    if (A->rows != A->columns) {
      status = ERR;
    } else {
      int code = lib_determinant(A, &det);
      if (fabs(det) < lib_EPS || code) {
        status = ERR;
      } else {
        if (!lib_calc_complements(A, &adjust) &&
            !(lib_transpose(&adjust, &transposed) ||
              lib_create_matrix(A->rows, A->columns, result))) {
          for (int i = 0; i < A->rows; ++i) {
            for (int j = 0; j < A->columns; ++j) {
              result->matrix[i][j] = transposed.matrix[i][j] / det;
            }
          }
        }
      }
    }
  } else {
    status = INCORRECT;
  }
  lib_remove_matrix(&transposed);
  lib_remove_matrix(&adjust);
  return status;
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

// utility-funcs

void getMinor(matrix_t *A, matrix_t *minor, int i, int j) {
  lib_create_matrix(A->rows - 1, A->columns - 1, minor);
  for (int a = 0, b = 0; a < A->rows; ++a, ++b) {
    if (a == i) ++a;
    if (a == A->rows) break;
    for (int c = 0, d = 0; c < A->columns; ++c, ++d) {
      if (c == j) ++c;
      if (c == A->columns) break;
      minor->matrix[b][d] = A->matrix[a][c];
    }
  }
}

int determinantRecur(matrix_t *A) {
  double res = 0;
  if (A->rows == 1) res = A->matrix[0][0];
  if (A->rows == 2) {
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  }
  if (A->rows >= 3) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor;
        getMinor(A, &minor, i, j);
        res += A->matrix[i][j] * pow(-1, i + j) * determinantRecur(&minor);
        lib_remove_matrix(&minor);
      }
      return res;
    }
  }
  return res;
}

int isIncorrect(matrix_t *Matrix) {
  int res = INCORRECT;
  if (Matrix != NULL && Matrix->matrix != NULL && Matrix->columns >= 1 &&
      Matrix->rows >= 1) {
    res = OK;
  }
  return res;
}
