#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef void Status;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

Status InitList(LinkList &L, int n)
{
	LinkList p, q;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	q = L;
	printf("������Ԫ��:");
	for (int i = 0; i<n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &(p->data));
		q->next = p;
		q = q->next;
	}
	p->next = NULL;

}

Status ListInsert(LinkList &L, int i, ElemType e)
{
	LinkList p = L;
	LinkList s;
	int j = 0;
	while (p&&j<i - 1)
	{
		p = p->next;
		j++;
	}
	if (!p || j>i - 1)
	{
		printf("����λ�ò��Ϸ�");
		exit(0);
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e; s->next = p->next;
	p->next = s;
}

Status DeleteSqList(LinkList L, int i)
{
	LinkList p = L;
	LinkList q;
	int j = 0;
	while (p->next&&j<i - 1)
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j>i - 1)
	{
		printf("ɾ��λ�ò��Ϸ�");
		exit(0);
	}
	q = p->next; 
	p->next = q->next;
	free(q);
}

Status FindList(LinkList L, int i)
{
	LinkList p;
	p = L->next;
	int j = 1;
	while (p&&j<i)
	{
		p = p->next;
		j++;
	}
	if (!p || j>i)
	{
		printf("���ҵ�Ԫ�ز�����");
		exit(0);
	}
	printf("���ҵ�Ԫ��ֵΪ��%d", p->data);
}

Status printSqList(LinkList L, int n)
{
	LinkList p = L->next;
	int j = 1;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
		j++;
	}
}

void main()
{
	LNode *L;
	int n, i, j, p, q;

	printf("��������Ҫ������Ԫ�ظ�����");
	scanf("%d", &i);
	InitList(L, i);
	printf("�µ�����");
	printSqList(L, i);
	printf("\n");

	printf("��������Ҫ�����λ�ü�Ԫ�أ�");
	scanf("%d %d", &p, &q);
	ListInsert(L, p, q);
	printf("�µ�����");
	printSqList(L, i);
	printf("\n");

	printf("��������Ҫ���ҵ�λ�ã�");
	scanf("%d", &n);
	FindList(L, n);
	printf("\n");

	printf("��������Ҫɾ����λ�ã�");
	scanf("%d", &j);
	DeleteSqList(L, j);
	printf("�µ�����");
	printSqList(L, i);
	printf("\n");
	
}