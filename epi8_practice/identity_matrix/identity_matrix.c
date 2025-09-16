#include <stdbool.h>
#include <stdio.h>

// bool identity_matrix(int matrix[10][10]) {
//   int i;
//   for (i = 0; i < 10; i++) {
//     if (matrix[i][i] != 1)
//       return false;
//   }
//   return true;
//}
bool identity_matrix(int matrix[10][10]) {
  int row;
  int column;
  for (row = 0; row < 10; row++) {
    for (column = 0; column < 10; column++) {
      if (matrix[row][column] != (row == column))
        return false;
    }
  }
  return true;
}

bool identity_matrix_advanced(int *matrix, int size) {
  int row;
  int column;

  // go through each of the matrix elements

  for (row = 0; row < size; row += 1) {
    for (column = 0; column < size; column += 1) {
      if (*matrix++ != (row == column))
        return false;
    }
  }
  return true;
}

int main(void) {
  int matrix[10][10] = {{
                            1,

                        },
                        {
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            0,
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            0,
                            0,
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            1,
                        },
                        {
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                            0,
                        }};

  bool if_matrix = identity_matrix(matrix);
  // bool if_matrix = identity_matrix_advanced(&matrix[0][0], 10);
  printf("this matrix is %s matrix.\n", if_matrix ? "actual" : "not");

  return 0;
}
