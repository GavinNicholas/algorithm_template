#pragma GCC optimize("O3,no-stack-protector")

#include <bits/stdc++.h>

using namespace std;

//#define debug
//#define file_io

int GetIndex(int array[], int arrayIndex[], int arrayLength) {
    int cnt = 0;
    arrayIndex[cnt++] = 0;
    for (int i = 1; i < arrayLength; i++) if (array[i] < array[i - 1]) arrayIndex[cnt++] = i;
    return cnt;
}

inline void Merge(int src[], int dst[], int left, int mid, int right) {
    int i = left, j = mid + 1, p = left;
    while (i <= mid && j <= right) {
        if (src[i] <= src[j]) dst[p++] = src[i++];
        else dst[p++] = src[j++];
    }
    for (int k = i > mid ? j : i, loop = i > mid ? right : mid; k <= loop; k++) dst[p++] = src[k++];
}

void MergePass(int left[], int right[], int arrayIndex[], int roundNum, int arrayLength, int cnt) {
    int i = 0;
    while (i <= cnt - 2 * roundNum) {
        int r = i + 2 * roundNum < cnt ? arrayIndex[i + 2 * roundNum] : arrayLength;
        Merge(left, right, arrayIndex[i], arrayIndex[i + roundNum] - 1, r - 1);
        i = i + 2 * roundNum;
    }
    if (i + roundNum < cnt) {
        Merge(left, right, arrayIndex[i], arrayIndex[i + roundNum] - 1, arrayLength - 1);
    } else if (i < cnt) {
        for (int j = arrayIndex[i]; j <= arrayLength - 1; j++) right[j] = left[j];
    }
}

void MergeSort(int array[], int arrayIndex[], int arrayLength, int cnt) {
    int *array_copy = new int[arrayLength];
    int roundNum = 1;
    while (roundNum < cnt) {
        MergePass(array, array_copy, arrayIndex, roundNum, arrayLength, cnt);
        roundNum <<= 1;
        MergePass(array_copy, array, arrayIndex, roundNum, arrayLength, cnt);
        roundNum <<= 1;
    }
    delete[] array_copy;
}

int main() {
#ifdef file_io
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int array[] = {1, 5, 2, 3, 6, 0, 7, 4, 8};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    int *arrayIndex = new int[arrayLength];
    int cnt = GetIndex(array, arrayIndex, arrayLength);
    MergeSort(array, arrayIndex, arrayLength, cnt);
    for (int i = 0; i < arrayLength; i++) printf("%d%s", array[i], i < arrayLength - 1 ? " " : "\n");
    delete[] arrayIndex;

    return 0;
}