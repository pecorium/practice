#include <stdio.h>

int factorial(int n) {
  if (n == 0)
    return 1;
  return n * factorial(n - 1);
}

int main(void) {
  for (int i = 0; i <= 10; i++) {
    printf("%2d! = %7d\n", i, factorial(i));
  }
  return 0;
}