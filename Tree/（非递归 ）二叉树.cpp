#define MAX_NODE  50
#include<stdio.h>
#include<stdlib.h>
typedef char TElemType;
typedef void Status;

typedef struct BiTNode {
	TElemType       data;
	struct BiTNode  *lchild, *rchild;//左右孩子指针
} BiTNode, *BiTree;

TElemType Visit(TElemType e) {  //输出元素e的值
	printf("%c", e);
	return e;
}

Status PreOrderTraverse(BiTree T) {
	//先序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
	BiTNode  *Stack[MAX_NODE], *p = T, *q;
	int  top = 0;
	Stack[0] = NULL;
	if (T == NULL)  
		printf("当前二叉树为空树");
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
	//中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
	BiTNode  *Stack[MAX_NODE], *p = T;
	int  top = 0, con = 1;
	Stack[0] = NULL;
	if (T == NULL)  printf("当前二叉树为空树");
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
	//后序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
	BiTNode  *S1[MAX_NODE], *p = T;
	int S2[MAX_NODE], top = 0 , con = 1;
	if (T == NULL)
		printf("当前二叉树为空树");
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
				/* 使循环继续进行而不至于死循环 */
			}
		} while (con != 0);
	}
}

Status CreatBiTree(BiTree &T) {
	//按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树
	//构造二叉链表表示的二叉树T
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

	printf("1-构建一棵二叉树\n2-先序遍历二叉树\n3-中序遍历二叉树\n4-后序遍历二叉树\n");
	do
	{
		printf("请输入指令序号：");
		scanf("%d", &p);
		getchar();
		if (p < 0 || p>4)
		{
			printf("输入指令错误，请重新输入\n");
		}
		else if (p == 1) {
			printf("请输入树中元素（空元素用#表示）：");
			CreatBiTree(T);
		}
		else if (p == 2) {
			printf("先序遍历二叉树的结果为：");
			PreOrderTraverse(T);
			printf("\n");
		}
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