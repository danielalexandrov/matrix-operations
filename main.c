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

double element_at_ij(matrix m, int i, int j) {
  return m.contents[i * m.col_count + j];
}

void set_element_at_ij(matrix m, int i, int j, double element) {
  m.contents[i * m.col_count + j] = element;
}

int main() {

  matrix test = create_matrix(5, 6);

  for (int i = 0; i < test.row_count; i++) {
    for (int j = 0; j < test.col_count; j++) {
      set_element_at_ij(test, i, j, 0);
    }
  }

  set_element_at_ij(test, 2, 3, 22);

  double test_element = element_at_ij(test, 2, 3);

  printf("%.2f\n", test_element);
}
