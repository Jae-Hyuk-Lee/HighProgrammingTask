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

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�
bool pmove[PLAYER_MAX]; //ī�޶� �������� ������ üũ 
void move_manual_mugunghwa(key_t key, bool moveType) {
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


    move_tail_mugunghwa(0, nx, ny, moveType);
}

void mugunghwa_map_init(int n_row, int n_col)
{
    // �� ���۸��� ������ ����
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            back_buf[i][j] = front_buf[i][j] = ' ';
        }
    }

    //N_ROW = n_row;
    //N_COL = n_col;
    //for (int i = 0; i < (N_ROW - 1); i++) {
    //    // ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
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

        // ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
        back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

    }
}

int Ai_randint_mugunghwa()
{
    int randomValue = rand() % 100;

    if (randomValue < 70) {
        return DIR_LEFT; // ����
    }
    else if (randomValue < 80) {
        return DIR_UP; // ����
    }
    else if (randomValue < 90) {
        return DIR_DOWN; // �Ʒ���
    }
    else {
        return DIR_STAY; // ���ڸ�
    }

    return randomValue;
}

void move_tail_mugunghwa(int player, int nx, int ny, bool moveType) {
    int p = player;  // �̸��� ��...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;

    if (moveType == true) pmove[p] = true;

}

void Print_Mugunghwa(int* firstTick, int *count, bool *moveType, int *deadPlayerArray, char *dialogarray, bool* dialogonoff)
{
    char mugunghwa[] = "����ȭ�����Ǿ����ϴ�";

    if (*count >= sizeof(mugunghwa))
    {
        *moveType = true;
        //3�� ��ٸ���
        if ((*firstTick + 3000) == tick)
        {
            for (int i = 0; i < *count; i++)
            {
                back_buf[N_ROW - 1][i] = ' ';
            }
            *count = 0;
            *firstTick += 3000;

            //ī�޶� ���󺹱�
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


            //������ �÷��̾� Ż��
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

        //ī�޶� ����
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
        //������
        if (*count <= 11)
        {
            *moveType = false;

            for (int i = 0; i < 2; i++)
            {
                //���� ��ġ ����
                back_buf[N_ROW - 1][*count] = mugunghwa[*count];
                *count += 1;
            }
            *firstTick += 300;
        }

        else if (*count >= sizeof(mugunghwa))
        {

        }

        //������
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
    int p = player;  // �̸��� ��...
    int nx = 0, ny = 0;  // �������� ������ ���� �ڸ�
    // ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

    //move_random_mugunghwa�� �Լ����� ������ Ȯ�� 10% �߰�
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

    //�ش� �÷��̾ �������ٰ� üũ

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