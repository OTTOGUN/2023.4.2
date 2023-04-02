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
    SElemType *base;     //》》》栈底指针
    SElemType *top;      //》》》栈顶指针
    int stacksize;       //栈可用的最大容量
}SqStack;

//》》》1.栈的初始化(InitStack)
Status InitStack(SqStack* S){
    //①为顺序栈分配一个最大容量MAXSIZE的数组
    S -> base = (SqStack*)malloc(sizeof(SElemType) * MAXSIZE);
    //②判断是否分配成功
    if(!S->base)
        strerror(errno);
    //③top初始为base，空栈
    S -> top = S -> base;
    //④stacksize置为最大容量MAXSIZE
    S -> stacksize = MAXSIZE;
    return OK;
}

//》》》2.入栈(Push)
Status Push(SqStack* S,SElemType e){
    //①判断是否栈满，若满返回ERROR
    if(S -> top - S -> base == S -> stacksize){
        printf("栈满");
        return ERROR;
    }
    //②将新元素压入栈顶，栈顶指针加1
    *(S -> top++) = e;
    return OK;
}

//》》》3.出栈(Pop)
char Pop(SqStack* S,SElemType* e){
    //①判断栈顶是否为空，若空则返回ERROR
    if(S -> top == S -> base){
        printf("栈空");
        return ERROR;
    }
    //②栈顶指针减1，栈顶元素出栈
    *e = *(--(S -> top));
    return e;
}

//》》》4.取栈顶元素(GetTop)
Status GetTop(SqStack* S){
    if(S -> top == S -> base){
        printf("栈空");
        return ERROR;
    }
    return *(S -> top--);
}

//》》》栈的其他操作
Status IsEmpty(SqStack* S){
    if(S -> base == S -> top){
        printf("空栈");
        return TRUE;
    }
    return ERROR;
}

Status IsFull(SqStack* S){
    if(S -> top - S -> base == S -> stacksize){
        printf("栈满");
        return OK;
    }
    return ERROR;
}

//》》》测试程序->>>(成功)
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

//》》》》》》》》》》》》》》》》》》》链栈的表示和实现《《《《《《《《《《《《《《《《《《《《

//》》》0.链栈的存储结构
typedef struct StackNode{
    ElemType data;
    struct StackNode *next;
}StackNode,*LinkStack;

//》》》1.初始化(InitLStack)
Status InitLStack1(LinkStack S){
    S = NULL;
    return OK;
}

//》》》2.入栈(Push)
Status Push1(LinkStack* S,ElemType e){
    //》》》生成新节点
    LinkStack p = (LinkStack)malloc(sizeof(StackNode));
    p -> data = e;
    p -> next = (*S);
    (*S) = p;
    return OK;
}

//》》》3.出栈(Pop)
Status Pop1(LinkStack* S,ElemType* e){
    //》》》判断是否为空栈
    if(S == NULL){
        printf("栈空");
        return ERROR;
    }
    //》》》创建新节点
    LinkStack p = (*S);
    //》》》将值赋给e
    *e = (*S) -> data;
    //》》》将当前栈顶节点赋给p，以便释放
    (*S) = (*S) -> next;
    free(p);
    return OK;
}

//》》》4.取栈顶元素
ElemType GetTop1(LinkStack S){
    //》》》判断是否为空栈
    if(S == NULL){
        printf("空栈");
        return ERROR;
    }
    return S -> data;
}

Status Empty1(LinkStack* S){
    if(*S == NULL)
        return OK;
    return ERROR;
}

//》》》调试程序>>>>>成功
/*
int main(){
    LinkStack S;
    InitLStack1(&S);
    Push1(&S,'A');
    Push1(&S,'B');
    Push1(&S,'C');
    Push1(&S,'D');
    Push1(&S,'E');
    while(!Empty1(&S)){
        ElemType e;
        Pop1(&S,&e);
        printf("%d ",e);
    }
    return OK;
}*/

//》》》》》》》》》》》》》》》》》》》队列的创建和实现《《《《《《《《《《《《《《《《《《
//》》》0.队列的创建
typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

//》》》1.初始化
Status InitQueue(SqQueue* Q){
    //》》》为队列分配初始空间
    Q->base = (QElemType *)malloc(sizeof(QElemType) * MAXSIZE);
    //》》》存储分配失败
    if(Q->base == NULL){
        printf("创建失败");
        return ERROR;
    }
    //》》》头指针和尾指针赋0
    Q->front = 0;
    Q->rear = Q->front;
    return OK;
}

//》》》2.求队列长度(QueueLength)
int QueueLength(SqQueue Q){
    return(Q.rear - Q.front + MAXSIZE) % MAXSIZE;
    return OK;
}

//》》》3.入队(EnQueue)
Status EnQueue(SqQueue* Q,QElemType e){
    if((Q->rear + 1) % MAXSIZE == Q->front){
        printf("队列已满");
        return ERROR;
    }
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

//》》》4.出队(DeQueue)
Status DeQueue(SqQueue* Q,QElemType* e){
    if(Q->front == Q->rear){
        printf("空队列");
        return ERROR;
    }
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

//》》》5.取队头元素(GetHead)
QElemType GetHead(SqQueue Q,QElemType e){
    if(Q.front == Q.rear){
        printf("空队列");
        return ERROR;
    }
    Q.base[Q.front] = e;
}

Status IsEmpty(SqQueue Q){
    if(Q.front == Q.rear){
        printf("空队列");
        return OK;
    }
    return ERROR;
}
