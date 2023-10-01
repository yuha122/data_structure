//------C언어에서 동적 할당------
//기존의 변수 선언은 정적 할당에 해당함. 이는 여러 제약이 존재하기에 동적 할당으로 원할 때 메모리 공간을 할당하고 해제
//메모리 공간을 할당 받을 때는 malloc()함수를 사용
//malloc()함수를 사용하기 위해서는 #include <stdlib.h> 해야 함
//원형: 주소를 저장할 변수 = (왼쪽 저장할 공간의 자료형) malloc(필요한 메모리 공간 or sizeof(자료형));
//malloc()함수의 반환형은 void pointer이기 때문에 주소를 저장할 공간의 자료형에 맞춰 강제 형변환을 해줘야 함
//동적 해제: free(저장 공간의 주소);

#include <stdio.h>
#include <stdlib.h>

int main(){

    /*malloc() 함수 사용 (공간 1개)
    int* ptr;
    ptr = (int*) malloc(sizeof(int));
    *ptr = 4;
    printf("동적 할당된 공간에 저장된 값: %d\n", *ptr);
    free(ptr);*/

    /*malloc() 함수 사용 (공간 2개)
    int* ptr;
    ptr = (int*) malloc(sizeof(int) * 2);
    ptr[0] = 10;
    ptr[1] = 20;
    printf("동적 할당된 공간에 저장된 값: %d %d\n", ptr[0], ptr[1]);
    free(ptr);*/

    /*동적 할당을 이용한 문제1
    int length;
    char* ptr;

    printf("영단어 길이 입력: ");
    scanf("%d", &length);

    ptr = (char*) malloc(sizeof(char) * (length+1));

    printf("영단어 입력: ");
    scanf("%s", ptr);
    printf("영단어 출력: ");
    for (int i = length; i >= 0; i--){
        printf("%c", ptr[i]);
    }
    printf("\n");

    free(ptr);*/




    return 0;
}