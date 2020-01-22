#include <stdbool.h>
#include <stdio.h>

bool HasOneDivisor(int x) {
  int count = 0;
  for (int i = 2; i < x; i++) {
    if (x % i != 0)
      continue;
    count++;
    if (count == 2)
      return false;
  }
  return count == 1;
}

int main(void) {
  for (int x = 1; x <= 100; x++) {
    if (HasOneDivisor(x))
      printf("%d, ", x);
  }
  printf("\n");
  return 0;
}
