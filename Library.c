#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define STOCK 20 //최대 도서개수

struct Book {
	char title[25]; //12자리까지
	char author[21]; //10자리까지
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
		puts("\n     * * * * * 도서 관리 프로그램 * * * * * \n");
		printf("             ┍┭─────────────────┐\n");
		printf("             ││ 1.신규 도서 입력│\n             ││ 2.도서 정보 삭제│\n");
		printf("             ││ 3.도서 정보 수정│\n             ││ 4.도서 목록 보기│\n");
		printf("             ││ 0.나가기        │\n");
		printf("             ┕┵─────────────────┘");
		printf("\n\n◈ 원하시는 동작을 입력해주세요 : ");
		scanf("%d", &flg); 
		printf("..............................................\n\n");
		switch (flg) {
		case 1: input(book_infos); break;
		case 2: deleteout(book_infos); break;
		case 3: modify(book_infos); break;
		case 4: print(book_infos); break;
		case 0: printf("프로그램을 종료합니다"); return 0;
		}
		getchar(); printf("\n..............................................\n\n\n\n\t\t아무키나 누르시면 메뉴로 이동합니다.");
		getchar(); system("cls");
	} while (flg != 0);

	return 0;
}

void input(struct Book* book_infos) {
	printf("도서 등록 화면입니다.\n제목 저자 페이지수를 입력해 주세요(내용띄어쓰기X, 띄어쓰기로 구분)\n");
	scanf("%s %s %d", book_infos[stock_cnt].title, book_infos[stock_cnt].author, &book_infos[stock_cnt].pages);
	puts("저장되었습니다."); stock_cnt++;
}

void deleteout(struct Book* book_infos) {
	puts("도서 삭제 화면입니다.\n삭제할 번호를 입력해주세요.\n");
	print(book_infos);
	printf("\n번호 : "); scanf("%d", &flg);

	if (flg > stock_cnt) {
		printf("해당 도서가 없습니다.");
		return;
	}
	for (i = flg-1; i < stock_cnt-1; i++) 
		book_infos[i] = book_infos[i + 1];

	puts("삭제되었습니다."); stock_cnt--;
}

void modify(struct Book* book_infos) {
	int flg2, flg4; char flg3[7];

	if (stock_cnt == 0) {
		printf("도서가 없습니다."); return;
	}
	
	puts("도서 수정 화면입니다.\n수정할 번호를 입력해주세요.\n");
	print(book_infos);
	printf("\n번호 : "); scanf("%d", &flg);

	if (flg > stock_cnt) {
		printf("해당 도서가 없습니다.");
		return;
	}
	
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0: strcpy(flg3, "제목"); break;
		case 1: strcpy(flg3, "작가"); break;
		case 2: strcpy(flg3, "페이지"); break;
		}

		printf("\n%s을 수정시 1를 입력(미수정시 아무키)>", flg3);
		scanf("%d", &flg2);
		if (flg2 == 1) {
			printf("수정할 %s 입력(12자이내) : ", flg3);
			switch(i){ 
			case 0: scanf("%s", book_infos[flg-1].title); break;
			case 1: scanf("%s", book_infos[flg-1].author); break;
			case 2: scanf("%d", &book_infos[flg-1].pages); 
			}
			printf("%s 수정 완료!", flg3);
		}
	}
	
}

void print(struct Book *book_infos) {
	puts("\n 도서목록");
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	for (i = 0; i < stock_cnt; i++) {
		printf("%03d[ %-12s(%s) - %-3dp ]\n----------------------------------------------\n", i+1, (book_infos + i)->title, (book_infos + i)->author, (book_infos + i)->pages);
	}
}