// 2023-2 고급프로그래밍 과제: 쭈꾸미 게임
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("플레이어 수: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

void intro1() {
	system("cls");
	printf("===========================================================================\n");
	printf("=-------------------------------------------------------------------------=\n");
	printf("=---------------#-----##------------------------#-----##------------------=\n");
	printf("=-----##-----##-#-----##--#########--#########--#-----##-##------##-##----=\n");
	printf("=-----##-----##-#-----##-##---------##----------#-----##-###----###-##----=\n");
	printf("=-----##-----##-##----##-#------##--##-----##---##----##-####-##-##-##----=\n");
	printf("=-----##-----##--######---#########--#########---######--##-###--##-##----=\n");
	printf("=-#--##--#--##--------------------##---------##----------##---------------=\n");
	printf("=--###----###----------------------##---------##---------##---------------=\n");
	printf("=-------------------------------------------------------------------------=\n");
	printf("=---------------------------#########----##---###-----###-#########-------=\n");
	printf("=--------------------------##-----------####--####---####-##++++++--------=\n");
	printf("=--------------------------#---#####---##++##-#####-##-##-##++#########---=\n");
	printf("=---------------------------#########--#++++##-##-####-##-##++++++#-------=\n");
	printf("=-----------------------------------##--------###---------#########-------=\n");
	printf("=------------------------------------##--------##-------------------------=\n");
	printf("=-------------------------------------------------------------------------=\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("===========================================================================\n\n");
	printf("                    쭈꾸미 게임에 오신 것을 환영합니다!\n\n");
	printf("===========================================================================\n");
	Sleep(1000);
}
void intro2() {
	system("cls");
	printf("===========================================================================\n");
	printf("=-------------------------------------------------------------------------=\n");
	printf("=---------------#-----##------------------------#-----##------------------=\n");
	printf("=-----##-----##-#-----##--#########--#########--#-----##-##------##-##----=\n");
	printf("=-----##-----##-#-----##-##---------##----------#-----##-###----###-##----=\n");
	printf("=-----##-----##-##----##-#------##--##-----##---##----##-####-##-##-##----=\n");
	printf("=-----##-----##--######---#########--#########---######--##-###--##-##----=\n");
	printf("=-#--##--#--##--------------------##---------##----------##---------------=\n");
	printf("=--###----###----------------------##---------##---------##---------------=\n");
	printf("=-------------------------------------------------------------------------=\n");
	printf("=---------------------------#########----##---###-----###-#########-------=\n");
	printf("=--------------------------##-----------####--####---####-##++++++--------=\n");
	printf("=--------------------------#---#####---##++##-#####-##-##-##++#########---=\n");
	printf("=---------------------------#########--#++++##-##-####-##-##++++++#-------=\n");
	printf("=-----------------------------------##--------###---------#########-------=\n");
	printf("=------------------------------------##--------##-------------------------=\n");
	printf("=-------------------------------------------------------------------------=\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("===========================================================================\n\n");
	printf("                    쭈꾸미 게임에 오신 것을 환영합니다!\n");
	printf("                  총 %d명의 참가자로 쭈꾸미 게임을 시작합니다!\n\n", n_player);
	printf("===========================================================================\n");
	Sleep(2000);
}
void intro() {
	intro1();
	intro2();
}

void ending1() {
	system("cls");
	printf("=========================================================================\n\n");
	printf("                       쭈꾸미 게임의 우승자는 바로\n\n");
	printf("=========================================================================\n");
	Sleep(1000);

}
void ending2() {
	int winner = -1;

	for (int i = 0; i < n_player; i++)
		if (player[i])
			winner = player[i];
	system("cls");

	printf("=========================================================================\n\n");
	printf("                       쭈꾸미 게임의 우승자는 바로\n");
	printf("                     %d번 플레이어입니다! 축하드립니다!\n\n", winner);
	printf("=========================================================================\n");
	Sleep(2000);

}

// 73
void ending3() {
	system("cls");
	printf("=========================================================================\n\n");
	printf("제한시간이 다 되었습니다.\n생존자는 ");
	for (int i = 0; i < n_player; i++) {
		if (player[i]) {
			printf("%d번 ", i);
			Sleep(1000);
		}
	}
	printf("입니다.\n\n");
	printf("=========================================================================\n");
	Sleep(3000);
}

void ending() {
	if (n_alive == 1) {
		ending1();
		ending2();
	}
	else {
		ending3();
	}
}

int main(void) {
	jjuggumi_init();
	//sample();
	intro();
	mugunghwa();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	ending();
	return 0;
}
