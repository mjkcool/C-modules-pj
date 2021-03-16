#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define STOCK 20 //�ִ� ��������

struct Book {
	char title[25]; //12�ڸ�����
	char author[21]; //10�ڸ�����
	int pages;
};

void input(struct Book *);
void deleteout(struct Book *);
void modify(struct Book *);
void print(struct Book *);

int stock_cnt=0;
int flg;
int i;

int main() {
	struct Book book_infos[STOCK];

	do {
		puts("\n     * * * * * ���� ���� ���α׷� * * * * * \n");
		printf("             �ȦѦ�����������������������������������\n");
		printf("             ���� 1.�ű� ���� �Է¦�\n             ���� 2.���� ���� ������\n");
		printf("             ���� 3.���� ���� ������\n             ���� 4.���� ��� ���⦢\n");
		printf("             ���� 0.������        ��\n");
		printf("             �Ʀզ�����������������������������������");
		printf("\n\n�� ���Ͻô� ������ �Է����ּ��� : ");
		scanf("%d", &flg); 
		printf("..............................................\n\n");
		switch (flg) {
		case 1: input(book_infos); break;
		case 2: deleteout(book_infos); break;
		case 3: modify(book_infos); break;
		case 4: print(book_infos); break;
		case 0: printf("���α׷��� �����մϴ�"); return 0;
		}
		getchar(); printf("\n..............................................\n\n\n\n\t\t�ƹ�Ű�� �����ø� �޴��� �̵��մϴ�.");
		getchar(); system("cls");
	} while (flg != 0);

	return 0;
}

void input(struct Book* book_infos) {
	printf("���� ��� ȭ���Դϴ�.\n���� ���� ���������� �Է��� �ּ���(�������X, ����� ����)\n");
	scanf("%s %s %d", book_infos[stock_cnt].title, book_infos[stock_cnt].author, &book_infos[stock_cnt].pages);
	puts("����Ǿ����ϴ�."); stock_cnt++;
}

void deleteout(struct Book* book_infos) {
	puts("���� ���� ȭ���Դϴ�.\n������ ��ȣ�� �Է����ּ���.\n");
	print(book_infos);
	printf("\n��ȣ : "); scanf("%d", &flg);

	if (flg > stock_cnt) {
		printf("�ش� ������ �����ϴ�.");
		return;
	}
	for (i = flg-1; i < stock_cnt-1; i++) 
		book_infos[i] = book_infos[i + 1];

	puts("�����Ǿ����ϴ�."); stock_cnt--;
}

void modify(struct Book* book_infos) {
	int flg2, flg4; char flg3[7];

	if (stock_cnt == 0) {
		printf("������ �����ϴ�."); return;
	}
	
	puts("���� ���� ȭ���Դϴ�.\n������ ��ȣ�� �Է����ּ���.\n");
	print(book_infos);
	printf("\n��ȣ : "); scanf("%d", &flg);

	if (flg > stock_cnt) {
		printf("�ش� ������ �����ϴ�.");
		return;
	}
	
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0: strcpy(flg3, "����"); break;
		case 1: strcpy(flg3, "�۰�"); break;
		case 2: strcpy(flg3, "������"); break;
		}

		printf("\n%s�� ������ 1�� �Է�(�̼����� �ƹ�Ű)>", flg3);
		scanf("%d", &flg2);
		if (flg2 == 1) {
			printf("������ %s �Է�(12���̳�) : ", flg3);
			switch(i){ 
			case 0: scanf("%s", book_infos[flg-1].title); break;
			case 1: scanf("%s", book_infos[flg-1].author); break;
			case 2: scanf("%d", &book_infos[flg-1].pages); 
			}
			printf("%s ���� �Ϸ�!", flg3);
		}
	}
	
}

void print(struct Book *book_infos) {
	puts("\n �������");
	printf("������������������������\n");
	for (i = 0; i < stock_cnt; i++) {
		printf("%03d[ %-12s(%s) - %-3dp ]\n----------------------------------------------\n", i+1, (book_infos + i)->title, (book_infos + i)->author, (book_infos + i)->pages);
	}
}