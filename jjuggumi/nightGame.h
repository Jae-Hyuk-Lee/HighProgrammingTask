#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <string.h>

#define height 8	// �� ����
#define width 23	// �� �ʺ�
#define n_item 2	// ������ ����

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3
#define DIR_STAY    4

// �÷��̾ ���� ������ 
// 0 ����
// 1 ����
// 2 ������
int playerItem[PLAYER_MAX] = { 0 };
int playerPos[PLAYER_MAX][2] = { 0 };
int isCrushed[PLAYER_MAX] = { 0 };

int map[height][width] = { 0 };

// �ʱ�ȭ
void nightGameInit() {

    // �� �� ����
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) map[i][j] = 99;
        }
    }

    // �÷��̾� �ʱ� ��ġ ����
    for (int i = 0; i < n_player; i++) {
        int flag = 1;
        while (flag) {
            srand(time(NULL));

            playerPos[i][0] = randint(1, width - 2);
            playerPos[i][1] = randint(1, height - 2);

            flag = 0;
            for (int j = 0; j < n_player; j++) {
                if (i == j) continue;
                if (playerPos[i][0] == playerPos[j][0] && playerPos[i][1] == playerPos[j][1]) {
                    flag = 1;
                    break;
                }
            }

        }

        map[playerPos[i][1]][playerPos[i][0]] = n_item + 1 + i;
    }

    n_alive = n_player;

    // ������ �ʱ� ��ġ ����
    for (int i = 0; i < n_item; i++) {

        int flag = 1;

        while (flag) {

            int itemType = randint(1, 2);
            int itemX = randint(1, width - 2);
            int itemY = randint(1, height - 2);

            flag = 0;
            for (int j = 0; j < n_player; j++) {
                if (i == j) continue;
                if (itemX == playerPos[j][0] && itemY == playerPos[j][1]) {
                    flag = 1;
                    break;
                }
            }

            if (map[itemY][itemX] != 0) flag = 1;
            else map[itemY][itemX] = itemType;

        }

    }

}

// ��Ż
int seizure(int player1, int player2) {

    if (n_playerstatus[player1][1] > n_playerstatus[player2][1]) {
        int tmp = playerItem[player1];
        playerItem[player1] = playerItem[player2];
        if (playerItem[player1] == 1) {
            n_playerstatus[player1][0] += 1;
        }
        else {
            n_playerstatus[player1][1] += 1;
        }
        playerItem[player2] = tmp;
        return 1;
    }
    return 0;

}

// ȸ��
int appeasement(int player1, int player2) {

    if (n_playerstatus[player1][0] > n_playerstatus[player2][0]) {
        int tmp = playerItem[player1];
        playerItem[player1] = playerItem[player2];
        if (playerItem[player1] == 1) {
            n_playerstatus[player1][0] += 1;
        }
        else {
            n_playerstatus[player1][1] += 1;
        }
        playerItem[player2] = tmp;
        return 1;
    }
    return 0;

}

// ������ �Ա�
void getItem(int x, int y, int player) {

    playerItem[player] = map[y][x];

    if (map[y][x] == 1) {
        n_playerstatus[player][0] += 1;
    }
    else {
        n_playerstatus[player][1] += 1;
    }

    map[y][x] = n_item + 1 + player;

}

// �ٴ� ������ ��ȯ
void swapItem(int x, int y, int player) {

    int tmp = playerItem[player];
    playerItem[player] = map[y][x];
    if (map[y][x] == 1) {
        n_playerstatus[player][0] += 1;
    }
    else {
        n_playerstatus[player][1] += 1;
    }
    map[y][x] = tmp;

}

// �÷��̾ AI ������ �� ����
void choosePlayer(int player) {

    int c;

    while (1) {

        printf("\n �������� ���� %d�� �÷��̾ �������ϴ�. \n", player);
        printf(" ������ �Ͻðڽ��ϱ�? \n");
        printf(" 1. ��Ż\n 2. ȸ��\n");
        printf(" �Է� > ");
        scanf("%d", &c);

        if (c == 1) {
            if (seizure(0, player)) {
                printf(" %d�� �÷��̾�� ��Ż�� �����߽��ϴ�. \n", player);
            }
            else {
                printf(" ��Ż�� �����߽��ϴ�.\n");
            }
            printf(" ����Ϸ��� �ƹ�Ű�� ��������. ");
            _getche();
            system("cls");
            break;
        }
        else if (c == 2) {
            if (appeasement(0, player)) {
                printf(" %d�� �÷��̾�� ȸ���� �����߽��ϴ�. \n", player);
            }
            else {
                printf(" ȸ���� �����߽��ϴ�.\n");
            }
            printf(" ����Ϸ��� �ƹ�Ű�� ��������. ");
            _getche();
            system("cls");
            break;
        }
        else {
            printf(" �߸��� �Է��Դϴ�. �ٽ��Ϸ��� �ƹ�Ű�� ��������. ");
            _getche();

        }
    }


}

// �÷��̾� �̵�
void movePlayer(key_t key) {

    // �� �������� ������ �� x, y�� delta
    static int dx[4] = { 0, 0, -1, 1 };
    static int dy[4] = { -1, 1, 0, 0 };

    int dir;  // ������ ����(0~3)
    switch (key) {
    case K_UP: dir = DIR_UP; break;
    case K_DOWN: dir = DIR_DOWN; break;
    case K_LEFT: dir = DIR_LEFT; break;
    case K_RIGHT: dir = DIR_RIGHT; break;
    default: return;
    }

    // �������� ���� �ڸ�
    int nx, ny;
    nx = playerPos[0][0] + dx[dir];
    ny = playerPos[0][1] + dy[dir];

    if (nx < 1) return;
    if (width - 2 < nx) return;
    if (ny < 1) return;
    if (height - 2 < ny) return;

    if (map[playerPos[0][1]][playerPos[0][0]] == n_item + 1) map[playerPos[0][1]][playerPos[0][0]] = 0;

    playerPos[0][0] = nx;
    playerPos[0][1] = ny;

    isCrushed[0] = 0;

}

int findDir(int player) {

    int cY = -1;
    int cX = -1;

    for (int i = 0; i < randint(1, height - 2); i++) {
        for (int j = 0; j < randint(1, width - 2); j++) {
            if (1 <= map[i][j] && map[i][j] <= n_item) {
                cY = i;
                cX = j;
                break;
            }
        }
    }

    for (int i = 0; i < randint(1, n_player); i++) {
        if (i == player) continue;
        if (cY == -1 && cX == -1) {
            cY = playerPos[i][0];
            cX = playerPos[i][1];
        }
    }

    if (cY < playerPos[player][1]) return DIR_UP;
    else if (cY > playerPos[player][1]) return DIR_DOWN;
    else if (cX < playerPos[player][0]) return DIR_LEFT;
    else if (cX > playerPos[player][0]) return DIR_RIGHT;
    return randint(0, 3);

}

// AI �̵�
void moveAI(int player) {
    // �� �������� ������ �� x, y�� delta
    static int dx[4] = { 0, 0, -1, 1 };
    static int dy[4] = { -1, 1, 0, 0 };

    int dir;  // ������ ����(0~3)
    int key = findDir(player);
    switch (key) {
    case 0: dir = DIR_UP; break;
    case 1: dir = DIR_DOWN; break;
    case 2: dir = DIR_LEFT; break;
    case 3: dir = DIR_RIGHT; break;
    default: return;
    }

    // �������� ���� �ڸ�
    int nx, ny;
    nx = playerPos[player][0] + dx[dir];
    ny = playerPos[player][1] + dy[dir];

    if (nx < 1) return;
    if (width - 2 < nx) return;
    if (ny < 1) return;
    if (height - 2 < ny) return;

    if (map[playerPos[player][1]][playerPos[player][0]] == n_item + 1 + player) map[playerPos[player][1]][playerPos[player][0]] = 0;

    playerPos[player][0] = nx;
    playerPos[player][1] = ny;

    isCrushed[player] = 0;

}

// ������ �ε���
void crushItem(int x, int y, int player) {

    if (1 <= map[y][x] && map[y][x] <= n_item && !isCrushed[player]) {
        isCrushed[player] = 1;
        if (player == 0) {
            if (playerItem[0] != 0) {
                int c;

                printf(" �������� �̹� ���� ���Դϴ�. \n");
                printf(" �ٴڿ� �ִ� �����۰� �ٲٰڽ��ϱ�? \n");
                printf(" 0 : �����Ѵ�, 1 : �� > ");
                scanf("%d", &c);

                if (c == 0) {
                    system("cls");
                    return;
                }
                else {
                    swapItem(x, y, player);
                    printf(" �ٴڿ� �ִ� �����۰� �� �������� �ٲ���ϴ�. \n");
                    printf(" ����Ϸ��� �ƹ�Ű�� ��������");
                    _getche();
                    system("cls");
                }
            }
            else {
                getItem(x, y, player);
                printf(" �ٴڿ� �ִ� �������� �ֿ����ϴ�. \n");
                printf(" ����Ϸ��� �ƹ�Ű�� ��������");
                _getche();
                system("cls");
            }
        }
        else {

            if (playerItem[player] != 0) {
                int c = randint(0, 1);

                if (c == 0) {
                    return;
                }
                else {
                    swapItem(x, y, player);
                    return;
                }
            }
            else {
                getItem(x, y, player);
            }

        }
    }
}

// �÷��̾�� �ε���
void crushPlayer(int x, int y, int player) {

    for (int i = 0; i < n_player; i++) {
        if (i == player) continue;

        if (playerPos[i][0] == playerPos[player][0] && playerPos[i][1] == playerPos[player][1] && (!isCrushed[i] || !isCrushed[player])) {
            isCrushed[i] = 1;
            isCrushed[player] = 1;

            if (player == 0) {
                choosePlayer(i);
            }
            else {
                int c = randint(0, 1);
                if (playerItem[i] != 0 && playerItem[player] == 0) {
                    if (c) {
                        seizure(player, i);
                    }
                    else {
                        appeasement(player, i);
                    }
                }
                else if (playerItem[i] == 0 && playerItem[player] != 0) {
                    if (c) {
                        seizure(i, player);
                    }
                    else {
                        appeasement(i, player);
                    }
                }
                else {
                    if (c) {
                        seizure(i, player);
                    }
                    else {
                        appeasement(i, player);
                    }
                }
            }
        }
    }

}

// �� ���
void printNightGameMap() {

    gotoxy(0, 0);

    for (int i = 0; i < n_player; i++) {
        if (map[playerPos[i][1]][playerPos[i][0]] == 0) map[playerPos[i][1]][playerPos[i][0]] = n_item + 1 + i;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char ch = ' ';

            switch (map[i][j]) {
            case 0: ch = ' '; break;
            case 99: ch = '*'; break;
            }

            if (1 <= map[i][j] && map[i][j] <= n_item) ch = 'i';
            else if (n_item < map[i][j] && map[i][j] <= n_item + n_player) ch = '0' + (map[i][j] - (n_item + 1));

            printf("%c", ch);
        }
        printf("\n");
    }

}