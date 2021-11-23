#include <stdio.h>

int price[] = {0,1,5,8,9,10,17,17,20,22,26};
int maxp(int m) {
   int i,p;
   int max; //최대 가격
   int maxCut = 10;

   if (m<=0)
      return 0;
   if (m<=10)
      maxCut = m;

   max = 0;
   for (i=1; i<=maxCut; i++)
   // i길이로 자를 때 최대 가격 계산하고, 최대가격 계산 시 업데이트 
   {  
       if(maxp(m-i)+price[i]>max)
       //maxp를 1로 잘랐을때부터 m-1로 잘랐을때까지 재귀적으로 호출
       {
           max=maxp(m-i)+price[i];
       }
   }
   return max;//max리턴
}

int main() {
   int l;
   printf("Length of stick? ");
   scanf("%d", &l);
   int p = maxp(l);
   printf("Maximum price:%d\n",p);
}