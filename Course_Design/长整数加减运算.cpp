#include <stdio.h>
#include<stdlib.h>
#define LENGTH 16

typedef char Elemtype;
typedef struct DuLNode
{
	Elemtype data;
	struct DuLNode *prior, *rear;
}DuLNode;

void CreateDulList(DuLNode *list[3])//创建双向循环链表
{
	int i, j;
	DuLNode *p, *q;

	for (i = 0; i < 3; i++)
	{
		p = list[i];
		p->data = '#';

		for (j = 0; j < LENGTH; j++)
		{
			q = (DuLNode*)malloc(sizeof(DuLNode));
			q->data = '#';
			p->rear = q;
			q->prior = p;
			p = p->rear;

		}
		p->rear = list[i];
		list[i]->prior = p;
	}
}

void Input(DuLNode *list[3], int *a, int *b, int *n1, int *n2)//录入数据函数，a,b操作数，n1被操作数的位数，n2操作数的位数
{
	int i;
	char temp;
	DuLNode *ctrl;

	printf("请输入算式:");
	for (i = 0; i<2; i++)
	{
		ctrl = list[i];
		scanf_s("%c", &temp, sizeof(temp));
		if (temp == '-')
		{
			*a = 0;
		}

		else if (temp < '0' || temp > '9')
		{
			printf("输入有误！\n"); 
			return;
		}

		else
		{
			if (i == 0)
				*a = 1;
			
			ctrl->data = temp;

			if (i == 0)
				(*n1)++;
			else 
				(*n2)++;
			
			ctrl = ctrl->rear;
		}

		while (scanf("%c", &temp, sizeof(temp)) && temp >= '0'&&temp <= '9')
		{
			ctrl->data = temp;
			if (i == 0)
				(*n1)++;
			else 
				(*n2)++;
			ctrl = ctrl->rear;
		}

		if (i == 0)
		{
			if (temp == '+') 
			{ 
				*b = 1; 
			}
			else if (temp == '-') 
			{ 
				*b = 0; 
			}
			else 
			{ 
				printf("输入有误！\n"); 
				return; 
			}
		}
		else
		{
			printf("算式正确！\n");
		}
	}
}

void ExchangeList(DuLNode *t1, int *n1, DuLNode *t2, int *n2)//交换两个双向循环链表
{
	DuLNode p, *q = &p;

	int a;

	*q = *t1;
	*t1 = *t2;
	*t2 = *q;

	t1->rear->prior = t1;
	t2->rear->prior = t2;

	a = *n1;
	*n1 = *n2;
	*n2 = a;
}

void JudgeSymbol(DuLNode *list[3], int *a, int *b, int *n1, int *n2)//判断结果的符号
{
	int i;

	DuLNode *c1 = list[0];
	DuLNode *c2 = list[1];

	if (*a == 0)
	{
		if (*b == 1)
		{
			*b = 0;
			*a = 1;
			ExchangeList(list[0], n1, list[1], n2);
			goto changed;
		}
		else
		{
			*b = 1;
			list[2]->data = '-';
			goto changed;
		}
	}

	else
	{
	changed:
		if (*b == 0)
		{
			if (*n1 < *n2)
			{
				ExchangeList(list[0], n1, list[1], n2);
				list[2]->data = '-';
			}
			else if (*n1 == *n2)
			{
				for (i = 0; i < *n2; i++)
				{
					if (c1->data < c2->data)
					{
						ExchangeList(list[0], n1, list[1], n2);
						list[2]->data = '-';
						break;
					}
					c1 = c1->rear;
					c2 = c2->rear;
				}
				if (i == *n2)
				{
					list[2]->data = '+';
				}
			}
			else
			{
				list[2]->data = '+';
			}
		}
		else if (*a == 1 && *b == 1)
		{
			list[2]->data = '+';
		}
	}
}

void Caculate(DuLNode *list[3], int *a, int *b, int *n1, int *n2)//计算过程
{
	DuLNode *c1 = list[0], *c2 = list[1], *c3 = list[2];

	int i;
	int max_len = *n1 > *n2 ? *n1 : *n2;

	for (i = 0; i < *n1 - 1; i++)
	{
		c1 = c1->rear;
	}

	for (i = 0; i < *n2 - 1; i++)
	{
		c2 = c2->rear;
	}

	for (i = 0; i < max_len + 1; i++)
	{
		c3 = c3->rear;
	}

	for (i = 0; i<max_len; i++)
	{
		if (c1->data == '#')
			c1->data = '0';
		if (c2->data == '#')
			c2->data = '0';

		if (*b == 1)
		{

			if (c3->data != '#')
				c3->data = c3->data + c1->data + c2->data - '0' - '0';
			else 
				c3->data = c1->data + c2->data - '0';

			if (c3->data > '9')
			{
				c3->data = c3->data - 10;
				c3->prior->data = '1'; 
			}
		}

		else
		{
			if (c1->data < c2->data)
			{
				c1->data = c1->data + 10;
				c1->prior->data = c1->prior->data - 1;
			}

			c3->data = '0' + c1->data - c2->data;
		}
		c3 = c3->prior;
		c1 = c1->prior;
		c2 = c2->prior;
	}
}

void OutputData(DuLNode *list[3], int n1, int n2)//输出结果的数据
{
	DuLNode *p;
	DuLNode *q;

	int zero = 1;
	int count = 0, max_len = n1>n2 ? n1 : n2, start = 0;

	p = list[2]->rear;
	if (list[2]->rear->data == '#')
	{
		zero = 1;
		p = p->rear;
	}
	while (zero == 1)
	{
		if (p->data == '0')
		{
			if (p->rear->data != '#')
			{

				q = p;
				p->prior->rear = p->rear;
				p->rear->prior = p->prior;
				p = p->rear;
				free(q);
				max_len--;
				zero = 1;

			}

			else
			{
				zero = 0;//
			}

		}

		else
		{
			zero = 0;
		}
	}
	
	start = (max_len + 2) % 4;
	p = list[2];

	for (int i = 0; p->data != '#' || (p->data == '#'&&p->rear->data != '#'); i++)
	{

		if (p->data == '#'&&p->rear->data != '#')
		{
			count++;
			p = p->rear;
			continue;
		}

		count++;
		printf("%c", p->data);
		if ((count - start) % 4 == 0 && p->rear->data != '#')
			printf(",");

		p = p->rear;

	}
	putchar(10);

}

int main()
{
	DuLNode *L[3];
	int n1_len = 0, n2_len = 0;
	int a, b;
	for (int i = 0; i < 3; i++)
	{
		L[i] = (DuLNode*)malloc(sizeof(DuLNode));
	}

	printf("——欢迎来到长整数加减法运算器——\n");
	CreateDulList(L);//创建三个循环链表
	Input(L, &a, &b, &n1_len, &n2_len);//录入数据
	JudgeSymbol(L, &a, &b, &n1_len, &n2_len);//判断结果的符号
	Caculate(L, &a, &b, &n1_len, &n2_len);//计算算式
	printf("算式结果是：");
	OutputData(L, n1_len, n2_len);//打印结果

	return 0;

}