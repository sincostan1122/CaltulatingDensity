#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
void intro();
void gotoxy(int x, int y);
int start_select();
void option(float x, float y);

float range1 = 0.5;
float range2 = 1.5;

int main() {


	//기본 변수 선언
	FILE* fp;
	char num[100];
	char density[100];
	char name[200];
	int d = 0;

	fp = fopen("nameData.txt", "r");
	while (fgets(num, sizeof(num), fp) != NULL) {
		fgets(density, sizeof(density), fp);
		fgets(name, sizeof(name), fp);
		d++;
	}
	fclose(fp);

	intro();
	//반복될 함수
	while (1) {
		int y = start_select();
		if (y == 2) {
			system("cls");
			fopen("nameData.txt", "r");
			while (fgets(num, sizeof(num), fp) != NULL) {
				num[strlen(num) - 1] = NULL;
				fgets(density, sizeof(density), fp);
				density[strlen(density) - 1] = NULL;
				fgets(name, sizeof(name), fp);
				name[strlen(name) - 1] = NULL;
				printf("%s - %s %sg/mL\n\n", num, name, density);
			}
			printf("아무 키나 눌러 뒤로가기");
			fclose(fp);
			char p = _getch();
		}
		else if (y == 3) { // 데이터 추가
			system("cls");
			printf("추가할 데이터의 이름과 밀도를 입력하세요.");
			fp = fopen("nameData.txt", "a");
			scanf("%s %s", name, density);
			d++;
			
			fputs(_itoa(d, num, 10), fp);
			fputs("\n", fp);
			fputs(density, fp);
			fputs("\n", fp);
			fputs(name, fp);
			fputs("\n", fp);
			fclose(fp);
		}
		else if (y == 4) {//오차범위 재설정
			option(range1, range2);
		}
		else if (y == 5) { //종료
			system("cls");
			return 0;
		}
	}
	
	return 0;

}

void intro() { //인트로
	printf("10409 박준성 탐구 발표\n밀도를 통한 물질 분류 시스템\n\n");
	printf("아무 키나 눌러 시작");
	char y = _getch();
	system("cls");
}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int start_select() {  //메인 인터페이스
	system("cls");
	int s = 1;
	char select = NULL;
	while (1) {
		system("cls");
		printf("밀도 계산\n데이터 열람\n데이터 추가\n오차범위 재설정\n종료");

		if (s == 1) {
			gotoxy(10, 0);
		}
		else if (s == 2) {
			gotoxy(12, 1);
		}
		else if (s == 3) {
			gotoxy(12, 2);
		}
		else if (s == 4) {
			gotoxy(16, 3);
		}
		else if (s == 5) {
			gotoxy(5, 4);
		}
		printf("<");

		while (1) {		
			if (_kbhit()) {				
				select = _getch();
				if (select == -32) {
					select = _getch();
					switch (select) {						
						case 72:
							if (s != 1) {
								s--;
								break;
							}
						case 80:
							if (s != 5) {
								s++;
								break;
							}
					}
					break;
				}
				else if (select == 'a') {
					return s;
				}
			}
		}
	}
}

void option() { //오차범위 설정
	char select = NULL;
	int s = 1;
	while (1) {
		system("cls");
		printf("1차 오차범위 : %g\n2차 오차범위 : %g\n\n", range1, range2);
		printf("1차 오차범위 수정\n2차 오차범위 수정\n뒤로가기");
		if (s == 1) {
			gotoxy(18, 3);
		}
		else if (s == 2) {
			gotoxy(18, 4);
		}
		else if (s == 3) {
			gotoxy(10, 5);
		}
		printf("<");
		int x = 0;
		while (1) {
			if (_kbhit()) {
				select = _getch();
				if (select == -32) {
					select = _getch();
					switch (select) {
					case 72:
						if (s != 1) {
							s--;
							break;
						}
					case 80:
						if (s != 3) {
							s++;

							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					x = s;
					break;
				}
			}
		}
		if (x == 1) {			
			float q = 0.0;
			int error = 0;
			while (1) {
				system("cls");
				printf("현재 1차 오차범위 : %g\n", range1);
				printf("변경할 값을 입력해주세요. : ");
				if (error == 1) {
					gotoxy(0, 3);
					printf("1차 오차범위는 2차 오차범위보다 클 수 없습니다.\n현재 2차 오차범위:%g", range2);
					gotoxy(28, 1);
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 3);
					printf("오차범위는 0보다 작을 수 없습니다.");
					gotoxy(28, 1);
					error = 0;
				}
				scanf("%f", &q);
				if (q > range2) {
					error = 1;
				}
				else if (q < 0) {
					error = 2;
				}
				else {
					break;
				}
			}
			range1 = q;
			x = 0;
		}
		else if (x == 2) {
			float q = 0.0;
			int error = 0;
			while (1) {
				system("cls");
				printf("현재 2차 오차범위 : %g\n", range2);
				printf("변경할 값을 입력해주세요. : ");
				if (error == 1) {
					gotoxy(0, 3);
					printf("2차 오차범위는 1차 오차범위보다 작을 수 없습니다.\n현재 1차 오차범위:%g", range1);
					gotoxy(28, 1);
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 3);
					printf("오차범위는 0보다 작을 수 없습니다.");
					gotoxy(28, 1);
					error = 0;
				}
				scanf("%f", &q);
				if (q < range1) {
					error = 1;
				}
				else if (q < 0) {
					error = 2;
				}
				else {
					break;
				}
			}
			range2 = q;
			x = 0;
		}
		else if (x == 3) {
			break;
		}

	}
}