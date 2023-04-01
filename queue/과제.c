#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 3

//고객 정보
typedef struct
{
    int id;
    int arrival_t;
    int service_t;
} element;


// 원형 큐
typedef struct
{
    element data[MAX_QUEUE_SIZE]; 
    int front, rear;
} QueueType;

//front, rear 초기화하는 함수
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

//비어있는지 확인하는 함수
int isQueueempty(QueueType* q)
{
    return (q->front == q->rear);
}
//가득 차 있는지 확인하는 함수
int isQueuefull(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//삽입 큐
void enqueue(QueueType* q, element item)
{
    if (isQueuefull(q))
    {
        printf("대기 인원이 너무 많습니다\n");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

//삭제 큐
element dequeue(QueueType* q)
{
    if (isQueueempty(q))
    {
        printf("공백상태입니다.\n");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}


int main(void)
{
    int minutes=0;
    int mode = 0;
    printf("몇 분 동안 시뮬레이션 하시겠습니까?");
    scanf("%d", &minutes);
    printf("직원 일의 강도는 어떻게 하시겠습니까? \n1부터 10의 숫자 중 하나를 입력해주세요. (1이 가장 강함, 10이 가장 약함): ");
    scanf("%d", &mode);
    int total_wait = 0; 
    int total_cus = 1;
    int a_service_t = 0,
        b_service_t = 0; 
    int a_service_cus, 
        b_service_cus; 
    bool a = true; 
    bool b = true; 
    QueueType q;
    init_queue(&q);
    srand(NULL); 
    for (int clock = 0; clock < minutes; clock++)
    {
        printf("\n===========================현재시각=%d분===========================\n", clock);
        printf("<현재> A직원 %d, B직원 %d (0: 부재 중, 1: 일하는 중)\n", a, b);
        if ((rand() % mode) < 3)
        {
            element customer;
            customer.id = total_cus++; 
            customer.arrival_t = clock;
            customer.service_t = rand() % 3 + 1; 
            enqueue(&q, customer);
            printf("손님 %d이 %d분에 들어옵니다. 크레페 주문 처리 시간=%d\n", customer.id, customer.arrival_t, customer.service_t);
        }
        if (a_service_t > 0) 
        {
            printf("손님 %d이 A직원 자리에서 대기 중 입니다.\n", a_service_cus);
            a_service_t--;

            if (a_service_t == 0)
            {
                printf("(A직원은 %d분부터 일합니다.)\n", clock + 1);
                a = true;
            }
        }
        else if (a) 
        {
            if (!isQueueempty(&q))
            {
                element customer = dequeue(&q);
                a_service_cus = customer.id;
                a_service_t = customer.service_t;

                printf("손님 %d이 %d분에 A직원 앞에서 크레페를 주문 중입니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_t);
                a = false;
                total_wait += clock - customer.arrival_t;
            }
        }
        if (b_service_t > 0) 
        {
            printf("손님 %d이 B직원 자리에서 대기 중 입니다.\n", b_service_cus);
            b_service_t--;

            if (b_service_t == 0)
            {
                printf("(B직원은 %d분부터 일합니다.)\n", clock + 1);
                b = true;
            }
        }
        else if (b) 
        {
            if (!isQueueempty(&q))
            {
                element customer = dequeue(&q);
                b_service_cus = customer.id;
                b_service_t= customer.service_t;
                printf("고객 %d이 %d분에 B직원 앞에서 크레페를 주문 중입니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_t);
                b = false;
                total_wait += clock - customer.arrival_t;
            }
        }
    }
    printf("전체 대기 시간 = %d분 \n", total_wait);
    return 0;
}