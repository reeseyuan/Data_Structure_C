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
	printf("请输入元素:");
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
		printf("插入位置不合法");
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
		printf("删除位置不合法");
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
		printf("查找的元素不存在");
		exit(0);
	}
	printf("查找的元素值为：%d", p->data);
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

	printf("请输入您要创建的元素个数：");
	scanf("%d", &i);
	InitList(L, i);
	printf("新的链表：");
	printSqList(L, i);
	printf("\n");

	printf("请输入您要插入的位置及元素：");
	scanf("%d %d", &p, &q);
	ListInsert(L, p, q);
	printf("新的链表：");
	printSqList(L, i);
	printf("\n");

	printf("请输入您要查找的位置：");
	scanf("%d", &n);
	FindList(L, n);
	printf("\n");

	printf("请输入您要删除的位置：");
	scanf("%d", &j);
	DeleteSqList(L, j);
	printf("新的链表：");
	printSqList(L, i);
	printf("\n");
	
}