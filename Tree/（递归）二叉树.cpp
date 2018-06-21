#include<stdio.h>
#include<stdlib.h>
typedef char TElemType;
typedef void Status;

typedef struct BiTNode {
	TElemType       data;
	struct BiTNode  *lchild, *rchild;//左右孩子指针
} BiTNode, *BiTree;

TElemType Visit(TElemType e) {  //输出元素e的值
	printf("%c",e);
	return e;
}

Status PreOrderTraverse(BiTree T) {
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
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
	//按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树
	//构造二叉链表表示的二叉树T
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

	printf("1-构建一棵二叉树\n2-先序遍历二叉树\n3-中序遍历二叉树\n4-后序遍历二叉树\n");
	do
	{
		printf("请输入指令序号：");
		scanf("%d", &p);
		getchar();
		if (p < 0 || p>4)
		{
			printf("输入指令错误，请重新输入");
		}
		else if (p == 1) {
			printf("请输入树中元素（空元素用#表示）：");
			CreatBiTree(T);
		}
		else if (p == 2) {
			printf("先序遍历二叉树的结果为：");
			PreOrderTraverse(T);
		    printf("\n");}
		else if (p == 3) {
			printf("中序遍历二叉树的结果为：");
			InOrderTraverse(T);
			printf("\n");
		}
		else if (p == 4) {
			printf("后序遍历二叉树的结果为：");
			PostOrderTraverse(T);
			printf("\n");
		}
	} while (p != 0);
	return 0;
}