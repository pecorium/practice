#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  char name[1000];
  double avg;
} Student;

void PrintStudent(Student *s) { // Student構造体のメンバー変数を表示する
  printf("%04d %-8s %4.1f\n", s->id, s->name, s->avg);
}

void swapStudent(Student **x, Student **y) {
  Student *z = *x;
  *x = *y;
  *y = z;
}

void BubbleSortStudent(int n, Student *data[n]) {
  for (int i = n; i > 1; i--) {
    for (int j = 0; j < i - 1; j++) {
      if (data[j]->avg < data[j + 1]->avg)
        swapStudent(&data[j], &data[j + 1]);
    }
  }
}

int main(void) {
  srand(1204);
  int n = 10;
  Student *data[n]; //構造体の配列
  for (int i = 0; i < n; i++) {
    Student *s = malloc(sizeof(Student));
    s->id = i;             //学籍番号
    s->avg = rand() % 100; //平均点
    for (int j = 0; j < 8; j++) {
      s->name[j] = 'a' + rand() % 26; // a~zのランダムな文字
    }
    s->name[rand() % 8 + 1] = '\0'; //終端文字
    data[i] = s;
  }
  BubbleSortStudent(n, data); //ソート
  for (int i = 0; i < n; i++) {
    PrintStudent(data[i]); //表示
  }
  return 0;
}