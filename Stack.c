#include <stdio.h>
#include <stdlib.h>
#define EMPTY 0


//------Stack------
//밑이 꽉 막힌 상자에 아레에서부터 데이터를 쌓는 구조
//후입선출 구조(Last In First Out)
//입력: Push, 출력: Pop, 맨 위에 있는 자료: Top


typedef struct node{
    int data;
    struct node* link;
}Stack;

Stack* Getnode(){
    Stack* tmp;
    tmp = (Stack*) malloc(sizeof(Stack));
    tmp->link = EMPTY;
    return tmp;
}

void Push(Stack** top, int data){
    Stack* tmp;
    tmp = *top;
    *top = Getnode();
    (*top)->data = data;
    (*top)->link = tmp;
}

void Pop(Stack** top){
    if (*top == EMPTY){
        printf("Stack is currently empty!\n");

    }
    else{
        Stack* tmp;
        tmp = *top;
        printf("%d\n", (*top)->data);
        *top = (*top)->link;
        free(tmp);
    }
}

int main(){

    Stack* top = EMPTY;
    
    Push(&top, 10);
    Push(&top, 20);
    Push(&top, 30);

    Pop(&top);
    Pop(&top);
    Pop(&top);
    Pop(&top);
    
}