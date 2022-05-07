#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
void intro();
void gotoxy(int x, int y);
int start_select();
int dataManage();
void addData();
void deleteData(int z);
int selectDataToDelete();
void option(float x, float y);

float range1 = 0.5;
float range2 = 1.5;
FILE* fp;
char num[100];
char density[100];
char name[200];
int d = 0;

int main() {

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
		if (y == 1) {

		}
		else if (y == 2) {
			while (1) {
				int u = dataManage();
				if (u == 1) {
					addData();
				}
				else if (u == 2) {
					while (1) {
						int z = selectDataToDelete();
						if (z == d + 1) {
							break;
						}
						else {
							deleteData(z);
						}
						
					}
					
				}
				else if (u == 3) {
					break;
				}
			}
 			
		}
		
		else if (y == 3) {//�������� �缳��
			option(range1, range2);
		}
		else if (y == 4) { //����
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
	int error = 0;
	char select = NULL;
	while (1) {
		system("cls");
		printf("�е� ���\n������ ����\n�������� �缳��\n����");
		if (error == 1) {
			gotoxy(0, 6);
			printf("Caps Lock�� Ǯ���ּ���.");
			error = 0;
		}
		else if (error == 2) {
			gotoxy(0, 6);
			printf("��/��Ű�� �ٲ��ּ���.");
			error = 0;
		}
		if (s == 1) {
			gotoxy(10, 0);
		}
		else if (s == 2) {
			gotoxy(12, 1);
		}
		else if (s == 3) {
			gotoxy(16, 2);
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
				else if (select == 'a') {
					return s;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
	}
}
void addData() {
	system("cls");
	printf("�߰��� �������� �̸��� �е��� �Է��ϼ���.");
	fp = fopen("nameData.txt", "r");
	scanf("%s %s", name, density);
	char numa[100];
	char densitya[100];
	char buffer[100];
	int cancel = 0;
	while (fgets(numa, sizeof(numa), fp) != NULL) {
		numa[strlen(numa) - 1] = NULL;
		fgets(densitya, sizeof(densitya), fp);
		densitya[strlen(densitya) - 1] = NULL;
		fgets(buffer, sizeof(buffer), fp);
		buffer[strlen(buffer) - 1] = NULL;
		if (strcmp(buffer, name) == 0) {
			int s = 1;
			int error = 0;
			char select = NULL;
			while (1) {
				system("cls");
				printf("%s�� ������ %s(%sg/mL)�� �̸��� �����ϴ�.\n�����ϰ� �߰��Ͻðڽ��ϱ�?\n", numa, buffer, densitya);
				printf("��\n�ƴϿ�");
				if (error == 1) {
					gotoxy(0, 4);
					printf("Caps Lock�� Ǯ���ּ���.");
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 4);
					printf("��/��Ű�� �ٲ��ּ���.");
					error = 0;
				}
				else if (error == 3) {
					break;
				}
				else if (error == 4) {
					break;
				}
				if (s == 1) {
					gotoxy(3, 2);
				}
				else if (s == 2) {
					gotoxy(7, 3);
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
								if (s != 2) {
									s++;
									break;
								}
							}
							break;
						}
						else if (select == 'a') {
							if (s == 1) {
								error = 3;

								break;
							}
							else if (s == 2) {
								error = 4;
								break;
							}
						}
						else if (select == 'A') {
							error = 1;
							break;
						}
						else if (select < 0 || select > 126) {
							error = 2;
							break;
						}
					}
				}
			}
			if (error == 4) {
				cancel = 1;
				break;
			}
		}
	}
	fclose(fp);
	if (cancel == 0) {
		fp = fopen("nameData.txt", "a");
		d++;
		fputs(_itoa(d, num, 10), fp);
		fputs("\n", fp);
		fputs(density, fp);
		fputs("\n", fp);
		fputs(name, fp);
		fputs("\n", fp);
		fclose(fp);
	}
}
void deleteData(int z) {
	fp = fopen("nameData.txt", "a");
	while (fgets(num, sizeof(num), fp) != NULL) {
		num[strlen(num) - 1] = NULL;
		fgets(density, sizeof(density), fp);
		fgets(name, sizeof(name), fp);	
		if (atoi(num) == z) {
			printf("%s - %s %sg/mL <\n\n", num, name, density);
		}
		else {
			printf("%s - %s %sg/mL\n\n", num, name, density);

		}
	}
	fclose(fp);
}
int selectDataToDelete() {
	system("cls");
	int s = 1;
	int error = 0;
	char select = NULL;
	while (1) {
		system("cls");
		fopen("nameData.txt", "r");
		while (fgets(num, sizeof(num), fp) != NULL) {
			num[strlen(num) - 1] = NULL;
			fgets(density, sizeof(density), fp);
			density[strlen(density) - 1] = NULL;
			fgets(name, sizeof(name), fp);
			name[strlen(name) - 1] = NULL;
			if (atoi(num) == s) {
				printf("%s - %s %sg/mL <\n\n", num, name, density);
			}
			else {
				printf("%s - %s %sg/mL\n\n", num, name, density);

			}
		}
		fclose(fp);
		if (s == d + 1) {
			printf("�ڷΰ��� <");
		}
		else {
			printf("�ڷΰ���");
		}
		
		if (error == 1) {
			gotoxy(0, 2 * d + 2);
			printf("Caps Lock�� Ǯ���ּ���.");
			error = 0;
		}
		else if (error == 2) {
			gotoxy(0, 2 * d + 2);
			printf("��/��Ű�� �ٲ��ּ���.");
			error = 0;
		}
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
						if (s != d+1) {
							s++;
							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					return s;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
	}
}
int dataManage() {
	system("cls");
	int s = 1;
	int error = 0;
	char select = NULL;
	while (1) {
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
		fclose(fp);
		printf("������ �߰�\n������ ����\n�ڷΰ���");
		if (error == 1) {
			gotoxy(0, 2*d+4);
			printf("Caps Lock�� Ǯ���ּ���.");
			error = 0;
		}
		else if (error == 2) {
			gotoxy(0, 2*d+4);
			printf("��/��Ű�� �ٲ��ּ���.");
			error = 0;
		}
		if (s == 1) {
			gotoxy(12 , 2*d);
		}
		else if (s == 2) {
			gotoxy(12, 2*d+1);
		}
		else if (s == 3) {
			gotoxy(9, 2*d+2);
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
						if (s != 3) {
							s++;
							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					return s;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
	}
}

void option() { //�������� ����
	char select = NULL;
	int s = 1;
	int error = 0;
	while (1) {
		system("cls");
		printf("1�� �������� : %g\n2�� �������� : %g\n\n", range1, range2);
		printf("1�� �������� ����\n2�� �������� ����\n�ڷΰ���");
		if (error == 1) {
			gotoxy(0, 7);
			printf("Caps Lock�� Ǯ���ּ���.");
			error = 0;
		}
		else if (error == 2) {
			gotoxy(0, 7);
			printf("��/��Ű�� �ٲ��ּ���.");
			error = 0;
		}
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
				else if(select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
		if (x == 1) {			
			float q = 0.0;
			error = 0;
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