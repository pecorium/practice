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
  int Index;
} Queue;

Queue *CreateQueue(int size) {
  Queue *q = ALLOC(Queue);
  q->Data = ALLOCN(double, size);
  q->Size = size;
  q->Count = 0;
  q->Index = 0;
  return q;
}

void DisposeQueue(Queue *q) {
  free(q->Data);
  free(q);
}

void Enqueue(Queue *q, double x) {
  if (q->Count == q->Size)
    error("queue overflow");
  int f = q->Index + q->Count;
  if (f >= q->Size) {
    f -= q->Size;
  }
  q->Data[f] = x;
  q->Count++;
}

double Dequeue(Queue *q) {
  if (q->Count == 0)
    error("queue underflow");
  q->Count--;
  int index = q->Index;
  if (q->Index == q->Size - 1) {
    q->Index -= q->Size;
  }
  q->Index++;
  return q->Data[index];
}

void PrintQueue(Queue *q) { //キューに格納されているデータ一覧を表示
  printf("queue: ");
  int f0 = q->Index + q->Count; //空き領域の先頭(巡回していない)
  int f1 = f0 - q->Size;        //空き領域の先頭(巡回している)
  for (int i = 0; i < q->Size; i++) {
    if ((q->Index <= i && i < f0) || i < f1)
      printf("%02.0f, ", q->Data[i]);
    else
      printf("--, ");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    error("specify random seed"); //コマンドライン引数エラー
  srand(atoi(argv[1]));      //コマンドライン引数で乱数初期化
  Queue *q = CreateQueue(4); //最大格納数4でキューを作成
  for (int i = 0; i < 12; i++) {
    if (i < 2 || rand() % 2 == 0) { //最初の2回はenqueue,後は確率半々
      double x = rand() % 100;
      printf("enqueue %02.0f ", x);
      Enqueue(q, x);
    } else {
      printf("dequeue ");
      double x = Dequeue(q);
      printf("%02.0f ", x);
    }
    PrintQueue(q); //キューの中身表示
  }
  DisposeQueue(q); //最後にキューを廃棄
  return 0;
}