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
	//�������
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
	{
		exit(0);
	}
	Q.front->next = NULL;
	printf("�������\n");
}

Status DestroyQueue(LinkQueue &Q)
{
	//�ݻٶ���
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	printf("�����Ѵݻ�\n");
}

Status ClearQueue(LinkQueue &Q)
{
	//��ն���
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
	printf("���������\n");
}

Status QueueEmpty(LinkQueue Q)
{
	//�鿴�����Ƿ�Ϊ��
	if (Q.front == Q.rear)
	{
		printf("����Ϊ��\n");
	}
	else
	{
		printf("���в�Ϊ��\n");
	}

}

Status QueueLength(LinkQueue Q)
{
	//�鿴���г���
	int i = 0;
	while (Q.front != Q.rear)
	{
		Q.front = Q.front->next;
		i++;
	}
	printf("���г���Ϊ��%d\n", i );
}
Status GetHead(LinkQueue Q, QElemType &e)
{
	//�鿴����
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("�޶���\n");
		exit(0);
	}
	p = Q.front->next;
	e = p->data;
	printf("����Ԫ��Ϊ:%d\n", e);
}

Status EnQueue(LinkQueue &Q, QElemType &e)
{
	//�������
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		printf("�ڴ����ʧ��\n");
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{
	//ɾ������
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("���������\n");
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
	//��ӡ����
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
	printf("1-�������\n2-�������\n3-ɾ������\n4-�鿴����\n5-�鿴���г�\n6-�鿴�����Ƿ�Ϊ��\n7-�ݻٶ���\n8-��ն���\n9-��ӡ����\n0-�˳�\n");
	do
	{
		printf("������ָ����ţ�");
		scanf("%d",&p);
		if (p<0 || p>9)
		{
			printf("�����������������\n");
		}
		if(p==1)
			InitQueue(Q); 
		else if (p == 2) {
			printf("�����������Ԫ�ظ�����");
			scanf("%d", &n);
			printf("����Ԫ��:");
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