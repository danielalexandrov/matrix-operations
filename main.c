#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int length;
  int *numbers;
} custom_array;

int main() {
  printf("Hello World\n");

  int test2[5];

  for (int i = 0; i < 5; i++) {
    test2[i] = i;
    printf("%d ", test2[i]);
  }

  printf("\n");
  custom_array test;
  test.length = 5;
  test.numbers = malloc(test.length * sizeof(int));
  for (int i = 0; i < test.length; i++) {
    test.numbers[i] = i;
    printf("%d ", test.numbers[i]);
  }

  printf("\n");
  free(test.numbers);
}
