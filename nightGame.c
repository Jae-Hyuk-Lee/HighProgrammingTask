#include "nightGame.h"

void nightgame() {

    system("cls");

	nightGameInit();

    int tick = 0;
    int gametick = 0;
	while (1) {

        tick += 1;
        gametick += 1;

		printNightGameMap();

        key_t key = get_key();
        if (key == K_QUIT) {
            break;
        }
        else if (key != K_UNDEFINED) {
            movePlayer(key);
        }

        if (tick >= 5) {
            for (int i = 1; i < n_player; i++) {
                moveAI(i);
            }
            tick = 0;
        }

        for (int i = 0; i < n_player; i++) {
            crushItem(playerPos[i][0], playerPos[i][1], i);
            crushPlayer(playerPos[i][0], playerPos[i][1], i);
        }

        Sleep(1000 / 20);

        if (gametick == 300)
        {
            return; 
        }
	}

}