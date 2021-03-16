//7일차 게임기본모듈 ppt슬라이드 61
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void intro_game(void);
void horizontal_slide(int x, int y, char* c2);
void draw_rectangle(int r, int c);
void display_text(int count, int r_count);
void game_control(int* r_c, int rnd);
void gotoxy(int x, int y);
void ramdomfish(void);

char fish[7]; //전역변수로 선언한 물고기 이름

int main(void) {
	int count = 0, rnd;
	int r_count = 0;
	char* target = "<')))>3";
	srand(time(NULL));
	intro_game();
	do {
		system("cls");
		draw_rectangle(20, 15);
		rnd = rand() % 35 + 4;
		gotoxy(rnd, 2);
		printf("%s", target);
		count++;
		display_text(count, r_count);
		ramdomfish();
		game_control(&r_count, rnd);
	} while (count < 10);

	return 0;
}

void intro_game(void) {
	printf("당신도 도시어부!\n\n");
	puts("게임영역 속 물고기를 겨눠 낚시바늘을 던지세요.");
	puts("스페이스 바를 눌러 던질 수 있습니다.\n");
	puts("아무버튼이나 누르면 낚시터로 이동합니다.");
	_getch();
}

void horizontal_slide(int x, int y, char* c2) {
	gotoxy(x, y);
	printf("%s", c2);
	Sleep(50);
	printf("\b\b ");
}

void display_text(int count, int r_count) {
	gotoxy(50, 2);
	printf("스페이스 키를 누르면 낚시바늘이 던져집니다. 바늘은 10개입니다.");
	gotoxy(50, 3);
	printf("Enter키를 누르면 이 물고기를 포기합니다.");
	gotoxy(50, 4);
	printf("바늘은 물고기의 주둥이나 꼬리가 아닌 배에 걸려야합니다.");
	gotoxy(50, 6);
	printf("---------");
	gotoxy(50, 7);
	printf("횟수 : %d", count);
	gotoxy(50, 8);
	printf("성공 : %d", r_count);
	gotoxy(50, 9);
	printf("---------");
}

void game_control(int* r_c, int rnd) {
	int i = 1, k = 1, y;
	char * house = "§", chr;
	do{
		i += k;
		if (i > 43) k = -1;
		else if (i < 3) k = +1;
		horizontal_slide(i+1, 21, house);
	}while (!_kbhit());

	chr = _getch();
	y = 21;
	if (chr == 32) {
		while (y > 2) {
			y -= 1;
			gotoxy(i + 1, y);
			printf(": ");
			Sleep(50);
			printf("\b  ");
		}
		if ((rnd <= i) && (i <= (rnd + 4))) {
			gotoxy(rnd, 2);
			printf("▒▒▒▒");
			gotoxy(50, 8);
			
			printf("%s을(를) 낚았습니다!", fish);
			Sleep(50);
			*r_c = *r_c + 1;
		}
		gotoxy(1, 24);
		puts("아무키나 눌러 계속 진행하세요.");
		_getch();
	}
}

//물고기 이름 랜덤으로 선택
void ramdomfish() {

	switch (rand() % 10 + 1) {
	case 1: strcpy(fish, "붕어"); break;
	case 2: strcpy(fish, "고등어"); break;
	case 3: strcpy(fish, "청새치"); break;
	case 4: strcpy(fish, "참치"); break;
	case 5: strcpy(fish, "날치"); break;
	case 6: strcpy(fish, "우럭"); break;
	case 7: strcpy(fish, "메기"); break;
	case 8: strcpy(fish, "광어"); break;
	case 9: strcpy(fish, "피라미"); break;
	case 10: strcpy(fish, "둥가리"); break;
	}

}

void draw_rectangle(int r, int c) {
	int i, j, k;
	unsigned char a = 0xa6, b[7];
	for (i = 1; i < 7; i++) b[i] = 0xa0 + i;

	printf("%c%c", a, b[3]);
	for (i = 0; i < c; i++) {
		for (k = 0; k < 3; k++) printf("%c%c", a, b[1]);
	}
	printf("%c%c", a, b[4]);
	printf("\n");

	for (i = 0; i < r; i++) {
		printf("%c%c", a, b[2]);
		for (j = 0; j < c; j++) {
			if (i == r - 1) {
				printf("   "); 
			}
			else {
				if (i % 2 == 0) printf("  ~");
				else printf(" ~ ");
			}
		}
		if((i!=3&&(0<=i&&i<=7))) printf("%c%c", a, b[2]);
		printf("%c%c", a, b[2]); printf("\n");
	}

	printf("%c%c", a, b[6]);
	for (i = 0; i < c; i++) {
		for (k = 0; k < 3; k++) {
			printf("%c%c", a, b[1]);
		}
	}
	printf("%c%c", a, b[5]); printf("\n");
}


void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}