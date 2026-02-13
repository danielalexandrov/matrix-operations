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

void delete_matrix(matrix *m) { free(m->contents); }

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

matrix sum_matrices(matrix *m, matrix *n) {
  matrix result = create_matrix(m->row_count, m->col_count);
  if (m->row_count != n->row_count && m->col_count != n->col_count) {
    printf("Cannot add matrices due to unequal dimensions\n");
    return result;
  }

  for (int i = 0; i < m->row_count; i++) {
    for (int j = 0; j < m->col_count; j++) {
      double sum =
          element_at_ij(m, i + 1, j + 1) + element_at_ij(n, i + 1, j + 1);
      set_element_at_ij(&result, i + 1, j + 1, sum);
    }
  }
  return result;
}

matrix subtract_matrices(matrix *m, matrix *n) {
  matrix result = create_matrix(m->row_count, m->col_count);
  if (m->row_count != n->row_count && m->col_count != n->col_count) {
    printf("Cannot subtract matrices due to unequal dimensions\n");
    return result;
  }

  for (int i = 0; i < m->row_count; i++) {
    for (int j = 0; j < m->col_count; j++) {
      double difference =
          element_at_ij(m, i + 1, j + 1) - element_at_ij(n, i + 1, j + 1);
      set_element_at_ij(&result, i + 1, j + 1, difference);
    }
  }
  return result;
}

// TODO add subtract_matrices

matrix multiply_matrices(matrix *m, matrix *n) {
  matrix result = create_matrix(m->row_count, n->col_count);
  if (m->col_count != n->row_count) {
    printf("The column count of matrix m does not equal the row count of "
           "matrix n\n");
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

double determinant(matrix *m) {
  double result = 0;
  if (m->row_count != m->col_count) {
    printf("This matrix is not square. Determinant cannot be computed\n.");
    return 0;
  }

  if (m->row_count == 2) {
    result = element_at_ij(m, 1, 1) * element_at_ij(m, 2, 2) -
             element_at_ij(m, 1, 2) * element_at_ij(m, 2, 1);
  }
  // TODO add determinant calculation for 3x3 and higher order matrices
  return result;
}

int main() {

  matrix test = create_matrix(2, 3);
  matrix test2 = create_matrix(3, 2);
  matrix test3 = create_matrix(3, 2);

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
  result = sum_matrices(&test2, &test3);

  double test_element = element_at_ij(&result, 2, 2);

  printf("%.2f\n", test_element);

  delete_matrix(&test);
  delete_matrix(&test2);
}
