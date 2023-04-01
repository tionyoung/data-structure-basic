#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 3

//�� ����
typedef struct
{
    int id;
    int arrival_t;
    int service_t;
} element;


// ���� ť
typedef struct
{
    element data[MAX_QUEUE_SIZE]; 
    int front, rear;
} QueueType;

//front, rear �ʱ�ȭ�ϴ� �Լ�
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

//����ִ��� Ȯ���ϴ� �Լ�
int isQueueempty(QueueType* q)
{
    return (q->front == q->rear);
}
//���� �� �ִ��� Ȯ���ϴ� �Լ�
int isQueuefull(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//���� ť
void enqueue(QueueType* q, element item)
{
    if (isQueuefull(q))
    {
        printf("��� �ο��� �ʹ� �����ϴ�\n");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

//���� ť
element dequeue(QueueType* q)
{
    if (isQueueempty(q))
    {
        printf("��������Դϴ�.\n");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}


int main(void)
{
    int minutes=0;
    int mode = 0;
    printf("�� �� ���� �ùķ��̼� �Ͻðڽ��ϱ�?");
    scanf("%d", &minutes);
    printf("���� ���� ������ ��� �Ͻðڽ��ϱ�? \n1���� 10�� ���� �� �ϳ��� �Է����ּ���. (1�� ���� ����, 10�� ���� ����): ");
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
        printf("\n===========================����ð�=%d��===========================\n", clock);
        printf("<����> A���� %d, B���� %d (0: ���� ��, 1: ���ϴ� ��)\n", a, b);
        if ((rand() % mode) < 3)
        {
            element customer;
            customer.id = total_cus++; 
            customer.arrival_t = clock;
            customer.service_t = rand() % 3 + 1; 
            enqueue(&q, customer);
            printf("�մ� %d�� %d�п� ���ɴϴ�. ũ���� �ֹ� ó�� �ð�=%d\n", customer.id, customer.arrival_t, customer.service_t);
        }
        if (a_service_t > 0) 
        {
            printf("�մ� %d�� A���� �ڸ����� ��� �� �Դϴ�.\n", a_service_cus);
            a_service_t--;

            if (a_service_t == 0)
            {
                printf("(A������ %d�к��� ���մϴ�.)\n", clock + 1);
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

                printf("�մ� %d�� %d�п� A���� �տ��� ũ���並 �ֹ� ���Դϴ�. ���ð��� %d���̾����ϴ�.\n", customer.id, clock, clock - customer.arrival_t);
                a = false;
                total_wait += clock - customer.arrival_t;
            }
        }
        if (b_service_t > 0) 
        {
            printf("�մ� %d�� B���� �ڸ����� ��� �� �Դϴ�.\n", b_service_cus);
            b_service_t--;

            if (b_service_t == 0)
            {
                printf("(B������ %d�к��� ���մϴ�.)\n", clock + 1);
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
                printf("�� %d�� %d�п� B���� �տ��� ũ���並 �ֹ� ���Դϴ�. ���ð��� %d���̾����ϴ�.\n", customer.id, clock, clock - customer.arrival_t);
                b = false;
                total_wait += clock - customer.arrival_t;
            }
        }
    }
    printf("��ü ��� �ð� = %d�� \n", total_wait);
    return 0;
}