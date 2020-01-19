    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    void PrintData(int n, double data[n], int L, int R) {
    return;
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

    double Measure(void (*sort)(int, double[])) { //sort関数の時間を計測
    srand(1127);
    int n = 30000;
    double data[n];
    for (int i = 0; i < n; i++) {
    data[i] = rand() % 100; //0~99の整数乱数
    }
    clock_t c0 = clock(); //計測開始
    sort(n, data); //ソート関数呼び出し
    clock_t c1 = clock(); //計測終了
    return (c1 - c0) / (double)CLOCKS_PER_SEC; //経過時間を計算
    }

    int main(void) {
    printf("bubble sort: %.2f秒\n", Measure(BubbleSort));
    printf("quick sort: %.2f秒\n", Measure(QuickSort));
    return 0;
    }
