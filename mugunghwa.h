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
int Ai_randint_mugunghwa();

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기

void move_manual_mugunghwa(key_t key) {
    // 각 방향으로 움직일 때 x, y값 delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int dir;  // 움직일 방향(0~3)
    switch (key) {
    case K_UP: dir = DIR_UP; break;
    case K_DOWN: dir = DIR_DOWN; break;
    case K_LEFT: dir = DIR_LEFT; break;
    case K_RIGHT: dir = DIR_RIGHT; break;
    default: return;
    }

    // 움직여서 놓일 자리
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
        back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

        for (int j = 1; j < N_COL - 1; j++) {
            back_buf[i][1] = (2 < i && i < 6) ? '#' : ' ';
            back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
        }
    }
}

int Ai_randint_mugunghwa()
{
    int randomValue = rand() % 100;

    if (randomValue < 70) {
        return DIR_LEFT; // 왼쪽
    }
    else if (randomValue < 80) {
        return DIR_UP; // 위쪽
    }
    else if (randomValue < 90) {
        return DIR_DOWN; // 아래쪽
    }
    else {
        return DIR_STAY; // 제자리
    }

    return randomValue;
}

void move_tail_mugunghwa(int player, int nx, int ny) {
    int p = player;  // 이름이 길어서...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

void Print_Mugunghwa(int* firstTick, int *count)
{
    printf("d");
    char mugunghwa[] = "무궁화꽃이 피었습니다";
    if ((*firstTick + 200) == tick)
    {
        //느리게
        if (*count <= 11)
        {
            for (int i = 0; i < 2; i++)
            {
                //버퍼 위치 정리
                back_buf[N_ROW - 1][*count] = mugunghwa[*count];
                *count += 1;
            }
            *firstTick += 200;
        }


        //빠르게
        else if (*count > 11)
        {
            for (int i = 0; i < 2; i++)
            {
                back_buf[N_ROW - 1][*count] = mugunghwa[*count];
                *count += 1;
            }
            *firstTick += 180;
        }

        else if (*count == sizeof(mugunghwa))
        {
            //써내려간 무궁화 없애기 정리

            //for (int i = 0; i < *count; i++)
            //{
            //    back_buf[N_ROW + 3][*count] = ' ';
            //}
            *count = 0;
            *firstTick += 220;
        }

    }

}


void move_random_mugunghwa(int player, int dir) {
    int p = player;  // 이름이 길어서...
    int nx = 0 , ny = 0 ;  // 움직여서 다음에 놓일 자리
    // 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

    
    //randint_mugunghwa위 함수에서 0을 70%, 1을 10%, 2를 10%, 3을 10%로 조정.

    do {
        int ndir = Ai_randint_mugunghwa();

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
