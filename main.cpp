#include <iostream>
#include <cstdio>
#include "matrix.h"

Matrix load_matrix_from_file(char* matrix_file);

Matrix multiply_matrices(Matrix a, Matrix b);

void print_matrix(Matrix matrix, FILE* where_to_print);

void matrix_cleanup(Matrix* matrix);

/* Take in two files on the command line
 * Each file contains a matrix
 * Multiply the two matrices
 * Print the resulting matrix
 *
 */

int main(int argc, char** argv ) {
  /*
   * 1. Load Matrix A
   * 2. Load Matrix B
   * 3. Multiply the matrices
   * 4. Print the result
   * 5. Clean up
   */

  Matrix a = load_matrix_from_file(argv[1]);
  Matrix b = load_matrix_from_file(argv[2]);
  Matrix c = multiply_matrices(a,b);
  print_matrix(c, stdout);
  matrix_cleanup(&a);
  matrix_cleanup(&b);
  matrix_cleanup(&c);

  return 0;
}



