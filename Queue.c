#include <stdio.h>
#include <stdlib.h>
#define EMPTY 0

//Queue
//양끝이 뚫린 원통 안에 데이터가 저장되는 구조
//선입선출의 구조(First In First Out)
//맨 앞의 데이터: Front(고정), 맨 뒤의 데이터: Rear(바뀜)
//Front
//  ↓
//----------------------------------------------
//   10                20                30
//data link    →    data link    →    data link
//----------------------------------------------
//                                       ↑
//                                      Rear
//입력: Enque, 출력: Deque


typedef struct node{
    int data;
    struct node* link;
}Queue;

Queue* Getnode(){
    Queue* tmp;
    tmp = (Queue*) malloc(sizeof(Queue));
    tmp->link = EMPTY;
    return tmp;
}

void Enqueue(Queue** front, Queue** rear, int data){//여기서 front, rear는 main의 front, rear의 주소를 받는 인자
    if (*front == EMPTY){
        *front = Getnode();
        *rear = *front;
    }
    else{
        (*rear)->link = Getnode();
        (*rear) = (*rear)->link;
    }
    (*rear)->data = data;
}

void Dequeue(Queue** front){
    if (*front != EMPTY){
        Queue* tmp;//동적 해제를 하기 위해서는 그 주소를 받아줄 수 있는 임시 변수가 필요
        tmp = *front;
        printf("%d\n", (*front)->data);
        *front = (*front)->link;
        free(tmp);
    }
    else{
        printf("The queue is currently empty!\n");
    }
}


int main(){
    Queue* front = EMPTY;
    Queue* rear = EMPTY;

    Enqueue(&front, &rear, 10);
    Enqueue(&front, &rear, 20);
    Enqueue(&front, &rear, 30);

    Dequeue(&front);
    Dequeue(&front);
    Dequeue(&front);
    Dequeue(&front);



    return 0;
}