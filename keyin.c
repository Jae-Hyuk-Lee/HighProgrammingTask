#include <conio.h>
#include <stdbool.h>
#include "keyin.h"

bool is_valid(key_t key) {
	static key_t key_list[] = {
        K_ARROW,
		K_UP,
		K_DOWN,
		K_LEFT,
		K_RIGHT,
		K_QUIT,
		K_DIALOG,
		K_SELECT,
        K_LEFTPULL,
        K_RIGHTPULL,
        K_LEFTLiEDOWN,
        K_RIGHTLiEDOWN
	};

	for (int i = 0; i < N_KEY; i++) {
		if (key_list[i] == key) {
			return true;
		}
	}

	return false;

}

key_t get_key(void) {
	if (!_kbhit()) {
		return K_UNDEFINED;
	}

	int key = _getch();
	if (key == K_ARROW) {
		key = _getch();
	}

	if (is_valid(key)) {
		return key;
	}
	else {
		return K_UNDEFINED;
	}	
}
