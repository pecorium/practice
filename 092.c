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
      if (data[j] > data[j + 1]) {
        swap(&data[j], &data[j + 1]);
      }
    }
    PrintData(n, data, 0, i - 1);
  }
}

void QuickSortBase(int n, double data[n], int L, int R) {
  int l = L;
  int r = R;
  double p = data[(L+R)/2];
  while (l <= r) {
    while (data[l] < p) l += 1;
    while (data[r] > p) r -= 1;
    if (l > r)  break;
    if (l < r)  swap(&data[l], &data[r]);
    l += 1;
    r -= 1;
  }
  PrintData(n, data, L, R);
  if (L < r)  QuickSortBase(n, data, L, r);
  if (l < R)  QuickSortBase(n, data, l, R);
}

void QuickSort(int n, double data[n]) {
  if (n <= 1) return;
  QuickSortBase(n, data, 0, n-1);
}

int main(void) {
  srand(1127);
  int n = 20;
  double data[n];
  for (int i = 0; i < n; i++) {
    data[i] = rand() % 100; // 0以上100未満の整数乱数
  }
  PrintData(n, data, 0, n - 1); //全要素を表示
  QuickSort(n, data);
  PrintData(n, data, 0, n - 1); //全要素を表示
  return 0;
}