#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int row_count;
  int col_count;
  double *contents;
} matrix;

matrix create_matrix(int rows, int cols) {
  matrix m = {rows, cols, malloc(rows * cols * sizeof(double))};
  return m;
}

double element_at_ij(matrix *m, int i, int j) {
  return m->contents[(i - 1) * m->col_count +
                     (j - 1)]; // subtract 1 from each index to ensure indeces
                               // match mathematical indeces
}

void set_element_at_ij(matrix *m, int i, int j, double element) {
  m->contents[(i - 1) * m->col_count + (j - 1)] =
      element; // subtract 1 from each index to ensure indeces match
               // mathematical indeces
}

matrix multiply_matrices(matrix *m, matrix *n) {
  matrix result = create_matrix(m->row_count, n->col_count);
  if (m->col_count != n->row_count) {
    perror("The column count of matrix m does not equal the row count of "
           "matrix n");
    return result;
  }

  for (int i = 0; i < result.row_count; i++) {
    for (int j = 0; j < result.col_count; j++) {
      double dot_product = 0;
      for (int k = 0; k < m->col_count; k++) {
        dot_product +=
            element_at_ij(m, i + 1, k + 1) * element_at_ij(n, k + 1, j + 1);
      }
      set_element_at_ij(&result, i + 1, j + 1, dot_product);
    }
  }

  return result;
}

int main() {

  matrix test = create_matrix(2, 3);
  matrix test2 = create_matrix(3, 2);

  for (int i = 0; i < test.row_count; i++) {
    for (int j = 0; j < test.col_count; j++) {
      set_element_at_ij(&test, i + 1, j + 1, 1);
    }
  }

  for (int i = 0; i < test2.row_count; i++) {
    for (int j = 0; j < test2.col_count; j++) {
      set_element_at_ij(&test2, i + 1, j + 1, 2);
    }
  }

  matrix result = multiply_matrices(&test, &test2);

  double test_element = element_at_ij(&result, 2, 2);

  printf("%.2f\n", test_element);
}
