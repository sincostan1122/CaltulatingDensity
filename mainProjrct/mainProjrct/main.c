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


	//�⺻ ���� ����
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
	//�ݺ��� �Լ�
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
			printf("�ƹ� Ű�� ���� �ڷΰ���");
			fclose(fp);
			char p = _getch();
		}
		else if (y == 3) { // ������ �߰�
			system("cls");
			printf("�߰��� �������� �̸��� �е��� �Է��ϼ���.");
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
		else if (y == 4) {//�������� �缳��
			option(range1, range2);
		}
		else if (y == 5) { //����
			system("cls");
			return 0;
		}
	}
	
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

int start_select() {  //���� �������̽�
	system("cls");
	int s = 1;
	char select = NULL;
	while (1) {
		system("cls");
		printf("�е� ���\n������ ����\n������ �߰�\n�������� �缳��\n����");

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

void option() { //�������� ����
	char select = NULL;
	int s = 1;
	while (1) {
		system("cls");
		printf("1�� �������� : %g\n2�� �������� : %g\n\n", range1, range2);
		printf("1�� �������� ����\n2�� �������� ����\n�ڷΰ���");
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
				printf("���� 1�� �������� : %g\n", range1);
				printf("������ ���� �Է����ּ���. : ");
				if (error == 1) {
					gotoxy(0, 3);
					printf("1�� ���������� 2�� ������������ Ŭ �� �����ϴ�.\n���� 2�� ��������:%g", range2);
					gotoxy(28, 1);
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 3);
					printf("���������� 0���� ���� �� �����ϴ�.");
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
				printf("���� 2�� �������� : %g\n", range2);
				printf("������ ���� �Է����ּ���. : ");
				if (error == 1) {
					gotoxy(0, 3);
					printf("2�� ���������� 1�� ������������ ���� �� �����ϴ�.\n���� 1�� ��������:%g", range1);
					gotoxy(28, 1);
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 3);
					printf("���������� 0���� ���� �� �����ϴ�.");
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