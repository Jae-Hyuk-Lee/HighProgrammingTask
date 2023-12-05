#include "juldarigi.h"

void juldarigi()
{
    tick = 0;

    //center는 10 - 12사이에서만 조정되어야 함.
    int center = 11;
    float sumstr = juldarigi_player_stateprint();
    int leftDeadCount = 0;
    int rightDeadCount = 0;
    bool rightwin = false;
    bool leftwin = false;
    bool leftliedown = false;
    bool rightliedown = false;

    system("cls");
    juldarigi_map_init(3, 29);
    juldarigi_player_locate(center, &leftDeadCount, &rightDeadCount);
    display_juldarigi();

    while (1)
    {
        key_t key = get_key();
        if (key == K_QUIT) {
            break;
        }
        else if (key == K_LEFTPULL) {
            sumstr -= 1;
        }
        else if (key == K_RIGHTPULL) {
            sumstr += 1;
        }
        else if (key == K_LEFTLiEDOWN)
        {
            leftliedown = true;
            char dialogarray[30] = { "왼쪽팀 눕기!" };
            dialog2(dialogarray, 30);
        }

        else if (key == K_RIGHTLiEDOWN)
        {
            rightliedown = true;
            char dialogarray[30] = { "오른쪽팀 눕기!" };
            dialog2(dialogarray, 30);
        }


        if(tick != 0 && tick % 1000 == 0)
        {

            system("cls");

            juldarigi_map_init(3, 29);


            if (rightliedown == true)
            {
                for (int i = 0; i < n_player; i++)
                {
                    if (i % 2 != 0)
                    {
                        player[i].str *= 2;
                        player[i].stamina -= 30;

                        if (player[i].stamina <= 0)
                            player[i].stamina = 0;
                    }
                    sumstr = juldarigi_player_stateprint();
                }
            }

            if (leftliedown == true)
            {
                for (int i = 0; i < n_player; i++)
                {
                    if (i % 2 == 0)
                    {
                        player[i].str *= 2;
                        player[i].stamina -= 30;

                        if (player[i].stamina <= 0)
                            player[i].stamina = 0;
                    }
                    sumstr = juldarigi_player_stateprint();
                }
            }


            gotoxy(6, 0);
            printf("str:    %.1f", sumstr);


            //오른쪽으로 한칸 땡겨질때. 만약 센터 크기가 12보다 작으면
            if (sumstr > 0 && center < 12)
            {
                center += 1;
            }

            else if (sumstr < 0 && center > 10)
            {
                center -= 1;
            }

            juldarigi_player_locate(center, &leftDeadCount, &rightDeadCount);

            display_juldarigi();


            if (tick >= 1000)
                checkPlayerdead(center, &sumstr, &leftwin, &rightwin);

            if (leftwin == true || rightwin == true)
            {
                ending4();
                return;
            }

            if (tick == 30000)
            {
                ending4();
                return;
            }




            if (leftliedown == true)
            {
                for (int i = 0; i < n_player; i++)
                {
                    if (i % 2 == 0)
                    {
                        player[i].str /= 2;
                    }
                }
                leftliedown = false;
                sumstr = juldarigi_player_stateprint();
            }

            if (rightliedown == true)
            {
                for (int i = 0; i < n_player; i++)
                {
                    if (i % 2 != 0)
                    {
                        player[i].str /= 2;
                    }
                }
                leftliedown = false;
                sumstr = juldarigi_player_stateprint();
            }
        }

        display_juldarigi();
        tick += 10;
        Sleep(10);
    }

    ending4();
}

void checkPlayerdead(int center, float *sumstr, bool* leftwin, bool* rightwin)
{
    if (center == 12 && *sumstr > 0 && player[0].is_dead)
    {
        player[0].is_dead = false;
        char dialogarray[30] = { "player dead! : 0" };

        dialog2(dialogarray, 30);
        *sumstr = juldarigi_player_stateprint();
    }

    else if (center == 12 && *sumstr > 0 && !player[0].is_dead && !player[2].is_dead)
    {
        player[4].is_dead = false;
        char dialogarray[30] = { "player dead! : 4" };

        dialog2(dialogarray, 30);

        *rightwin = true;
    }

    else if (center == 12 && *sumstr > 0 && !player[0].is_dead)
    {
        player[2].is_dead = false;
        char dialogarray[30] = { "player dead! : 2" };
        *sumstr = juldarigi_player_stateprint();
        dialog2(dialogarray, 30);
    }

    //============================


    if (center == 10 && *sumstr < 0 && player[1].is_dead)
    {
        player[1].is_dead = false;
        char dialogarray[30] = { "player dead! : 1" };
        *sumstr = juldarigi_player_stateprint();
        dialog2(dialogarray, 30);
    }

    else if (center == 10 && *sumstr < 0 && !player[1].is_dead && !player[3].is_dead)
    {
        player[5].is_dead = false;
        char dialogarray[30] = { "player dead! : 5" };
        *sumstr = juldarigi_player_stateprint();
        dialog2(dialogarray, 30);

        *leftwin = true;
    }

    else if (center == 10 && *sumstr < 0 && !player[1].is_dead)
    {
        player[3].is_dead = false;
        char dialogarray[30] = { "player dead! : 3" };
        *sumstr = juldarigi_player_stateprint();
        dialog2(dialogarray, 30);
    }


}

void juldarigi_map_init(int n_row, int n_col)
{
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            back_buf[i][j] = front_buf[i][j] = ' ';
        }
    }

    N_ROW = n_row;
    N_COL = n_col;
    for (int i = 0; i < N_ROW; i++) {
        back_buf[i][0] = back_buf[i][N_COL - 1] = '#';
        
        for (int j = 1; j < N_COL - 1; j++) {
            back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
        }

    }

    back_buf[0][15] = ' ';
    back_buf[2][15] = ' ';
}

//플레이어 총 힘 합 출력함수
float juldarigi_player_stateprint()
{
    float sumstr = 0;

    for (int i = 0; i < n_player; i++)
    {
        if (player[i].id % 2 == 0)
        {
            if (player[i].is_dead)
            {
                if (player[i].is_alive)
                {
                    sumstr -= player[i].str;
                }

                else
                {
                    sumstr -= (player[i].str/2);
                }
            }
        }

        else
        {
            if (player[i].is_dead)
            {
                if (player[i].is_alive)
                {
                    sumstr += player[i].str;
                }

                else
                {
                    sumstr += (player[i].str/2);
                }
            }
        }
    }

    return sumstr;
}

//플레이어 위치 출력함수
void juldarigi_player_locate(int center, int *leftDeadCount, int *rightDeadCount)
{

    int printcenter = center + *leftDeadCount;

    gotoxy(1, printcenter);

    if (player[0].is_dead)
    {
        printf("%d%d%d", player[4].id, player[2].id, player[0].id);
    }

    else if (!player[2].is_dead && !player[0].is_dead)
    {
        printf("%d", player[4].id);
        *leftDeadCount += 1;

    }

    else if (!player[0].is_dead)
    {
        printf("%d%d", player[4].id, player[2].id);
        *leftDeadCount += 2;
    }

    printf("---");
    

    if (player[1].is_dead)
    {
        printf("%d%d%d", player[1].id, player[3].id, player[5].id);
    }

    else if (!player[1].is_dead && !player[3].is_dead)
    {
        printf("%d", player[5].id);
    }

    else if (!player[1].is_dead)
    {
        printf("%d%d", player[3].id, player[5].id);
    }




}

void display_juldarigi()
{
    draw();
    gotoxy(N_ROW + 4, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
    print_status_juldarigi();
}

void print_status_juldarigi()
{
    int count = 0;

    for (int i = 0; i < n_player; i++)
    {
        if (player[i].is_alive == true)
        {
            count++;
        }
    }

    printf("no. of players left: %d\n", count);
    for (int p = 0; p < n_player; p++) {
        if (player[p].is_dead)
            printf("player %2d: %5s\n", p, player[p].is_alive ? "alive" : "alive*");

        else
            printf("player %2d: %5s\n", p, "DEAD");
    }
}

void set_is_alive() {
    for (int i = 0; i < n_player; i++) {
        player[i].is_alive = !player[i].is_dead;
    }
}