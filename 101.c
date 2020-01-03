#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  char name[1000];
  double avg;
} Student;

void PrintStudent(Student s) {
  printf("%04d %-8s %4.1f\n", s.id, s.name, s.avg);
}

void swapStudent(Student *x, Student *y) {
  Student z = *x;
  *x = *y;
  *y = z;
}

void BubbleSortStudent(int n, Student data[n]) {
  for (int i = n; i > 1; i--) {
    for (int j = 0; j < i - 1; j++) {
      if (data[j].avg > data[j + 1].avg)
        swapStudent(&data[j], &data[j + 1]);
    }
  }
}

int main(void) {
  srand(1204);
  int n = 10;
  Student data[n];
  for (int i = 0; i < n; i++) {
    Student s;
    s.id = i;
    s.avg = rand() % 100;
    for (int j = 0; j < 8; j++) {
      s.name[j] = 'a' + rand() % 26;
    }
    s.name[rand() % 8 + 1] = '\0';
    data[i] = s;
  }
  BubbleSortStudent(n, data);
  for (int i = 0; i < n; i++) {
    PrintStudent(data[i]);
  }
  return 0;
}