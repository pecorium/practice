#include <stdio.h>

void PrintData(int n, int data[n]) {
  for (int i = 0; i < n; i++) {
    printf("%d, ", data[i]);
  }
  printf("\n");
}

void RotateRight(int n, int data[n], int index) {
  int last = data[n - 1];
  for (int i = n - 1; --i >= index;) {
    data[i + 1] = data[i];
  }
  data[index] = last;
}

int main(void) {
  int n = 10;
  int data[n];
  for (int i = 0; i < n; i++) {
    data[i] = i;
  }
  PrintData(n, data);
  for (int i = 0; i < n; i++) {
    RotateRight(n, data, i);
    PrintData(n, data);
  }
  return 0;
}