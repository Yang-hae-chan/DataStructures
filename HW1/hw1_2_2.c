#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX 1000000

typedef struct _node {
    int key;
    struct _node* next;
} node;
node* head, * tail;
void init_stack(void) {
    head = (node*)malloc(sizeof(node));
    tail = (node*)malloc(sizeof(node));
    head->next = tail;
    tail->next = tail;
}
int push(int k) {
    node* t;
    if ((t = (node*)malloc(sizeof(node))) == NULL) {
        printf("\n Out of memory...");
        return -1;
    }
    t->key = k; t->next = head->next; head->next = t;
    return k;
}
int pop(void) {
    node* t;
    int i;
    if (head->next == tail) /* if empty */ {
        printf("\n Stack underflow.");
        return -1;
    }
    t = head->next; i = t->key;
    head->next = t->next; free(t);
    return i;
}
void clear_stack(void) {
    node* t, * s;
    t = head->next;
    while (t != tail) {
        s = t; t = t->next;
        free(s);
    }
    head->next = tail;
}



int push_or_pop(int pushnum, int popnum, int max)
{
    // max 정도 쌓일 때까지는 push 가 주로 나옴.
    // 전에 push 였으면 push 가 가능성이 높고 pop 이었으면 pop 이 가능성이 높음.
    static double cont = 1.0;
    int j = rand();
    if (j % 10 + 1 > ((pushnum - popnum) * cont / max) * 10)
    {
        cont = 0.2;
        return 1;
    }
    else
    {
        cont = 5.0;
        return 0;
    }
}

int main()
{
    int i = 0;
    clock_t st1, st2, end1, end2;
    float t1, t2;
    int popNum = 0;
    int pushNum = 0;
    int v;
    st1 = clock();
    init_stack();
    while (i++ < MAX * 40)
    { /*100 만번씩 40 회 수행 */
        v = rand();
        if (push_or_pop(pushNum, popNum, MAX))
        {
            push(v);
            pushNum++;
        }
        else
        {
            pop();
            popNum++;
        }
        if (i % MAX == 0) printf("%d ", pushNum - popNum);
    }
    printf("\npush:%d, pop:%d\n", pushNum, popNum);
    end1 = clock();
}