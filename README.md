# C-modules-pj
* 개발 기간: 2020.1 ~ 2020.2
* 개요: 방과후C언어 수강 후 복습을 위해 학습한 내용을 토대로 발전시켜 만든 4가지의 모듈 프로그램
* 활용한 문법들: 
문자열, 사용자정의함수, 라이브러리함수, 구조체,
포인터(+구조체포인터), 파일입출력(+2진파일) 등

<br>

## 블록쌓기 게임
### 게임 설명
 좌우로 반복이동하는 사각형 블럭을 아무 키를 눌러 원하는 위치에 떨어뜨린다. 떨어뜨릴 수 있는 블럭의 개수는 15개이며 오른쪽에 블록의 개수와 시도 횟수(블럭이 나타남과 동시에 횟수 증가) 그리고 게임영역의 열 중 가장 많이 쌓인 열의 블럭 개수가 나타난다. 10개 이상을 연달아 쌓은 경우 게임 클리어 메시지가, 그렇지 못한 경우 게임 오버 메시지와 함께 게임이 종료되며 프로그램이 종료된다.

![tetris_play](https://user-images.githubusercontent.com/53461080/112748237-73f30d00-8ff5-11eb-95f6-49e95e0d63a5.gif)  
### function 1
 출력창의 커서 위치를 지정(이동)시키는 함수. 블럭 배치(출력)나 게임 정보와 방법 등의 문자열을 배치하는데 사용됨.
COORD는 x와 y값을 멤버변수로 가지는 구조체이다.
```
void gotoxy(int x, int y) {
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```
### function 2
바닥에 쌓인 블록의 최대 개수를 계산하여 반환하는 함수
```
int max_block(void) {
    int i, max = 0;
    for (i = 1; i < box_height * 2 + 1; i++) { //블럭이 쌓이는 열
        if (max <= block_stack[i]) max = block_stack[i]; //해당 열에 쌓인 개수 비교
    }
    return max;
}
```
### function 3
블럭을 바닥으로 이동시켜 쌓는 함수. 현재 블럭이 위치한 열을 파라미터로 넘겨받아 블럭이 쌓일 y값을 계산한다.  
block_stack[x] = x열에 블록이 쌓인 개수
```
void move_down(int x) {
    int y;
    for (y = 2; y < box_height + 2 - block_stack[x]; y += 1) { 
    //게임영역 세로 높이에서 현재 열에 쌓인 개수를 뺀 만큼까지만 하강. 
        gotoxy(x, y); //커서 배치(x값=열 고정)
        printf("■"); //현재 행에 나타난다.
        Sleep(20); 
        gotoxy(x, y);
        printf("  "); //다음 반복 전 현재 행에서 사라진다.
        Sleep(10); //시간지연을 통해 블럭이 한칸씩 내려가는 것이 반복되어 보인다.
    }
    gotoxy(x, box_height + 2 - block_stack[x]); 
    printf("■"); //최대 높이에 커서 배치 후 블럭이 쌓인다.
}
```
<br>

## 물고기 낚시 게임
### 게임 설명
다양한 라이브러리 함수를 사용하였으며 랜덤 난수와 문자 배열 관련 함수를 적극 활용하였다.
프로그램에 의해 좌우로 반복이동하는 바늘이 타킷인 물고기 문자열과 수직일 때 스페이스키를 눌러 바늘을 발사한다. 바늘이 물고기의 배에 맞아야만 성공으로 인정된다. 게임영역 우측에 시도 횟수와 성공횟수가 표시되며 시도횟수는 10회까지이다. 성공시 랜덤으로 나오는 물고기 이름과 메시지가 표시되고 아무키를 입력하여 이어서 다음회차를 진행한다.  
![fising_play](https://user-images.githubusercontent.com/53461080/112748829-6c356780-8ff9-11eb-9f26-c89b979927fd.png)

#### 사용된 중요 라이브러리 함수
* system("cls") >> 게임 동작을 10번 반복하는 main함수의 do-while문에서 매 회차마다 이전 회차의 출력을 모두 지운다.
* _kbhit() >> 바늘을 좌우로 움직이는 do-while문의 반복문을 중단할 키를 입력받는다(화살을 발사할 경우).
* rand() >> 물고기 이름을 랜덤으로 선택하기 위해 switch문에 사용한다.
* Sleep() >> 반복문이나 함수에서 코드 실행 속도를 지연시켜 문자열과 기호가 움직이는 속도를 코드 내에서 조절할 수 있다.
* _getch() >> 바늘을 던진 후 다음 회차를 이어가기 위해 아무키를 입력받는다.
* strcpy() >> 문자배열 변수에 문자열을 대입한다.

### function 1
타킷 문자열의 위치를 랜덤 배치하는 부분.
```
char* target = "<')))>3"; //타킷 문자열 선언

do{
    ...
    rnd = rand() % 35 + 4; //게임 영역 속의 특정 칸 랜덤 지정
    gotoxy(rnd, 2); //커서의 위치(좌우) 랜덤 배치
    printf("%s", target); //타킷 배치(출력)
    ...
}while (count < 10);
```
### function 2
물고기 이름을 나타내는 문자열을 전역변수로 선언한 다음 함수에서 랜덤 난수를 사용하여 물고기 이름을 랜덤으로 선택해 대입하는 함수이다. 낚시 회차를 반복하는 메인함수의 do-while문에서 게임 동작 함수보다 먼저 호출한다.
```
char fish[7]; //물고기 이름 문자열 전역변수

//물고기 이름 랜덤 선택 함수
void ramdomfish() {
    switch (rand() % 10 + 1) {
    case 1: strcpy(fish, "붕어"); break;
    case 2: strcpy(fish, "고등어"); break;
    ...
    case 9: strcpy(fish, "피라미"); break;
    case 10: strcpy(fish, "둥가리"); break;
    }
}
```
<br>

## 도서 관리 시스템
### 게임 설명
구조체와 구조체 포인터, 문자열를 적극 활용하였다. 
도서관의 도서를 관리하는 프로그램으로, 기능으로는 도서 정보 추가, 도서 정보 삭제, 도서 정보 수정, 도서 목록 조회 그리고 프로그램 종료가 있다. 초기 화면에서 원하는 동작의 번호를 입력하면 해당 기능이 수행되고, 수행 기록에 대한 출력이 지워진 후 다시 초기의 화면으로 돌아간다.

|  |  |  |
| ------------- | ------------- | ------------- |
| <img src=https://user-images.githubusercontent.com/53461080/112749012-8de31e80-8ffa-11eb-9daa-2508a100bbd0.png>  | <img src=https://user-images.githubusercontent.com/53461080/112749040-b10dce00-8ffa-11eb-944f-942a1168218a.png>  | <img src=https://user-images.githubusercontent.com/53461080/112749043-b703af00-8ffa-11eb-81f6-7e9da65f7b27.png>  |

### function 1
도서 정보를 정의한 구조체 Book. 도서의 정보인 제목, 작가, 페이지수를 속성으로 정의하였다. 사용자 정의 함수의 매개변수로 구조체 Book의 포인터 타입을 선언하였다.
```
struct Book {
    char title[25]; //12자리까지
    char author[21]; //10자리까지
    int pages;
};

//사용된 사용자 정의 함수
void input(struct Book *);
void deleteout(struct Book *);
void modify(struct Book *);
void print(struct Book *);
```
### function 2
아래는 구조체 배열을 선언하여 구조체 변수의 개수 제한을 두어 사용하는 부분이다. 메인 함수에 정의되어 도서 추가, 삭제, 수정, 조회의 동작을 수행하는 함수에 파라미터로 넘겨진다.
```
#define STOCK 20 //도서 최대 개수

int main(){
    struct Book book_infos[STOCK]; 
    //도서 구조체 변수(배열) 정의

    //구조체 배열 의 사용
    input(book_infos);
    deleteout(book_infos);
    modify(book_infos);
    print(book_infos);
    ...
}
```
### function 3
도서 정보 삭제와 수정 동작에서 존재하지 않는 도서 번호를 입력하는 경우엔 안내 메시지 출력과 함께 해당 함수가 종료되어 메인 화면으로 돌아간다. (예외처리) 아래는 도서 정보 삭제 함수이다.
```
void deleteout(struct Book* book_infos) {
    puts("도서 삭제 화면입니다.\n삭제할 번호를 입력해주세요.\n");
    print(book_infos);
    printf("\n번호 : "); scanf("%d", &flg);

    //존재하지 않는 도서 번호 입력시
    if (flg > stock_cnt) {
        printf("해당 도서가 없습니다.");
        return;
    }

    //도서 삭제 후 번호 정렬(고유번호X)
    for (i = flg-1; i < stock_cnt-1; i++) 
        book_infos[i] = book_infos[i + 1];

    puts("삭제되었습니다."); stock_cnt--;
}
```
<br>

## 전화번호부 데이터 프로그램
### 게임 설명
2진 파일 입출력을 활용하여 데이터 저장과 수정이 가능하도록 하였다. 구조체 사용으로 프로그램의 효율성을 높였다. 
전화번호부 주소록을 관리하는 프로그램이다. 기능으로는 연락처 정보 추가, 정보 삭제, 정보 수정, 전화번호부 목록 조회 그리고 프로그램 종료가 있다. 프로그램이 동작하면서 만들어지는 텍스트 파일에 데이터가 저장되어 프로그램 종료 후 다시 실행해도 그 데이터가 남아있다. 최초 실행시 정보가 기록된 파일이 존재하지 않으므로 정보 등록 과정이 필요하다. 주소록 한도 개수를 초과할 경우 더이상의 정보 등록이 불가능하다. 정보 조회, 삭제, 수정 동작에서 존재하지 않는 정보를 입력할 시 해당 정보가 없다는 메시지가 출력된다. 주소록 정보에 대한 primary key는 해당 주소록 정보의 이름이다.

|  |  |
| ------------- | ------------- |
| <img src=https://user-images.githubusercontent.com/53461080/112749160-78babf80-8ffb-11eb-9c64-b8284447e86f.png>  | <img src=https://user-images.githubusercontent.com/53461080/112749127-4f019880-8ffb-11eb-9aa0-c13139ff38a4.png>  |
| <img src=https://user-images.githubusercontent.com/53461080/112749139-62146880-8ffb-11eb-8a9f-89ac959fa1cb.png>  | <img src=https://user-images.githubusercontent.com/53461080/112749146-68a2e000-8ffb-11eb-83af-0f5de35089c5.png>  |

### function 1
주소록 정보를 담는 구조체의 선언 부분이다. name이 primary key로 사용되었다.
```
//주소록 정보 
struct phone {
    char name[7];
    char no[14];
};
```
### function 2
주소록 정보를 등록하는 함수의 일부분이다. 프로그램을 처음 실행하였을 때 첫 주소록 정보를 등록하는 동시에 전화번호부 텍스트 파일이 생성되도록 쓰기와 파일생성이 가능한 모드로 파일 포인터를 선언하였다(이미 텍스트 파일이 존재한다면 파일이 생성되지 않는다).
다음은 전화번호부 파일에 저장된 정보의 개수를 계산하였다. 전화번호부에 저장될 수 있는 정보의 개수에 한도를 두었기 때문에 그 한도가 넘어가면 추가 등록을 막기 위함이다. fseek함수를 사용해 파일 포인터를 파일의 끝 지점으로 이동시켰다. 파일 포인터의 현재 위치는 파일의 총크기(비트 수)와 같으므로 해당 위치값을 주소록 정보 구조체의 크기(비트 수)로 나눈 값이 주소록 정보의 개수가 된다.
```
//이진 파일을 쓰기용(a)으로 열기
    FILE*fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("\nOpen file error!\n"); exit(1);
    }

    fseek(fp, 0, SEEK_END); 
    //파일 위치 지시자를 파일의 끝 지점으로 이동
   int totalsize = ftell(fp); //끝 지점의 위치값을 담는 변수
    size = totalsize / sizeof(struct phone); 
    //전역변수 size 값: 저장된 구조체 개수​
```
### function 3
파라미터로 받은 이름의 정보가 총 주소록 목록에서 위치한 순서를 반환하는 함수이다. 이것은 정보 조회, 수정, 삭제 동작시 호출되어 사용된다. 파일 포인터를 읽기 모드로 연 후 fread함수를 사용해 파일에 저장된 정보를 주소록 구조체 단위로 읽어내려가면서 strcmp함수로 파라미터로 받은 것과 비교한다. 정보가 일치하면 현재의 반복 회차값를 반환한다.
```
//파라미터로 받은 이름(primary key)의 정보의 순번 반환
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
}​
```
### function 4
전화번호부 전체 목록을 출력하는 부분이다. 읽기모드로 연 텍스트 파일에서 fread 함수를 사용해 정보를 구조체 단위로 읽어와 구조체 배열 변수에 저장 후 출력하는 것을 반복하였다. 텍스트 파일의 정보가 순서대로 모두 출력된다.
```
printf("\n┏━━━━━━━━━━━━━━━━━━━━━━┓\n");
printf("┃  전화번호부 목록(%2d) ┃\n", size);
printf("┠───────┬──────────────┨\n");
for (int i = 0; i < size; i++) {
    //fp에 연결된 파일에서 정보를 읽어옴
    fread(&book[i], sizeof(struct phone), 1, fp);
    printf("┃%7s│%14s┃\n", book[i].name, book[i].no);
}
printf("┗━━━━━━━┷━━━━━━━━━━━━━━┛\n");​
```
### function 5
정보 수정 함수의 일부분이다. 먼저 텍스트파일을 읽기와 쓰기 모드로 열었다. 앞서 설명한 정보의 순번을 반환하는 사용자 정의함수를 사용해 수정할 정보의 이름을 입력받아 넘겨 순번을 반환받는다. fseek함수를 사용해 이 값과 구조체 크기를 곱하여 텍스트 파일 속 수정할 정보의 시작 위치에 포인터를 세팅한다. 포인터가 가리키는 위치에 입력받은 수정 정보를 기록(insert)한다. 수정 정보는 기존 정보에 덮어쓰기된다.
```
FILE* fp = fopen(filename, "r+b"); //읽기+쓰기 모드
if (fp == NULL) {
    printf("\n파일 열기에 실패했습니다.\n"); return;
}

printf("\n수정할 정보의 이름을 입력하세요: ");
scanf("%s", temp.name); 
int del_pos = returnPosition(temp.name); //수정할 정보의 순번
if (del_pos >= 0) {
    printf("\n[수정정보]\n이름 입력: "); scanf("%s", temp.name);
    printf("전화번호 입력: "); scanf("%s", temp.no);
        
    //수정할 정보의 시작 위치에 포인터 세팅
    fseek(fp, sizeof(struct phone)*del_pos, SEEK_SET); 
    //입력받은 수정정보 기록
    fwrite(&temp, sizeof(struct phone), 1, fp); ​
```
## function 6
정보를 삭제하는 함수의 일부분이다. 기존 파일을 읽기모드로 열고, 새 이진파일을 쓰기 모드로 생성한 후 기존 파일에서 삭제할 정보만 제외하고 모든 정보를 새 파일로 옮긴다. 그 후 새 파일의 이름을 기존 파일명과 동일하게 바꿨다(기존 파일명을 전역변수로 선언하였기에 프로그램의 효율성을 위함). 이후 다른 동작 수행시 파일을 불러오는데 전혀 문제가 없다.
remove 함수를 사용해 기존 파일을 삭제하고, rename 함수로 새 파일 이름을 수정하였다.
```
//정보를 옮길 새 파일을 불러오기(생성)
FILE*fp2 = fopen(filename2, "w");
if (fp2 == NULL) {
printf("\n파일 열기에 실패했습니다.\n"); return;
}

//새 파일에 정보 기록(삭제할 정보만 제외하고 옮긴다)
for (int i = 0; i < size; i++) {
if (i == del_pos) continue; //del_pos: 삭제할 정보의 순번
fseek(fp, sizeof(struct phone) * i, SEEK_SET); //파일포인터를 처음 위치로 이동
fread(&temp, sizeof(struct phone), 1, fp); //구조체 단위 정보 1개 읽기
fwrite(&temp, sizeof(struct phone), 1, fp2); //읽은 정보를 새 파일에 기록
}
fclose(fp); fclose(fp2);

int status;
//기존 파일 삭제
status = remove(filename);
if (status == -1) perror("수정 오류(파일 삭제 실패)\n");

//새 파일의 이름을 기존 파일과 동일하게 변경
status = rename(filename2, filename);
if (status == -1) perror("수정 오류(파일 이름 변경 실패)\n");
```
