#define _CRT_SECURE_NO_WARNINGS
#define BASE(i)     ((char*)base + (i)*width)
#include<stdio.h>
#include<stdlib.h>

typedef int (*FCMP)(const void*, const void*);

typedef struct _people {
    char major[10];
    char name[15];
    double point;
}people;
int major_cmp(const void* a, const void* b) {
    if (((people*)a)->major == ((people*)b)->major) {//학과가 같으면
        return strcmp(((people*)a)->name, ((people*)b)->name);
        //이름으로 비교
    }
    return strcmp(((people*)a)->major, ((people*)b)->major);
}//구조체 데이터를 학과로 비교

int point_cmp(const void* a, const void* b) {
    return (((people*)b)->point - ((people*)a)->point);
}//구조체 데이터를 점수로 비교
int split(void* base, size_t nelem, size_t width, FCMP fcmp) {
    int i, j;
    void* v, * t;
    v = malloc(width);
    v = BASE(nelem - 1);//v = a[n-1]
    t = malloc(width);
    i = -1;
    j = nelem - 1;
    while (1) {
        while (fcmp(BASE(++i), v) < 0);//while (a[++i] < v)
        while (fcmp(BASE(--j), v) > 0 && j > i);//while (a[--j] > v && j > i)
        if (i >= j) break;
        memcpy(t, BASE(i), width);
        memcpy(BASE(i), BASE(j), width);
        memcpy(BASE(j), t, width);//t = a[i]; a[i] = a[ j]; a[j] = t
    }
    memcpy(t, BASE(i), width);
    memcpy(BASE(i), BASE(nelem - 1), width);
    memcpy(BASE(nelem - 1), t, width);//t = a[i]; a[i] = a[n-1]; a[n-1] = t
    return i;
    free(t);
    free(v);
}
void quick_sort(void* base, size_t nelem, size_t width, FCMP fcmp) {
    int i;
    if (nelem > 1) {
        i = split(base, nelem, width, fcmp);//i = split(a, n)
        quick_sort(base, i, width, fcmp);//quick_sort(a, i)
        quick_sort(BASE(i + 1), nelem - i - 1, width, fcmp);//quick_sort(a+i+1, n-i-1)
    }
}


int main() {
    people p[5];//구조체 변수 선언
    int i;
    FILE* fp = fopen("infile.txt", "r"); //구조체로 입력할 txt파일 fopen
    for (i = 0;i < 5;i++) {//해당 파일에 대해 구조체 배열에 각각 저장
        fscanf(fp, "%s %s %Lf\n", &p[i].major, &p[i].name, &p[i].point);
    }
    fclose(fp);
    FILE* fp1 = fopen("result.txt", "w");//정렬 후 저장할 파일
    fprintf(fp1, "-------------------------\n");
    quick_sort(p, 5, sizeof(people), major_cmp);//전공에 대해 퀵정렬
    for (i = 0;i < 5;i++) {//정렬한 구조체 배열을 파일에 써줌
        fprintf(fp1, "\n%s %s %.1Lf\n", p[i].major, p[i].name, p[i].point);
    }
    fprintf(fp1, "\n-------------------------\n");
    quick_sort(p, 5, sizeof(people), point_cmp);//점수에 대해 퀵정렬
    for (i = 0;i < 5;i++) {//정렬한 구조체 배열을 파일에 써줌
        fprintf(fp1, "\n%s %s %.1Lf\n", p[i].major, p[i].name, p[i].point);
    }
    fprintf(fp1, "\n-------------------------\n");
    fclose(fp1);
}

