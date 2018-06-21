#define MAX_NODE  50
#include<stdio.h>
#include<stdlib.h>
typedef char TElemType;
typedef void Status;

typedef struct BiTNode {
	TElemType       data;
	struct BiTNode  *lchild, *rchild;//���Һ���ָ��
} BiTNode, *BiTree;

TElemType Visit(TElemType e) {  //���Ԫ��e��ֵ
	printf("%c", e);
	return e;
}

Status PreOrderTraverse(BiTree T) {
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	BiTNode  *Stack[MAX_NODE], *p = T, *q;
	int  top = 0;
	Stack[0] = NULL;
	if (T == NULL)  
		printf("��ǰ������Ϊ����");
	else {
		do
		{
			Visit(p->data);   
			q = p->rchild;
			if (q != NULL)  
				Stack[++top] = q;
			p = p->lchild;
			if (p == NULL) 
			{ 
				p = Stack[top];  
				top--; 
			}
		} while (p != NULL);
	}
}//PreOrderTraverse

Status InOrderTraverse(BiTree T) {
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	BiTNode  *Stack[MAX_NODE], *p = T;
	int  top = 0, con = 1;
	Stack[0] = NULL;
	if (T == NULL)  printf("��ǰ������Ϊ����");
	else {
		do
		{
			while (p != NULL)
			{
				Stack[++top] = p;  
				p = p->lchild;
			}
			if (top == 0)
				con = 0;
			else {
				p = Stack[top];  
				top--;
				Visit(p->data);  
				p = p->rchild;
			}
		} while (con != 0);
	}
}//InOrderTraverse

Status PostOrderTraverse(BiTree T){
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	BiTNode  *S1[MAX_NODE], *p = T;
	int S2[MAX_NODE], top = 0 , con = 1;
	if (T == NULL)
		printf("��ǰ������Ϊ����");
	else {
		do
		{
			while (p != NULL)
			{
				S1[++top] = p;
				S2[top] = 0;
				p = p->lchild;
			}
			if (top == 0)
				con = 0;
			else if (S2[top] == 0)
			{
				p = S1[top]->rchild;  
				S2[top] = 1;
			}
			else
			{
				p = S1[top];  
				top--;
				Visit(p->data); 
				p = NULL;
				/* ʹѭ���������ж���������ѭ�� */
			}
		} while (con != 0);
	}
}

Status CreatBiTree(BiTree &T) {
	//�������������������н���ֵ��һ���ַ������ո��ַ���ʾ����
	//������������ʾ�Ķ�����T
	TElemType ch;
	scanf("%c",&ch);
	if (ch == '#')
		T = NULL;
	else {
		if ((T = (BiTNode *)malloc(sizeof(BiTNode))))
			T->data = ch;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}//CreateBiTree

int main() {
	int p;
	BiTNode *T;

	printf("1-����һ�ö�����\n2-�������������\n3-�������������\n4-�������������\n");
	do
	{
		printf("������ָ����ţ�");
		scanf("%d", &p);
		getchar();
		if (p < 0 || p>4)
		{
			printf("����ָ���������������\n");
		}
		else if (p == 1) {
			printf("����������Ԫ�أ���Ԫ����#��ʾ����");
			CreatBiTree(T);
		}
		else if (p == 2) {
			printf("��������������Ľ��Ϊ��");
			PreOrderTraverse(T);
			printf("\n");
		}
		else if (p == 3) {
			printf("��������������Ľ��Ϊ��");
			InOrderTraverse(T);
			printf("\n");
		}
		else if (p == 4) {
			printf("��������������Ľ��Ϊ��");
			PostOrderTraverse(T);
			printf("\n");
		}
	} while (p != 0);
	return 0;
}