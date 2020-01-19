#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  char name[1000];
  double avg;
} Student;

void PrintStudentP(Student *s) {
  printf("%04d %-8s %4.1f\n", s->id, s->name, s->avg);
}

void swapStudentP(Student **x, Student **y) {
  Student *z = *x;
  *x = *y;
  *y = z;
}

void BubbleSortStudentP(int n, Student *data[n]) {
  for (int i = n; i > 1; i--) {
    for (int j = 0; j < i - 1; j++) {
      if (data[j]->avg > data[j + 1]->avg)
        swapStudentP(&data[j], &data[j + 1]);
    }
  }
}

int main(void) {
  srand(1204);
  int n = 10;
  Student *data[n]; //←ポインタの配列
  for (int i = 0; i < n; i++) {
    Student *s = malloc(sizeof(Student)); //←メモリ確保
    s->id = i;
    s->avg = rand() % 100; //平均点
    for (int j = 0; j < 8; j++) {
      s->name[j] = 'a' + rand() % 26; // a~zのランダムな文字
    }
    s->name[rand() % 8 + 1] = '\0'; //終端文字
    data[i] = s;
  }
  BubbleSortStudentP(n, data); //ソート
  for (int i = 0; i < n; i++) {
    PrintStudentP(data[i]); //表示
  }
  for (int i = 0; i < n; i++) {
    free(data[i]); //←メモリ解放
  }
  return 0;
}