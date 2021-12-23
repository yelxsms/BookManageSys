/*图书管理系统，每本书具有编号，书名，作者，余量信息，每位读者具有姓名，所借的书的相关信息，所借书的数量。所借的书
又具有书名和借阅日期，归还日期信息，规定每个人最多借五本书*/



#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Windows.h"


typedef struct book
{
	int num;
	char name[20];
	char author[20];
	int qunatity;
	//int flag;

};

typedef struct borrow
{
	char name[20];
	char borrow_date;
	char return_date;
};

typedef struct personalin
{
	char name[20];
	struct borrow borrow_list[5];
	int personborrow_count;

};

void showmenu();
void add_new_book();
void add_new_reader();
void find_book();
int BinarySearch(struct book s[], int n, int key);
void borrow_book();
void return_book();
void check_reader();
void overlook();


int book_count = 1;
int person_count = 0;

struct book book_list[99];
struct personalin person_list[99];


int main()
{
	printf("\n欢迎来到图书管理系统！\n");
	int choice=-1;
	while (choice != 0)
	{
		showmenu();
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			add_new_book();
			break;
		case 2:
			find_book();
			break;
		case 3:
			borrow_book();
			break;
		case 4:
			return_book();
			break;
		case 5:
			add_new_reader();
			break;
		case 6:
			check_reader();
			break;
		case 7:
			overlook();
			break;
		case 0:
			printf("退出系统！");
		default: printf("请选择正确的功能！\n");
		}
	}
	exit(0);
}


void showmenu()
{
	Sleep(1500);
	printf("\n功能选择:\n");
	printf("\n1.图书采编\t2.图书查询\t3.图书借阅\t4.图书归还\n5.增加读者\t6.查看读者信息\t7.图书概览\t0.退出系统\n");
	printf("\n请选择功能;");
}

void add_new_book()
{
	printf("图书采编\n");
	printf("请输入增加的图书的编号：\n");
	int temp,flag=0;
	int check=scanf("%d", &temp);
	if (check==1)//合法性检查
	{
		for (int i = 0; i < book_count; i++)
		{
			if (temp == book_list[i].num)
			{
				printf("图书馆内已有此书。数量增加\n");
				book_list[i].qunatity++;
				flag = 1;
			}			
		}
		if (flag == 0)
		{
			book_list[book_count].num = temp;
			printf("请输入书名：");
			scanf("%s", &book_list[book_count].name);
			printf("请输入作者：");
			scanf("%s", &book_list[book_count].author);
			book_list[book_count].qunatity = 1;			
			int buynumber;
			printf("请输入采购数量:");
			scanf("%d", &buynumber);
			//book_list[book_count].flag = 1;
			book_list[book_count].qunatity = buynumber;
			printf("图书采编成功！\n");
			book_count++;
		}

	}
	else
	{
		printf("请输入正确的书号！");
		check = 0;
	}
}

//增加读者
void add_new_reader()
{
	char temp[10] = { 0 };
	printf("输入姓名：");
	scanf("%s", &temp);
	int flag = 0;
	for (int i = 0; i < person_count; i++)
	{
		if (strcmp(temp, person_list[person_count].name) == 1)
		{
			printf("已有此读者。\n");
			flag = 1;
		}
	}
	if (flag == 0)
	{
		strcpy(person_list[person_count].name, temp);
		person_list[person_count].personborrow_count = 0;
		person_count++;
		printf("读者增加成功！\n");
	}
	

}

//查找
void find_book() {
	//先对书籍从小到大进行插入排序
	for (int i = 2; i < book_count; i++)
	{
		if (book_list[i].num < book_list[i - 1].num)
		{
			int j;
			book_list[0] = book_list[i];
			book_list[i] = book_list[i - 1];
			for (j = i - 1; book_list[0].num < book_list[j].num; j--)
			{
				book_list[j + 1] = book_list[j];
			}
			book_list[j + 1] = book_list[0];
		}
	}
	//输出排序好的序列
	/*for (int i = 0; i < book_count; i++)
	{
		printf("%d  ", book_list[i].num);
	}*/
	//查找书籍
	int find_num;
	printf("输入需要查询的书籍编号：");
	scanf("%d", &find_num);
	int pos = BinarySearch(book_list, book_count, find_num);
	if (pos >= 0)
		printf("查找成功！\n书籍的信息如下：\n编号：%d\n书名：%s\t作者：%s\t余量：%d"
			, book_list[pos].num, book_list[pos ].name, book_list[pos].author, book_list[pos].qunatity);
	else
		printf("查找失败！\n");
}

//折半查找
int BinarySearch(struct book s[], int n, int key)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (s[mid].num == key)
			return mid;
		else if (s[mid].num > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

//借阅书籍
void borrow_book()
{
	printf("请输入需要借阅的书籍的编号;");
	int borrow_num;
	scanf("%d", &borrow_num);
	int pos = BinarySearch(book_list, book_count, borrow_num);
	if (pos >= 0) {
		if (book_list[pos].qunatity > 0) {
			printf("成功找到此书！\n请输入借阅人的姓名：");
			char borrow_person[10] = { 0 };
			scanf("%s",&borrow_person);
			int flag = 0;
			for (int i = 0; i < person_count; i++)
			{
				if (strcmp(person_list[i].name, borrow_person) == 1) {
					flag = 1;
					strcpy(person_list[i].borrow_list[person_list[i].personborrow_count].name, book_list[pos].name);
					printf("请输入借阅日期：");
					//char Borrow_date[10] = { 0 };
					scanf("%s", &person_list[i].borrow_list[person_list[i].personborrow_count].borrow_date);
					//strcpy(person_list[i].borrow_list[person_list[i].personborrow_count].borrow_date, Borrow_date);
					printf("请输入归还日期：");
					//char Return_date[10] = { 0 };
					scanf("%s", &person_list[i].borrow_list[person_list[i].personborrow_count].return_date);
					//strcpy(person_list[i].borrow_list[person_list[i].personborrow_count].return_date, Return_date);
					person_list[i].personborrow_count++;
					printf("图书借阅成功！\n");
					//从图书馆中删除一本被借阅的图书
					book_list[pos].qunatity--;
				}					
			}
			if(flag==0)
				printf("未找到此读者，请在系统录入后再借阅。\n");

		}
		else
			printf("此书余量不足。请联系管理员采编。\n");
	}
	else
		printf("未找到此书。\n");

}

//归还书籍
void return_book()
{
	printf("请输入归还图书的编号：");
	int returnbook_num=0;
	scanf("%d", &returnbook_num);
	int pos = BinarySearch(book_list, book_count, returnbook_num);
	if (pos >= 0)
	{
		printf("成功找到此书\n请输入还书者的姓名;");
		char return_person[10] = { 0 };
		scanf("%s", &return_person);
		int flag = 0;
		for (int i = 0; i < person_count; i++)
		{
			if (strcmp(person_list[i].name, return_person) == 1) {
				flag = 1;
				//消除借阅者的借阅记录
				for (int j = 0; j < person_list[i].personborrow_count; j++)
				{
					if (strcmp(person_list[i].borrow_list[j].name, book_list[pos + 1].name) == 1)
					{
						//struct borrow temp;
						for (int k = j; k < person_list[i].personborrow_count; k++)
						{
							person_list[i].borrow_list[j] = person_list[i].borrow_list[j + 1];
						}
					}
				}
				//此书数量加一
				book_list[pos + 1].qunatity++;
				printf("图书归还成功。\n");
			}
		}
		if(flag==0)
			printf("未找到此读者，请在系统录入后再借阅。\n");

	}
	else
		printf("未找到此书。\n");
}

void check_reader()
{
	printf("请输入需要查询的读者:");
	char check_reader[10] = { 0 };
	scanf("%s",&check_reader);
	for (int i = 0; i < person_count; i++)
	{
		if (strcmp(person_list[i].name, check_reader) == 1)
		{
			printf("\n读者的相关信息为:\n借阅的书籍：\t借阅日期\t归还日期\n");
			printf("%s\t%s\t%s\n",person_list[i].borrow_list[person_list[i].personborrow_count].name, 
				person_list[i].borrow_list[person_list[i].personborrow_count].borrow_date, 
				person_list[i].borrow_list[person_list[i].personborrow_count].return_date);
			person_list[i].personborrow_count++;
		}
	}
}
void overlook()
{
	printf("书号\t书名\t作者\t余量\n");
	for (int i = 1; i < book_count; i++)
	{
		printf("%d\t%s\t%s\t%d\n", book_list[i].num, book_list[i].name, book_list[i].author, book_list[i].qunatity);
	}
 }
