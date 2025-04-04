#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 100000  // ソート3を試す場合は10程度に変更推奨

// **関数プロトタイプ宣言**
void shuffleArray(int arr[], int n);
bool isSorted(int arr[], int n);
void sort1(int arr[], int n);
void sort2(int arr[], int low, int high);
void sort3(int arr[], int n);

// **ソート関数 (ここで選択)**
void sort(int arr[], int n) {
    // *** 使用するソート手法を選択 ***
    sort1(arr, n);
    // sort2(arr, 0, n - 1);
    // sort3(arr, n);
}

void sort1(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort2(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1, temp;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        
        int p = i + 1;
        sort2(arr, low, p - 1);
        sort2(arr, p + 1, high);
    }
}

void sort3(int arr[], int n) {
    int attempts = 0;
    while (!isSorted(arr, n)) {
        shuffleArray(arr, n);
        attempts++;
        if (attempts % 100000 == 0) {
            printf("Attempt %d... still sorting...\n", attempts);
        }
    }
    printf("Sorted after %d attempts!\n", attempts);
}


// **ソートされているか確認する関数**
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// **配列をシャッフルする関数**
void shuffleArray(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// **最初の5個と最後の5個を表示する関数**
void printArray(int arr[], int n) {
    int displayCount = 5;
    for (int i = 0; i < displayCount && i < n; i++) {
        printf("%d ", arr[i]);
    }
    if (n > 2 * displayCount) {
        printf("... ");
    }
    for (int i = n - displayCount; i < n; i++) {
        if (i >= displayCount) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[SIZE];

    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    srand(time(NULL));
    shuffleArray(arr, SIZE);

    printf("before:\n");
    printArray(arr, SIZE);

    clock_t start = clock();
    sort(arr, SIZE);
    clock_t end = clock();

    printf("\nafter:\n");
    printArray(arr, SIZE);

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nSorting took %f seconds.\n", time_taken);

    return 0;
}
