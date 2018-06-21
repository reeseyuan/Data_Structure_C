//栈的顺序存储表示
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#include<stdio.h>
#include<stdlib.h>
typedef void Status;
typedef int SElemType;
typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

Status InitStack(SqStack &S) {
	//构造一个空栈S
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(0); //存储分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	printf("构建完成\n");
}//InitStack

Status GetTop(SqStack S, SElemType &e) {
	//若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
	if (S.top == S.base) {
		printf("栈为空\n");
		exit(0);
	}
	e = *(S.top - 1);
	printf("%d\n",e);

}//GetTop

Status Push(SqStack &S, SElemType e) {
	//插入元素e为新的栈顶元素
	if (S.base)
	{
		if (S.top - S.base >= S.stacksize)
		{
			S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
			if (!S.base)
			{
				printf("追加内存失败\n");
				exit(0);
			}
			S.top = S.base + S.stacksize;
			S.stacksize += STACKINCREMENT;
		}
		*S.top++ = e;
	}
}//Push

Status Pop(SqStack &S, SElemType &e) {
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
	if (S.top == S.base) {
		printf("栈为空\n");
		exit(0);
	}
	e = *--S.top;
	printf("%d\n", e);
}//Pop

Status ClearStack(SqStack &S)
{
	S.top = S.base;
	printf("栈已清空\n");
}

Status DestoryStack(SqStack &S)
{
	free(S.base);
	S.base = NULL;
	S.stacksize = 0;
	printf("栈已摧毁\n");
}

Status StackLength(SqStack S)
{
	printf("栈长度为:%d\n", S.top - S.base);
	printf("栈的空间为:%d\n", S.top - S.base + 1);
}

Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
	{
		printf("栈为空\n");
	}
	else
	{
		printf("栈不为空\n");
	}
}

Status printStack(SqStack &S)
{
	int *t;
	printf("输出元素：");
	t = S.top - 1;
	while (t != S.base - 1)
	{
		printf("%d ",*t);
		*t--;
	}
	printf("\n");
}

int main()
{
	int n, p, i, x;
	SElemType m;
	SqStack S;

	printf("1-构造栈\n2-入栈\n3-出栈\n4-查看栈顶\n5-查看栈长\n6-查看栈是否为空\n7-摧毁栈\n8-清空栈\n9-打印栈\n0-退出\n");
	do
	{
		printf( "请输入指令序号：");
		scanf("%d", &p);
		if (p<0 && p>9)
		{
			printf("输入错误，请重新输入:\n");
		}
		else if(p == 1)
			InitStack(S);
		else if(p==2)
		{
			printf("请输入入栈元素个数：");
			scanf("%d", &n);
			printf("输入元素:");
			for (i = 1; i <= n; i++)
			{
				scanf("%d", &x);
				Push(S, x);
			}
		}

		else if (p == 3)
			Pop(S, m); 
		else if (p == 4)
			GetTop(S, m);
		else if (p == 5)
			StackLength(S);
		else if (p == 6)
			StackEmpty(S);
		else if (p == 7)
			DestoryStack(S);
		else if (p == 8)
			ClearStack(S); 
		else if (p == 9)
			printStack(S);
		else if (p == 0)
			exit(0);
	} while (p != 0);
	return 0;
}

