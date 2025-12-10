#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Function to read dimensions of matrix
int readMatrixDim(int *r, int *c) {
  if (scanf("%d %d", r, c) == 2) {
    return 0;
  } else if (*r == EOF) {
    return 1;
  }
  fprintf(stderr, "Cannot read dim of m.\n");
  exit(101);
  return 2;
}
 
// Function to print matrix
void printMatrix(int rows, int cols, int matrix[rows][cols]) {
 
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      printf("%d", matrix[r][c]);
      if (c != cols - 1) {
        printf(" ");
      }
    }
    printf("\n");
  }
}
 
// Function to read matrix
_Bool readMatrix(int rows, int cols, int matrix[rows][cols]) {
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (scanf("%d", &(matrix[r][c])) != 1) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
      }
    }
  }
  return 1;
}
 
// MAke sum of matrices
void sum(int r_rows, int r_cols, int m1[r_rows][r_cols], int m2[r_rows][r_cols],
         int result[r_rows][r_cols]) {
  for (int r = 0; r < r_rows; r++) {
    for (int c = 0; c < r_cols; c++) {
      result[r][c] = m1[r][c] + m2[r][c];
    }
  }
}
 
// Substract matrices
void substract(int r_rows, int r_cols, int m1[r_rows][r_cols],
               int m2[r_rows][r_cols], int result[r_rows][r_cols]) {
  for (int r = 0; r < r_rows; r++) {
    for (int c = 0; c < r_cols; c++) {
      result[r][c] = m1[r][c] - m2[r][c];
    }
  }
}
 
// Multiply matrices
void multiply(int rows1, int cols1, int rows2, int cols2, int r_rows,
              int r_cols, int m1[rows1][cols1], int m2[rows2][cols2],
              int result[r_rows][r_cols]) {
  int tmp;
  for (int r = 0; r < rows1; r++) {
    for (int c = 0; c < cols2; c++) {
      tmp = 0;
      for (int n = 0; n < cols1; n++) {
        tmp += m1[r][n] * m2[n][c];
      }
      result[r][c] = tmp;
    }
  }
}
 
void printWrongOutput(void) {
  fprintf(stderr, "Error: Chybny vstup!\n");
  exit(100);
}
 
void printMemoryFailure(int rows, int cols, int m[rows][cols]) {
  fprintf(stderr, "Error: Nepodařilo se realokovat!\n");
  free(m);
  exit(100);
}
 
int main(int argc, char *argv[]) {
  int ret = 0;
  int rows, cols, rows1 = 1, cols1 = 1, rows2 = 1, cols2 = 1, rows3, cols3, r_rows = 0,
                                                            r_cols = 0;
  char operation_tmp = 'x', operation1 = 'x', operation2 = 'x';
  int x = 0, c = 1;
  int(*m1)[c] = malloc(sizeof *m1);
  int(*m2)[c] = malloc(sizeof *m2);
  int(*m3)[c] = malloc(sizeof *m3);
  int(*result)[c] = malloc(sizeof *result);
  // The last thing we deed
  int ending = -1;
 
  //rows1 = cols1 = 1;
 
  // I am sorry for implementing the whole thing in main
  // I struggled with poinetrs. It actually worked,
  // but clang gave warnings
 
  // The whole idea is to read matrices one by one
  // We remember only three of them at ones
  // so we do not use a lot of memory
 
  while (readMatrixDim(&rows, &cols) != 1) {
    // Just read three matrices here
    if (x == 0) {
      rows1 = rows;
      cols1 = cols;
      m1 = realloc(m1, rows1 * cols1 * sizeof(int));
      if (m1 == NULL) {
        printMemoryFailure(rows1, cols1, m1);
      }
      readMatrix(rows1, cols1, m1);
      x += 1;
    } else if (x == 1) {
      rows2 = rows;
      cols2 = cols;
      m2 = realloc(m2, rows2 * cols2 * sizeof(int));
      if (m2 == NULL) {
        printMemoryFailure(rows2, cols2, m2);
      }
      readMatrix(rows2, cols2, m2);
      x += 1;
    } else if (x == 2) {
      rows3 = rows;
      cols3 = cols;
      m3 = realloc(m3, rows3 * cols3 * sizeof(int));
      if (m3 == NULL) {
        printMemoryFailure(rows3, cols3, m3);
      }
      readMatrix(rows3, cols3, m3);
      x += 1;
    }
 
    // If we have already read 2 matrices
    // and the first operation was
    // multiplication, we just multiply
    // to save space
    if (x == 2 && operation1 == '*') {
      if (cols1 != rows2) {
        printWrongOutput();
      }
      r_rows = rows1;
      r_cols = cols2;
      result = realloc(result, r_rows * r_cols * sizeof(int));
      if (result == NULL) {
        printMemoryFailure(r_rows, r_cols, result);
      }
      multiply(rows1, cols1, rows2, cols2, r_rows, r_cols, m1, m2, result);
      rows1 = r_rows;
      cols1 = r_cols;
      m1 = realloc(m1, r_rows * r_cols * sizeof(int));
      if (m1 == NULL) {
        printMemoryFailure(r_rows, r_cols, m1);
      }
      memcpy(m1, result, r_rows * r_cols * sizeof(int));
      x = 1;
      ending = 1;
    }
 
    // If the first 2 matrices were sum or substraction
    // and the second and third are multiplication
    // we just multiply second and third and leave alone
    // the first one
    if (x == 3 && operation2 == '*') {
      if (cols2 != rows3) {
        printWrongOutput();
      }
      r_rows = rows2;
      r_cols = cols3;
      result = realloc(result, r_rows * r_cols * sizeof(int));
      if (result == NULL) {
        printMemoryFailure(r_rows, r_cols, result);
      }
      multiply(rows2, cols2, rows3, cols3, r_rows, r_cols, m2, m3, result);
      rows2 = r_rows;
      cols2 = r_cols;
      m2 = realloc(m2, r_rows * r_cols * sizeof(int));
      if (m2 == NULL) {
        printMemoryFailure(rows3, cols3, m2);
      }
      memcpy(m2, result, r_rows * r_cols * sizeof(int));
      x = 2;
      ending = 2;
    }
 
    // If the second and third are also sum or substraction
    // we just sum or substract the first 2
    // and move the third one to the second one
    if (x == 3 && (operation1 == '+' || operation1 == '-')) {
      if (rows1 != rows2 || cols1 != cols2) {
        printWrongOutput();
      }
      r_rows = rows1;
      r_cols = cols1;
      result = realloc(result, r_rows * r_cols * sizeof(int));
      if (result == NULL) {
        printMemoryFailure(r_rows, r_cols, result);
      }
      if (operation1 == '+') {
        sum(r_rows, r_cols, m1, m2, result);
      } else {
        substract(r_rows, r_cols, m1, m2, result);
      }
      m1 = realloc(m1, r_rows * r_cols * sizeof(int));
      if (m1 == NULL) {
        printMemoryFailure(r_rows, r_cols, m1);
      }
      memcpy(m1, result, r_rows * r_cols * sizeof(int));
      rows1 = r_rows;
      r_cols = cols;
      m2 = realloc(m2, rows3 * cols3 * sizeof(int));
      if (m2 == NULL) {
        printMemoryFailure(rows3, cols3, m2);
      }
      memcpy(m2, m3, rows3 * cols3 * sizeof(int));
      rows2 = rows3;
      cols2 = cols3;
      ending = 3;
      operation1 = operation2;
      operation2 = 'x';
      x = 2;
    }
 
    // Scan the operation
    // Only +, - or * are valid
    if (scanf(" %c", &operation_tmp) != 1) {
      goto ending_sequence;
    } else {
      if (x == 1) {
        operation1 = operation_tmp;
      } else if (x == 2) {
        operation2 = operation_tmp;
      } else {
        fprintf(stderr, "Error: Nepodarilo se nacist operaci!\n");
        return 100;
      }
    }
  }
 
// If there is nothing left, we just move to an end
ending_sequence:
  // If there were only 2 matrices, which were multiplied
  if (ending == 1 && operation2 != 'x') {
  }
  // If we stopped on multipling second and third ones
  else if (ending == 2 && operation2 != 'x') {
    r_rows = rows1;
    r_cols = cols2;
    result = realloc(result, r_rows * r_cols * sizeof(int));
    if (result == NULL) {
      printMemoryFailure(r_rows, r_cols, result);
    }
    if (operation1 == '+') {
      sum(r_rows, r_cols, m1, m2, result);
    } else {
      substract(r_rows, r_cols, m1, m2, result);
    }
 
  }
  // If the operations were + or - and there are
  //  3 matrices
  else if (ending == 3 && operation2 == 'x') {
    if (rows1 != rows2 || cols1 != cols2) {
      printWrongOutput();
    }
    r_rows = rows1;
    r_cols = cols2;
    result = realloc(result, r_rows * r_cols * sizeof(int));
    if (result == NULL) {
      printMemoryFailure(r_rows, r_cols, result);
    }
    if (operation1 == '+') {
      sum(r_rows, r_cols, m1, m2, result);
    } else {
      substract(r_rows, r_cols, m1, m2, result);
    }
 
  }
  // If there were only 2 matrices, which were summed
  //  or substracted
  else if (operation2 == 'x' && (operation1 == '+' || operation1 == '-')) {
    r_rows = rows1;
    r_cols = cols1;
    result = realloc(result, r_rows * r_cols * sizeof(int));
    if (result == NULL) {
      printMemoryFailure(r_rows, r_cols, result);
    }
    if (rows1 != rows2 || cols1 != cols2) {
      printWrongOutput();
    }
    if (operation1 == '+') {
      sum(r_rows, r_cols, m1, m2, result);
    } else {
      substract(r_rows, r_cols, m1, m2, result);
    }
  }
 
  if (ret == 0) {
    printf("%d %d\n", r_rows, r_cols);
    printMatrix(r_rows, r_cols, result);
  }
 
  free(m1);
  free(m2);
  free(m3);
  free(result);
  return ret;
}
