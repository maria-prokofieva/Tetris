#include <stdio.h>

#define N 4

void printMatrix(int mat[N][N]) {
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void rotate90(int src[N][N], int dst[N][N]) {
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            dst[j][N - 1 - i] = src[i][j];
        }
    }
}

int main() {

    int mat[N][N] = {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    int temp[N][N];

    printf("0°:\n");
    printMatrix(mat);

    // 90°
    rotate90(mat, temp);
    printf("90°:\n");
    printMatrix(temp);

    // 180°
    rotate90(temp, mat);
    printf("180°:\n");
    printMatrix(mat);

    // 270°
    rotate90(mat, temp);
    printf("270°:\n");
    printMatrix(temp);

    return 0;
}