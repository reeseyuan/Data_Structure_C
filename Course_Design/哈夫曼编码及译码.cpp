#include <stdio.h>    
#include<stdlib.h>    
#include<string.h>    

int s2;
int s1;
int m;

typedef struct {
	char ch;
	int data;
	int p, lc, rc;
}Htree, *Hufftree;
typedef char* Huffcode;

void Select(Hufftree &Ht, int n)//ѡ���㷨
{
	char *cd;
	int min1, min2;
	min1 = min2 = 32765;
	s1 = s2 = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		if (!Ht[i].p)
			if (Ht[i].data<min1)
			{
				min2 = min1;
				s2 = s1;
				min1 = Ht[i].data;
				s1 = i;
			}
			else if (Ht[i].data<min2)
			{
				s2 = i;
				min2 = Ht[i].data;
			}
	}
}

void Huffman(Hufftree &Ht, Huffcode Hc[], int *w, int n)//�����������㷨
{
	int start;
	char *cd;
	int i, c, f;
	if (n<1)
		return;
	m = 2 * n - 1;
	Ht = (Htree*)malloc((m + 1) * sizeof(Htree));
	for (i = 1; i <= n; i++)
	{
		Ht[i].data = w[i - 1];
		Ht[i].p = 0;
		Ht[i].lc = -1;
		Ht[i].rc = -1;
	}
	for (i = n + 1; i <= m; i++)
	{
		Ht[i].data = 0;
		Ht[i].lc = -1;
		Ht[i].rc = -1;
		Ht[i].p = 0;
	}
	for (i = n + 1; i <= m; ++i)
	{
		Select(Ht, i - 1);
		Ht[s1].p = i;
		Ht[s2].p = i;
		Ht[i].lc = s1;
		Ht[i].rc = s2;
		Ht[i].data = Ht[s1].data + Ht[s2].data;
	}

	cd = (char *)malloc(n * sizeof(char));
	start = 0;
	cd[n - 1] = '\0';

	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = Ht[i].p; f != 0; c = f, f = Ht[f].p)
		{
			if (Ht[f].lc == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}

		Hc[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(Hc[i], &cd[start]);
	}
}

void Decode(Hufftree &Ht)//�����㷨
{
	int i, j = 0;
	i = m;
	char b[20];

	printf("�������(��'#'Ϊ������־):\n");
	scanf("%s", b);
	printf("�������ַ�Ϊ:\n");
	while (b[j] != '#')
	{
		//printf("%c ",b[j]);  
		if (b[j] == '0')
			i = Ht[i].lc;
		else
			i = Ht[i].rc;
		if (Ht[i].lc == -1)
		{
			printf("%d", Ht[i].data);
			i = m;              //ÿ�������ͷ��ʼ  
		}
		j++;
	}
	printf("\n");
}

int main()
{
	Hufftree Ht;
	Huffcode *Hc;
	int w[20];
	int i, n;
	printf("����\n\n����Ҫ�����ַ�����:\n");
	scanf("%d", &n);
	Hc = (Huffcode*)malloc(n * sizeof(Huffcode));
	printf("����Ҫ������ַ���Ƶ��:\n");
	for (i = 0; i<n; i++)
		scanf("%d", &w[i]);
	Huffman(Ht, Hc, w, n);
	printf("�ַ�����Ϊ:\n");
	for (i = 1; i <= n; i++)
	{
		printf("%d  %s\n", w[i - 1], Hc[i]);
	}
	printf("����\n");
	Decode(Ht);
	return 0;
}