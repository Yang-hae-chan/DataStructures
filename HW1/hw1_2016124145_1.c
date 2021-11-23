#include <stdio.h>
#include <stdlib.h>

void transpose(int a[], int b[], int row, int column) //1차원 배열 주소와 행, 열 정보를 인자로 받아 전치
{
    int i, j;
    int k = 0;
    for (i = 0;i < column;i++) 
    {
        for (j = 0;j < row;j++)
        {
            b[row * i + j] = a[j * column + i];
            //b에 a행렬을 전치해서 저장
        }
    }
}
int main()
{
    int i, j, k = 0;
    int row, column;//row=a행렬 열, b 행렬 행 column=a행렬 행, b 행렬 열
    int* a;
    int* b;
    printf("Input the size of matrix: ");
    scanf_s("%d %d", &row, &column);
    a = (int*)malloc(sizeof(int) * row * column);//1차원 배열을 입력받기 위해 메모리 동적할당
    b = (int*)malloc(sizeof(int) * row * column);//a행렬을 전치해서 저장하기 위한 배열
    printf("Input elements of the %d x %d matrix: ", row, column);//행 열 입력(a)
    for (i = 0;i < row * column;i++)//1차원 배열로 가정해 입력한다
    {
        scanf_s("%d", &a[i]);
    }
    transpose(a, b, row, column);//a행렬을 전치해서 b행렬에 저장
    int** arr = (int**)malloc(sizeof(int*) * column);//b행렬을 2차원 행렬로 만들기 위해 세로방향으로 메모리 동적할당 
    for (i = 0;i < column;i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * row);//가로방향으로 메모리 동적할당
        for (j = 0;j < row;j++)
        {
            arr[i][j] = b[k];//b행렬을 2차원 행렬로 변환
            k++;
        }
    }
    for (i = 0;i < column;i++)//2차원 행렬 출력
    {
        for (j = 0;j < row;j++)
        {
            printf("% d ", arr[i][j]);
        }
        printf("\n");
    }

    for (i = 0;i < column;i++)
    {
        free(arr[i]);//가로방향 메모리 해제
    }
    free(arr);//세로방향 메모리 해제
    free(a);//a 행렬 메모리 해제
    free(b);//b 행렬 메모리 해제
}