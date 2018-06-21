#include<stdio.h>
#include<stdlib.h>
typedef char TElemType;
typedef void Status;

typedef struct BiTNode {
	TElemType       data;
	struct BiTNode  *lchild, *rchild;//���Һ���ָ��
} BiTNode, *BiTree;

TElemType Visit(TElemType e) {  //���Ԫ��e��ֵ
	printf("%c",e);
	return e;
}

Status PreOrderTraverse(BiTree T) {
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	if (T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}//PreOrderTraverse

Status InOrderTraverse(BiTree T) {
	if (T)
	{
		InOrderTraverse(T->lchild);
		Visit(T->data);       
		InOrderTraverse(T->rchild);
	}
}//InOrderTraverse

Status PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		Visit(T->data); 
	}
}

BiTNode *CreatBiTree(BiTree &T) {
	//�������������������н���ֵ��һ���ַ������ո��ַ���ʾ����
	//������������ʾ�Ķ�����T
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
	{
		T = NULL;
		return(T);
	}

	else {
		if ((T = (BiTNode *)malloc(sizeof(BiTNode))))
			T->data = ch;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
		return(T);
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
			printf("����ָ���������������");
		}
		else if (p == 1) {
			printf("����������Ԫ�أ���Ԫ����#��ʾ����");
			CreatBiTree(T);
		}
		else if (p == 2) {
			printf("��������������Ľ��Ϊ��");
			PreOrderTraverse(T);
		    printf("\n");}
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