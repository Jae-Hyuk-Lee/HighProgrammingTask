#include "mugunghwa.h"

void mugunghwa_init(void) 
{

    mugunghwa_map_init(10, 60);
    int x, y;
    int summonx = 2;

    for (int i = 0; i < n_player; i++) {
        // ���� �ڸ��� ������ �ٽ� ����

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

    //3�ʰ� ���ߴ� �ð��뿡 true�� �ٲ�.
    bool moveType = false;


    int deadPlayerArray[PLAYER_MAX] = { 0 };
    bool dialogonoff = false;

    while (1) {
        char dialogarray[30] = { "player dead! : " };
        // player 0�� ������ ������(4����)
        key_t key = get_key();
        if (key == K_QUIT) {
            break;
        }
        else if (key != K_UNDEFINED) {
            move_manual_mugunghwa(key, moveType);
        }

        for (int i = 1; i < n_player; i++)
        {
            if (tick % period[i] == 0 && player[i]) {
                move_random_mugunghwa(i, -1, moveType);
            }
        }
        
        //for (int i = 0; i < n_player; i++)
        //{
        //    if (pmove[i] == true)
        //    {
        //        deadPlayerArray[i] += i;
        //        dialogarray[len] = deadPlayerArray[i] + '0';
        //        dialogonoff = true;
        //    }
        //}

        //if (dialogonoff)
        //{
        //    dialog(dialogarray, 30);
        //    dialogonoff = false;
        //}

        //for (int i = 0; i < n_player; i++)
        //{
        //    pmove[i] = false;
        //}

        Print_Mugunghwa(&fisrtTick, &tickCount, &moveType, deadPlayerArray, dialogarray, &dialogonoff);

        display();
        Sleep(10);

        tick += 10;

        if (tick == 30000)
        {
            //���� ���� ���� �ֵ��� �� ����
            playerPointCheck();
            ending();
            return;
        }

        if (n_alive == 1) {
            ending1();
            ending2();
            return;
        }
    }
}