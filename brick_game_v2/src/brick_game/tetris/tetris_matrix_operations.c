#include "tetris_matrix_operations.h"

#include <stdlib.h>

/**
 * @brief Create matrix
 * @param rows Rows of 2x array.
 * @param cols Columns of 2x array.
 * @param ***m Pointer of 2x array.
 */
void create_matrix(int rows, int cols, int ***dest) {
  *dest = (int **)calloc(rows, sizeof(int *));
  for (int i = 0; i < rows; ++i) {
    (*dest)[i] = (int *)calloc(cols, sizeof(int));
  }
}

/**
 * @brief Delete matrx
 * @param rows Rows of 2x array.
 * @param cols Columns of 2x array.
 * @param ***m Pointer of 2x array.
 */
void delete_matrix(int rows, int ***dest) {
  for (int i = 0; i < rows; ++i) {
    free((*dest)[i]);
  }
  free(*dest);
  *dest = NULL;
}
