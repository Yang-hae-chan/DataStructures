#include <stdio.h>
int maxpp[100] = { 0};//함수 호출을 줄이기 위한 저장공간 초기화
int price[] = { 0,1,5,8,9,10,17,17,20,22,26 };
int maxp(int m) {
    int i, p;
    int max; //최대 가격
    int maxCut = 10;
    
    if (m <= 0)
        return 0;
    max = 0;
    if (maxpp[m] != 0)//maxpp[m]값이 이미 있다면 그것을 return
        return maxpp[m];
    if (m <= 10)
        maxCut = m;

    for (i = 1; i <= maxCut; i++)
        // i길이로 자를 때 최대 가격 계산하고, 최대가격 계산 시 업데이트
    {
        p = maxp(m - i) + price[i];//i길이로 자르고 난 후의 maxp값을 호출
        if (p > max)//p가 max보다 크면
        {
            max = p;
        }
    }
    maxpp[m] = max;//maxpp[m]에 max값 저장
    return maxpp[m];
}

int main() {
    int l;
    printf("Length of stick? ");
    scanf_s("%d", &l);
    int p = maxp(l);
    printf("Maximum price:%d\n", p);
}