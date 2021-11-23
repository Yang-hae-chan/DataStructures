
#include <stdlib.h>
#include <stdio.h>
#define MAX 1000000

typedef struct _node* nodeptr;
typedef struct _node {
    int value[10];
    nodeptr next;
} node;

typedef struct {
    int num;
    nodeptr head;
} stack;

int pop(stack* stk)
{
    node* n;
    n = stk->head;
    int i;
    if ((stk->num % 10 == 0) && (stk->num != 0))
    {
        stk->head = n->next;
        stk->num--;
        free(n);
        return stk->head->value[9];
    }
    else if (stk->num == 0)
    {
        free(n);
        free(stk);
    }
    else
    {
        i = stk->num % 10;
        stk->num--;
        return n->value[i-1];
    }
}

void push(stack* stk, int v) {
    if (stk->num % 10 == 0) {
        node* n = (node*)malloc(sizeof(node));
        n->value[0] = v;
        stk->num++;
        n->next = stk->head;
        stk->head = n;
    }
    else {
        int i = stk->num % 10;
        stk->head->value[i] = v;
        stk->num++;
    }
}

stack* init_stack() {
    stack* s = malloc(sizeof(stack));
    s->num = 0;
    s->head = NULL;
    return s;
}

printstack(stack* s) {
    node* n = s->head;
    int num = s->num;
    while (num > 0) {
        printf("%d ", n->value[(num - 1) % 10]);
        num--;
        if (num % 10 == 0) n = n->next;
    }
    printf("\n");
}

int main() {
    stack* s = init_stack(); //stack s노드의 num에 0이 들어가면서 노드 생성
    push(s, 1); // 새로운 노드를 만들고 노드의 배열 0번째 index에 1넣어주고 s노드의 num은 1증가한다. stack s의 head에 새로운 노드를 넣어준다.
    push(s, 2); //위에서 생성된 새로운 노드의 (s의 head가 가리키는 노드)배열 1번째 index에 2를 넣어주고 s노드의 num은 1증가한다. 
    push(s, 3); //s의 head가 가리키는 노드의 배열 2번째 index에 3를 넣어주고 s노드의 num은 1증가한다. 
    push(s, 4); //s의 head가 가리키는 노드의 배열 3번째 index에 4를 넣어주고 s노드의 num은 1증가한다. 
    push(s, 5); //s의 head가 가리키는 노드의 배열 4번째 index에 5를 넣어주고 s노드의 num은 1증가한다. 
    push(s, 6);
    push(s, 7);
    push(s, 8);
    push(s, 9);
    push(s, 10);
    //s의 head가 가리키는 노드의 배열이 꽉 찼음으로 새로운 노드 생성 
    push(s, 11);//새로운 노드를 만들고 그 노드의 배열 0번째 index에 11넣어주고 새로운 s노드의 num은 1증가한다. stack stk(s)와 처음에 생성된 노드 사이에 새로운 노드를 넣어준다.
    printf(" %d ", pop(s));
    printf(" %d ", pop(s));
    printf(" %d ", pop(s));
    printf(" %d ", pop(s));
    printf(" %d ", pop(s));
    printf(" %d ", pop(s));
    printstack(s);
}