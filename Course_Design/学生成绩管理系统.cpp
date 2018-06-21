#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

#define LEN 10
#define NAME_LEN 12
#define SUBJECT_NUM 3

typedef struct Student
{
	int term;
	int num;
	char name[12];
	float score[SUBJECT_NUM];
	float sum;
	float average;
}stu;

int ErrorCheck()//错误检测算法
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return 1;
	}
	else return 0;
}

void FreePointer(stu**p)//释放空间算法
{
	delete[] * p;
	*p = NULL;
}

int InputSingleInfo(stu*s)//录入单个学生信息
{
	int i;
	cin >> s->term;
	cin >> s->num;
	cin >> s->name;
	if (ErrorCheck()) { cout << "Input Error!" << endl; return 1; }
	s->sum = 0;
	for (i = 0; i < SUBJECT_NUM; i++)
	{
		cin >> s->score[i];
		if (ErrorCheck()) { cout << "Input Error!" << endl; return 1; }
		s->sum += s->score[i];
	}
	s->average = s->sum / 3;
	return 0;
}

void InputInformation()//创建一个文件并录入学生数据
{
	FILE *fp;

	if ((fp = (fopen("student.txt", "wb"))) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	cout << "please input students number:" << endl;
	int n = 0;
	cin >> n;
	if (ErrorCheck()) { cout << "Input error!" << endl; return; }

	stu *s = new stu[n];

	fprintf(fp, "%d", n);
	cout << "Please input by:Term Number Name Course1 Course2 Course3:" << endl;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (InputSingleInfo(&s[i]) == 1)
			return;
	}
	fwrite(s, sizeof(stu), n, fp);

	FreePointer(&s);
	fclose(fp);
}

void OutputSingleInfo(stu s)//输出单个学生的信息
{
	cout << s.term << "\t";
	cout << s.num << "\t";
	cout << s.name << "\t";
	for (int i = 0; i<SUBJECT_NUM; i++)
		cout << s.score[i] << "\t";
	cout << s.sum << "\t";
	cout << s.average << "\n";
}

void OutputInformation()//输出所有的学生的信息
{
	int n = 0;
	stu *temp;
	FILE *fp;
	if ((fp = fopen("student.txt", "rb")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	if (fscanf(fp, "%d", &n) == EOF) { cout << "空文件！" << endl; }
	temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	int i = 0;
	cout << "Term\tNumber\tName\tCourse1\tCourse2\tCourse3\tSum\tAverage" << endl;
	for (i = 0; i < n; i++)
	{
		OutputSingleInfo(temp[i]);
	}

	FreePointer(&temp);
	fclose(fp);
}

int CompareChar(char n1[], char n2[], int length)//比较字符串算法
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if (n1[i] == '\0'&&n2[i] == '\0')  return 1;
		if (n1[i] == '\0'&&n2[i] != '\0' || n1[i] != '\0'&&n2[i] == '\0')return 0;

		if (n1[i] != n2[i])
		{
			return 0;
		}
	}
	if (i == length)return 1;
	else return 0;
}

void SearchTemplet(int flag)//查找算法
{
	int n = 0;
	stu *temp;
	FILE *fp;
	if ((fp = fopen("student.txt", "rb")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	fscanf(fp, "%d", &n);
	temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	int i = 0;
	int ter, nu;
	char nam[12];

	if (flag == 0)
	{
		cout << "Please input term and number:" << endl;
		cin >> ter >> nu;
		if (ErrorCheck()) { cout << "Input Error!" << endl; return; }
	}
	else
	{
		cout << "Please input term and name:" << endl;
		cin >> ter >> nam;
		if (ErrorCheck()) { cout << "Input Error!" << endl; return; }
	}

	for (i = 0; i < n; i++)
	{
		if (flag == 0)
		{
			if (nu == temp[i].num&&ter == temp[i].term)
			{
				cout << "Term\tNumber\tName\tCourse1\tCourse2\tCourse3\tSum\tAverage" << endl;
				OutputSingleInfo(temp[i]);
				break;
			}
		}
		else
		{
			if (CompareChar(nam, temp[i].name, 12) == 1 && ter == temp[i].term)
			{
				cout << "Term\tNumber\tName\tCourse1\tCourse2\tCourse3\tSum\tAverage" << endl;
				OutputSingleInfo(temp[i]);
				break;
			}
		}
	}
	if (i == n)cout << "Can't find!" << endl;

	FreePointer(&temp);
	fclose(fp);
}

void Change()//修改单个学生的信息
{
	FILE *fp;

	if ((fp = fopen("student.txt", "rb+")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	int n = 0;
	if (fscanf(fp, "%d", &n) == EOF) { cout << "Empty File!" << endl; return; }
	stu*temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	int i = 0;
	int num;
	int term;

	int Continue;
	do
	{
		cout << "Please input the number and term:" << endl;
		cin >> num >> term;
		if (ErrorCheck()) { cout << "Input Error!" << endl; return; }
		for (i = 0; i < n; i++)
		{
			if (temp[i].num == num&&temp[i].term == term)
			{
				OutputSingleInfo(temp[i]);
				break;
			}
		}
		cout << "Please change by:term,number,name,course1,course2,course3:" << endl;
		if (InputSingleInfo(&temp[i]) == 1)return;
		cout << "Continue？1--continue\t0--abort" << endl;
		cin >> Continue;
		if (ErrorCheck()) { cout << "Input Error!" << endl; return; }
	} while (Continue == 1);

	rewind(fp);
	fprintf(fp, "%d", n);
	fwrite(temp, sizeof(stu), n, fp);

	FreePointer(&temp);
	fclose(fp);
	cout << "Success!" << endl;
}

int CheckIfRepetition(stu temp[], stu t, int n)//检查学生信息算法
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (temp[i].num == t.num&&temp[i].term == t.term)
		{
			return 1;
		}
	}
	if (i == n)return 0;
	else return 1;
}

void Insert()//插入单个学生的信息
{
	FILE *fp;

	if ((fp = fopen("student.txt", "rb+")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	int n = 0;
	if (fscanf(fp, "%d", &n) == EOF) { cout << "Empty File!" << endl; return; }
	stu*temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	stu t;
	int Continue;
	do
	{
		fseek(fp, 0L, 2);//将位置标记移动到文件末尾
		cout << "Please insert by:term,number,name,course1,course2,course3:\n" << endl;
		InputSingleInfo(&t);
		if (CheckIfRepetition(temp, t, n) == 1)
		{
			cout << "Already insist!" << endl;
			return;
		}

		fwrite(&t, sizeof(stu), 1, fp);
		rewind(fp);
		fprintf(fp, "%d", n + 1);
		cout << "Continue？1--continue\t0--abort" << endl;
		cin >> Continue;
		if (ErrorCheck()) { cout << "Input Error!" << endl; return; }
	} while (Continue == 1);

	FreePointer(&temp);
	fclose(fp);
}

void CopyString(char *n1, char *n2)//非string类型的字符串的复制
{
	int i;
	for (i = 0; i < NAME_LEN; i++)
	{
		n1[i] = n2[i];
	}
}

void CopyStruct(stu *n, stu*m)//结构体元素复制
{
	n->term = m->term;
	n->num = m->num;
	CopyString(n->name, m->name);
	for (int i = 0; i < SUBJECT_NUM; i++)
		n->score[i] = m->score[i];
	n->sum = m->sum;
	n->average = m->average;
}

void DeleteStudentInfo()//删除单个学生的信息。
{
	FILE *fp;

	if ((fp = fopen("student.txt", "rb+")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	int n = 0;
	fscanf(fp, "%d", &n);
	stu*temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	int term, num;
	int i, j, Continue;
	do
	{
		cout << "Please input the term and number:" << endl;
		cin >> term >> num;
		if (ErrorCheck()) { cout << "Input Error!" << endl; return; }
		int m = n;
		for (i = 0; i < n; i++)
		{
			if (temp[i].num == num&&temp[i].term == term)
			{
				for (j = i; j < n - 1; j++)
					CopyStruct(&temp[j], &temp[j + 1]);
				n--;
				cout << "Success!" << endl;
				break;
			}
		}
		
		if (i == m)cout << "Can't find!" << endl;

		fclose(fp);
		fp = fopen("student.txt", "wb");
		fprintf(fp, "%d", n);
		fwrite(temp, sizeof(stu), n, fp);
		cout << "Continue？1--continue\t0--abort" << endl;
		cin >> Continue;
		if (ErrorCheck()) { cout << "Input error!" << endl; return; }
	} while (Continue == 1);

	FreePointer(&temp);
	fclose(fp);
}

void SwapStruct(stu&n1, stu&n2)//结构体元素交换算法
{
	stu temp, *t = &temp;
	CopyStruct(t, &n1);
	CopyStruct(&n1, &n2);
	CopyStruct(&n2, t);
}

void BulbleSort(stu*temp, int n, int sub)//冒泡排序
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = n - 1; j >i; j--)
		{
			if (temp[j].score[sub - 1] > temp[j - 1].score[sub - 1])
				SwapStruct(temp[j], temp[j - 1]);
		}
	}
}

void SortDecSingle()//单科成绩冒泡排序
{
	FILE *fp;

	if ((fp = fopen("student.txt", "rb+")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	int n = 0;
	fscanf(fp, "%d", &n);
	stu*temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	int subject;
	cout << "Please input the course number(descending):" << endl;
	cin >> subject;
	if (ErrorCheck()) { cout << "Input error!" << endl; return; }
	BulbleSort(temp, n, subject);
	cout << "Finish!" << endl;

	rewind(fp);
	fprintf(fp, "%d", n);
	fwrite(temp, sizeof(stu), n, fp);

	FreePointer(&temp);
	fclose(fp);
}

void SelectionSort(stu*t, int n)//选择排序
{
	int i, j, min;
	for (i = 0; i < n - 1; i++)
	{
		min = 0;
		for (j = 0; j < n - i; j++)
		{
			if (t[min].sum> t[j].sum)
				min = j;
		}
		SwapStruct(t[min], t[j - 1]);
	}
}

void SortDecSum()//总分选择排序
{
	FILE *fp;

	if ((fp = fopen("student.txt", "rb+")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	int n = 0;
	fscanf(fp, "%d", &n);
	stu*temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	SelectionSort(temp, n);
	cout << "Finish!" << endl;

	rewind(fp);
	fprintf(fp, "%d", n);
	fwrite(temp, sizeof(stu), n, fp);

	FreePointer(&temp);
	fclose(fp);
}

void SubjectInfo()//科目信息
{
	FILE *fp;

	if ((fp = fopen("student.txt", "rb+")) == NULL)
	{
		cout << "Can't open the file!" << endl;
		exit(0);
	}

	int n = 0;
	fscanf(fp, "%d", &n);
	stu*temp = new stu[n];
	fread(temp, sizeof(stu), n, fp);

	int i, j;
	float sum[SUBJECT_NUM] = { 0 }, ave[SUBJECT_NUM] = { 0 };
	for (j = 0; j < SUBJECT_NUM; j++)
	{
		for (i = 0; i < n; i++)
		{
			sum[j] += temp[i].score[j];
		}
		ave[j] = sum[j] / n;
	}

	cout << "\tSum\tAverage" << endl;
	for (i = 0; i<SUBJECT_NUM; i++)
		cout << "Course" << i + 1 << ":" << sum[i] << '\t' << ave[i] << endl;

	rewind(fp);
	fprintf(fp, "%d", n);
	fwrite(temp, sizeof(stu), n, fp);

	FreePointer(&temp);
	fclose(fp);
}

void prompt()//提示信息
{
	cout << "1--Input Information" << endl;
	cout << "2--Search(term&number)" << endl;
	cout << "3--Search(term&name)" << endl;
	cout << "4--Change Information" << endl;
	cout << "5--Insert Information" << endl;
	cout << "6--Sum Sort" << endl;
	cout << "7--Course Sort" << endl;
	cout << "8--Delete Information" << endl;
	cout << "9--Course Information" << endl;
	cout << "10-Output Information" << endl;
	cout << "0--Quit" << endl;
}

int main()
{
	int order;//选择命令
	while (1)
	{
		cin.clear();
		cout << "Please choose：" << endl;
		prompt();
		cin >> order;
		if (ErrorCheck()) { cout << "Input Error!" << endl; continue; }

		switch (order)
		{
		case 0:break;
		case 1:InputInformation(); break;
		case 2:SearchTemplet(0); break;//按学号以及学期搜索
		case 3:SearchTemplet(1); break;//按姓名以及学期搜索
		case 4:Change(); break;
		case 5:Insert(); break;
		case 6:SortDecSum(); OutputInformation(); break;
		case 7:SortDecSingle(); OutputInformation(); break;
		case 8:DeleteStudentInfo(); break;
		case 9:SubjectInfo(); break;
		case 10:OutputInformation(); break;
		default:cout << "Input Error!" << endl;
		}
		if (order == 0)break;
	}
	return 0;
}