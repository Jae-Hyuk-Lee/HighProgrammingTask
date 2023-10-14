#pragma once

#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <string.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3
#define DIR_STAY    4


void move_manual_mugunghwa(key_t key, bool moveType);
void move_random_mugunghwa(int player, int dir, bool moveType);
void mugunghwa_map_init(int n_row, int n_col);
void move_tail_mugunghwa(int player, int nx, int ny, bool moveType);
void Print_Mugunghwa(int* firstTick, int* count, bool* moveType, int* deadPlayerArray, char* dialogarray, bool* dialogonoff);
int Ai_randint_mugunghwa();

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기
bool pmove[PLAYER_MAX]; //카메라 돌렸을때 움직임 체크 
void move_manual_mugunghwa(key_t key, bool moveType) {
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


    move_tail_mugunghwa(0, nx, ny, moveType);
}

void mugunghwa_map_init(int n_row, int n_col)
{
    // 두 버퍼를를 완전히 비우기
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            back_buf[i][j] = front_buf[i][j] = ' ';
        }
    }

    //N_ROW = n_row;
    //N_COL = n_col;
    //for (int i = 0; i < (N_ROW - 1); i++) {
    //    // 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
    //    back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

    //    for (int j = 1; j < N_COL - 1; j++) {
    //        back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
    //    }
    //}


    N_ROW = n_row;
    N_COL = n_col;
    for (int i = 0; i < (N_ROW - 1); i++) {

        for (int j = 1; j < N_COL; j++) {
                if (back_buf[i][1] = (2 < i && i < 6))
                {
                    back_buf[i][1] = '#';
                }

                else
                {
                    back_buf[i][1] = ' ';
                }
                back_buf[i][j] = (i == 0 || i == N_ROW - 2) ? '*' : ' ';
        }
        back_buf[0][1] = '*';
        back_buf[N_ROW - 2][1] = '*';

        // 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
        back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

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

void move_tail_mugunghwa(int player, int nx, int ny, bool moveType) {
    int p = player;  // 이름이 길어서...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;

    if (moveType == true) pmove[p] = true;

}

void Print_Mugunghwa(int* firstTick, int *count, bool *moveType, int *deadPlayerArray, char *dialogarray, bool* dialogonoff)
{
    char mugunghwa[] = "무궁화꽃이피었습니다";

    if (*count >= sizeof(mugunghwa))
    {
        *moveType = true;
        //3초 기다리기
        if ((*firstTick + 3000) == tick)
        {
            for (int i = 0; i < *count; i++)
            {
                back_buf[N_ROW - 1][i] = ' ';
            }
            *count = 0;
            *firstTick += 3000;

            //카메라 원상복구
            for (int i = 0; i < N_COL; i++)
            {
                if (back_buf[i][1] = (2 < i && i < 6))
                {
                    back_buf[i][1] = '#';
                }

                else
                {
                    back_buf[i][1] = ' ';
                }
            }
            back_buf[0][1] = '*';
            back_buf[N_ROW - 2][1] = '*';


            //움직인 플레이어 탈락
            //dialog()
            for (int i = 0; i < n_player; i++)
            {
                int len = strlen(dialogarray);

                if (pmove[i] == true)
                {
                    deadPlayerArray[i] += i;
                    dialogarray[len] = deadPlayerArray[i] + '0';
                    *dialogonoff = true;
                }
            }

            if (*dialogonoff)
            {
                dialog(dialogarray, 30);
                *dialogonoff = false;
            }


            for (int i = 0; i < PLAYER_MAX; i++)
            {
                if (pmove[i] == true)
                {
                    player[i] = false;
                    back_buf[px[i]][py[i]] = ' ';
                }
            }

            for (int i = 0; i < n_player; i++)
            {
                pmove[i] = false;
            }

            *dialogarray = " ";

            for (int i = 0; i < PLAYER_MAX; i++)
            {
                deadPlayerArray[i] = 0;
            }

            return;
        }

        //카메라 변경
        for (int i = 0; i < N_COL; i++)
        {
            if (back_buf[i][1] = (2 < i && i < 6))
            {
                back_buf[i][1] = '@';
            }

            else
            {
                back_buf[i][1] = ' ';
            }
        }
        back_buf[0][1] = '*';
        back_buf[N_ROW - 2][1] = '*';
    }
        
    if ((*firstTick + 600) == tick)
    {
        //느리게
        if (*count <= 11)
        {
            *moveType = false;

            for (int i = 0; i < 2; i++)
            {
                //버퍼 위치 정리
                back_buf[N_ROW - 1][*count] = mugunghwa[*count];
                *count += 1;
            }
            *firstTick += 300;
        }

        else if (*count >= sizeof(mugunghwa))
        {

        }

        //빠르게
        else if (*count > 11)
        {
            *moveType = false;

            for (int i = 0; i < 2; i++)
            {
                back_buf[N_ROW - 1][*count] = mugunghwa[*count];
                *count += 1;
            }
            *firstTick += 100;
        }


    }

}

void move_random_mugunghwa(int player, int dir, bool moveType) {
    int p = player;  // 이름이 길어서...
    int nx = 0, ny = 0;  // 움직여서 다음에 놓일 자리
    // 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

    //move_random_mugunghwa위 함수에서 움직임 확률 10% 추가
    do {
        int ndir = Ai_randint_mugunghwa();

        if (moveType == true)
        {
            int rMove = rand() % 100;

            if (rMove < 90)
            {
                return;
            }
        }

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

    //해당 플레이어가 움직였다고 체크

    move_tail_mugunghwa(p, nx, ny, moveType);
}

void playerPointCheck()
{
    for (int i = 0; i < n_player; i++)
    {
        if (px[i] == 2 && py[i] == 1)
        {

        }
        else if (px[i] == 3 && py[i] == 2)
        {

        }
        else if (px[i] == 4 && py[i] == 2)
        {

        }
        else if (px[i] == 5 && py[i] == 2)
        {

        }
        else if (px[i] == 6 && py[i] == 1)
        {

        }

        else
        {
            player[i] = false;
            back_buf[px[i]][py[i]] = ' ';
        }

    }
}