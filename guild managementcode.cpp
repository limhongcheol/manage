#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#define numberofsuro 100
#define limitedguildpeople 200
struct charcter_info {
	char* name;
	int level;
	char* job;
	char goday[numberofsuro][11];//������ 100�������� ���� ���� 100ȸ��
	int twoweeks_pla;
	int total_pla;
	int deleted;
	int temporarly;//
	int checkout;
};
void waitcount(int secc);
int alltotalpeople = 0;//
int weekssofunder = 100;//���ΰ� ����
struct charcter_info* characters = NULL;
time_t t = time(NULL);
struct tm tm = *localtime(&t);
int calculatetheweek(char aday[11]);//��ȸ�� �������� ���
void undergroundwaterway();//�޴� 4�� �������� ������ ���� ���� ���
int intro();//�޴���
void showall(int allnumber, int weeksofunder);//�޴� 1���������� ������ ��ü ȭ�� allnumber�� �� �ο���, weeksofunder�� ���θ��° ������.
void showsuro(int check, int weeksofunder);//�޴� 1������ �߰� ���� �������� ������ ȭ��
void newtoguild();//���� ���
void guildedit(int allnumber);//���� ����
void guilddelete(int allnumber);//�������� ���� ��ü limitedguildpeople����� ����
void plagscore();//�÷��� ���� �ޱ�
int numberofweek = 0;//���� �� �� ǥ��
int controltime();
char dayoflastedit[100] = { 0 };//���� ���������� ������ �� ǥ��
int relocates[200] = { 0 };//showall���� ���� ���� �迭
int dayoflasteditday;
void savedata(int peopleall);
void ScreenMode(int cols, int lines) {
	char str[100];
	sprintf(str, "mode con:cols=%d lines=%d", cols, lines);
	system(str);
}
void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void setcolor(int foreground, int background) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = foreground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}
void guildskill();//��� ��ų ���� �ֳ� Ȯ��
void plagreset();//�÷��� 1�������� �ʱ�ȭ
void isheout();//��� Ż���� ��� ã��
void oneweekplag();//�������÷��� ���
void calculatew();//���ΰ� ����� ��賻��
int main() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
	/*int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	//HWND hwnd = CreateWindow(szwindowclass, szTitle, WS_EX_TOPMOST | WS_POPUP, 0, 0, width, height, NULL, NULL, hInstance, NULL);
	//system("mode con cols=180 lines=60");//�ܼ�â ũ�� ����*/
	system("title=����Ʈģ�� ��� ����");
	//ScreenMode(width, height);
	//printf("width=%d,height=%d", width, height);
	system(" mode con lines=40 cols=146");
	int menu = 0;
	int qptmxmclsrn = 1;
	int peopleall = limitedguildpeople;//�� ������� Ȯ��
	for (int askorders = 0; askorders < limitedguildpeople; askorders++) {
		relocates[askorders] = askorders;
	}
	characters = (struct charcter_info*)malloc(limitedguildpeople * sizeof(struct charcter_info));
	for (int i = 0; i < limitedguildpeople; i++) {
		characters[i].deleted = 0;
	}
	FILE *fp;
	fp = fopen("guild_data", "r");
	if (fp == NULL)printf("������ �������Խ��ϴ�.\n");
	if (fp != NULL) {
		fscanf(fp, "%d %d", &peopleall,&alltotalpeople);
		fscanf(fp, "%d", &dayoflasteditday);
		fscanf(fp, "%[^\n]\n", dayoflastedit);
		for (int i = 0; i < alltotalpeople; i++) {
			if (alltotalpeople == 0) { printf("����� ������ �����ϴ�.3�� �ִ� �ڵ����� �����մϴ�.\n"); fclose(fp); waitcount(3); break; }
			system("cls");
			gotoxy(108, 0);
			printf("]");
			gotoxy(0, 0);
			float floalltotalpeople = (float)alltotalpeople;
			float loadingpercentage = 100. / floalltotalpeople;
			printf("%0.2lf%%", loadingpercentage*i);
			printf("[");
			for (int ppp = 0; ppp < loadingpercentage * i; ppp++) { setcolor(0, 1); printf(" "); setcolor(7, 0); }printf("\n");//���Ⱑ �Ķ���
			char tmpnamememo[100] = { 0 };
			char tmpjobmemo[100] = { 0 };
			//printf("0\n");
			fscanf(fp, "%s %d %s %d %d %d\n", tmpnamememo, &characters[i].level, tmpjobmemo, &characters[i].twoweeks_pla, &characters[i].total_pla, &characters[i].deleted);
			//printf("%s %d %s %d %d %d\n", tmpnamememo, characters[i].level, tmpjobmemo, characters[i].twoweeks_pla, characters[i].total_pla, characters[i].deleted);
			if (tmpnamememo[0] == '(') { break; }
			characters[i].name = (char*)malloc((strlen(tmpnamememo)+1) * sizeof(char));
			characters[i].job = (char*)malloc((strlen(tmpjobmemo)+1) * sizeof(char));
			strcpy(characters[i].name, tmpnamememo);
			strcpy(characters[i].job, tmpjobmemo);
			printf("%s %d %s %d %d\n", characters[i].name, characters[i].level, characters[i].job, characters[i].twoweeks_pla, characters[i].total_pla);
			for (int j = 0; j < numberofsuro; j++) { //numberofsuro��  define���� �����Ѱ����� �ڵ�� �̹� ���ص� ������ 100
				char tmpforfile[11] = { 0 };
				fscanf(fp, "%s", tmpforfile);
				//Sleep(10);
				if (tmpforfile[0] == '*') {break; }
				if (tmpforfile[0] != '*') { printf("%s\n", tmpforfile); strcpy(characters[i].goday[j], tmpforfile); }
			}//fscanf(fp, "\n");
			//char onlyforcheck[100] = { 0 };
			//fscanf(fp, "%s",onlyforcheck);
			//printf("%s %d��°", onlyforcheck,i);
			//Sleep(3000);
		}
		fclose(fp);
	}
	system("cls");
	//gotoxy(1, 1);
	//printf("!!!");
	plagreset();
	//waitcount(3);
	while (qptmxmclsrn == 1) {
		int makezero = 0;
		for (int j = 0; j < limitedguildpeople; j++) { makezero += characters[j].deleted; }
		alltotalpeople = makezero;
		menu = intro();
		//printf("%d", menu);
		if (menu == 1) {
			showall(limitedguildpeople, weekssofunder);
		}
		if (menu == 2) {
			newtoguild();
		}
		if (menu == 3) {
			guilddelete(limitedguildpeople);
		}
		if (menu == 4) {
			guildedit(limitedguildpeople);
		}
		if (menu == 5) {
			undergroundwaterway();
		}
		if (menu == 6) {
			plagscore();
		}
		if (menu == 7) {
			guildskill();
		}
		if (menu == 9) {
			isheout();
		}
		if (menu == 10) {
			oneweekplag();
		}
		if (menu == 11) {
			calculatew();
		}
		if (menu == 8) { savedata(limitedguildpeople);  qptmxmclsrn = 2; break; }
	}
	if (alltotalpeople != 0) {
		for (int i = 0; i < limitedguildpeople; i++) { free(characters[i].name); free(characters[i].job); }
		free(characters);
	}
	return 0;
}
void calculatew() {
	system("cls");
	int rnseorksek = 1;
	int abbcs = 0;
	char temprepeatweek[40][11] = { 0 };
	int zz = 0;
	int countforrepeatweek = 0;
	char lastofsurowithme[11] = { '2','0','2','1','/','0','6','/','0','5' };
	printf("%s", lastofsurowithme);
	int totalweeksineed = calculatetheweek(lastofsurowithme);
	char eachweekweplay[11] = { '2','0','2','0','/','1','1','/','2','1' };
	for (int qwera = 0; qwera < 3; qwera++) {
		for (int i = 0; i < limitedguildpeople; i++) {
			for (int j = 0; j < totalweeksineed; j++) {
				if (characters[i].deleted == 1) {
					if (characters[i].goday[j][0] == '2') {
						if (strcmp(eachweekweplay, characters[i].goday[j]) != 0) {
							for (int qw = 0; qw < 40; qw++) {
								if (strcmp(characters[i].goday[j], temprepeatweek[qw]) == 0) { countforrepeatweek++; }
							}
							if (countforrepeatweek == 0) {
								{ strcpy(eachweekweplay, characters[i].goday[j]); strcpy(temprepeatweek[zz], characters[i].goday[j]); zz++; }
							} countforrepeatweek = 0;
						}
					}
				}
			}
		}
	}
	int weekorderab[40] = { 0 };
	for (int i = 0; i < 40; i++) {
		weekorderab[i] = i;
	}
	char tempweekab[11] = { 0 };
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if ((temprepeatweek[weekorderab[j]][0] == '2') && (temprepeatweek[weekorderab[j + 1]][0] == '2')) {
				if (strcmp(temprepeatweek[weekorderab[j]], temprepeatweek[weekorderab[j + 1]]) > 0) {
					for (int qwa = 0; qwa < 11; qwa++) { tempweekab[qwa] = NULL; }
					strcpy(tempweekab, temprepeatweek[weekorderab[j]]); strcpy(temprepeatweek[weekorderab[j]], temprepeatweek[weekorderab[j + 1]]); strcpy(temprepeatweek[weekorderab[j + 1]], tempweekab);
				}
			}
		}
	}
	/*for (int onlytest = 0; onlytest < 30; onlytest++) {
		printf("%s\n", temprepeatweek[weekorderab[onlytest]]);
	}
	scanf("%d", &abbcs);*/
	int countpeopleinsuro = 0;
	int balanceforspace = 22;
	system("cls");
	int peopleorderab[200] = { 0 };
	for (int i = 0; i < 200; i++) {
		peopleorderab[i] = i;
	}
	int numberofsuropeoplegone[200] = { 0 };
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < totalweeksineed; j++) {
			if (characters[i].deleted == 1) {
				if (characters[i].goday[j][0] == '2') {
					numberofsuropeoplegone[i]++;
				}
			}
		}
	}
	int tmpofsuropeoplegone = 0;
	int tmpofsuropeoplegone1 = 0;
/*	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 199; j++) {
			if (numberofsuropeoplegone[peopleorderab[j]] < numberofsuropeoplegone[peopleorderab[j + 1]]) {
				tmpofsuropeoplegone = numberofsuropeoplegone[peopleorderab[j]]; numberofsuropeoplegone[peopleorderab[j]] = numberofsuropeoplegone[peopleorderab[j + 1]]; numberofsuropeoplegone[peopleorderab[j + 1]] = tmpofsuropeoplegone;
			}
		}
	}*/ 
	system("cls");
	printf("��¥�� ���� ���ΰ� ��� ���� ������ 0�� �����ּ���.\nĳ���ͼ����� ���� ���ΰ� Ƚ���� ������ 1�� �����ּ���\n");
	scanf("%d", &rnseorksek);
	while (rnseorksek == 1) {
		system("cls");
		printf("          ĳ���ͼ����� ���� ���ΰ� Ƚ��(1���̻�)\n");
		for (int i = 0; i < limitedguildpeople; i++) {
			if ((characters[i].deleted == 1)&&(numberofsuropeoplegone[peopleorderab[i]]>1)) {
				printf("%20s:", characters[peopleorderab[i]].name);
				for (int j = 0; j < numberofsuropeoplegone[peopleorderab[i]]; j++) {
					setcolor(8, 8); printf(" "); setcolor(7, 0);
				}
				float percentageofeffort = (float)numberofsuropeoplegone[peopleorderab[i]] / 29.0;
				printf("%d�� %4f%%\n", numberofsuropeoplegone[peopleorderab[i]],percentageofeffort*100);
			}
			//Sleep(100);
		}
		printf("����ȭ������ ������ -1�� �Է����ּ���.");
		scanf("%d", &abbcs);
		if (abbcs < 0) { break; }
	}
	while (rnseorksek == 0) {
		system("cls");
		printf("�� ���� �ش����� ���� ������� ��Ÿ���ϴ�. ȸ���� �Է��ϸ� �� ȸ���� ���� ����� ���ɴϴ�.\n");
		for (int z = 1; z < 30; z++) {
			printf("%2dȸ��:%s", z, temprepeatweek[weekorderab[z]]);
			//scanf("%d", &abbcs);
			for (int i = 0; i < limitedguildpeople; i++) {
				for (int j = 0; j < totalweeksineed; j++) {
					if (characters[i].deleted == 1) {
						if (characters[i].goday[j][0] == '2') {
							if (strcmp(temprepeatweek[weekorderab[z]], characters[i].goday[j]) == 0) {
								countpeopleinsuro++;
							}
						}
					}
				}
			}
			for (int asdf = 0; asdf < countpeopleinsuro; asdf++) { setcolor(0, 8); printf(" "); setcolor(7, 0); }
			for (int asdf = 22 - countpeopleinsuro; asdf > 0; asdf--) { printf(" "); }
			printf("%d��\n", countpeopleinsuro);
			countpeopleinsuro = 0;
			//Sleep(1000);
		}
		scanf("%d", &abbcs);
		if ((abbcs > 0) && (abbcs < 30)) {
			for (int i = 0; i < limitedguildpeople; i++) {
				for (int j = 0; j < totalweeksineed; j++) {
					if (characters[i].deleted == 1) {
						if (characters[i].goday[j][0] == '2') {
							if (strcmp(temprepeatweek[weekorderab[abbcs]], characters[i].goday[j]) == 0) {
								printf("%s ", characters[i].name);
							}
						}
					}
				}
			}
			printf("\n����ȭ������ ���÷��� -1�� �����ּ���");
			scanf("%d", &abbcs);
		}
		if (abbcs < 0) { break; }
	}
}
void savedata(int peopleall) {
	FILE* fp;
	fp = fopen("guild_data", "w");
	if (fp == NULL) { printf("������ �������� ���߽��ϴ�."); }
	if (fp != NULL) {
		fprintf(fp, "%d %d", peopleall, alltotalpeople);
		fprintf(fp, " %d %d-%d-%d %d:%d:%d\n", tm.tm_wday, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		if (alltotalpeople != 0) {
			for (int i = 0; i < peopleall; i++) {
				if (characters[i].deleted == 1) {
					fprintf(fp, "%s %d %s %d %d %d\n", characters[i].name, characters[i].level, characters[i].job, characters[i].twoweeks_pla, characters[i].total_pla, characters[i].deleted);
					for (int j = 0; j < numberofsuro; j++) { //numberofsuro��  define���� �����Ѱ����� �ڵ�� �̹� ���ص� ������ 100
						//char tmpforfile[11] = { 0 };
						if (characters[i].goday[j][0] == '2') { fprintf(fp, "%s ", characters[i].goday[j]); }
					}
					char onlyforoncetime = '*';
					fprintf(fp, "%c\n", onlyforoncetime);
					//fprintf(fp, "\n");
				}
			}
		}
			fclose(fp);
			printf("���������� ����Ǿ����ϴ�!!");
		}
	}
void plagscore() {
	system("cls");
	while (1) {
		printf("�÷��� ������ �Է��Ͻ� ������ �г����� �Է����ּ���.\n����ȭ������ ���ư��÷��� 0�� �����ּ���.\n");
		char tmpname[2000] = { 0 };
		scanf("%s", tmpname);
		if (strlen(tmpname) == 1) { system("cls"); break; }
		int check = 0, plage = 0;
		for (int i = 0; i < limitedguildpeople; i++) {
			if (characters[i].deleted == 1) {
				if (strcmp(tmpname, characters[i].name) == 0) {
					check++; plage = i;
				}
			}
		}
		int checktwo = -1;
		if (check == 0) { printf("�ش�Ǵ� %sĳ���Ͱ� �����ϴ�.\n",tmpname); }
		if (check == 1) {
			printf("�� ���� �߰� �Ͻðڽ��ϱ�?(-�� ��밡��)(-1�� ���Ұ�)\n");
			while (check==1) {
				scanf("%d", &checktwo);
				//printf("%d\n", checktwo);
				rewind(stdin);
				if(-1 != checktwo){break;}
				printf("�߸��� ���� �Է��߽��ϴ�. �ٽ� ���ڷ� �Է����ּ���.\n");
				//checktwo = 0;
			}
			printf("%d������ %d���� �߰��Ͽ� %d���� �˴ϴ�.\n", characters[plage].twoweeks_pla, checktwo, characters[plage].twoweeks_pla + checktwo);
			characters[plage].twoweeks_pla += checktwo;
		}
	}
}
void guildedit(int allnumber) {
	system("cls");
	while (1) {
		printf("�����Ͻ� ������ �̸��� �Է��� �ּ���.\n0�� ������ �ٽ� �޴��� ���ư��ϴ�.\n");
		char tmpname[2000] = { 0 };
		scanf("%s", tmpname);
		rewind(stdin);
		if (strlen(tmpname) == 1) { system("cls"); break; }
		int check = 0, numberedit = 0;
		for (int i = 0; i < allnumber; i++) {
			if (characters[i].deleted == 1) {
				if (strcmp(tmpname, characters[i].name) == 0) {
					check++; numberedit = i;
				}
			}
		}
		int checktwo = -1;
		if (check == 0) { printf("�ش�Ǵ� ĳ���Ͱ� �����ϴ�.\n"); }
		if (check == 1) {
			printf("�����Ͻ� ������ �Է����ּ���.\n");
			printf("1.����\n2.����\n3.��������\n");
			scanf("%d", &checktwo);
			if (checktwo == 1) {
				printf("%s���� ������ �����մϴ�.\n ���� ������ %dLv�Դϴ�.\n�����Ͻ� ������ �Է����ּ���.\n", characters[numberedit].name, characters[numberedit].level);
				int getnewlevel = 0;
				scanf("%d", &getnewlevel);
				printf("%s���� ������ %d�������� %d�� �����Ǿ����ϴ�.\n", characters[numberedit].name, characters[numberedit].level, getnewlevel);
				characters[numberedit].level = getnewlevel;
			}
			if (checktwo == 2) {
				printf("%s���� ������ �����մϴ�.\n ���� ������ %s�Դϴ�.\n�����Ͻ� ������ �Է����ּ���.\n", characters[numberedit].name, characters[numberedit].job);
				char getnewjob[2000] = { 0 };
				//getchar();
				scanf("%s", getnewjob);
				rewind(stdin);
				printf("%s���� ������ %s�������� %s�� �����Ǿ����ϴ�.\n", characters[numberedit].name, characters[numberedit].job, getnewjob);
				strcpy(characters[numberedit].job , getnewjob);
			}
		}
	}
}
void guilddelete(int allnumber) {
	system("cls");
	while (1) {
		//printf("������ �����մϴ�.\n");
		printf("�����Ͻ� ������ �̸��� �Է����ּ���.0�� ������ �ٽ� �޴��� ���ư��ϴ�.\n");
		char tmpname[2000] = { 0 };
		getchar();
		scanf("%s", tmpname);
		if (strlen(tmpname) == 1) { system("cls"); break; }
		int check = 0, numberdelete = 0;
		for (int i = 0; i < allnumber; i++) {
			if (characters[i].deleted == 1) {
				if (strcmp(tmpname, characters[i].name) == 0) {
					check++; numberdelete = i;
				}
			}
		}
		int checktwo = -1;
		if (check == 0) { printf("�ش�Ǵ� ĳ���Ͱ� �����ϴ�.\n"); }
		if (check == 1) {
			printf("%s��(��) �����մϴ�. 0�� ������ �����ǰ� 1�� ������ �ٽ� �����մϴ�.\n", tmpname);
			scanf("%d", &checktwo);
			if (checktwo == 0) {
				printf("%s�� �����մϴ�.\n", characters[numberdelete].name);
				characters[numberdelete].name = NULL;
				characters[numberdelete].job = NULL;
				characters[numberdelete].level = NULL;
				characters[numberdelete].total_pla = NULL;
				characters[numberdelete].twoweeks_pla = NULL;
				characters[numberdelete].deleted = 0;
				for (int i = 0; i < 100; i++) { for (int j = 0; j < 11; j++) { characters[numberdelete].goday[i][j] = NULL; } }
			}
		}
	}
}
void newtoguild() {
	system("cls");
	int check = 0;
	printf("������ ���� �����մϴ�.\n");
	printf("������ �Ѹ� Ȯ���ϸ� �����ҰŸ� 1��, maple.gg�� �ִ� ������ �ٿ��ֱ� �Ͻ÷��� 2���� �����ּ���.\n");
	while (1) {
		scanf("%d", &check);
		if ((check == 1) || (check == 2)) { break; }
		rewind(stdin);
		printf("�߸��� ���� �Է��ϼ̽��ϴ� 1�̳� 2�߿��� �Է����ּ���.\n");
	}
	int checkgg = 0;
	if (check == 2) { printf("https://maple.gg�� ���ż� ��� ����~����Ʈ ������ �����ؼ� �ٿ��־��\n 5���ִ� �־��ּ���.\n�ڳ����÷��� �������� �� 0�� �Է��ϼž��մϴ�.\n"); waitcount(5); system("cls"); }
	int waitforonetime = 0;//checkgg�� 5�϶� ������ Ȱ���� ��� ���ϱ� ���ؼ�. 2����
	int waitfortwotime = 0;//�ѹ���
	int duplicated = 0;
	int letsfindnew = 0;
	int newguild = 0;
	while (check != -1) {
		//int newguild = 0;
		int outgg = 0;
		int duplicated1 = 0;
		if (letsfindnew==0){
		for (int i = 0; i < limitedguildpeople; i++) {
			if (characters[i].deleted == 0) { newguild = i; letsfindnew = 1; break; } //������ ����ȵ� ���� ã�� �ڵ�
			}
			}
		if (check == 2) {
			//	for (int gg = 0;gg>-1; gg++) {
			char mapleggtmp[1000] = { 0 };
			getchar();
			scanf("%s", mapleggtmp);//�̸� ����
			for (int i = 0; i < limitedguildpeople; i++) {
				if (characters[i].deleted == 1) {
					if (strcmp(characters[i].name,mapleggtmp) == 0) {
						//printf("���� �̸��� ����%s\n", characters[i].name);
						duplicated++; newguild = i; //printf("%dnewguild i�� �ٲ����\n", newguild);
						if (duplicated == 1) {
							free(characters[newguild].job);
						}
						//printf("duplicated%d\n",duplicated);
						{ break; }
					}
				}
			}
			//printf("\n*%s*mapleggtmp\n", mapleggtmp);
			//if (waitfortwotime == 1) { checkgg = 3; printf("%s", mapleggtmp); }//�ѹ� ���� ���ؼ� ���� ������ ������ <-�����ؾߵ�<<����
			if (strlen(mapleggtmp) == 1) { system("cls"); printf("�̸� ������ �Ϸ�Ǿ����ϴ�.\n"); outgg = 1; break; }
			if ((checkgg == 2) || (checkgg == 4)) { //<<���� checkgg
				//if (duplicated <2) {
				//printf("duplicated=%d", duplicated);
				//if (duplicated == 2) { free(characters[newguild].job); characters[newguild].job = NULL; }
				char ggjob[1000] = { 0 };
				int gglv = 0;
				//int getggg = 0;
				for (int ggg = 0; mapleggtmp[ggg] != '/'; ggg++) {//���ڿ��� ��������
					ggjob[ggg] = mapleggtmp[ggg];
					//printf("����Ȯ��");
				}
				//printf("%s", ggjob);
				int controlten = 100;//�ڸ���������
				for (int ggg = 0; ggg < strlen(mapleggtmp); ggg++) {//���ڿ��� ���� ����
					if ((mapleggtmp[ggg] >= '0') && (mapleggtmp[ggg] <= '9')) {
						gglv += controlten * (mapleggtmp[ggg] - '0');
						controlten /= 10;
					}
				}
				characters[newguild].job = (char*)malloc((strlen(ggjob) + 1) * sizeof(char));//������ �־���
				strcpy(characters[newguild].job, ggjob);
				if (characters[newguild].deleted == 1) { if (characters[newguild].level != gglv) { printf("%s�� ������ �ö����ϴ�.%d->%d", characters[newguild].name,characters[newguild].level, gglv); } }
				characters[newguild].level = gglv;
				//printf("duplicated%d\n", duplicated);
				if (duplicated>=2){
					printf("%s %dLv %s��(��) �����Ǿ����ϴ�.%d \n", characters[newguild].name, characters[newguild].level, characters[newguild].job,newguild);
					//Sleep(1000);
				}
				if (duplicated < 1) {
					//Sleep(5000);
					printf("%s %dLv %s��(��) ��ϵǾ����ϴ�. \n", characters[newguild].name, characters[newguild].level, characters[newguild].job);
					//printf("duplicated=%d", duplicated);
					characters[newguild].deleted = 1;
					characters[newguild].twoweeks_pla = 0;
					characters[newguild].total_pla = 0;
				}
				if (checkgg == 2) { checkgg = 0; }
				if (checkgg == 4) { checkgg = 0; }//<<���� checkgg
			//}////
		}
			if ((checkgg == 1) || (checkgg == 3)) {//<<���� checkgg
				//if (duplicated < 2) {//
				//printf("duplicated2=%d new guild=%d",duplicated,newguild);
				//if (duplicated != 2) {
				if (duplicated < 2) {
					characters[newguild].name = (char*)malloc((strlen(mapleggtmp) + 1) * sizeof(char));
					strcpy(characters[newguild].name, mapleggtmp);//}
				}
					if (checkgg == 1) { checkgg = 2; }
					if (checkgg == 3) { checkgg = 4; }//<<���� checkgg
				//}//duplicated ���� ���� �޸�, ������,�θ����ʹ� duplicated�� �������� 1�̳����� �Ϲ� �������� 1���´�.
			}
			if ((strcmp(mapleggtmp, "������") == 0) || (strcmp(mapleggtmp, "�θ�����") == 0)) { checkgg = 1; }
			if (waitfortwotime == 1) { waitfortwotime = 0; checkgg = 3; }
			if ((strcmp(mapleggtmp, "����") == 0)) { checkgg = 100; waitfortwotime = 1; duplicated = 0; }
			if (((strcmp(mapleggtmp, "��") == 0) || (strcmp(mapleggtmp, "�˼�����") == 0)) && (checkgg != 1) && (checkgg != 100)) { waitfortwotime = 1; duplicated = 0; letsfindnew = 0; }//<<���� checkgg
			//if (checkgg == 5) { waitforonetime++; }//<<���� checkgg
			//if (waitforonetime == 3) { waitforonetime = 0; checkgg = 3; }//<<���� checkgg
			//printf("check gg=%d waitforonetime%d waitfortwotime %d\n", checkgg,waitforonetime,waitfortwotime); //<<����checkgg
			//printf("duplicated=%d", duplicated);
		}
		//} if (outgg == 1) { break; }
	//	printf("%d", characters[newguild].deleted);
		if (check == 1) {
			printf("������ �г����� �����ΰ���?(�׸� �����ϰ� �����ø� 0�� �Է����ּ���.)\n");
			getchar();
			char tmpname[1000] = { 0 };
			scanf("%s", tmpname);
			if (strlen(tmpname) == 1) { system("cls"); break; }
			characters[newguild].name = (char*)malloc((strlen(tmpname) + 1) * sizeof(char));
			strcpy(characters[newguild].name, tmpname);
			printf("%s���� ���� ��ϵǾ����ϴ�. ������ ��ΰ���?\n", characters[newguild].name);
			//getchar();
			scanf("%d", &characters[newguild].level);
			printf("%s���� %d�����Դϴ�. ������ �����ΰ���?\n", characters[newguild].name, characters[newguild].level);
			getchar();
			char tmpjob[1000] = { 0 };
			scanf("%s", tmpjob);
			characters[newguild].job = (char*)malloc((strlen(tmpjob) + 1) * sizeof(char));
			strcpy(characters[newguild].job, tmpjob);
			printf("%s %dLv %s��(��) ��ϵǾ����ϴ�. \n", characters[newguild].name, characters[newguild].level, characters[newguild].job);
			characters[newguild].deleted = 1;
			characters[newguild].twoweeks_pla = 0;
			characters[newguild].total_pla = 0;
			letsfindnew = 0;
		}
		//	printf("%d deleted���� �׸��� newguild�� ����%d\n", characters[newguild].deleted,newguild);
			/*if (check == 1) {
				printf("����ȭ������ ���ư��÷��� -1�� �Է����ּ���. ��� �����ϽǰŸ� -2�� �Է����ּ���.");
				int secondcheck = 0;
				scanf("%d", &secondcheck);
				if (secondcheck == -1) { system("cls"); break; }
				system("cls");
			}*/
	}
}
void showall(int allnumber, int weeksofunder) {
	system("cls");
	int check = -99;
	int showthinglast = 17;
	int showthingstart = 0;
	int onlyforshow = 0;
	for (int i = 0; i < 200; i++) { if (characters[i].deleted == 1) { onlyforshow = i+1; } }
	while (check != -1) {
		//allnumber=�������� �ƴϰ� limitedguildpeople�̿���
		if (check == -2) { for (int j = 0; j < 17; j++) { if (showthingstart < onlyforshow - 17) { showthingstart++; } if (showthinglast < onlyforshow) { showthinglast++; } } }
		if (check == -3) { for (int j = 0; j < 17; j++) { if (showthingstart > 0) { showthingstart--; } if (showthinglast > 17) { showthinglast--; } } }
		//printf("check=%dallnumber=%dshowthingstart=%dshowthingfinal=%d\n", check,allnumber,showthingstart, showthinglast);
		int colorchangeonebyone = 0;
		for (int i = showthingstart; i < showthinglast; i++) {
			if (characters[relocates[i]].deleted == 1) {
				if (colorchangeonebyone == 1) { setcolor(0, 10); colorchangeonebyone = -1; }
				if (colorchangeonebyone == 0) { setcolor(0, 11); colorchangeonebyone = 1; }
				printf("%3d. �г���:%12s ����:%dLv ����:%18s 1�ְ� �÷��� ����:%3d �÷��� �� ����:%5d ���� �� ���� Ȯ���Ϸ��� %3d�� �Է����ּ���.\n", i, characters[relocates[i]].name, characters[relocates[i]].level, characters[relocates[i]].job, characters[relocates[i]].twoweeks_pla, characters[relocates[i]].total_pla, relocates[i]);
				setcolor(7, 7);
				for (int dec = 0; dec < 146; dec++) { printf("="); }//��輱 �������.
				setcolor(7, 0);
				printf("\n");
				if (colorchangeonebyone == -1) { colorchangeonebyone = 0; }
			}
		}
		//int check = -99;
		printf("����ȭ������ ���ư��� �����ø� -1�� �Է����ּ���.\n");
		int askorder = -2;//�ڿ��� �迭 ���� �ٲܶ���
		if (showthingstart == 0) { printf("���� ������� ���� ������ -2�� �Է����ּ���.\n"); }
		else if (showthinglast == onlyforshow) { printf("���� ������� ���� ������ -3�� �Է����ּ���.\n"); }
		else { printf("���� ������� ���� ������ -2�� �Է����ּ���.\n���� ������� ���� ������ -3�� �Է����ּ���.\n"); }
		printf("���� ���ļ��� �ٲٰ� ������ -4�� �Է����ּ���.\n");
		printf("ã����� ������ ������ -5�� �Է����ּ���\n");
		if (check == -4) {
			system("cls");
			printf("������ ������ �ٲߴϴ�.\n");
			printf("0.��ȭ����\n");
			printf("1.���� ��������(���� ����->���� ����)\n");
			printf("2.���� ��������(���� ����->���� ����)\n");
			printf("3.�� �÷��� ���� ��������\n");
			printf("4.�̹��� �÷��� ���� ��������\n");
			scanf("%d", &askorder);
			if (askorder == 0) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//�迭 �ʱ�ȭ 
				printf("������� �迭�� �Ϸ� �Ǿ����ϴ�.\n����� �迭�� ���÷��� 0�� �Է����ּ���.\n");
			}
			if (askorder == 1) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//�迭 �ʱ�ȭ 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].level < characters[relocates[relocatearr + 1]].level) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(����)������������ �迭�� �Ϸ� �Ǿ����ϴ�.\n����� �迭�� ���÷��� 0�� �Է����ּ���.\n");
			}
			if (askorder == 2) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//�迭 �ʱ�ȭ 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].level > characters[relocates[relocatearr + 1]].level) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(����)������������ �迭�� �Ϸ� �Ǿ����ϴ�.\n����� �迭�� ���÷��� 0�� �Է����ּ���.\n");
			}
			if (askorder == 3) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//�迭 �ʱ�ȭ 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].total_pla < characters[relocates[relocatearr + 1]].total_pla) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(�� �÷��� ����)������������ �迭�� �Ϸ� �Ǿ����ϴ�.\n����� �迭�� ���÷��� 0�� �Է����ּ���.\n");
			}
			if (askorder == 4) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//�迭 �ʱ�ȭ 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].twoweeks_pla < characters[relocates[relocatearr + 1]].twoweeks_pla) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(�̹��� �÷��� ����)������������ �迭�� �Ϸ� �Ǿ����ϴ�.\n����� �迭�� ���÷��� 0�� �Է����ּ���.\n");
			}
		}
		if (check == -5) {
			system("cls");
			printf("ã�� ���� ������ �̸��� �Է����ּ���.\n");
			char getfindname[100] = { 0 };
			scanf("%s", getfindname);
			rewind(stdin);
			//printf("\n%s\n", getfindname);
			int getfindnameint = -1;
			for (int findname = 0; findname < onlyforshow; findname++) {
				if (characters[findname].deleted == 1) {
					if (strcmp(characters[findname].name, getfindname) == 0) {
						printf("���� ã�ҽ��ϴ�\n"); setcolor(8, 0);
					 printf("%d. �г���:%s ����:%dLv ����:%s 2�ְ� �÷��� ����:%d �÷��� �� ����:%d ���� �� ���� Ȯ���Ϸ��� %d�� �Է����ּ���.\n", findname, characters[relocates[findname]].name, characters[relocates[findname]].level, characters[relocates[findname]].job, characters[relocates[findname]].twoweeks_pla, characters[relocates[findname]].total_pla, relocates[findname]);
					 setcolor(7, 0);
					 printf("����ȭ������ ���ư��� �����ø� -1�� �Է����ּ���.\n");
					 printf("���� ���ļ��� �ٲٰ� ������ -4�� �Է����ּ���.\n");
					 printf("ã����� ������ ������ -5�� �Է����ּ���\n");
					 getfindnameint = findname; break; }
				}
			}
			if (getfindnameint == -1) { printf("���� ã�����߽��ϴ�. �ٽ� Ȯ�����ּ��� %s\n", getfindname); 
			printf("����ȭ������ ���ư��� �����ø� -1�� �Է����ּ���.\n");
			printf("���� ���ļ��� �ٲٰ� ������ -4�� �Է����ּ���.\n");
			printf("ã����� ������ ������ -5�� �Է����ּ���\n");
			}
		}
		if (askorder != -2) { scanf("%d", &check); system("cls"); }
		if (askorder == -2) {
			scanf("%d", &check);
			if (check == -1) { rewind(stdin); system("cls"); break; }
			system("cls");
			if (check > -1 && check < onlyforshow) {
				showsuro(check, weeksofunder);
				printf("����ȭ������ ���ư��� �����ø� -1�� �Է����ּ���\n����ȭ������ ���ư��� �����ø� 0�� �Է����ּ���\n");
				scanf("%d", &check);
				if (check == -1) { rewind(stdin); system("cls"); break; }
				system("cls");
			}
		}rewind(stdin);
	}
}
void showsuro(int check, int weeksofunder) {
	for (int i = 0; i < weeksofunder; i++) {
		if (characters[check].goday[i][0] == '2') {
			printf("%s���� %s�� ���� ���̽��ϴ�.\n", characters[check].name, characters[check].goday[i]);
		}
	}
}
int intro() {
	system("cls");
	printf("�ȳ��ϼ��� ����Ʈģ�� ��� �ý��� ���� â�� ���Ű��� ȯ���մϴ�.\n");
	printf("������ ��������:%s\n", dayoflastedit);
	printf("���ϴ� ��ȣ�� �Է��Ͻ��� ���͸� �Է����ּ���.\n");
	printf("1.����Ǿ� �ִ� ���� ��ü ��ȸ\n");
	printf("2.���� �űԵ��\n");
	printf("3.���� ���� ����\n");
	printf("4.���� ���� ���� ����\n");
	printf("5.���� ���� �Է�\n");
	printf("6.�÷��� ���� �Է�\n");
	printf("7.��彺ų �� �� �ִ� ��� Ȯ��\n");
	printf("8.���α׷� ���� (����� �� �����Է����ּ���)\n");
	printf("9.������ ���� ���\n");
	printf("10.�÷��� ���������� ������� ��Ÿ����.\n");
	printf("11.���\n");
	int getmenu = 0;
	while (1) {
		scanf("%d", &getmenu);
		if ((getmenu >= 1) && (getmenu <= 11)) { break; }
		printf("�߸��� ���� �Է��߽��ϴ�. 1~11���̿��� �Է����ּ���\n"); rewind(stdin);
	}
	if (getmenu == 8) { system("cls"); printf("���α׷��� �����մϴ�."); } //���⿡ ������ ���� ���� �����ϰ� �޸��� �ݱ�.
	return getmenu;
}
void undergroundwaterway() {
	//	printf("���� ���� �� ����� ����Դϱ�?\n");
	//	int numberofpeople = 0;
	//	scanf("%d", &numberofpeople);
	//	printf("%d���� �����ϴ�. ������ ��� ��� �����Դϱ�? 2020/01/28 ���� ó�� ���ּ���\n", numberofpeople);
	system("cls");
	for (int asd = 0; asd < 1; asd++) {
		printf("���� ���θ� �����ϱ�? 2020/11/28 ���� ó�� ���ּ���\n");
		char dayoftoday[11];
		scanf("%s", dayoftoday);
		getchar();
		if ((dayoftoday[4] != '/') || (dayoftoday[7] != '/')||(strlen(dayoftoday)!=10)) { printf("�ùٸ��� ���� ���� �Դϴ�. xxxx/xx/xx���·� ���ּ���\n 3���ִ� ���� �޴��� ���ư��ϴ�.\n"); for (int pp = 0; pp < 3; pp++) { printf("%d\n", 3 - pp); Sleep(1000); } break; }
		numberofweek = calculatetheweek(dayoftoday);
		//for (int j=0;j<limitedguildpeople;j++){if(characters[j].goday[numberofweek]) }
		printf("������ %s�Դϴ�. ���ΰ� ����� �г����� �Է����ּ���.\n*�� �Է��ϼ����� �������� 0�� �Է����ּ���*\n���� �ϼ����� enterŰ�� �ѹ� ������ �ۼ����ּ���.\n", dayoftoday);
		int wait = 0;
		char** ppt = NULL;
		ppt = (char**)malloc(200 * (sizeof(char*))); //�ϴ� 2�� �����迭 ����
		wait = getchar();
		system("cls");
		int numberofnewline = 1;//����Ʈ�� ���� �̸� �����
		//int dayoffirst = 0;//ù��°�� ����� ��
		for (int i = 0; i < limitedguildpeople; i++) {
			char nametmp[limitedguildpeople] = { 0 };
			scanf("%s", nametmp);
			getchar();
			int checkinlist = 0;//�ѹ��̶� �̰��� �۵��ϸ� �ؿ��� �۵����ϰ� ��.
			if (strlen(nametmp) == 1) { break; }
			for (int j = 0; j < limitedguildpeople; j++) {
				if (characters[j].deleted == 1) {								//�����Ҵ� �ȵ� �κ� ���� �о� ��� ������ ����.
					if (strcmp(characters[j].name, nametmp) == 0) {
						strcpy(characters[j].goday[numberofweek], dayoftoday);
						checkinlist++;//�ѹ��̶� �̰��� �۵��ϸ� �ؿ��� �۵����ϰ� ��.
						printf("%s�� ���������� �Է� �޾ҽ��ϴ�.\n", characters[j].name);
						characters[j].temporarly = 1;
						break;
						//printf("errorcheckinlist1");
					}
				}
			}
			if (checkinlist == 0) {
				//printf("errorcheckinlist");
				ppt[numberofnewline] = (char*)malloc((strlen(nametmp) + 1) * sizeof(char));
				strcpy(ppt[numberofnewline], nametmp);
				numberofnewline++;//���ο� �� �������ְ� 1������.
			}
		}
		if (numberofnewline > 1) {
			printf("���� ��ܿ� ���� ����� %d���ֽ��ϴ�.\n", numberofnewline - 1);
			for (int i = 1; i < numberofnewline; i++) {
				int getok = 0;
				printf("%s����� ���� ��ܿ� �߰��Ϸ��� 1�� �����ּ���. �߰����� �������� 2�� �����ּ���.\n", ppt[i]);
				scanf("%d", &getok);
				if (getok == 1) {
					int newguild = 0;	for (int i = 0; i < limitedguildpeople; i++) { if (characters[i].deleted == 0) { newguild = i; break; } }//���� �迭���� ��� ã���ڵ�
					characters[newguild].name = (char*)malloc((strlen(ppt[i]) + 1) * sizeof(char));
					strcpy(characters[newguild].name, ppt[i]);
					printf("%s���� ���� ��ϵǾ����ϴ�. ������ ��ΰ���?\n", characters[newguild].name);
					//getchar();
					scanf("%d", &characters[newguild].level);
					printf("%s���� %d�����Դϴ�. ������ �����ΰ���?\n", characters[newguild].name, characters[newguild].level);
					getchar();
					char tmpjob[1000] = { 0 };
					scanf("%s", tmpjob);
					getchar();
					characters[newguild].job = (char*)malloc((strlen(tmpjob) + 1) * sizeof(char));
					strcpy(characters[newguild].job, tmpjob);
					strcpy(characters[newguild].goday[numberofweek], dayoftoday);
					printf("%s %dLv %s��(��) ��ϵǾ����ϴ�. \n", characters[newguild].name, characters[newguild].level, characters[newguild].job);
					characters[newguild].deleted = 1;
					characters[newguild].twoweeks_pla = 0;
					characters[newguild].total_pla = 0;
				}
				if (getok != 1) { printf("%s�� �������� �ʽ��ϴ�.\n", ppt[i]); }
			}
		}
		//printf("����ã����");
	}
}
int controltime() {
	printf("����: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	/*struct tm {
		int tm_sec;          ��,  range 0 to 59
		int tm_min;          ��, range 0 to 59
		int tm_hour;         �ð�, range 0 to 23
		int tm_mday;         ��, range 1 to 31
		int tm_mon;          ��, range 0 to 11
		int tm_year;         1900�� ������ ��
		int tm_wday;         ����, range ��(0) to ��(6)
		int tm_yday;         1�� �� ��� ��, range 0 to 365
		int tm_isdst;        ���Ÿ��
	};*/
	return tm.tm_wday;
}
int calculatetheweek(char aday[100]) {
	//2020/11/21 ����
	int year = 0;
	int month = 0;
	int day = 0;
	year = aday[3] - '0';
	if (aday[5] == '0') { month = aday[6] - '0'; }
	else if (aday[5] == '1') { month = 10 + aday[6] - '0'; }
	if (aday[8] == '0') { day = aday[9] - '0'; }
	else if (aday[8] == '1') { day = 10 + aday[9] - '0'; }
	else if (aday[8] == '2') { day = 20 + aday[9] - '0'; }
	else if (aday[8] == '3') { day = 30 + aday[9] - '0'; }
	int totalday = 0;
	int newyear = 0;
	int newmonth = 0;
	int newday = 0;
	newyear = year;
	//newmonth = month - 11; //monthday=304�� ���´�.
	int monthday = 0;
	newday = day - 21;
	//printf("newday=%d\n", newday);
	for (int i = 1; i < month; i++) {
		if ((i == 1) || (i == 3) || (i == 5) || (i == 7) || (i == 8) || (i == 10) || (i == 12)) { monthday += 31; }
		if ((i == 4) || (i == 6) || (i == 9) || (i == 11)) { monthday += 30; }
		if (i == 2) { monthday += 28; }
	}
	//printf("%d\n", monthday);
	newmonth = monthday - 304; //334 304
	totalday = 365 * year + newmonth + newday;
	//printf("totalday=%d ��������=%d Ȯ��%d", totalday,totalday/7,totalday%7);//0���� ���� ���� 2020/11/21 0������. 2024/3/2�Ϻ��� ���� ����.
	printf("%d����", totalday / 7);
	return totalday / 7;
	//1,3,5,7,8,10,12 31�� 
	//4,6,9,11 30��      
	//2 28��
	/*int flagyear = 0;//���� �ޱ����� 4���ֱ�
	if (year % 4 == 0) { flagyear = 1; }
	if (year % 4 != 0) { flagyear = 0; }*/

}
void guildskill() {
	system("cls");
	char lastestsuro[11] = { 0 };
	char seclastestsuro[11] = { 0 };
	char thirdlastestsuro[11] = { 0 };
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < numberofsuro; j++) {
			if (characters[i].deleted == 1) {
				if (characters[i].goday[j][0] == '2') {
					if (strcmp(lastestsuro, characters[i].goday[j]) < 0) { strcpy(lastestsuro, characters[i].goday[j]); }
				}
			}
		}
	}
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < numberofsuro; j++) {
			if (characters[i].deleted == 1) {
				if (characters[i].goday[j][0] == '2') {
					if ((strcmp(seclastestsuro, characters[i].goday[j]) < 0) && (strcmp(lastestsuro, characters[i].goday[j]) != 0)) { strcpy(seclastestsuro, characters[i].goday[j]); }
				}
			}
		}
	}
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < numberofsuro; j++) {
			if (characters[i].deleted == 1) {
				if (characters[i].goday[j][0] == '2') {
					if ((strcmp(thirdlastestsuro, characters[i].goday[j]) < 0) && (strcmp(lastestsuro, characters[i].goday[j]) != 0)&& (strcmp(seclastestsuro, characters[i].goday[j]) != 0)) { strcpy(thirdlastestsuro, characters[i].goday[j]); }
				}
			}
		}
	}
	int peoplewhocanuseskill = 0;
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < numberofsuro; j++) {
			if (characters[i].deleted == 1) {
				if (strcmp(characters[i].goday[j], thirdlastestsuro) == 0) {
					characters[i].temporarly = -1;
				}
			}
		}
	}//�̰ɷδ� 3������ ���� �� ��� ã��
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < numberofsuro; j++) {
			if (characters[i].deleted == 1) {
				if (((strcmp(characters[i].goday[j], lastestsuro) == 0)) || (strcmp(characters[i].goday[j], seclastestsuro) == 0)||(characters[i].twoweeks_pla>=20)) {
					characters[i].temporarly = 1;
					peoplewhocanuseskill++;
				}
			}
		}
	}//�̰ɷδ� 2�� ���̿� ���� �� ��� ã��.
	int check = -999;
	int showthingstart = 0;
	int showthinglast = 35;
	printf("���� �ֱ� ���� �� ���� �������� ã�ڽ��ϴ�.\n");//���߿� ���⿡ ������ �˻� �� �Է¹ް� ������ ������ ��ü �÷��� ���� Ȯ�� temporarly���� 1�����
	/*while (check != -1) {
		if (check == -2) { for (int j = 0; j < 35; j++) { if (showthingstart < peoplewhocanuseskill - 35) { showthingstart++; } if (showthingstart < peoplewhocanuseskill) { showthinglast++; } } }
		if (check == -3) { for (int j = 0; j < 35; j++) { if (showthingstart > 0) { showthingstart--; } if (showthinglast > 35) { showthinglast--; } } }
		//printf("check=%dallnumber=%dshowthingstart=%dshowthingfinal=%d\n", check,allnumber,showthingstart, showthinglast);
		for (int i = showthingstart; i < showthinglast; i++) {
			if (characters[i].deleted == 1) {
				if ((characters[i].twoweeks_pla >= 20) || (characters[i].temporarly == 1)) {
					printf("%s\n", characters[i].name);
				}
			}
		}
		//int check = -99;
		int dayoftoday = controltime();
		printf("���� �ֱ� ���� �� ��=%s,���� �ֱ� ���� �� ���� ��=%s\n", lastestsuro, seclastestsuro);
		printf("����ȭ������ ���ư��� �����ø� -1�� �Է����ּ���.\n");
		printf("�� ��ų�� �� �� �ִ� ��� ��=%d", peoplewhocanuseskill);
		if (showthingstart == 0) { printf("���� ������� ���� ������ -2�� �Է����ּ���.\n"); }
		else if (showthinglast == peoplewhocanuseskill) { printf("���� ������� ���� ������ -3�� �Է����ּ���.\n"); }
		else { printf("���� ������� ���� ������ -2�� �Է����ּ���.\n���� ������� ���� ������ -3�� �Է����ּ���.\n"); }
		scanf("%d", &check);
		rewind(stdin);
		if (check == -1) { system("cls"); break; }
		system("cls");
	}*/
	int dayoftoday = controltime();
	printf("���� �ֱ� ���� �� ��=%s,���� �ֱ� ���� �� ���� ��=%s,2������ �� ����=%s\n", lastestsuro, seclastestsuro,thirdlastestsuro);
	int coloronebyone = 0;
	int changeline = 0;
	peoplewhocanuseskill = 0;
	setcolor(7, 6);
	printf("��� ��ų�� �� �� �ִ� ���.\n");
	for (int i = 0; i < limitedguildpeople; i++) {
		if (characters[i].deleted == 1) {
			if ((characters[i].twoweeks_pla >= 20) || (characters[i].temporarly > 0)) {
				if (coloronebyone == 0) { setcolor(7, 1); coloronebyone = 2; }
				if (coloronebyone == 1) { setcolor(7, 9); coloronebyone = 0; }
				printf("%12s", characters[i].name);
				if (coloronebyone == 2) { coloronebyone = 1; }
				changeline++;
				if (changeline == 12) { printf("\n"); changeline = 0; }
				peoplewhocanuseskill++;
			}
		}
	}
	setcolor(7, 6);
	int peoplewhocantuseskill = 0;
	printf("\n��� ��ų�� �� �� ���Ե� ���.\n");
	for (int i = 0; i < limitedguildpeople; i++) {
		if (characters[i].deleted == 1) {
			if (characters[i].temporarly < 0) {
				if (coloronebyone == 0) { setcolor(7, 4); coloronebyone = 2; }
				if (coloronebyone == 1) { setcolor(7, 12); coloronebyone = 0; }
				printf("%12s", characters[i].name);
				if (coloronebyone == 2) { coloronebyone = 1; }
				changeline++;
				peoplewhocantuseskill++;
				if (changeline == 12) { printf("\n"); changeline = 0; }
			}
		}
	}
	setcolor(7, 0);
	printf("\n�� ��ų�� �� �� �ִ� ��� ��=%d\n", peoplewhocanuseskill);
	printf("�� ��ų�� �� ���Ե� ��� ��=%d\n",peoplewhocantuseskill);
	printf("����ȭ������ ���ư��� �����ø� -1�� �Է����ּ���.\n");
	//int check = 0;
	scanf("%d", &check);
	rewind(stdin);
}
void waitcount(int secc) {
	for (int i = 0; i < secc; i++) {
		printf("%d\n", secc - i);
		Sleep(1000);
	}
}
void plagreset() {
	//printf("dayoflastedit = %s\n",dayoflastedit);
	int yearpl = 0, monthpl = 0, daypl = 0;
	yearpl = (dayoflastedit[3] - '0') * 10 + dayoflastedit[4] - '0';
	if (dayoflastedit[7] != '-') {
		monthpl = (dayoflastedit[6] - '0') * 10 + dayoflastedit[7] - '0';
		if (dayoflastedit[8] == '-') {
			if ((dayoflastedit[10] >= '0') && (dayoflastedit[10] <= '9')) {daypl = (dayoflastedit[9] - '0') * 10 + dayoflastedit[10] - '0';}
			else {	daypl = dayoflastedit[9] - '0';}
		}
	}
	if (dayoflastedit[7] == '-') {
		monthpl = dayoflastedit[6] - '0';
			if ((dayoflastedit[9] >= '0') && (dayoflastedit[9] <= '9')) { daypl = (dayoflastedit[8] - '0') * 10 + dayoflastedit[9] - '0'; }
			else { daypl = dayoflastedit[8] - '0'; }
	}
	int monthpldays=0;
	for (int i = 1; i < monthpl; i++) {
		if ((i == 1) || (i == 3) || (i == 5) || (i == 7) || (i == 8) || (i == 10) || (i == 12)) { monthpldays += 31; }
		if ((i == 4) || (i == 6) || (i == 9) || (i == 11)) { monthpldays += 30; }
		if (i == 2) { monthpldays += 28; }
	}
	int year = tm.tm_year - 100, month = tm.tm_mon+1, day = tm.tm_mday;
	int monthday = 0;
	for (int i = 1; i < month; i++) {
		if ((i == 1) || (i == 3) || (i == 5) || (i == 7) || (i == 8) || (i == 10) || (i == 12)) { monthday += 31; }
		if ((i == 4) || (i == 6) || (i == 9) || (i == 11)) { monthday += 30; }
		if (i == 2) { monthday += 28; }
	}
	int totalpldays = yearpl*365 + monthpldays + daypl;
	int totaltodays = year * 365 + monthday + day;
	int soresult = totaltodays - totalpldays;//0�� 6��
	int howmakemon = 8 - dayoflasteditday; //ex ���� ȭ 6�̳���
	if (howmakemon == 8) { howmakemon = 1; }
	int counthowmanyplayed = 0;
	//printf("yearpl=%dmonthply=%ddaypl=%d\n", yearpl, monthpl, daypl);
	//printf("totalpldays=%dtotaltodays%dsoresult=%dhowmakemon=%dyear=%dmonth=%dday=%d", totalpldays, totaltodays, soresult, howmakemon, year, month, day);
	//Sleep(1000000);
	if (soresult >= howmakemon) {
		for (int i = 0; i <limitedguildpeople; i++) {
			if (characters[i].total_pla >= 20) { characters[i].temporarly = -1; }
			characters[i].total_pla += characters[i].twoweeks_pla;
			if (characters[i].twoweeks_pla > 0) { counthowmanyplayed++; }
			characters[i].twoweeks_pla = 0;
		}
		printf("�÷��� ��ϵ��� ������ �Ѿ���ϴ�. �Ѿ %d��ϵ��� ��ȯ�߽��ϴ�.\n",counthowmanyplayed);
		waitcount(3);
	}
}
void isheout() {
	system("cls");
	printf("���� ����Ǿ��ִ� ���� ��ܰ� ����, ��带 Ż���� ����� ã���ϴ�.\n");
	printf("maple.gg���� 2.���� �űԵ�Ͽ��� 2��ó�� �����ؼ� �پ�־��ּ���.\n");
	printf("�ظ��������� ���������� 0�� �Է����ּ���. 3�� �ִ� �����մϴ�.\n");
	waitcount(3);
	system("cls");
	printf("���� ���� �Է����ּ���.\n");
	for (int i = 0; i < limitedguildpeople; i++) {
		characters[i].checkout = 0;
	}
	int repeatuntilout = 0;
	while (repeatuntilout == 0) {
		char tmpforout[100] = { 0 };
		scanf("%s", tmpforout);
		//printf("tmpforout=%s\n", tmpforout);
		//rewind(stdin);
		if ((strcmp(tmpforout, "��") == 0) || (strcmp(tmpforout, "�˼�����") == 0) || (strcmp(tmpforout, "���") == 0) || (strcmp(tmpforout, "����") == 0)) {
			char checkdeletename[100] = { 0 };
			rewind(stdin);
			scanf("%s", checkdeletename);
			if (strcmp(checkdeletename, "����") == 0) {
				for (int p = 0; p < 100; p++) { checkdeletename[p] = { 0 }; }
				scanf("%s", checkdeletename);
			}
			//printf("checkdeletename=%s", checkdeletename);
			if (checkdeletename[0] == '0') { break; }
			for (int i = 0; i < limitedguildpeople; i++) {
				if (characters[i].deleted == 1) {
					if (strcmp(checkdeletename, characters[i].name) == 0) { characters[i].checkout = 1; }
				}
			}
		}
		if (tmpforout[0] == '0') { break; }
	}
	system("cls");
	int onlyforwaiting4 = 0;//���� ������ while ���� ��
	while (onlyforwaiting4 == 0) {
		printf("��忡 Ż���� ���:");
		int peoplewhoguildout = 0;
		int whoguildoutarr[limitedguildpeople] = { 0 };
		for (int i = 0; i < limitedguildpeople; i++) {
			if ((characters[i].deleted == 1) && (characters[i].checkout == 0)) {
				setcolor(4, 0);
				peoplewhoguildout++;
				whoguildoutarr[peoplewhoguildout] = i;
				printf("%d.%s ", peoplewhoguildout, characters[i].name); setcolor(7, 0);
			}
		}
		if (peoplewhoguildout == 0) { printf("��带 Ż���� ����� �����ϴ�.\n"); waitcount(3); break; }
		printf("\n�� ��� Ż���� ����� ��:%d\n", peoplewhoguildout);
		printf("����ȭ������ ���ư����� -1�� �Է����ּ���.\n");
		printf("��带 Ż���� ������� �ϰ� �����Ϸ��� -2�� �Է����ּ���.\n");
		printf("���������� ������ �����ϰ� ������ ������ ��ȣ(1~%d)�� �Է����ּ���.\n",peoplewhoguildout);
		int onlyforwaiting1 = 0;//���� �޴��� �����
		int onlyforwaiting2 = 0;//���������� �������� Ȯ��
		int onlyforwaiting3 = 0;//���� ������ while ����
		scanf("%d", &onlyforwaiting1);
			if ((onlyforwaiting1 >= 0) && (onlyforwaiting1 <= peoplewhoguildout)) {
				printf("��%s�� ������ �����Ͻðڽ��ϱ�?\n1�� �Է��ϸ� ����\n2�� �Է��ϸ� �������� �ʽ��ϴ�.\n", characters[whoguildoutarr[onlyforwaiting1]].name);
				scanf("%d", &onlyforwaiting2);
				if (onlyforwaiting2 == 1) {
					printf("%s�� �����մϴ�.\n", characters[whoguildoutarr[onlyforwaiting1]].name);
					characters[whoguildoutarr[onlyforwaiting1]].name = NULL;
					characters[whoguildoutarr[onlyforwaiting1]].job = NULL;
					characters[whoguildoutarr[onlyforwaiting1]].level = NULL;
					characters[whoguildoutarr[onlyforwaiting1]].total_pla = NULL;
					characters[whoguildoutarr[onlyforwaiting1]].twoweeks_pla = NULL;
					characters[whoguildoutarr[onlyforwaiting1]].deleted = 0;
					for (int i = 0; i < 100; i++) { for (int j = 0; j < 11; j++) { characters[whoguildoutarr[onlyforwaiting1]].goday[i][j] = NULL; } }
				}
				//waitcount(3);
			}
		if (onlyforwaiting1 == -2) {
			printf("�������� �����Ͻðڽ��ϱ�?\n1�� �Է��ϸ� ����\n2�� �Է��ϸ� �������� �ʽ��ϴ�.\n");
			scanf("%d", &onlyforwaiting2);
			for (int ppp = 1; ppp < peoplewhoguildout + 1; ppp++) {
				if (onlyforwaiting2 == 1) {
					printf("%s�� �����մϴ�.\n", characters[whoguildoutarr[ppp]].name);
					Sleep(1000);
					characters[whoguildoutarr[ppp]].name = NULL;
					characters[whoguildoutarr[ppp]].job = NULL;
					characters[whoguildoutarr[ppp]].level = NULL;
					characters[whoguildoutarr[ppp]].total_pla = NULL;
					characters[whoguildoutarr[ppp]].twoweeks_pla = NULL;
					characters[whoguildoutarr[ppp]].deleted = 0;
					for (int i = 0; i < 100; i++) { for (int j = 0; j < 11; j++) { characters[whoguildoutarr[ppp]].goday[i][j] = NULL; } }
				}
			}
			//waitcount(3);
			//break;
		}
		rewind(stdin);
		system("cls");
	}
}
void oneweekplag() {
	int realtotalweekplag = 0;
	int recordtotalweekplag = 0;
	int menuoneweekplag=0;
	int totalpeopleoneweekplag=0;
	system("cls");
	printf("�̹��� �� ���� �÷��� ������ �Է��Ϸ��� 1��, �ٷ� �޴����� ������ 2���� �Է����ּ���.\n");
	scanf("%d", &menuoneweekplag);
	if (menuoneweekplag == 1) {
		printf("�̹��� ���� �÷��� ������ �� �� �Դϱ�?\n");
		scanf("%d", &realtotalweekplag);
		printf("\n%d��\n", realtotalweekplag);
		waitcount(3);
	}
	system("cls");
	for (int i = 0; i < limitedguildpeople; i++) {
		if (characters[i].deleted == 1) {
			recordtotalweekplag += characters[i].twoweeks_pla;
			if (characters[i].twoweeks_pla > 0) { totalpeopleoneweekplag++; }
		}
	}
	float percentageoneweekplag =0.0;
	percentageoneweekplag = (float)(recordtotalweekplag) / (float)realtotalweekplag * 100;
	printf("������ ���� �÷��� �� ������� ��Ÿ���ϴ�.\n");
	printf("����: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("�� ���� �ο�:%d �̹��� �� ���� �÷��� ����:%d ��ϵ� �̹��� �� ���� �÷��� ����:%d %0.2lf%%\n", totalpeopleoneweekplag,realtotalweekplag,recordtotalweekplag,percentageoneweekplag);
	int onlyforshow = 0;
	int check = -999;
	onlyforshow = totalpeopleoneweekplag + 1;
	int maxoneweekplag = 0, secmaxoneweekplag = 0, thrmaxoneweekplag=0, fourmaxoneweekplag = 0;
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < limitedguildpeople; j++) {
			if (maxoneweekplag < characters[i].twoweeks_pla) {maxoneweekplag = characters[i].twoweeks_pla; }
		}
	}
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < limitedguildpeople; j++) {
			if ((secmaxoneweekplag < characters[i].twoweeks_pla)&&(maxoneweekplag!=characters[i].twoweeks_pla)) { secmaxoneweekplag = characters[i].twoweeks_pla; }
		}
	}
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < limitedguildpeople; j++) {
			if ((thrmaxoneweekplag < characters[i].twoweeks_pla) && (maxoneweekplag != characters[i].twoweeks_pla) && (secmaxoneweekplag != characters[i].twoweeks_pla)) { thrmaxoneweekplag = characters[i].twoweeks_pla; }
		}
	}
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < limitedguildpeople; j++) {
			if ((fourmaxoneweekplag < characters[i].twoweeks_pla) && (maxoneweekplag != characters[i].twoweeks_pla) && (secmaxoneweekplag != characters[i].twoweeks_pla) && (thrmaxoneweekplag != characters[i].twoweeks_pla)) { fourmaxoneweekplag = characters[i].twoweeks_pla; }
		}
	}

	for (int askorders = 0; askorders < limitedguildpeople; askorders++) { relocates[askorders] = askorders; }//�迭 �ʱ�ȭ 
	for (int repeat_relo = 0; repeat_relo < limitedguildpeople; repeat_relo++) {//�÷��� 1�ְ� ���� ������� �迭
		for (int relocatearr = 0; relocatearr < limitedguildpeople; relocatearr++) {
			if (characters[relocates[relocatearr]].deleted == 1) {
				if (characters[relocates[relocatearr]].twoweeks_pla < characters[relocates[relocatearr + 1]].twoweeks_pla) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
			}
		}
	}
	int colorarr[8] = { 4,12,6,2,1,9,5,8 };
	printf("1����� 4����� %d %d %d %d\n", maxoneweekplag, secmaxoneweekplag, thrmaxoneweekplag, fourmaxoneweekplag);
		int colorchangeonebyone = 0;
		int countline = 0;
		int countlinecolor = 0;
		for (int i = 0; i < limitedguildpeople; i++) {
			if (characters[relocates[i]].deleted == 1) {
				if (characters[relocates[i]].twoweeks_pla >= 0) {
					if (colorchangeonebyone == 0) { setcolor(countlinecolor+8, 0);  }
					//if (colorchangeonebyone == 0) { setcolor(0, colorarr[countlinecolor]); }
					/*if (maxoneweekplag==characters[relocates[i]].twoweeks_pla) { setcolor(7, colorarr[countlinecolor]); }
					if (secmaxoneweekplag == characters[relocates[i]].twoweeks_pla) { setcolor(3, colorarr[countlinecolor]); }
					if (thrmaxoneweekplag == characters[relocates[i]].twoweeks_pla) { setcolor(1, colorarr[countlinecolor]); }
					if (fourmaxoneweekplag == characters[relo
					cates[i]].twoweeks_pla) { setcolor(15, colorarr[countlinecolor]); }*/
					printf("%12s 1��:%3d �� ����:%5d", characters[relocates[i]].name, characters[relocates[i]].twoweeks_pla, characters[relocates[i]].twoweeks_pla +characters[relocates[i]].total_pla);
					countline++;
					if (countline == 4) { printf("\n"); countline = 0; countlinecolor++; if (countlinecolor == 8) { countlinecolor = 7; } }
					/*setcolor(7, 7);
					for (int dec = 0; dec < 146; dec++) { printf("="); }//��輱 �������.
					printf("\n");*/
					setcolor(7, 0);
				//	if (colorchangeonebyone == -1) { colorchangeonebyone = 0; }
				}
			}
		}
		printf("\n����ȭ������ ���ư��� �����ø� -1�� �Է����ּ���.\n");
		scanf("%d", &check);
}