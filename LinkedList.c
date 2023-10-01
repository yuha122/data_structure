//------LinkedList------
//각 노드가 데이터와 포이터를 가지고 한 줄로 연결되어 있는 방식으로 데이터를 저장하는 구조
//양옆이 뚫려있는 원통형 구조를 생각하면 됨
//입력: Insert, 출려기 Output, 데이터 찾기: Search, 지우기: Delete, 추가: Add, 정리(오름 or 내림): Sort, 맨 앞: Head
//Head는 NULL에서 처음 입력한 데이터의 주소를 갖게끔 바뀐 후 더 이상 바뀌지 않음

#include <stdio.h>
#include <stdlib.h>
#define EMPTY 0

typedef struct node{
    int data;
    struct node* link;
}LinkedList;

LinkedList* Getnode(){
    LinkedList* tmp;
    tmp = (LinkedList*) malloc(sizeof(LinkedList));
    tmp->link = EMPTY;
    return tmp;
}

void Insert(LinkedList** Head, int data){
    if (*Head == EMPTY){
        *Head = Getnode();
        (*Head)->data = data;
        return;
    }
    else{
        Insert(&(*Head)->link, data);
    }
}

//동적 해제 없이 그냥 출력하는 것
void Output(LinkedList** Head){
    if (*Head){
        printf("%d\n", (*Head)->data);
        Output(&(*Head)->link);
    }
}

void Search(LinkedList** Head, int data){
    if (*Head == EMPTY){
        printf("%d is not found\n", data);
    }
    else if ((*Head)->data == data){
        printf("%d is found\n", data);
    }
    else{
        Search(&(*Head)->link, data);
    }
}

void Delete(LinkedList** Head, int data){
    if (*Head == EMPTY){
        printf("%d is not found\n", data);
    }
    else if ((*Head)->data == data){
        LinkedList* tmp;
        tmp = *Head; 
        *Head = (*Head)->link;
        free(tmp);
        printf("%d is deleted\n", data);

    }
    else{
        Delete(&(*Head)->link, data);
    }
}

void Add(LinkedList** Head, int data1, int data2){
    if (*Head == EMPTY){
        printf("%d is not found\n", data1);
    }
    else if ((*Head)->data == data1){
        LinkedList* tmp = EMPTY;
        Insert(&tmp, data2);
        tmp->link = (*Head)->link;
        (*Head)->link = tmp;
        printf("%d is added\n", data2);
    }
    else{
        Add(&(*Head)->link, data1, data2);
    }
}

void Sort(LinkedList** Head){
    if (*Head){
        LinkedList* tmp;
        tmp = (*Head)->link;

        while (tmp){
            if ((*Head)->data < tmp->data){
                int data;
                data = (*Head)->data;
                (*Head)->data = tmp->data;
                tmp->data = data;
            }
            tmp = tmp->link;
        }
        Sort(&(*Head)->link);
    }
}
int main(){
    LinkedList* Head = EMPTY;

    Insert(&Head, 10);
    Insert(&Head, 20);
    Insert(&Head, 30);
    Insert(&Head, 50);

    Add(&Head, 30, 40);
    Delete(&Head, 20);
    Sort(&Head);
    Output(&Head);
}