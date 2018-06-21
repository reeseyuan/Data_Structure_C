#include<stdio.h>
#include<stdlib.h>
typedef int QElemType;
typedef void Status;
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
Status InitQueue(LinkQueue &Q)
{
	//构造队列
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
	{
		exit(0);
	}
	Q.front->next = NULL;
	printf("创建完成\n");
}

Status DestroyQueue(LinkQueue &Q)
{
	//摧毁队列
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	printf("队列已摧毁\n");
}

Status ClearQueue(LinkQueue &Q)
{
	//清空队列
	if (!Q.front)
	{
		exit(0);
	}
	QueuePtr p;
	while (Q.front != Q.rear)
	{
		p = Q.front;
		Q.front = Q.front->next;
		free(p);
	}
	printf("队列已清空\n");
}

Status QueueEmpty(LinkQueue Q)
{
	//查看队列是否为空
	if (Q.front == Q.rear)
	{
		printf("队列为空\n");
	}
	else
	{
		printf("队列不为空\n");
	}

}

Status QueueLength(LinkQueue Q)
{
	//查看队列长度
	int i = 0;
	while (Q.front != Q.rear)
	{
		Q.front = Q.front->next;
		i++;
	}
	printf("队列长度为：%d\n", i );
}
Status GetHead(LinkQueue Q, QElemType &e)
{
	//查看队首
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("无队首\n");
		exit(0);
	}
	p = Q.front->next;
	e = p->data;
	printf("队首元素为:%d\n", e);
}

Status EnQueue(LinkQueue &Q, QElemType &e)
{
	//插入队列
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		printf("内存分配失败\n");
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{
	//删除队首
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("队列已清空\n");
		exit(0);
	}
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
	{
		Q.rear = Q.front;
	}
	free(p);
}
Status PrintQueue(LinkQueue &Q)
{
	//打印队列
	if (Q.front == Q.rear)
	{
		exit(0);
	}
	QNode *p = Q.front->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
int main()
{
	int n, p, i, m, x;
	LinkQueue Q;
	printf("1-构造队列\n2-插入队列\n3-删除队首\n4-查看队首\n5-查看队列长\n6-查看队列是否为空\n7-摧毁队列\n8-清空队列\n9-打印队列\n0-退出\n");
	do
	{
		printf("请输入指令序号：");
		scanf("%d",&p);
		if (p<0 || p>9)
		{
			printf("输入错误，请重新输入\n");
		}
		if(p==1)
			InitQueue(Q); 
		else if (p == 2) {
			printf("请输入入队列元素个数：");
			scanf("%d", &n);
			printf("输入元素:");
			for (i = 1; i <= n; i++)
			{
				scanf("%d", &x);
				EnQueue(Q, x);
			}
		}

		else if (p == 3)
			DeQueue(Q, m);
		else if (p == 4)
			GetHead(Q, m);
		else if (p == 5)
			QueueLength(Q);
		else if (p == 6)
			QueueEmpty(Q);
		else if (p == 7)
			DestroyQueue(Q);
		else if (p == 8)
			ClearQueue(Q);
		else if (p == 9)
			PrintQueue(Q);
		else if (p == 0)
			exit(0);
	
	}while (p != 0);
	return 0;
}