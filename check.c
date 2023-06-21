#include "lib_matrix.h"
#include "stdio.h"

void set_matrix(matrix_t *A, double in_matrix[][10]) {
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) A->matrix[i][j] = in_matrix[i][j];
}


int main() {
    matrix_t matrix1, etalon, result;
    printf("c1:%d\n", lib_create_matrix(5, 3, &matrix1));
    printf("c2:%d\n", lib_create_matrix(3, 5, &etalon));
//    printf("c3:%d\n", lib_create_matrix(3, 3, &etalon));
    double in_mat1[10][10] = {
            {1.5, 2.5, 4.5}, {3, 5, 6}, {13, 15, -6}, {1, 8, 7}, {6, 9, 1}};
    double in_etalon[10][10] = {
            {1.5, 3, 13, 1, 6}, {2.5, 5, 15, 8, 9}, {4.5, 6, -6, 7, 1}};

    set_matrix(&matrix1, in_mat1);
    set_matrix(&etalon, in_etalon);
    printf("sub1: %d\n", lib_transpose(&matrix1, &result));
    printf("eq1 after sub: %d\n", lib_eq_matrix(&result, &etalon));
    lib_remove_matrix(&matrix1);
    lib_remove_matrix(&etalon);
    lib_remove_matrix(&result);
}