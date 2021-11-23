#include<stdio.h>
#include<stdlib.h>
#define MAX 256
int stack[MAX];
int top;
typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;//트리 노드를 위한 구조체 선언
node* head, * tail;
void init_stack(void) {
    top = -1;
}
void visit(node* t) {
    printf("%c", t->key);
}//visit시 해당 노드의 key출력
int push(int t) {
    if (top >= MAX - 1) {
        printf("\n Stack overflow.");
        return -1;
    }
    stack[++top] = t;
    return t;
}

int pop(void) {
    if (top < 0) {
        printf("\n Stack underflow.");
        return -1;
    }
    return stack[top--];
}

int is_operator(int k) {
    return (k == '+' || k == '-' || k == '*' || k == '/');
}
int precedence(int op) {
    if (op == '+') return 0;
    if (op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}// 과제에선 -에도 괄호를 쳐주기 때문에 우선순위 * = / > - > + 순서로 설정
void init_tree(void)
{
    head = (node*)malloc(sizeof(node));
    tail = (node*)malloc(sizeof(node));
    head->left = tail;
    head->right = tail;
    tail->left = tail;
    tail->right = tail;
}   //트리생성
node* make_parse_tree(char* p) {
    node* t;
    while (*p) {
        while (*p == ' ') p++;
        t = (node*)malloc(sizeof(node));
        t->key = *p;
        t->left = tail;
        t->right = tail;
        if (is_operator(*p)) {
            t->right = pop();
            t->left = pop();
        }
        push(t);
        p++;
    }
    return pop();
}//수식나무 생성

void brackets(node* t) {//괄호생성함수
    node* l = t;//괄호를 칠 연산노드의 왼쪽을 위한 변수
    node* r = t;//괄호를 칠 연산노드의 오른쪽을 위한 변수
    if (t->left != tail&&t->right!=tail) {
        brackets(t->left);//현재 노드의 왼쪽부분 수행
        if (is_operator(t->key) && is_operator(t->right->key) && precedence(t->right->key) < precedence(t->key)) {
            //오른쪽 child 노드의 연산이 현재 노드 보다 우선 순위가 낮으면
            l = r = t->right;//오른쪽 연산에 괄호가 필요하므로 l r 오른쪽으로 이동
            node* lb = (node*)malloc(sizeof(node));
            node* rb = (node*)malloc(sizeof(node));//(을 위한 lb, )을 위한 rb
            while (l->left != tail) {//tail전까지
                l = l->left;//l 이동
            }
            l->left = lb;
            lb->left = tail;
            lb->right = tail;
            lb->key = '(';//왼쪽 마지막에 ( 노드 만들어줌
            while (r->right != tail) {//tail 전까지
                r = r->right; //r 이동
            }
            r->right = rb;
            rb->left = tail;
            rb->right = tail;
            rb->key = ')';      //오른쪽 마지막에 ) 노드 생성

        }
        else if (is_operator(t->key) && is_operator(t->left->key) && precedence(t->left->key) <= precedence(t->key)) {
            //왼쪽 child 노드의 연산의 우선 순위가 현재 노드보다 높지 않으면
            l = r = t->left;    //왼쪽 연산에 괄호가 필요하므로 l r 왼쪽으로 이동
            node* lb = (node*)malloc(sizeof(node));
            node* rb = (node*)malloc(sizeof(node));
            while (l->left != tail) {//이하 동일
                l = l->left;
            }
            l->left = lb;
            lb->left = tail;
            lb->right = tail;
            lb->key = '(';
            while (r->right != tail) {
                r = r->right;
            }
            r->right = rb;
            rb->left = tail;
            rb->right = tail;
            rb->key = ')';
            free(lb);
            free(rb);
        }
        brackets(t->right); //오른쪽에 대해서도 똑같이 수행
    }
}
void inorder_traverse(node* t) {//중위 표기법 탐색
    if (t != tail) {
        inorder_traverse(t->left);
        visit(t);
        inorder_traverse(t->right);
    }
}
void main(void) {
    char post[256];
    init_stack();//스택생성
    init_tree();//트리생성

    printf("\n\nInput a postfix expression : ");
    gets(post);//후위표기법 입력
    if (*post == NULL) {
        printf("\n Program ends...");
        exit(0);
    }

    head->right = make_parse_tree(post);//수식나무를 헤드노드와 ㅗ연결
    brackets(head->right);              //수식나무에 괄호 생성
    printf("\nThe infix expression :  ");
    inorder_traverse(head->right);//수식나무 중위표기법 탐색
}
