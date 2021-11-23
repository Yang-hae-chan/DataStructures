#include <stdio.h>
int is_operator(char c)
{
    return((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

int is_legal(char* s) {
    int f = 0;
    while (*s) {
        while (*s == ' ') s++;
        if (*s== '\0') break;
        if (is_operator(*s))//식 뒤에 공백 처리용
        {
            f--;
            if (f >= 0)
                return 0;
        }
        else
            f++;
        if (f > 1)
            break;
        s++;
    }
    return (f == 1);
}

int main()
{
    char a[100] = "1+2+3";
    char b[100] = "-*/123+22 ";
    char c[100] = "+++";
    char d[100] = "1";
    char e[100] = "12+3-";
    char f[100] = "12+3-";
    printf("%s=>%d\n", a, is_legal(a));
    printf("%s=>%d\n", b, is_legal(b));
    printf("%s=>%d\n", c, is_legal(c));
    printf("%s=>%d\n", d, is_legal(d));
    printf("%s=>%d\n", e, is_legal(e));
    printf("%s=>%d\n", f, is_legal(f));
}