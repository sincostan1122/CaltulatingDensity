#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
void intro();
void gotoxy(int x, int y);
void start_select();
int main() {
	intro();

	//�⺻ ���� ����
	FILE* fp;
	char num[100];
	char density[100];
	char name[200];
	int d = 0;
	//�ݺ��� �Լ�
	while (1) {
		start_select();
		scanf("%d", d);
	}
	fp = fopen("nameData.txt", "r");
	while (fgets(num, sizeof(num), fp) != NULL) {
		fgets(density, sizeof(density), fp);
		fgets(name, sizeof(name), fp);
		name[strlen(name) - 1] = NULL;
		d = atoi(density);
		if (d > 120) {
			printf("%s, %d\n", name, d);
		}
	}

	fclose(fp);
	return 0;

}

void intro() { //��Ʈ��
	printf("10409 ���ؼ� Ž�� ��ǥ\n�е��� ���� ���� �з� �ý���\n\n");
	printf("�ƹ� Ű�� ���� ����");
	char y = _getch();
	system("cls");
}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void start_select() {
	system("cls");
	int s = 1;
	char select = NULL;
	while (1) {
		system("cls");
		printf("�е� ���\n������ �߰�\n����\n����");
		if (s == 1) {
			gotoxy(10, 0);
		}
		else if (s == 2) {
			gotoxy(12, 1);
		}
		else if (s == 3) {
			gotoxy(5, 2);
		}
		else if (s == 4) {
			gotoxy(5, 3);
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

							if (s != 4) {
								s++;

								break;
							}
					}
					break;
				}
			}



		}
	}
}