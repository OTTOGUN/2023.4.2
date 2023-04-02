#include<stdio.h>
#include <synchapi.h>
#include<string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100
typedef int Status;
typedef char SElemType;
typedef int ElemType;

typedef struct{
    SElemType *base;     //������ջ��ָ��
    SElemType *top;      //������ջ��ָ��
    int stacksize;       //ջ���õ��������
}SqStack;

//������1.ջ�ĳ�ʼ��(InitStack)
Status InitStack(SqStack* S){
    //��Ϊ˳��ջ����һ���������MAXSIZE������
    S -> base = (SqStack*)malloc(sizeof(SElemType) * MAXSIZE);
    //���ж��Ƿ����ɹ�
    if(!S->base)
        strerror(errno);
    //��top��ʼΪbase����ջ
    S -> top = S -> base;
    //��stacksize��Ϊ�������MAXSIZE
    S -> stacksize = MAXSIZE;
    return OK;
}

//������2.��ջ(Push)
Status Push(SqStack* S,SElemType e){
    //���ж��Ƿ�ջ������������ERROR
    if(S -> top - S -> base == S -> stacksize){
        printf("ջ��");
        return ERROR;
    }
    //�ڽ���Ԫ��ѹ��ջ����ջ��ָ���1
    *(S -> top++) = e;
    return OK;
}

//������3.��ջ(Pop)
char Pop(SqStack* S,SElemType* e){
    //���ж�ջ���Ƿ�Ϊ�գ������򷵻�ERROR
    if(S -> top == S -> base){
        printf("ջ��");
        return ERROR;
    }
    //��ջ��ָ���1��ջ��Ԫ�س�ջ
    *e = *(--(S -> top));
    return e;
}

//������4.ȡջ��Ԫ��(GetTop)
Status GetTop(SqStack* S){
    if(S -> top == S -> base){
        printf("ջ��");
        return ERROR;
    }
    return *(S -> top--);
}

//������ջ����������
Status IsEmpty(SqStack* S){
    if(S -> base == S -> top){
        printf("��ջ");
        return TRUE;
    }
    return ERROR;
}

Status IsFull(SqStack* S){
    if(S -> top - S -> base == S -> stacksize){
        printf("ջ��");
        return OK;
    }
    return ERROR;
}

//���������Գ���->>>(�ɹ�)
/*int main(){
    SqStack S;
    InitStack(&S);
    Push(&S,'A');
    Push(&S,'B');
    Push(&S,'C');
    Push(&S,'D');
    Push(&S,'E');
    while(!IsEmpty(&S)){
        SElemType e = 0;
        Pop(&S,&e);
        printf("%c ",e);
    }
}*/

//����������������������������������������ջ�ı�ʾ��ʵ�֡���������������������������������������

//������0.��ջ�Ĵ洢�ṹ
typedef struct StackNode{
    ElemType data;
    struct StackNode *next;
}StackNode,*LinkStack;

//������1.��ʼ��(InitLStack)
Status InitLStack1(LinkStack S){
    S = NULL;
    return OK;
}

//������2.��ջ(Push)
Status Push1(LinkStack S,SElemType e){
    //�����������½ڵ�
    LinkStack p = (LinkStack)malloc(sizeof(StackNode));
    p -> data = e;
    p -> next = S;
    S = p;
    return OK;
}

//������3.��ջ(Pop)
Status Pop1(LinkStack S,SElemType e){
    //�������ж��Ƿ�Ϊ��ջ
    if(S == NULL){
        printf("ջ��");
        return ERROR;
    }
    //�����������½ڵ�
    LinkStack p = S;
    //��������ֵ����e
    e = S -> data;
    //����������ǰջ���ڵ㸳��p���Ա��ͷ�
    S = S -> next;
    free(p);
    return OK;
}

//������4.ȡջ��Ԫ��
SElemType GetTop1(LinkStack S){
    //�������ж��Ƿ�Ϊ��ջ
    if(S == NULL){
        printf("��ջ");
        return ERROR;
    }
    return S -> data;
}

Status Empty1(LinkStack* S){
    if(*S == NULL)
        return OK;
    return ERROR;
}

int main(){
    LinkStack S;
    InitLStack1(S);
    Push1(S,'A');
    Push1(S,'B');
    Push1(S,'C');
    Push1(S,'D');
    Push1(S,'E');
    while(!Empty1(&S)){
        SElemType e;
        Pop1(S,&e);
        printf("%c ",e);
    }
    return OK;
}
