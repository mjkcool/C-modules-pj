//9���� ����-�ٵ�-1 ppt �����̵� 77

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define box_length 15 //������ ����(�¿� ����)
#define box_height 15 //�ٴ��� ����(���� ����)

void intro_game(void);
void game_control(void);
void gotoxy(int x, int y);
int left_right_move(void);
void move_down(int x);
void draw_rectangle(int c, int r);
int max_block(void);

int block_stack[box_length * 2 + 1] = { 0 }; //�ش���ġ�� ���� 0���� �ʱ�ȭ

int main(void) {
	intro_game();
	game_control();
	gotoxy(1, box_height+3);
	if (max_block() >= 10) {
		printf("     GAME CLEAR!                           \n                                     \n");
	}
	else {
		printf("     GAME OVER                             \n                                     \n");
	}
	return 0;
}

void intro_game(void) {
	system("cls");
	printf("���� �ױ�  \n\n");
	printf("������ �¿�� ������ �� �����̽�Ű�� ������\n");
	printf("������ ������ �ٴڿ� ���Դϴ�.\n\n");
	printf("�ƹ�Ű�� ������ ������ �����մϴ�. \n");
	_getch();
}

void game_control(void) {
	int x, count = 0;
	system("cls");
	draw_rectangle(box_length, box_height);
	gotoxy(box_length*2+5,3);
	printf("������ ����: %2d", box_height);
	gotoxy(1, box_height + 3);
	printf("�����̽� Ű�� ������ ������ ��������\n�ٴڿ� ���Դϴ�.\n");

	while (count < box_height) {
		gotoxy(box_length * 2 + 5, 4);
		printf("�õ��� Ƚ��: %2d", count +1);
		gotoxy(box_length * 2 + 5, 5);
		printf("���� ���ϼ� : %2d", (max_block()==14)?15: max_block());
		x = left_right_move();
		move_down(x);
		count++;
		_getch();
	}
}

int left_right_move(void) {
	int x = 3, y = 2, temp = 2;
	do {
		x += temp;
		if (x > (box_length * 2 -2)) //x���� �ִ밪 ����
			temp = -2;
		if (x < 3) {
			x = 3; temp = 2;
		}
		gotoxy(x, y);
		printf("��");
		Sleep(500); //������ �¿�� �����̴� �ӵ�
		gotoxy(x, y);
		printf("  ");
	} while (!_kbhit());
	block_stack[x] += 1;
	return x;
}

void move_down(int x) {
	int y;
	for (y = 2; y < box_height + 2 - block_stack[x]; y += 1) {
		gotoxy(x, y);
		printf("��");
		Sleep(20);
		gotoxy(x, y);
		printf("  ");
		Sleep(10);
	}
	gotoxy(x, box_height + 2 - block_stack[x]);
	printf("��");
}

int max_block(void) {
	int i, max = 0;
	for (i = 1; i < box_height * 2 + 1; i++) {
		if (max <= block_stack[i]) max = block_stack[i];
	}
	return max;
}

void draw_rectangle(int c, int r) {
	int i, j, k;
	unsigned char a = 0xa6;
	unsigned char b[7];
	for (i = 1; i < 7; i++) b[i] = 0xa0 + i;
	printf("%c%c", a, b[3]);
	for(i=0; i<c*2; i++) printf("%c%c", a, b[1]);
	printf("%c%c", a, b[4]);
	puts("");
	for (i = 0; i < r; i++) {
		printf("%c%c", a, b[2]);
		for (j = 0; j < c; j++) printf("  ");
		if(1<=i&&i<=3) printf("%c%c", a, b[2]);
		printf("%c%c", a, b[2]);
		puts("");
	}
	printf("%c%c", a, b[6]);
	for (i = 0; i < c * 2; i++) printf("%c%c", a, b[1]);
	printf("%c%c", a, b[5]); puts("");
}

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}