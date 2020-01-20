#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

void error(const char *message) { //エラーメッセージを表示して強制終了
  fprintf(stdout, "\x1b[33m%s\x1b[39m\n", message); //黄色で表示
  exit(EXIT_FAILURE);
}

void *alloc(size_t size, size_t n) { //エラーチェック付動的メモリ確保
  void *p = calloc(n, size); //ゼロクリアした動的メモリ確保
  if (p == NULL)
    error("cannot allocate memory");
  return p;
}

#define ALLOC(type) alloc(sizeof(type), 1) //型付動的メモリ確保(単体)
#define ALLOCN(type, n) alloc(sizeof(type), n) //型付動的メモリ確保(配列)

typedef struct {
  double *Data;
  int Size;
  int Count;
} List;

List *CreateList(void) {
  List *l = ALLOC(List);
  l->Size = 1;
  l->Count = 0;
  l->Data = ALLOCN(double, l->Size);
  return l;
}

void DisposeList(List *l) {
  free(l->Data);
  free(l);
}

void InsertList(List *l, int index, double x) {
  if (index < 0 || index > l->Count)
    error("index is out of range");

  if (l->Count < l->Size) {
    for (int i = l->Count - 1; i >= index; i--) {
      l->Data[i + 1] = l->Data[i];
    }
    l->Data[index] = x;
    l->Count++;
  } else {
    double *old = l->Data;
    l->Size *= 2;
    l->Data = ALLOCN(double, l->Size);
    for (int i = 0; i < index; i++) {
      l->Data[i] = old[i];
    }
    for (int i = index; i < l->Count; i++) {
      l->Data[i + 1] = old[i];
    }
    l->Data[index] = x;
    l->Count++;
    free(old);
  }
}

void AddList(List *l, double x) { InsertList(l, l->Count, x); }

void RemoveList(List *l, int index) {
  if (index < 0 || index >= l->Count)
    error("index is out of range");
  for (int i = index + 1; i < l->Count; i++) {
    l->Data[i - 1] = l->Data[i];
  }
  l->Count--;
}

void PrintList(List *l) { //アレイリストのデータ一覧を表示
  printf("list: ");
  for (int i = 0; i < l->Size; i++) {
    if (i < l->Count)
      printf("%02.0f, ", l->Data[i]);
    else
      printf("--, ");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    error("specify random seed"); //コマンドライン引数エラー
  srand(atoi(argv[1]));
  List *l = CreateList(); //アレイリストを作成
  for (int i = 0; i < 12; i++) {
    double x = rand() % 100;         //新データ
    int a = rand() % (l->Count + 2); //位置
    if (i < 2 || rand() % 2 == 0) {
      printf("add %02.0f [--]: ", x);
      AddList(l, x);
    } else if (rand() % 2 == 0) {
      printf("ins %02.0f [%02d]: ", x, a);
      InsertList(l, a, x);
    } else {
      printf("rmv -- [%02d]: ", a);
      RemoveList(l, a);
    }
    PrintList(l);
  }
  DisposeList(l); //アレイリストを廃棄
  return 0;
}