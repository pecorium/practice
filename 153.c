#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  int score;
} Exam;

void PrintData(int n, Exam data[n]) {
  for (int i = 0; i < n; i++) {
    printf("%2d:%2d, ", data[i].id, data[i].score);
  }
  printf("\n");
}

void swap(Exam *x, Exam *y) {
  Exam z = *x;
  *x = *y;
  *y = z;
}

void MarginalizeMin(int n, Exam data[n]) {
  int m = 0;
  for (int i = 1; i < n; i++) {
    if (data[m].score > data[i].score)
      m = i;
  }
  swap(&data[m], &data[n - 1]);
}

void Sort(int n, Exam data[n]) {
  for (int i = n; i >= 2; i--) {
    MarginalizeMin(i, data);
  }
}

int main(void) {
  srand(130);
  int n = 10;
  Exam data[n];
  for (int i = 0; i < n; i++) {
    data[i].id = i;
    data[i].score = rand() % 20 + 80;
  }
  PrintData(n, data);
  Sort(n, data);
  PrintData(n, data);
  return 0;
}