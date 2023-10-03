#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <string.h>

#define DIR_LEFT	-1
#define DIR_RIGHT	1
int result[PLAYER_MAX];
int map_row = 30;
int map_col = 5;
int current_pos;
int aa;
int q = 0;
int player_turn;
int round_round;
int round = 0;


void concatStrings(const char* str1, const char* str2, char* result) {
    int i, j;

    // ù ��° ���ڿ� ����
    for (i = 0; str1[i] != '\0'; ++i) {
        result[i] = str1[i];
    }

    // �� ��° ���ڿ� ����
    for (j = 0; str2[j] != '\0'; ++j, ++i) {
        result[i] = str2[j];
    }

    result[i] = '\0';  // ���ڿ��� ���� NULL ���� �߰�
}


void reverse(char str[], int length) {
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

char* intToStr(int num, char* str) {
	int i = 0;
	bool isNegative = false;

	// 0�� ��츦 ó��
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// ������ ��츦 ó��
	if (num < 0) {
		isNegative = true;
		num = -num;
	}

	// num�� ���ڿ��� ��ȯ
	while (num != 0) {
		int rem = num % 10;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / 10;
	}

	// ������ ��� '-'�� �߰�
	if (isNegative) {
		str[i++] = '-';
	}

	str[i] = '\0'; // ���ڿ� ���� NULL ���� �߰�

	// ���ڿ� ������
	reverse(str, i);

	return str;
}

void jebi_init() {
	player_turn = 0;
	round_round = 0;
	aa = n_alive;


	while (player[player_turn] == false) {
		player_turn += 1;

	}
	

	

	current_pos = 0;
	map_init(map_col , map_row);

	for (int i = 0; i < aa; i++) {
		result[i] = 0;
	}

	result[randint(0, aa-1)] = 1;

	int row = 2;
	for (int col = 3; col < aa+3; col++) {
		if (col ==3) {
			back_buf[row][col * 2] = '@';
		}
		else {
			back_buf[row][col * 2] = '?';
		}
	}

}
void next_jebi() {
	player_turn += 1;
	round_round += 1;


	while (player[player_turn] == false) {
		player_turn += 1;

	}

	
	current_pos = 0;
	map_init(map_col, map_row);
	for (int i = 0; i < aa - round_round; i++) {
		result[i] = 0;
	}

	result[randint(0, aa - round_round - 1)] = 1;

	int row = 2;
	for (int col = 3; col < aa - round_round + 3; col++) {
		if (col == 3) {
			back_buf[row][col * 2] = '@';
		}
		else {
			back_buf[row][col * 2] = '?';
		}
	}
}


void buf_jebi(int x) {
	current_pos += x;
	
	int row = 2;
	for (int col = 3; col < aa-round_round+3; col++) {
		if (col - 3 == current_pos) {
			back_buf[row][col * 2] = '@';
		}
		else {
			back_buf[row][col * 2] = '?';
		}
	}
}
void sel_jebi(key_t key) {
	int dir = 0;  // ������ ����(0~3)
	switch (key) {
	case K_LEFT: dir += -1; break;
	case K_RIGHT: dir += 1; break;
	default: return;
	}
	if (current_pos + dir == -1 || current_pos + dir == aa-round_round) {
		return;
	}
	else {
		buf_jebi(dir);

	}
}
int get_result() {
	char str1[] = "player ";
	char str2[10];
	char str3[] = " fail!";
	char str4[] = " pass!";

	intToStr(player_turn, str2);

	char str12[sizeof(str1) + sizeof(str2) - 1];
	concatStrings(str1, str2, str12);
	if (result[current_pos] == 1) {
		char str123[sizeof(str12) + sizeof(str3) - 1];
		concatStrings(str12, str3, str123);
		dialog(str123);
		
		player[player_turn] = false;
		n_alive -= 1;
		return 1;
	}
	else {
		char str124[sizeof(str12) + sizeof(str4) - 1];
		concatStrings(str12, str4, str124);
		dialog(str124);
		return 0;
	}

}

void reset_buf() {
	int row = 2;
	for (int col = 3; col < aa + 3; col++) {
			back_buf[row][col * 2] = ' ';
	
	}
}

void jebi() {
	int cur_x = 3;
	int cur_y = 4;
	while (n_alive > 1) {
		round += 1;
		if (q == 1) {
			break;
		}

		system("cls");
		jebi_init();
		display();

		while (1) {
			key_t key = get_key();
			if (key == K_QUIT) {
				q = 1;
				break;

			}//DŰ�� ������ ���̾�α� �Լ� ȣ��
			else if (key == K_DIALOG) {
				dialog("message");
			}
			else if (key == K_SELECT) {
				reset_buf();
				if (get_result() == 1) {
					break;
				}
				else {
					next_jebi();
				}
				
			}
			else if (key != K_UNDEFINED) {

				sel_jebi(key);
			}
			else if (n_alive == 1) {
				break;
			}

			gotoxy(N_ROW, 0);
			printf("round %d, turn: player %d", round, player_turn);
			display();
			Sleep(10);
			tick += 10;
		}

	}	

}


