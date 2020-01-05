#include <stdio.h>
#include <stdlib.h>
#define ALLOC(type) alloc(sizeof(type), 1) //型付動的メモリ確保(単体)
#define ALLOCN(type, n) alloc(sizeof(type), n) //型付動的メモリ確保(配列)

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

void *calloc(size_t n, size_t size); // sizeバイトのものをn個分確保

typedef struct {
  double *Data; //データを格納する配列
  int Size;     //最大格納数
  int Count;    //現在の格納数
} Stack;

Stack *CreateStack(int size) {
  Stack *s = ALLOC(Stack);        // Stackのメモリを確保
  s->Data = ALLOCN(double, size); //データ配列のメモリを確保
  s->Size = size;                 //最大格納数
  s->Count = 0;                   //初期格納数
  return s;
}

void DisposeStack(Stack *s) {
  free(s->Data); //データ配列を解放
  free(s);       // Stackを解放
}

void PushStack(Stack *s, double x) {
  if (s->Count == s->Size)
    error("stack overflow"); //スタックが満杯
  s->Data[s->Count] = x;     //空き領域の先頭位置に格納
  s->Count++;
}

double PopStack(Stack *s) {
  if (s->Count == 0)
    error("stack underflow"); //スタックが空
  s->Count--;                 //格納数を1減少
  return s->Data[s->Count];   //最新データを返す
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