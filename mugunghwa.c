#include "mugunghwa.h"

void mugunghwa_init(void) 
{

    mugunghwa_map_init(10, 60);
    int x, y;
    int summonx = 2;

    for (int i = 0; i < n_player; i++) {
        // 같은 자리가 나오면 다시 생성

        do {
            x = summonx;
            y = 58;

            summonx++;

        } while (!placable(x, y));
        px[i] = x;
        py[i] = y;
        period[i] = randint(100, 500);
        pmove[i] = false;
        back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
    }

    tick = 0;

}

void mugunghwa(void) 
{
    mugunghwa_init();

    system("cls");
    display();

    int fisrtTick = 0;
    int tickCount = 0;

    //3초간 멈추는 시간대에 true로 바뀜.
    bool moveType = false;


    int deadPlayerArray[PLAYER_MAX] = { 0 };
    bool dialogonoff = false;

    while (1) {
        char dialogarray[30] = { "player dead! : " };
        // player 0만 손으로 움직임(4방향)
        key_t key = get_key();
        if (key == K_QUIT) {
            break;
        }
        else if (key != K_UNDEFINED) {
            move_manual_mugunghwa(key, moveType);
        }

        for (int i = 1; i < n_player; i++)
        {
            if (tick % period[i] == 0 && player[i].is_alive) {
                move_random_mugunghwa(i, -1, moveType);
            }
        }

        Print_Mugunghwa(&fisrtTick, &tickCount, &moveType, deadPlayerArray, dialogarray, &dialogonoff);

        display();
        Sleep(10);

        tick += 10;

        if (tick == 30000)
        {
            //영희 옆에 없는 애들은 다 죽음
            playerPointCheck();
            return;
        }

        int count = 0;

        for (int i = 0; i < n_player; i++)
        {
            if (player[i].is_alive == true)
            {
                count++;
            }
        }

        if (count == 1) {
            playerPointCheck();
            return;
        }
    }
}