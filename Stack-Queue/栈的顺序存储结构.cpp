//ջ��˳��洢��ʾ
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
	//����һ����ջS
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(0); //�洢����ʧ��
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	printf("�������\n");
}//InitStack

Status GetTop(SqStack S, SElemType &e) {
	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if (S.top == S.base) {
		printf("ջΪ��\n");
		exit(0);
	}
	e = *(S.top - 1);
	printf("%d\n",e);

}//GetTop

Status Push(SqStack &S, SElemType e) {
	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if (S.base)
	{
		if (S.top - S.base >= S.stacksize)
		{
			S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
			if (!S.base)
			{
				printf("׷���ڴ�ʧ��\n");
				exit(0);
			}
			S.top = S.base + S.stacksize;
			S.stacksize += STACKINCREMENT;
		}
		*S.top++ = e;
	}
}//Push

Status Pop(SqStack &S, SElemType &e) {
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S.top == S.base) {
		printf("ջΪ��\n");
		exit(0);
	}
	e = *--S.top;
	printf("%d\n", e);
}//Pop

Status ClearStack(SqStack &S)
{
	S.top = S.base;
	printf("ջ�����\n");
}

Status DestoryStack(SqStack &S)
{
	free(S.base);
	S.base = NULL;
	S.stacksize = 0;
	printf("ջ�Ѵݻ�\n");
}

Status StackLength(SqStack S)
{
	printf("ջ����Ϊ:%d\n", S.top - S.base);
	printf("ջ�Ŀռ�Ϊ:%d\n", S.top - S.base + 1);
}

Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
	{
		printf("ջΪ��\n");
	}
	else
	{
		printf("ջ��Ϊ��\n");
	}
}

Status printStack(SqStack &S)
{
	int *t;
	printf("���Ԫ�أ�");
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

	printf("1-����ջ\n2-��ջ\n3-��ջ\n4-�鿴ջ��\n5-�鿴ջ��\n6-�鿴ջ�Ƿ�Ϊ��\n7-�ݻ�ջ\n8-���ջ\n9-��ӡջ\n0-�˳�\n");
	do
	{
		printf( "������ָ����ţ�");
		scanf("%d", &p);
		if (p<0 && p>9)
		{
			printf("�����������������:\n");
		}
		else if(p == 1)
			InitStack(S);
		else if(p==2)
		{
			printf("��������ջԪ�ظ�����");
			scanf("%d", &n);
			printf("����Ԫ��:");
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

