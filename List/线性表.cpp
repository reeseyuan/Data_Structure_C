#define  OK   1
#define  ERROR   0
#define OVERFLOW -1
#define  MAX_SIZE  100
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#include<stdio.h>
#include<stdlib.h>
typedef  int  Status;
typedef  int  ElemType;
typedef struct {
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList &L) {
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status StartList(SqList &L) {
	ElemType number;
	int i = 0;
	int n = 0;
	printf("������Ԫ�صĸ�����");
	scanf("%d", &n);
	printf("���������֣�");
	for (i = 0; i < n; i++) {
		scanf("%d",&number);
		L.elem[i] = number;
		L.length += 1;
	}
	printf("�µ�˳��� :");
	for (i = 0; i < n; i++) {
		printf("%d ",L.elem[i]);
	}
	printf("\n");
	return OK;
}

Status InsertList(SqList &L , int i , ElemType e){
	int j;
	if (i<0 || i>L.length)
		return ERROR;
	if (L.length >= L.listsize) {
		L.elem = (ElemType*)realloc(L.elem,(L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!L.elem)exit(OVERFLOW);
		L.listsize += LISTINCREMENT;
	}
	++L.length;
	for (j = L.length; j >= i; j--) {
		L.elem[j] = L.elem[j - 1];
	}
	L.elem[j] = e;
	return OK;
}

Status FindList(SqList &L,int i) {
	return L.elem[i-1];
}

Status DeleteList(SqList &L,int i) {
	int j;
	ElemType *p;
	ElemType *q;
	if ((i < 1) || (i > L.length))
		return ERROR;
	for (j = i; j < L.length; j++) {
		L.elem[j - 1] = L.elem[j];
	}
	L.length--;
	return OK;
}

void main() {
	int i = 0;
	int a,b,d,n;
	SqList List;
	InitList_Sq(List);
	StartList(List);
	
	printf("������Ҫ�����λ�ü�Ԫ�أ�");
	scanf("%d %d",&a,&b);

	InsertList(List, a, b);
	printf("�µ�˳��� :");
	for (i = 1; i <= List.length; i++)
		printf("%d ", *(List.elem + i - 1));

	printf("\n");
	int c;
	printf("������Ҫ���ҵ�Ԫ�ص�λ�ã�");
  scanf("%d",&c);
	printf("�����ҵ�Ԫ��Ϊ :");
	printf("%d\n", FindList(List,c));
	printf("������Ҫɾ����Ԫ�ص�λ�ã�");
	scanf("%d", &d);
	DeleteList(List, d);
	printf("�µ�˳��� :");
	for (i = 1; i <= List.length; i++)
		printf("%d ", *(List.elem + i - 1));

	printf("\n");
}