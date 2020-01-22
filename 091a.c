#include <stdio.h>
#include <stdlib.h>

void PrintData(int n, double data[n], int L, int R) {
  for (int i = 0; i < n; i++) {
    if (L <= i && i <= R)
      printf("%2.0f ", data[i]); // L~R番目は要素の値を表示
    else
      printf(" | "); //それ以外は縦線を表示
  }
  printf("\n");
}

void swap(double *x, double *y) {
  double z = *x;
  *x = *y;
  *y = z;
}

void BubbleSort(int n, double data[n]) {
  for (int i = n; i > 1; i--) {
    for (int j = 0; j < i - 1; j++) {
      if (data[j] > data[j + 1])
        swap(&data[j], &data[j + 1]);
    }
    PrintData(n, data, 0, i - 1);
  }
}

int main(void) {
  srand(1234);
  int n = 20;
  double data[n];
  for (int i = 0; i < n; i++) {
    data[i] = rand() % 100; // 0以上100未満の整数乱数
  }
  PrintData(n, data, 0, n - 1); //全要素を表示
  BubbleSort(n, data);
  PrintData(n, data, 0, n - 1); //全要素を表示
  return 0;
}