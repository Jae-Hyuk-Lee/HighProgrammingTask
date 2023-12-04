#pragma once

#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <string.h>

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�


void juldarigi_map_init(int n_row, int n_col);
float juldarigi_player_stateprint();
void juldarigi_player_locate(int center, int* leftDeadCount, int* rightDeadCount);
void checkPlayerdead(int center, float *sumstr, bool *leftwin, bool *rightwin);
void display_juldarigi();
void print_status_juldarigi();