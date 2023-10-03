#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"
#include <Windows.h>


#define DIALOG_DURATION_SEC 1
int CURRENT_MAP_SIZE_ROW;
int CURRENT_MAP_SIZE_COL;

void draw(void);
void print_status(void);

// (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	CURRENT_MAP_SIZE_ROW = n_row;
	CURRENT_MAP_SIZE_COL = n_col;
	// 두 버퍼를를 완전히 비우기
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// 상단에 맵을, 하단에는 현재 상태를 출력
void display(void) {
	draw();
	gotoxy(N_ROW + 3, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");		
	}
}
// dialog("메세지");
void dialog(char message[]) {
	int mlength = strlen(message) + 6;
	int n = DIALOG_DURATION_SEC;
	//다이얼로그 텍스트 출력 기준점
	int dialog_col = CURRENT_MAP_SIZE_ROW/5;
	int dialog_row = 3; 

	while (1) {
		if (n==0) {
			system("cls");

			//맵 복구 back_buf 사용
			for (int row = 0; row < N_ROW; row++) {
				for (int col = 0; col < N_COL; col++) {
					printxy(back_buf[row][col], row, col);
				}
			}
			break;
		}
		else {

			gotoxy(dialog_col , dialog_row);
			for (int i = 0; i < mlength; i++) {
				printf("*");
			}
			gotoxy(dialog_col+1, dialog_row);
			printf("* %d %s *",n, message);
			gotoxy(dialog_col+2, dialog_row);
			for (int i = 0; i < mlength; i++) {
				printf("*");
			}
		}
		
		Sleep(1000);
		n -= 1;
		
	}
}
