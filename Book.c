/*ͼ�����ϵͳ��ÿ������б�ţ����������ߣ�������Ϣ��ÿλ���߾����������������������Ϣ����������������������
�־��������ͽ������ڣ��黹������Ϣ���涨ÿ���������屾��*/



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
	printf("\n��ӭ����ͼ�����ϵͳ��\n");
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
			printf("�˳�ϵͳ��");
		default: printf("��ѡ����ȷ�Ĺ��ܣ�\n");
		}
	}
	exit(0);
}


void showmenu()
{
	Sleep(1500);
	printf("\n����ѡ��:\n");
	printf("\n1.ͼ��ɱ�\t2.ͼ���ѯ\t3.ͼ�����\t4.ͼ��黹\n5.���Ӷ���\t6.�鿴������Ϣ\t7.ͼ�����\t0.�˳�ϵͳ\n");
	printf("\n��ѡ����;");
}

void add_new_book()
{
	printf("ͼ��ɱ�\n");
	printf("���������ӵ�ͼ��ı�ţ�\n");
	int temp,flag=0;
	int check=scanf("%d", &temp);
	if (check==1)//�Ϸ��Լ��
	{
		for (int i = 0; i < book_count; i++)
		{
			if (temp == book_list[i].num)
			{
				printf("ͼ��������д��顣��������\n");
				book_list[i].qunatity++;
				flag = 1;
			}			
		}
		if (flag == 0)
		{
			book_list[book_count].num = temp;
			printf("������������");
			scanf("%s", &book_list[book_count].name);
			printf("���������ߣ�");
			scanf("%s", &book_list[book_count].author);
			book_list[book_count].qunatity = 1;			
			int buynumber;
			printf("������ɹ�����:");
			scanf("%d", &buynumber);
			//book_list[book_count].flag = 1;
			book_list[book_count].qunatity = buynumber;
			printf("ͼ��ɱ�ɹ���\n");
			book_count++;
		}

	}
	else
	{
		printf("��������ȷ����ţ�");
		check = 0;
	}
}

//���Ӷ���
void add_new_reader()
{
	char temp[10] = { 0 };
	printf("����������");
	scanf("%s", &temp);
	int flag = 0;
	for (int i = 0; i < person_count; i++)
	{
		if (strcmp(temp, person_list[person_count].name) == 1)
		{
			printf("���д˶��ߡ�\n");
			flag = 1;
		}
	}
	if (flag == 0)
	{
		strcpy(person_list[person_count].name, temp);
		person_list[person_count].personborrow_count = 0;
		person_count++;
		printf("�������ӳɹ���\n");
	}
	

}

//����
void find_book() {
	//�ȶ��鼮��С������в�������
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
	//�������õ�����
	/*for (int i = 0; i < book_count; i++)
	{
		printf("%d  ", book_list[i].num);
	}*/
	//�����鼮
	int find_num;
	printf("������Ҫ��ѯ���鼮��ţ�");
	scanf("%d", &find_num);
	int pos = BinarySearch(book_list, book_count, find_num);
	if (pos >= 0)
		printf("���ҳɹ���\n�鼮����Ϣ���£�\n��ţ�%d\n������%s\t���ߣ�%s\t������%d"
			, book_list[pos].num, book_list[pos ].name, book_list[pos].author, book_list[pos].qunatity);
	else
		printf("����ʧ�ܣ�\n");
}

//�۰����
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

//�����鼮
void borrow_book()
{
	printf("��������Ҫ���ĵ��鼮�ı��;");
	int borrow_num;
	scanf("%d", &borrow_num);
	int pos = BinarySearch(book_list, book_count, borrow_num);
	if (pos >= 0) {
		if (book_list[pos].qunatity > 0) {
			printf("�ɹ��ҵ����飡\n����������˵�������");
			char borrow_person[10] = { 0 };
			scanf("%s",&borrow_person);
			int flag = 0;
			for (int i = 0; i < person_count; i++)
			{
				if (strcmp(person_list[i].name, borrow_person) == 1) {
					flag = 1;
					strcpy(person_list[i].borrow_list[person_list[i].personborrow_count].name, book_list[pos].name);
					printf("������������ڣ�");
					//char Borrow_date[10] = { 0 };
					scanf("%s", &person_list[i].borrow_list[person_list[i].personborrow_count].borrow_date);
					//strcpy(person_list[i].borrow_list[person_list[i].personborrow_count].borrow_date, Borrow_date);
					printf("������黹���ڣ�");
					//char Return_date[10] = { 0 };
					scanf("%s", &person_list[i].borrow_list[person_list[i].personborrow_count].return_date);
					//strcpy(person_list[i].borrow_list[person_list[i].personborrow_count].return_date, Return_date);
					person_list[i].personborrow_count++;
					printf("ͼ����ĳɹ���\n");
					//��ͼ�����ɾ��һ�������ĵ�ͼ��
					book_list[pos].qunatity--;
				}					
			}
			if(flag==0)
				printf("δ�ҵ��˶��ߣ�����ϵͳ¼����ٽ��ġ�\n");

		}
		else
			printf("�����������㡣����ϵ����Ա�ɱࡣ\n");
	}
	else
		printf("δ�ҵ����顣\n");

}

//�黹�鼮
void return_book()
{
	printf("������黹ͼ��ı�ţ�");
	int returnbook_num=0;
	scanf("%d", &returnbook_num);
	int pos = BinarySearch(book_list, book_count, returnbook_num);
	if (pos >= 0)
	{
		printf("�ɹ��ҵ�����\n�����뻹���ߵ�����;");
		char return_person[10] = { 0 };
		scanf("%s", &return_person);
		int flag = 0;
		for (int i = 0; i < person_count; i++)
		{
			if (strcmp(person_list[i].name, return_person) == 1) {
				flag = 1;
				//���������ߵĽ��ļ�¼
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
				//����������һ
				book_list[pos + 1].qunatity++;
				printf("ͼ��黹�ɹ���\n");
			}
		}
		if(flag==0)
			printf("δ�ҵ��˶��ߣ�����ϵͳ¼����ٽ��ġ�\n");

	}
	else
		printf("δ�ҵ����顣\n");
}

void check_reader()
{
	printf("��������Ҫ��ѯ�Ķ���:");
	char check_reader[10] = { 0 };
	scanf("%s",&check_reader);
	for (int i = 0; i < person_count; i++)
	{
		if (strcmp(person_list[i].name, check_reader) == 1)
		{
			printf("\n���ߵ������ϢΪ:\n���ĵ��鼮��\t��������\t�黹����\n");
			printf("%s\t%s\t%s\n",person_list[i].borrow_list[person_list[i].personborrow_count].name, 
				person_list[i].borrow_list[person_list[i].personborrow_count].borrow_date, 
				person_list[i].borrow_list[person_list[i].personborrow_count].return_date);
			person_list[i].personborrow_count++;
		}
	}
}
void overlook()
{
	printf("���\t����\t����\t����\n");
	for (int i = 1; i < book_count; i++)
	{
		printf("%d\t%s\t%s\t%d\n", book_list[i].num, book_list[i].name, book_list[i].author, book_list[i].qunatity);
	}
 }
