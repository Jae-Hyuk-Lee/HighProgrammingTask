#pragma once

#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3
#define DIR_STAY    4


void move_manual_mugunghwa(key_t key);
void move_random_mugunghwa(int player, int dir);
void mugunghwa_map_init(int n_row, int n_col);
void move_tail_mugunghwa(int player, int nx, int ny);
int randint_mugunghwa();

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

void move_manual_mugunghwa(key_t key) {
    // �� �������� ������ �� x, y�� delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

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
    nx = px[0] + dx[dir];
    ny = py[0] + dy[dir];
    if (!placable(nx, ny)) {
        return;
    }

    move_tail_mugunghwa(0, nx, ny);
}

void mugunghwa_map_init(int n_row, int n_col)
{
    // �� ���۸��� ������ ����
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            back_buf[i][j] = front_buf[i][j] = ' ';
        }
    }

    N_ROW = n_row;
    N_COL = n_col;
    for (int i = 0; i < N_ROW; i++) {
        // ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
        back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

        for (int j = 1; j < N_COL - 1; j++) {
            back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
        }
    }
}

int randint_mugunghwa()
{
    int randomValue = rand() % 100;

    if (randomValue < 70) {
        return DIR_LEFT; // ����
    }
    else if (randomValue < 80) {
        return DIR_UP; // ����
    }
    else if (randomValue < 90) {
        return DIR_RIGHT; // �Ʒ���
    }
    else {
        return DIR_STAY; // ���ڸ�
    }

    return 0;
}

void move_tail_mugunghwa(int player, int nx, int ny) {
    int p = player;  // �̸��� ��...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

// 0 <= dir < 4�� �ƴϸ� ����


void move_random_mugunghwa(int player, int dir) {
    int p = player;  // �̸��� ��...
    int nx = 0 , ny = 0 ;  // �������� ������ ���� �ڸ�
    // ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

    int ndir = randint_mugunghwa();
    //randint_mugunghwa�� �Լ����� 0�� 70%, 1�� 10%, 2�� 10%, 3�� 10%�� ����.

    do {
        switch (ndir)
        {

        case DIR_LEFT:
            ny = py[p] - 1;
            nx = px[p];
            break;

        case DIR_UP:
            nx = px[p] - 1;
            ny = py[p];

            break;

        case DIR_DOWN:
            nx = px[p] + 1;
            ny = py[p];

            break;

        case DIR_STAY:
            break;

        default:
            printf("AI Move Error");
            break;

        }
    } while (!placable(nx, ny));

    move_tail_mugunghwa(p, nx, ny);
}




// back_buf[][]�� ���