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
	char goday[numberofsuro][11];//아직은 100개까지만 받음 수로 100회분
	int twoweeks_pla;
	int total_pla;
	int deleted;
	int temporarly;//
	int checkout;
};
void waitcount(int secc);
int alltotalpeople = 0;//
int weekssofunder = 100;//수로간 주차
struct charcter_info* characters = NULL;
time_t t = time(NULL);
struct tm tm = *localtime(&t);
int calculatetheweek(char aday[11]);//몇회차 수로인지 계산
void undergroundwaterway();//메뉴 4번 눌렀을시 나오는 수로 정보 등록
int intro();//메뉴판
void showall(int allnumber, int weeksofunder);//메뉴 1번눌렀을시 나오는 전체 화면 allnumber은 총 인원수, weeksofunder은 수로몇번째 갔는지.
void showsuro(int check, int weeksofunder);//메뉴 1번에서 추가 숫자 눌렀을시 나오는 화면
void newtoguild();//길드원 등록
void guildedit(int allnumber);//길드원 수정
void guilddelete(int allnumber);//길드원삭제 길드원 전체 limitedguildpeople명까지 가능
void plagscore();//플래그 점수 받기
int numberofweek = 0;//수로 간 주 표시
int controltime();
char dayoflastedit[100] = { 0 };//가장 마지막으로 수정한 날 표시
int relocates[200] = { 0 };//showall에서 순서 관련 배열
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
void guildskill();//길드 스킬 쓸수 있나 확인
void plagreset();//플래그 1주지나면 초기화
void isheout();//길드 탈퇴한 사람 찾기
void oneweekplag();//일주일플래그 결산
void calculatew();//수로간 사람들 통계내기
int main() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
	/*int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	//HWND hwnd = CreateWindow(szwindowclass, szTitle, WS_EX_TOPMOST | WS_POPUP, 0, 0, width, height, NULL, NULL, hInstance, NULL);
	//system("mode con cols=180 lines=60");//콘솔창 크기 조절*/
	system("title=베스트친구 길드 관리");
	//ScreenMode(width, height);
	//printf("width=%d,height=%d", width, height);
	system(" mode con lines=40 cols=146");
	int menu = 0;
	int qptmxmclsrn = 1;
	int peopleall = limitedguildpeople;//총 몇명인지 확인
	for (int askorders = 0; askorders < limitedguildpeople; askorders++) {
		relocates[askorders] = askorders;
	}
	characters = (struct charcter_info*)malloc(limitedguildpeople * sizeof(struct charcter_info));
	for (int i = 0; i < limitedguildpeople; i++) {
		characters[i].deleted = 0;
	}
	FILE *fp;
	fp = fopen("guild_data", "r");
	if (fp == NULL)printf("파일을 못가져왔습니다.\n");
	if (fp != NULL) {
		fscanf(fp, "%d %d", &peopleall,&alltotalpeople);
		fscanf(fp, "%d", &dayoflasteditday);
		fscanf(fp, "%[^\n]\n", dayoflastedit);
		for (int i = 0; i < alltotalpeople; i++) {
			if (alltotalpeople == 0) { printf("저장된 정보가 없습니다.3초 있다 자동으로 시작합니다.\n"); fclose(fp); waitcount(3); break; }
			system("cls");
			gotoxy(108, 0);
			printf("]");
			gotoxy(0, 0);
			float floalltotalpeople = (float)alltotalpeople;
			float loadingpercentage = 100. / floalltotalpeople;
			printf("%0.2lf%%", loadingpercentage*i);
			printf("[");
			for (int ppp = 0; ppp < loadingpercentage * i; ppp++) { setcolor(0, 1); printf(" "); setcolor(7, 0); }printf("\n");//여기가 파란색
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
			for (int j = 0; j < numberofsuro; j++) { //numberofsuro는  define에서 정의한것으로 코드로 이미 정해둠 지금은 100
				char tmpforfile[11] = { 0 };
				fscanf(fp, "%s", tmpforfile);
				//Sleep(10);
				if (tmpforfile[0] == '*') {break; }
				if (tmpforfile[0] != '*') { printf("%s\n", tmpforfile); strcpy(characters[i].goday[j], tmpforfile); }
			}//fscanf(fp, "\n");
			//char onlyforcheck[100] = { 0 };
			//fscanf(fp, "%s",onlyforcheck);
			//printf("%s %d번째", onlyforcheck,i);
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
	printf("날짜로 보는 수로간 사람 수를 보려면 0을 눌러주세요.\n캐릭터순으로 보는 수로간 횟수를 보려면 1을 눌러주세요\n");
	scanf("%d", &rnseorksek);
	while (rnseorksek == 1) {
		system("cls");
		printf("          캐릭터순으로 보는 수로간 횟수(1번이상)\n");
		for (int i = 0; i < limitedguildpeople; i++) {
			if ((characters[i].deleted == 1)&&(numberofsuropeoplegone[peopleorderab[i]]>1)) {
				printf("%20s:", characters[peopleorderab[i]].name);
				for (int j = 0; j < numberofsuropeoplegone[peopleorderab[i]]; j++) {
					setcolor(8, 8); printf(" "); setcolor(7, 0);
				}
				float percentageofeffort = (float)numberofsuropeoplegone[peopleorderab[i]] / 29.0;
				printf("%d번 %4f%%\n", numberofsuropeoplegone[peopleorderab[i]],percentageofeffort*100);
			}
			//Sleep(100);
		}
		printf("메인화면으로 가려면 -1을 입력해주세요.");
		scanf("%d", &abbcs);
		if (abbcs < 0) { break; }
	}
	while (rnseorksek == 0) {
		system("cls");
		printf("각 수로 해당차에 갔던 사람들을 나타냅니다. 회차를 입력하면 그 회차에 갔던 사람이 나옵니다.\n");
		for (int z = 1; z < 30; z++) {
			printf("%2d회차:%s", z, temprepeatweek[weekorderab[z]]);
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
			printf("%d명\n", countpeopleinsuro);
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
			printf("\n메인화면으로 가시려면 -1을 눌러주세요");
			scanf("%d", &abbcs);
		}
		if (abbcs < 0) { break; }
	}
}
void savedata(int peopleall) {
	FILE* fp;
	fp = fopen("guild_data", "w");
	if (fp == NULL) { printf("파일을 저장하지 못했습니다."); }
	if (fp != NULL) {
		fprintf(fp, "%d %d", peopleall, alltotalpeople);
		fprintf(fp, " %d %d-%d-%d %d:%d:%d\n", tm.tm_wday, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		if (alltotalpeople != 0) {
			for (int i = 0; i < peopleall; i++) {
				if (characters[i].deleted == 1) {
					fprintf(fp, "%s %d %s %d %d %d\n", characters[i].name, characters[i].level, characters[i].job, characters[i].twoweeks_pla, characters[i].total_pla, characters[i].deleted);
					for (int j = 0; j < numberofsuro; j++) { //numberofsuro는  define에서 정의한것으로 코드로 이미 정해둠 지금은 100
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
			printf("성공적으로 저장되었습니다!!");
		}
	}
void plagscore() {
	system("cls");
	while (1) {
		printf("플래그 점수를 입력하실 길드원의 닉네임을 입력해주세요.\n메인화면으로 돌아가시려면 0을 눌러주세요.\n");
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
		if (check == 0) { printf("해당되는 %s캐릭터가 없습니다.\n",tmpname); }
		if (check == 1) {
			printf("몇 점을 추가 하시겠습니까?(-도 사용가능)(-1은 사용불가)\n");
			while (check==1) {
				scanf("%d", &checktwo);
				//printf("%d\n", checktwo);
				rewind(stdin);
				if(-1 != checktwo){break;}
				printf("잘못된 값을 입력했습니다. 다시 숫자로 입력해주세요.\n");
				//checktwo = 0;
			}
			printf("%d점에서 %d점을 추가하여 %d점이 됩니다.\n", characters[plage].twoweeks_pla, checktwo, characters[plage].twoweeks_pla + checktwo);
			characters[plage].twoweeks_pla += checktwo;
		}
	}
}
void guildedit(int allnumber) {
	system("cls");
	while (1) {
		printf("수정하실 길드원의 이름을 입력해 주세요.\n0을 누르면 다시 메뉴로 돌아갑니다.\n");
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
		if (check == 0) { printf("해당되는 캐릭터가 없습니다.\n"); }
		if (check == 1) {
			printf("수정하실 정보를 입력해주세요.\n");
			printf("1.레벨\n2.직업\n3.수정안함\n");
			scanf("%d", &checktwo);
			if (checktwo == 1) {
				printf("%s님의 레벨을 수정합니다.\n 현재 레벨은 %dLv입니다.\n수정하실 레벨을 입력해주세요.\n", characters[numberedit].name, characters[numberedit].level);
				int getnewlevel = 0;
				scanf("%d", &getnewlevel);
				printf("%s님의 레벨이 %d레벨에서 %d로 수정되었습니다.\n", characters[numberedit].name, characters[numberedit].level, getnewlevel);
				characters[numberedit].level = getnewlevel;
			}
			if (checktwo == 2) {
				printf("%s님의 직업을 수정합니다.\n 현재 직업은 %s입니다.\n수정하실 직업을 입력해주세요.\n", characters[numberedit].name, characters[numberedit].job);
				char getnewjob[2000] = { 0 };
				//getchar();
				scanf("%s", getnewjob);
				rewind(stdin);
				printf("%s님의 직업이 %s직업에서 %s로 수정되었습니다.\n", characters[numberedit].name, characters[numberedit].job, getnewjob);
				strcpy(characters[numberedit].job , getnewjob);
			}
		}
	}
}
void guilddelete(int allnumber) {
	system("cls");
	while (1) {
		//printf("길드원을 삭제합니다.\n");
		printf("삭제하실 길드원의 이름을 입력해주세요.0을 누르면 다시 메뉴로 돌아갑니다.\n");
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
		if (check == 0) { printf("해당되는 캐릭터가 없습니다.\n"); }
		if (check == 1) {
			printf("%s을(를) 삭제합니다. 0을 누르면 삭제되고 1을 누르면 다시 선택합니다.\n", tmpname);
			scanf("%d", &checktwo);
			if (checktwo == 0) {
				printf("%s을 삭제합니다.\n", characters[numberdelete].name);
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
	printf("길드원을 새로 저장합니다.\n");
	printf("길드원을 한명씩 확인하며 저장할거면 1번, maple.gg에 있는 정보를 붙여넣기 하시려면 2번을 눌러주세요.\n");
	while (1) {
		scanf("%d", &check);
		if ((check == 1) || (check == 2)) { break; }
		rewind(stdin);
		printf("잘못된 값을 입력하셨습니다 1이나 2중에서 입력해주세요.\n");
	}
	int checkgg = 0;
	if (check == 2) { printf("https://maple.gg에 들어가셔서 운영진 부터~사이트 끝까지 복사해서 붙여넣어세요\n 5초있다 넣어주세요.\n★끝내시려면 마지막에 꼭 0을 입력하셔야합니다.\n"); waitcount(5); system("cls"); }
	int waitforonetime = 0;//checkgg가 5일때 마지막 활동일 기록 안하기 위해서. 2번쉼
	int waitfortwotime = 0;//한번쉼
	int duplicated = 0;
	int letsfindnew = 0;
	int newguild = 0;
	while (check != -1) {
		//int newguild = 0;
		int outgg = 0;
		int duplicated1 = 0;
		if (letsfindnew==0){
		for (int i = 0; i < limitedguildpeople; i++) {
			if (characters[i].deleted == 0) { newguild = i; letsfindnew = 1; break; } //기존에 저장안된 공간 찾는 코드
			}
			}
		if (check == 2) {
			//	for (int gg = 0;gg>-1; gg++) {
			char mapleggtmp[1000] = { 0 };
			getchar();
			scanf("%s", mapleggtmp);//이름 받음
			for (int i = 0; i < limitedguildpeople; i++) {
				if (characters[i].deleted == 1) {
					if (strcmp(characters[i].name,mapleggtmp) == 0) {
						//printf("같은 이름이 나옴%s\n", characters[i].name);
						duplicated++; newguild = i; //printf("%dnewguild i로 바꿔야지\n", newguild);
						if (duplicated == 1) {
							free(characters[newguild].job);
						}
						//printf("duplicated%d\n",duplicated);
						{ break; }
					}
				}
			}
			//printf("\n*%s*mapleggtmp\n", mapleggtmp);
			//if (waitfortwotime == 1) { checkgg = 3; printf("%s", mapleggtmp); }//한번 쉬기 위해서 직업 넣을때 그위에 <-수정해야됨<<수정
			if (strlen(mapleggtmp) == 1) { system("cls"); printf("이름 저장이 완료되었습니다.\n"); outgg = 1; break; }
			if ((checkgg == 2) || (checkgg == 4)) { //<<수정 checkgg
				//if (duplicated <2) {
				//printf("duplicated=%d", duplicated);
				//if (duplicated == 2) { free(characters[newguild].job); characters[newguild].job = NULL; }
				char ggjob[1000] = { 0 };
				int gglv = 0;
				//int getggg = 0;
				for (int ggg = 0; mapleggtmp[ggg] != '/'; ggg++) {//문자에서 직업추출
					ggjob[ggg] = mapleggtmp[ggg];
					//printf("실행확인");
				}
				//printf("%s", ggjob);
				int controlten = 100;//자릿수맞쳐줌
				for (int ggg = 0; ggg < strlen(mapleggtmp); ggg++) {//문자에서 레벨 추출
					if ((mapleggtmp[ggg] >= '0') && (mapleggtmp[ggg] <= '9')) {
						gglv += controlten * (mapleggtmp[ggg] - '0');
						controlten /= 10;
					}
				}
				characters[newguild].job = (char*)malloc((strlen(ggjob) + 1) * sizeof(char));//직업값 넣어줌
				strcpy(characters[newguild].job, ggjob);
				if (characters[newguild].deleted == 1) { if (characters[newguild].level != gglv) { printf("%s의 레벨이 올랐습니다.%d->%d", characters[newguild].name,characters[newguild].level, gglv); } }
				characters[newguild].level = gglv;
				//printf("duplicated%d\n", duplicated);
				if (duplicated>=2){
					printf("%s %dLv %s이(가) 수정되었습니다.%d \n", characters[newguild].name, characters[newguild].level, characters[newguild].job,newguild);
					//Sleep(1000);
				}
				if (duplicated < 1) {
					//Sleep(5000);
					printf("%s %dLv %s이(가) 등록되었습니다. \n", characters[newguild].name, characters[newguild].level, characters[newguild].job);
					//printf("duplicated=%d", duplicated);
					characters[newguild].deleted = 1;
					characters[newguild].twoweeks_pla = 0;
					characters[newguild].total_pla = 0;
				}
				if (checkgg == 2) { checkgg = 0; }
				if (checkgg == 4) { checkgg = 0; }//<<수정 checkgg
			//}////
		}
			if ((checkgg == 1) || (checkgg == 3)) {//<<수정 checkgg
				//if (duplicated < 2) {//
				//printf("duplicated2=%d new guild=%d",duplicated,newguild);
				//if (duplicated != 2) {
				if (duplicated < 2) {
					characters[newguild].name = (char*)malloc((strlen(mapleggtmp) + 1) * sizeof(char));
					strcpy(characters[newguild].name, mapleggtmp);//}
				}
					if (checkgg == 1) { checkgg = 2; }
					if (checkgg == 3) { checkgg = 4; }//<<수정 checkgg
				//}//duplicated 관련 간단 메모, 마스터,부마스터는 duplicated가 마지막에 1이나오고 일반 길드원들은 1나온다.
			}
			if ((strcmp(mapleggtmp, "마스터") == 0) || (strcmp(mapleggtmp, "부마스터") == 0)) { checkgg = 1; }
			if (waitfortwotime == 1) { waitfortwotime = 0; checkgg = 3; }
			if ((strcmp(mapleggtmp, "길드원") == 0)) { checkgg = 100; waitfortwotime = 1; duplicated = 0; }
			if (((strcmp(mapleggtmp, "전") == 0) || (strcmp(mapleggtmp, "알수없음") == 0)) && (checkgg != 1) && (checkgg != 100)) { waitfortwotime = 1; duplicated = 0; letsfindnew = 0; }//<<수정 checkgg
			//if (checkgg == 5) { waitforonetime++; }//<<수정 checkgg
			//if (waitforonetime == 3) { waitforonetime = 0; checkgg = 3; }//<<수정 checkgg
			//printf("check gg=%d waitforonetime%d waitfortwotime %d\n", checkgg,waitforonetime,waitfortwotime); //<<수정checkgg
			//printf("duplicated=%d", duplicated);
		}
		//} if (outgg == 1) { break; }
	//	printf("%d", characters[newguild].deleted);
		if (check == 1) {
			printf("길드원의 닉네임은 무엇인가요?(그만 저장하고 싶으시면 0을 입력해주세요.)\n");
			getchar();
			char tmpname[1000] = { 0 };
			scanf("%s", tmpname);
			if (strlen(tmpname) == 1) { system("cls"); break; }
			characters[newguild].name = (char*)malloc((strlen(tmpname) + 1) * sizeof(char));
			strcpy(characters[newguild].name, tmpname);
			printf("%s님이 새로 등록되었습니다. 레벨은 몇렙인가요?\n", characters[newguild].name);
			//getchar();
			scanf("%d", &characters[newguild].level);
			printf("%s님은 %d레벨입니다. 직업은 무엇인가요?\n", characters[newguild].name, characters[newguild].level);
			getchar();
			char tmpjob[1000] = { 0 };
			scanf("%s", tmpjob);
			characters[newguild].job = (char*)malloc((strlen(tmpjob) + 1) * sizeof(char));
			strcpy(characters[newguild].job, tmpjob);
			printf("%s %dLv %s이(가) 등록되었습니다. \n", characters[newguild].name, characters[newguild].level, characters[newguild].job);
			characters[newguild].deleted = 1;
			characters[newguild].twoweeks_pla = 0;
			characters[newguild].total_pla = 0;
			letsfindnew = 0;
		}
		//	printf("%d deleted값은 그리고 newguild의 값은%d\n", characters[newguild].deleted,newguild);
			/*if (check == 1) {
				printf("메인화면으로 돌아가시려면 -1을 입력해주세요. 계속 저장하실거면 -2를 입력해주세요.");
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
		//allnumber=마지막이 아니고 limitedguildpeople이였네
		if (check == -2) { for (int j = 0; j < 17; j++) { if (showthingstart < onlyforshow - 17) { showthingstart++; } if (showthinglast < onlyforshow) { showthinglast++; } } }
		if (check == -3) { for (int j = 0; j < 17; j++) { if (showthingstart > 0) { showthingstart--; } if (showthinglast > 17) { showthinglast--; } } }
		//printf("check=%dallnumber=%dshowthingstart=%dshowthingfinal=%d\n", check,allnumber,showthingstart, showthinglast);
		int colorchangeonebyone = 0;
		for (int i = showthingstart; i < showthinglast; i++) {
			if (characters[relocates[i]].deleted == 1) {
				if (colorchangeonebyone == 1) { setcolor(0, 10); colorchangeonebyone = -1; }
				if (colorchangeonebyone == 0) { setcolor(0, 11); colorchangeonebyone = 1; }
				printf("%3d. 닉네임:%12s 레벨:%dLv 직업:%18s 1주간 플래그 점수:%3d 플래그 총 점수:%5d 수로 간 날을 확인하려면 %3d을 입력해주세요.\n", i, characters[relocates[i]].name, characters[relocates[i]].level, characters[relocates[i]].job, characters[relocates[i]].twoweeks_pla, characters[relocates[i]].total_pla, relocates[i]);
				setcolor(7, 7);
				for (int dec = 0; dec < 146; dec++) { printf("="); }//경계선 만들어줌.
				setcolor(7, 0);
				printf("\n");
				if (colorchangeonebyone == -1) { colorchangeonebyone = 0; }
			}
		}
		//int check = -99;
		printf("메인화면으로 돌아가고 싶으시면 -1을 입력해주세요.\n");
		int askorder = -2;//뒤에서 배열 순서 바꿀때씀
		if (showthingstart == 0) { printf("다음 사람들을 보고 싶으면 -2를 입력해주세요.\n"); }
		else if (showthinglast == onlyforshow) { printf("이전 사람들을 보고 싶으면 -3을 입력해주세요.\n"); }
		else { printf("다음 사람들을 보고 싶으면 -2를 입력해주세요.\n이전 사람들을 보고 싶으면 -3을 입력해주세요.\n"); }
		printf("길드원 정렬순을 바꾸고 싶으면 -4를 입력해주세요.\n");
		printf("찾고싶은 길드원이 있으면 -5를 입력해주세요\n");
		if (check == -4) {
			system("cls");
			printf("길드원의 순서를 바꿉니다.\n");
			printf("0.변화없음\n");
			printf("1.레벨 내림차순(높은 레벨->낮은 레벨)\n");
			printf("2.레벨 오름차순(낮은 레벨->높은 레벨)\n");
			printf("3.총 플래그 점수 내림차순\n");
			printf("4.이번주 플래그 점수 내림차순\n");
			scanf("%d", &askorder);
			if (askorder == 0) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//배열 초기화 
				printf("원래대로 배열이 완료 되었습니다.\n변경된 배열을 보시려면 0을 입력해주세요.\n");
			}
			if (askorder == 1) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//배열 초기화 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].level < characters[relocates[relocatearr + 1]].level) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(레벨)내림차순으로 배열이 완료 되었습니다.\n변경된 배열을 보시려면 0을 입력해주세요.\n");
			}
			if (askorder == 2) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//배열 초기화 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].level > characters[relocates[relocatearr + 1]].level) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(레벨)오름차순으로 배열이 완료 되었습니다.\n변경된 배열을 보시려면 0을 입력해주세요.\n");
			}
			if (askorder == 3) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//배열 초기화 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].total_pla < characters[relocates[relocatearr + 1]].total_pla) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(총 플래그 점수)내림차순으로 배열이 완료 되었습니다.\n변경된 배열을 보시려면 0을 입력해주세요.\n");
			}
			if (askorder == 4) {
				for (int askorders = 0; askorders < 200; askorders++) { relocates[askorders] = askorders; }//배열 초기화 
				for (int repeat_relo = 0; repeat_relo < onlyforshow; repeat_relo++) {
					for (int relocatearr = 0; relocatearr < onlyforshow - 1; relocatearr++) {
						if (characters[relocates[relocatearr]].twoweeks_pla < characters[relocates[relocatearr + 1]].twoweeks_pla) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
					}
				}
				printf("(이번주 플래그 점수)내림차순으로 배열이 완료 되었습니다.\n변경된 배열을 보시려면 0을 입력해주세요.\n");
			}
		}
		if (check == -5) {
			system("cls");
			printf("찾고 싶은 길드원의 이름을 입력해주세요.\n");
			char getfindname[100] = { 0 };
			scanf("%s", getfindname);
			rewind(stdin);
			//printf("\n%s\n", getfindname);
			int getfindnameint = -1;
			for (int findname = 0; findname < onlyforshow; findname++) {
				if (characters[findname].deleted == 1) {
					if (strcmp(characters[findname].name, getfindname) == 0) {
						printf("값을 찾았습니다\n"); setcolor(8, 0);
					 printf("%d. 닉네임:%s 레벨:%dLv 직업:%s 2주간 플래그 점수:%d 플래그 총 점수:%d 수로 간 날을 확인하려면 %d을 입력해주세요.\n", findname, characters[relocates[findname]].name, characters[relocates[findname]].level, characters[relocates[findname]].job, characters[relocates[findname]].twoweeks_pla, characters[relocates[findname]].total_pla, relocates[findname]);
					 setcolor(7, 0);
					 printf("메인화면으로 돌아가고 싶으시면 -1을 입력해주세요.\n");
					 printf("길드원 정렬순을 바꾸고 싶으면 -4를 입력해주세요.\n");
					 printf("찾고싶은 길드원이 있으면 -5를 입력해주세요\n");
					 getfindnameint = findname; break; }
				}
			}
			if (getfindnameint == -1) { printf("값을 찾지못했습니다. 다시 확인해주세요 %s\n", getfindname); 
			printf("메인화면으로 돌아가고 싶으시면 -1을 입력해주세요.\n");
			printf("길드원 정렬순을 바꾸고 싶으면 -4를 입력해주세요.\n");
			printf("찾고싶은 길드원이 있으면 -5를 입력해주세요\n");
			}
		}
		if (askorder != -2) { scanf("%d", &check); system("cls"); }
		if (askorder == -2) {
			scanf("%d", &check);
			if (check == -1) { rewind(stdin); system("cls"); break; }
			system("cls");
			if (check > -1 && check < onlyforshow) {
				showsuro(check, weeksofunder);
				printf("메인화면으로 돌아가고 싶으시면 -1을 입력해주세요\n이전화면으로 돌아가고 싶으시면 0을 입력해주세요\n");
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
			printf("%s님은 %s에 수로 가셨습니다.\n", characters[check].name, characters[check].goday[i]);
		}
	}
}
int intro() {
	system("cls");
	printf("안녕하세요 베스트친구 길드 시스템 관리 창에 오신것을 환영합니다.\n");
	printf("마지막 저장일자:%s\n", dayoflastedit);
	printf("원하는 번호를 입력하신후 엔터를 입력해주세요.\n");
	printf("1.저장되어 있는 길드원 전체 조회\n");
	printf("2.길드원 신규등록\n");
	printf("3.기존 길드원 삭제\n");
	printf("4.기존 길드원 정보 수정\n");
	printf("5.수로 정보 입력\n");
	printf("6.플래그 정보 입력\n");
	printf("7.길드스킬 쓸 수 있는 사람 확인\n");
	printf("8.프로그램 종료 (종료시 꼭 종료입력해주세요)\n");
	printf("9.없어진 길드원 목록\n");
	printf("10.플래그 위에서부터 순서대로 나타내기.\n");
	printf("11.통계\n");
	int getmenu = 0;
	while (1) {
		scanf("%d", &getmenu);
		if ((getmenu >= 1) && (getmenu <= 11)) { break; }
		printf("잘못된 값을 입력했습니다. 1~11사이에서 입력해주세요\n"); rewind(stdin);
	}
	if (getmenu == 8) { system("cls"); printf("프로그램을 종료합니다."); } //여기에 수정된 파일 내용 저장하고 메모장 닫기.
	return getmenu;
}
void undergroundwaterway() {
	//	printf("오늘 수로 간 사람은 몇명입니까?\n");
	//	int numberofpeople = 0;
	//	scanf("%d", &numberofpeople);
	//	printf("%d명이 갔습니다. 오늘은 몇년 몇월 몇일입니까? 2020/01/28 예시 처럼 써주세요\n", numberofpeople);
	system("cls");
	for (int asd = 0; asd < 1; asd++) {
		printf("언제 수로를 갔습니까? 2020/11/28 예시 처럼 써주세요\n");
		char dayoftoday[11];
		scanf("%s", dayoftoday);
		getchar();
		if ((dayoftoday[4] != '/') || (dayoftoday[7] != '/')||(strlen(dayoftoday)!=10)) { printf("올바르지 않은 형식 입니다. xxxx/xx/xx형태로 써주세요\n 3초있다 메인 메뉴로 돌아갑니다.\n"); for (int pp = 0; pp < 3; pp++) { printf("%d\n", 3 - pp); Sleep(1000); } break; }
		numberofweek = calculatetheweek(dayoftoday);
		//for (int j=0;j<limitedguildpeople;j++){if(characters[j].goday[numberofweek]) }
		printf("오늘은 %s입니다. 수로간 사람의 닉네임을 입력해주세요.\n*다 입력하셨으면 마지막에 0을 입력해주세요*\n이해 하셨으면 enter키를 한번 누르고 작성해주세요.\n", dayoftoday);
		int wait = 0;
		char** ppt = NULL;
		ppt = (char**)malloc(200 * (sizeof(char*))); //일단 2중 동적배열 시작
		wait = getchar();
		system("cls");
		int numberofnewline = 1;//리스트에 없는 이름 저장용
		//int dayoffirst = 0;//첫번째로 기록한 날
		for (int i = 0; i < limitedguildpeople; i++) {
			char nametmp[limitedguildpeople] = { 0 };
			scanf("%s", nametmp);
			getchar();
			int checkinlist = 0;//한번이라도 이것이 작동하면 밑에서 작동안하게 함.
			if (strlen(nametmp) == 1) { break; }
			for (int j = 0; j < limitedguildpeople; j++) {
				if (characters[j].deleted == 1) {								//동적할당 안된 부분 값을 읽어 계속 오류가 생김.
					if (strcmp(characters[j].name, nametmp) == 0) {
						strcpy(characters[j].goday[numberofweek], dayoftoday);
						checkinlist++;//한번이라도 이것이 작동하면 밑에서 작동안하게 함.
						printf("%s을 성공적으로 입력 받았습니다.\n", characters[j].name);
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
				numberofnewline++;//새로운 값 받을수있게 1더해줌.
			}
		}
		if (numberofnewline > 1) {
			printf("기존 명단에 없는 사람이 %d명있습니다.\n", numberofnewline - 1);
			for (int i = 1; i < numberofnewline; i++) {
				int getok = 0;
				printf("%s사람을 새로 명단에 추가하려면 1을 눌러주세요. 추가하지 않으려면 2를 눌러주세요.\n", ppt[i]);
				scanf("%d", &getok);
				if (getok == 1) {
					int newguild = 0;	for (int i = 0; i < limitedguildpeople; i++) { if (characters[i].deleted == 0) { newguild = i; break; } }//기존 배열에서 빈곳 찾는코드
					characters[newguild].name = (char*)malloc((strlen(ppt[i]) + 1) * sizeof(char));
					strcpy(characters[newguild].name, ppt[i]);
					printf("%s님이 새로 등록되었습니다. 레벨은 몇렙인가요?\n", characters[newguild].name);
					//getchar();
					scanf("%d", &characters[newguild].level);
					printf("%s님은 %d레벨입니다. 직업은 무엇인가요?\n", characters[newguild].name, characters[newguild].level);
					getchar();
					char tmpjob[1000] = { 0 };
					scanf("%s", tmpjob);
					getchar();
					characters[newguild].job = (char*)malloc((strlen(tmpjob) + 1) * sizeof(char));
					strcpy(characters[newguild].job, tmpjob);
					strcpy(characters[newguild].goday[numberofweek], dayoftoday);
					printf("%s %dLv %s이(가) 등록되었습니다. \n", characters[newguild].name, characters[newguild].level, characters[newguild].job);
					characters[newguild].deleted = 1;
					characters[newguild].twoweeks_pla = 0;
					characters[newguild].total_pla = 0;
				}
				if (getok != 1) { printf("%s를 저장하지 않습니다.\n", ppt[i]); }
			}
		}
		//printf("오류찾는중");
	}
}
int controltime() {
	printf("오늘: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	/*struct tm {
		int tm_sec;          초,  range 0 to 59
		int tm_min;          분, range 0 to 59
		int tm_hour;         시간, range 0 to 23
		int tm_mday;         일, range 1 to 31
		int tm_mon;          월, range 0 to 11
		int tm_year;         1900년 부터의 년
		int tm_wday;         요일, range 일(0) to 토(6)
		int tm_yday;         1년 중 경과 일, range 0 to 365
		int tm_isdst;        써머타임
	};*/
	return tm.tm_wday;
}
int calculatetheweek(char aday[100]) {
	//2020/11/21 기준
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
	//newmonth = month - 11; //monthday=304가 나온다.
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
	//printf("totalday=%d 몇주차임=%d 확인%d", totalday,totalday/7,totalday%7);//0주차 부터 시작 2020/11/21 0주차임. 2024/3/2일부터 오류 생김.
	printf("%d주차", totalday / 7);
	return totalday / 7;
	//1,3,5,7,8,10,12 31일 
	//4,6,9,11 30일      
	//2 28일
	/*int flagyear = 0;//윤달 받기위함 4년주기
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
	}//이걸로는 3주전에 수로 간 사람 찾음
	for (int i = 0; i < limitedguildpeople; i++) {
		for (int j = 0; j < numberofsuro; j++) {
			if (characters[i].deleted == 1) {
				if (((strcmp(characters[i].goday[j], lastestsuro) == 0)) || (strcmp(characters[i].goday[j], seclastestsuro) == 0)||(characters[i].twoweeks_pla>=20)) {
					characters[i].temporarly = 1;
					peoplewhocanuseskill++;
				}
			}
		}
	}//이걸로는 2주 사이에 수로 간 사람 찾음.
	int check = -999;
	int showthingstart = 0;
	int showthinglast = 35;
	printf("가장 최근 수로 간 날을 기준으로 찾겠습니다.\n");//나중에 여기에 마지막 검사 주 입력받고 일주일 지나면 전체 플래그 간거 확인 temporarly에서 1빼면됨
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
		printf("가장 최근 수로 간 주=%s,가장 최근 수로 간 이전 주=%s\n", lastestsuro, seclastestsuro);
		printf("메인화면으로 돌아가고 싶으시면 -1을 입력해주세요.\n");
		printf("총 스킬을 쓸 수 있는 사람 수=%d", peoplewhocanuseskill);
		if (showthingstart == 0) { printf("다음 사람들을 보고 싶으면 -2를 입력해주세요.\n"); }
		else if (showthinglast == peoplewhocanuseskill) { printf("이전 사람들을 보고 싶으면 -3을 입력해주세요.\n"); }
		else { printf("다음 사람들을 보고 싶으면 -2를 입력해주세요.\n이전 사람들을 보고 싶으면 -3을 입력해주세요.\n"); }
		scanf("%d", &check);
		rewind(stdin);
		if (check == -1) { system("cls"); break; }
		system("cls");
	}*/
	int dayoftoday = controltime();
	printf("가장 최근 수로 간 주=%s,가장 최근 수로 간 이전 주=%s,2주전에 간 수로=%s\n", lastestsuro, seclastestsuro,thirdlastestsuro);
	int coloronebyone = 0;
	int changeline = 0;
	peoplewhocanuseskill = 0;
	setcolor(7, 6);
	printf("길드 스킬을 쓸 수 있는 사람.\n");
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
	printf("\n길드 스킬을 쓸 수 없게된 사람.\n");
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
	printf("\n총 스킬을 쓸 수 있는 사람 수=%d\n", peoplewhocanuseskill);
	printf("총 스킬을 못 쓰게된 사람 수=%d\n",peoplewhocantuseskill);
	printf("메인화면으로 돌아가고 싶으시면 -1을 입력해주세요.\n");
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
	int soresult = totaltodays - totalpldays;//0일 6토
	int howmakemon = 8 - dayoflasteditday; //ex 오늘 화 6이나옴
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
		printf("플래그 기록들이 일주일 넘어갔습니다. 넘어간 %d기록들을 변환했습니다.\n",counthowmanyplayed);
		waitcount(3);
	}
}
void isheout() {
	system("cls");
	printf("기존 저장되어있는 길드원 명단과 비교해, 길드를 탈퇴한 사람을 찾습니다.\n");
	printf("maple.gg에서 2.길드원 신규등록에서 2번처럼 복사해서 붙어넣어주세요.\n");
	printf("※마찬가지로 마지막에는 0을 입력해주세요. 3초 있다 시작합니다.\n");
	waitcount(3);
	system("cls");
	printf("지금 값을 입력해주세요.\n");
	for (int i = 0; i < limitedguildpeople; i++) {
		characters[i].checkout = 0;
	}
	int repeatuntilout = 0;
	while (repeatuntilout == 0) {
		char tmpforout[100] = { 0 };
		scanf("%s", tmpforout);
		//printf("tmpforout=%s\n", tmpforout);
		//rewind(stdin);
		if ((strcmp(tmpforout, "전") == 0) || (strcmp(tmpforout, "알수없음") == 0) || (strcmp(tmpforout, "운영진") == 0) || (strcmp(tmpforout, "길드원") == 0)) {
			char checkdeletename[100] = { 0 };
			rewind(stdin);
			scanf("%s", checkdeletename);
			if (strcmp(checkdeletename, "길드원") == 0) {
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
	int onlyforwaiting4 = 0;//개별 삭제시 while 조건 앞
	while (onlyforwaiting4 == 0) {
		printf("길드에 탈퇴한 사람:");
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
		if (peoplewhoguildout == 0) { printf("길드를 탈퇴한 사람이 없습니다.\n"); waitcount(3); break; }
		printf("\n총 길드 탈퇴한 사람들 수:%d\n", peoplewhoguildout);
		printf("메인화면으로 돌아가려면 -1을 입력해주세요.\n");
		printf("길드를 탈퇴한 사람들을 일괄 삭제하려면 -2을 입력해주세요.\n");
		printf("개별적으로 길드원을 삭제하고 싶으면 길드원의 번호(1~%d)를 입력해주세요.\n",peoplewhoguildout);
		int onlyforwaiting1 = 0;//삭제 메뉴판 만들기
		int onlyforwaiting2 = 0;//마지막까지 삭제여부 확인
		int onlyforwaiting3 = 0;//개별 삭제시 while 조건
		scanf("%d", &onlyforwaiting1);
			if ((onlyforwaiting1 >= 0) && (onlyforwaiting1 <= peoplewhoguildout)) {
				printf("※%s를 정말로 삭제하시겠습니까?\n1을 입력하면 삭제\n2를 입력하면 삭제하지 않습니다.\n", characters[whoguildoutarr[onlyforwaiting1]].name);
				scanf("%d", &onlyforwaiting2);
				if (onlyforwaiting2 == 1) {
					printf("%s을 삭제합니다.\n", characters[whoguildoutarr[onlyforwaiting1]].name);
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
			printf("※정말로 삭제하시겠습니까?\n1을 입력하면 삭제\n2를 입력하면 삭제하지 않습니다.\n");
			scanf("%d", &onlyforwaiting2);
			for (int ppp = 1; ppp < peoplewhoguildout + 1; ppp++) {
				if (onlyforwaiting2 == 1) {
					printf("%s을 삭제합니다.\n", characters[whoguildoutarr[ppp]].name);
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
	printf("이번주 총 얻은 플래그 점수를 입력하려면 1번, 바로 메뉴판을 보려면 2번을 입력해주세요.\n");
	scanf("%d", &menuoneweekplag);
	if (menuoneweekplag == 1) {
		printf("이번주 얻은 플래그 점수는 몇 점 입니까?\n");
		scanf("%d", &realtotalweekplag);
		printf("\n%d점\n", realtotalweekplag);
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
	printf("일주일 동안 플래그 뛴 사람들을 나타냅니다.\n");
	printf("오늘: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("총 참가 인원:%d 이번주 총 얻은 플래그 점수:%d 기록된 이번주 총 얻은 플래그 점수:%d %0.2lf%%\n", totalpeopleoneweekplag,realtotalweekplag,recordtotalweekplag,percentageoneweekplag);
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

	for (int askorders = 0; askorders < limitedguildpeople; askorders++) { relocates[askorders] = askorders; }//배열 초기화 
	for (int repeat_relo = 0; repeat_relo < limitedguildpeople; repeat_relo++) {//플래그 1주간 높은 순서대로 배열
		for (int relocatearr = 0; relocatearr < limitedguildpeople; relocatearr++) {
			if (characters[relocates[relocatearr]].deleted == 1) {
				if (characters[relocates[relocatearr]].twoweeks_pla < characters[relocates[relocatearr + 1]].twoweeks_pla) { int tmp_relocate = 0; tmp_relocate = relocates[relocatearr]; relocates[relocatearr] = relocates[relocatearr + 1]; relocates[relocatearr + 1] = tmp_relocate; }
			}
		}
	}
	int colorarr[8] = { 4,12,6,2,1,9,5,8 };
	printf("1등부터 4등까지 %d %d %d %d\n", maxoneweekplag, secmaxoneweekplag, thrmaxoneweekplag, fourmaxoneweekplag);
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
					printf("%12s 1주:%3d 총 점수:%5d", characters[relocates[i]].name, characters[relocates[i]].twoweeks_pla, characters[relocates[i]].twoweeks_pla +characters[relocates[i]].total_pla);
					countline++;
					if (countline == 4) { printf("\n"); countline = 0; countlinecolor++; if (countlinecolor == 8) { countlinecolor = 7; } }
					/*setcolor(7, 7);
					for (int dec = 0; dec < 146; dec++) { printf("="); }//경계선 만들어줌.
					printf("\n");*/
					setcolor(7, 0);
				//	if (colorchangeonebyone == -1) { colorchangeonebyone = 0; }
				}
			}
		}
		printf("\n메인화면으로 돌아가고 싶으시면 -1을 입력해주세요.\n");
		scanf("%d", &check);
}