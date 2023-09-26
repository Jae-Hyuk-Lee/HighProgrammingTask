#include "mugunghwa.h"

void mugunghwa_init(void) 
{

    mugunghwa_map_init(9, 60);
    int x, y;
    int summony = 2;

    for (int i = 0; i < n_player; i++) {
        // 같은 자리가 나오면 다시 생성

        do {
            x = summony;
            y = 58;

            summony++;

        } while (!placable(x, y));
        px[i] = x;
        py[i] = y;
        period[i] = randint(100, 500);

        back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
    }

    tick = 0;

}

void mugunghwa(void) {
    mugunghwa_init();

    system("cls");
    display();
    while (1) {
        // player 0만 손으로 움직임(4방향)
        key_t key = get_key();
        if (key == K_QUIT) {
            break;
        }
        else if (key != K_UNDEFINED) {
            move_manual_mugunghwa(key);
        }

        // player 1 부터는 랜덤으로 움직임(8방향)
        for (int i = 1; i < n_player; i++) {
            if (tick % period[i] == 0) {
                move_random_mugunghwa(i, -1);
            }
        }

        display();
        Sleep(10);
        tick += 10;
    }
}