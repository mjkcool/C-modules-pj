#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 15

struct phone {
	char name[7];
	char no[14];
};

void add();
void output_list(struct phone book[]);
void remove_();
int returnPosition(char name[]);
void deleteRecord(int del_pos);
void modify();

int size;
char filename[80] = "PhoneBook.txt";

int main() {
	struct phone book[MAX];
	int menu;
	do {
		//�޴� ǥ��
		printf("\n�� ��ȭ��ȣ ���� ���� �� �� �� �� �� �� �� �� \n��������������������������������������������������������������������������������������������\n");
		printf("�� �纸�� �� ���� �� ����� �� ����� �� ������ ��\n��������������������������������������������������������������������������������������������");
		printf("\n  �޴� ���� �� ��\b\b\b");
		scanf("%d", &menu);
		printf("\n�����������������������������\n");

		switch (menu) {
		case 1: output_list(book); break;
		case 2: add(); break;
		case 3: modify(); break;
		case 4: remove_(); break;
		case 5: return 0;
		default:printf("\n�߸��� ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n");
		}
		getchar();
		printf("\n�����������������������������\n");
		printf("������Ϸ��� �ƹ�Ű�� ��������.");
		getchar();  system("cls");
	} while (menu != 5);

	return 0;
}

//�ּҷ� ���� �߰� �Լ�
void add() {
	struct phone temp;
	FILE*fp = fopen(filename, "a");
	if (fp == NULL) {
		printf("\nOpen file error!\n"); exit(1);
	}
	fseek(fp, 0, SEEK_END);
	int totalsize = ftell(fp);
	size = totalsize / sizeof(struct phone);

	if (size < MAX) {

		printf("\n����� �̸�(3��������): "); scanf("%s", temp.name);
		printf("��ȭ��ȣ: "); scanf("%s", temp.no);

		fwrite(&temp, sizeof(struct phone), 1, fp);

		printf("\n'%s'�Կ� ���� ���� ��� �Ϸ�\n", temp.name);

		size++;
	}
	else if(size>=MAX)
		printf("\n��ȭ��ȣ�ΰ� �� á���ϴ�. (%d)", MAX);

	fflush(fp);
	fclose(fp);
}

//�ּҷ� ���� ��� �Լ�
void output_list(struct phone book[]) {
	int tmp; char name[7];	
	printf("\n�˻��Ͻ÷��� 1, ��ü����� ������ �ƹ�Ű�� �Է��ϼ��� [ ]\b\b"); getchar();
	scanf("%d", &tmp);

	int pos = -1;

	if (tmp == 1) {
		printf("\n�˻��� �̸��� �Է��ϼ��� : ");
		scanf("%s", name);
		pos = returnPosition(name);
	}

	FILE* fp = fopen(filename, "r"); //f_name�� ������ �б������ ����
	if (fp == NULL) {
		printf("\n�ּҷ��� ����ֽ��ϴ�. ������ �߰����ּ���.\n"); return;
	}
	int position;
	fseek(fp, 0, SEEK_END);
	position = ftell(fp);
	size = position / sizeof(struct phone);
	rewind(fp);

	int cnt=0;
	//�˻�
	if (tmp == 1) {
		if (pos >=0) {
			printf("\n������������������������������������������������\n");
			for (int j = 0; j < size; j++) {
				//fp�� ����� ���Ͽ��� ������ �о��
				fread(&book[j], sizeof(struct phone), 1, fp);
				if (strcmp(name, book[j].name) == 0) {
					printf("��%7s��%14s��\n", book[j].name, book[j].no);
					cnt++;
				} 
			}
			printf("������������������������������������������������\n");
			printf(" �˻����:%2d��\n", cnt);
		}
		else if(pos==-1) printf("������ �����ϴ�.\n");
		fclose(fp);
		return;
	}
	
	printf("\n������������������������������������������������\n");
	printf("��  ��ȭ��ȣ�� ���(%2d) ��\n", size);
	printf("������������������������������������������������\n");
	for (int i = 0; i < size; i++) {
		//fp�� ����� ���Ͽ��� ������ �о��
		fscanf(fp, "%s %s", book[i].name, book[i].no);
		printf("��%7s��%14s��\n", book[i].name, book[i].no);
	}
	printf("������������������������������������������������\n");

	fclose(fp);
}

//���� �Լ�
void remove_() {
	int i;
	
	char name[7];

	FILE*fp = fopen(filename, "r"); 
	if (fp == NULL) {
		printf("\n���� ���⿡ �����߽��ϴ�.\n"); fclose(fp); return;
	}
	int position;
	fseek(fp, 0, SEEK_END);
	position = ftell(fp);
	size = position / sizeof(struct phone);
	rewind(fp);

	printf("\n������ ������ �̸� : "); scanf("%s", name);
	//����������
	int del_pos = returnPosition(name);//������ �̸��� ��ġ
	if (del_pos >= 0) {
		fclose(fp); deleteRecord(del_pos);
		printf("%s - ������ �����Ͽ����ϴ�.", name);
		size--;
	}
	else if(del_pos == -1) {
		printf("%s�� ��ϵ� �̸��� �ƴմϴ�.", name);
	}
	fclose(fp);
}

void deleteRecord(int del_pos) {
	//�о�� ������ �ӽ� ����
	struct phone temp;

	//���� ������ �б�
	FILE*fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\n���� ���⿡ �����߽��ϴ�.\n"); return;
	}

	char filename2[80] = "PhoneBook_T.txt";

	//����� �� ���� �ҷ�����
	FILE*fp2 = fopen(filename2, "w");
	if (fp2 == NULL) {
		printf("\n���� ���⿡ �����߽��ϴ�.\n"); return;
	}

	//�� ���Ͽ� ���� ���
	for (int i = 0; i < size; i++) {
		if (i == del_pos) continue;//������ �ุ ����.
		fseek(fp, sizeof(struct phone) * i, SEEK_SET);
		fread(&temp, sizeof(struct phone), 1, fp);
		fwrite(&temp, sizeof(struct phone), 1, fp2);
	}
	fclose(fp); fclose(fp2);

	int status;
	//���� ���� ����
	status = remove(filename);
	if (status == -1) perror("���� ����(���� ���� ����)\n");

	//�� ������ �̸� ����
	status = rename(filename2, filename);
	if (status == -1) perror("���� ����(���� �̸� ���� ����)\n");
}

//�����ϱ�
void modify() {
	struct phone temp;
	FILE* fp = fopen(filename, "r+b");
	if (fp == NULL) {
		printf("\n���� ���⿡ �����߽��ϴ�.\n"); return;
	}

	printf("\n������ ������ �̸��� �Է��ϼ���: ");
	scanf("%s", temp.name); 
	int del_pos=returnPosition(temp.name);
	if (del_pos >= 0) {
		printf("\n[��������]\n�̸� �Է�: "); scanf("%s", temp.name);
		printf("��ȭ��ȣ �Է�: "); scanf("%s", temp.no);
		
		fseek(fp, sizeof(struct phone)*del_pos, SEEK_SET);
		fwrite(&temp, sizeof(struct phone), 1, fp);

		printf("\n������ �����Ͽ����ϴ�.", temp.name);
	}
	else if (del_pos == -1) {
		printf("\n%s�� ��ϵ� �̸��� �ƴմϴ�.", temp.name);
	}
	fclose(fp);
}

//�ش� �̸��� ���� ��ġ ��ȯ
int returnPosition(char name[]) {
	struct phone temp;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\n���� ���⿡ �����߽��ϴ�.\n"); return;
	}

	for (int i = 0; i < size; i++) {
		fread(&temp, sizeof(struct phone), 1, fp);
		if (strcmp(name, temp.name) == 0) { //position=i
			fclose(fp); return i;
		}
	}
	fclose(fp); return -1;
}
