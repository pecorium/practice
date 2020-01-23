#include <stdio.h>
#include <stdlib.h>

void error(const char *message) { //エラーメッセージを表示して強制終了
  fprintf(stdout, "\e[33m%s\e[39m\n", message); //黄色で表示
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
} Stack;

Stack *CreateStack(int size) {
  Stack *s = ALLOC(Stack);
  s->Data = ALLOCN(double, size);
  s->Size = size;
  s->Count = 0;
  return s;
}

void DisposeStack(Stack *s) {
  free(s->Data);
  free(s);
}

void PushStack(Stack *s, double x) {
  if (s->Count == s->Size)
    error("stack overflow");
  s->Data[s->Count] = x;
  s->Count++;
}

double PopStack(Stack *s) {
  if (s->Count == 0)
    error("stack underflow");
  s->Count--;
  return s->Data[s->Count];
}

void PrintStack(Stack *s) { //スタックに格納されているデータ一覧を表示
  printf("stack: ");
  for (int i = 0; i < s->Size; i++) {
    if (i < s->Count)
      printf("%02.0f, ", s->Data[i]);
    else
      printf("--, ");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    error("specify random seed"); //コマンドライン引数エラー
  srand(atoi(argv[1]));      //コマンドライン引数で乱数初期化
  Stack *s = CreateStack(4); //最大格納数4でスタックを作成
  for (int i = 0; i < 12; i++) {
    if (i < 2 || rand() % 2 == 0) { //最初の2回はpush,後は確率半々
      double x = rand() % 100;
      printf("push %02.0f ", x);
      PushStack(s, x);
    } else {
      printf("pop ");
      double x = PopStack(s);
      printf("%02.0f ", x);
    }
    PrintStack(s); //スタックの中身表示
  }
  DisposeStack(s); //最後にスタックを廃棄
  return 0;
}
