#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>
#include <stdlib.h>

#define PLAYER_MAX		10
#define ITEM_MAX		10

typedef struct {
    char name[100];
    int intel_buf, str_buf, stamina_buf;
} ITEM;

typedef struct {
    int id;
    char name[100];
    // 능력치: 지능, 힘, 스태미나
    int intel, str, stamina;
    // 현재 상태
    bool is_dead; // 줄다리기에서 사용하는 탈락 bool 살아있으면 true, 죽으면 false
    bool is_alive; // 탈락했으면 false
    bool hasitem; // 아이템이 있으면 true
    ITEM item; // 아이템 1개 장착 가능
} PLAYER;


PLAYER player[PLAYER_MAX];  // 기본값 true, 탈락하면 false
int n_player, n_item;
int n_playerstatus[PLAYER_MAX][2];
int tick;  // 시계
ITEM item[ITEM_MAX];

// 미니게임
void sample(void);
void mugunghwa(void);
void mugunghwa(void);
//void nightgame(void);
void juldarigi(void);
void jebi(void);

int randint(int low, int high);



#endif