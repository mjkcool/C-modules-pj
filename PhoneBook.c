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
		//메뉴 표시
		printf("\n【 전화번호 관리 】☎ ☏ ☎ ☏ ☎ ☏ ☎ ☏ ☎ \n┏━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┓\n");
		printf("┃ ①보기 ┃ ②등록 ┃ ③수정 ┃ ④삭제 ┃ ⑤종료 ┃\n┗━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┛");
		printf("\n  메뉴 선택 【 】\b\b\b");
		scanf("%d", &menu);
		printf("\n〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");

		switch (menu) {
		case 1: output_list(book); break;
		case 2: add(); break;
		case 3: modify(); break;
		case 4: remove_(); break;
		case 5: return 0;
		default:printf("\n잘못된 번호입니다. 다시 입력해주세요.\n");
		}
		getchar();
		printf("\n〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
		printf("▷계속하려면 아무키나 누르세요.");
		getchar();  system("cls");
	} while (menu != 5);

	return 0;
}

//주소록 정보 추가 함수
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

		printf("\n등록할 이름(3글자이하): "); scanf("%s", temp.name);
		printf("전화번호: "); scanf("%s", temp.no);

		fwrite(&temp, sizeof(struct phone), 1, fp);

		printf("\n'%s'님에 대한 정보 등록 완료\n", temp.name);

		size++;
	}
	else if(size>=MAX)
		printf("\n전화번호부가 꽉 찼습니다. (%d)", MAX);

	fflush(fp);
	fclose(fp);
}

//주소록 정보 출력 함수
void output_list(struct phone book[]) {
	int tmp; char name[7];	
	printf("\n검색하시려면 1, 전체목록을 보려면 아무키나 입력하세요 [ ]\b\b"); getchar();
	scanf("%d", &tmp);

	int pos = -1;

	if (tmp == 1) {
		printf("\n검색할 이름을 입력하세요 : ");
		scanf("%s", name);
		pos = returnPosition(name);
	}

	FILE* fp = fopen(filename, "r"); //f_name의 파일을 읽기용으로 열기
	if (fp == NULL) {
		printf("\n주소록이 비어있습니다. 정보를 추가해주세요.\n"); return;
	}
	int position;
	fseek(fp, 0, SEEK_END);
	position = ftell(fp);
	size = position / sizeof(struct phone);
	rewind(fp);

	int cnt=0;
	//검색
	if (tmp == 1) {
		if (pos >=0) {
			printf("\n┏━━━━━━━┯━━━━━━━━━━━━━━┓\n");
			for (int j = 0; j < size; j++) {
				//fp에 연결된 파일에서 정보를 읽어옴
				fread(&book[j], sizeof(struct phone), 1, fp);
				if (strcmp(name, book[j].name) == 0) {
					printf("┃%7s│%14s┃\n", book[j].name, book[j].no);
					cnt++;
				} 
			}
			printf("┗━━━━━━━┷━━━━━━━━━━━━━━┛\n");
			printf(" 검색결과:%2d개\n", cnt);
		}
		else if(pos==-1) printf("정보가 없습니다.\n");
		fclose(fp);
		return;
	}
	
	printf("\n┏━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃  전화번호부 목록(%2d) ┃\n", size);
	printf("┠───────┬──────────────┨\n");
	for (int i = 0; i < size; i++) {
		//fp에 연결된 파일에서 정보를 읽어옴
		fscanf(fp, "%s %s", book[i].name, book[i].no);
		printf("┃%7s│%14s┃\n", book[i].name, book[i].no);
	}
	printf("┗━━━━━━━┷━━━━━━━━━━━━━━┛\n");

	fclose(fp);
}

//삭제 함수
void remove_() {
	int i;
	
	char name[7];

	FILE*fp = fopen(filename, "r"); 
	if (fp == NULL) {
		printf("\n파일 열기에 실패했습니다.\n"); fclose(fp); return;
	}
	int position;
	fseek(fp, 0, SEEK_END);
	position = ftell(fp);
	size = position / sizeof(struct phone);
	rewind(fp);

	printf("\n삭제할 정보의 이름 : "); scanf("%s", name);
	//삭제와정렬
	int del_pos = returnPosition(name);//삭제할 이름의 위치
	if (del_pos >= 0) {
		fclose(fp); deleteRecord(del_pos);
		printf("%s - 정보를 삭제하였습니다.", name);
		size--;
	}
	else if(del_pos == -1) {
		printf("%s는 등록된 이름이 아닙니다.", name);
	}
	fclose(fp);
}

void deleteRecord(int del_pos) {
	//읽어온 파일을 임시 저장
	struct phone temp;

	//기존 파일을 읽기
	FILE*fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\n파일 열기에 실패했습니다.\n"); return;
	}

	char filename2[80] = "PhoneBook_T.txt";

	//기록할 새 파일 불러오기
	FILE*fp2 = fopen(filename2, "w");
	if (fp2 == NULL) {
		printf("\n파일 열기에 실패했습니다.\n"); return;
	}

	//새 파일에 정보 기록
	for (int i = 0; i < size; i++) {
		if (i == del_pos) continue;//삭제할 행만 뺀다.
		fseek(fp, sizeof(struct phone) * i, SEEK_SET);
		fread(&temp, sizeof(struct phone), 1, fp);
		fwrite(&temp, sizeof(struct phone), 1, fp2);
	}
	fclose(fp); fclose(fp2);

	int status;
	//이전 파일 삭제
	status = remove(filename);
	if (status == -1) perror("수정 오류(파일 삭제 실패)\n");

	//새 파일의 이름 변경
	status = rename(filename2, filename);
	if (status == -1) perror("수정 오류(파일 이름 변경 실패)\n");
}

//수정하기
void modify() {
	struct phone temp;
	FILE* fp = fopen(filename, "r+b");
	if (fp == NULL) {
		printf("\n파일 열기에 실패했습니다.\n"); return;
	}

	printf("\n수정할 정보의 이름을 입력하세요: ");
	scanf("%s", temp.name); 
	int del_pos=returnPosition(temp.name);
	if (del_pos >= 0) {
		printf("\n[수정정보]\n이름 입력: "); scanf("%s", temp.name);
		printf("전화번호 입력: "); scanf("%s", temp.no);
		
		fseek(fp, sizeof(struct phone)*del_pos, SEEK_SET);
		fwrite(&temp, sizeof(struct phone), 1, fp);

		printf("\n정보를 수정하였습니다.", temp.name);
	}
	else if (del_pos == -1) {
		printf("\n%s는 등록된 이름이 아닙니다.", temp.name);
	}
	fclose(fp);
}

//해당 이름을 가진 위치 반환
int returnPosition(char name[]) {
	struct phone temp;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\n파일 열기에 실패했습니다.\n"); return;
	}

	for (int i = 0; i < size; i++) {
		fread(&temp, sizeof(struct phone), 1, fp);
		if (strcmp(name, temp.name) == 0) { //position=i
			fclose(fp); return i;
		}
	}
	fclose(fp); return -1;
}
