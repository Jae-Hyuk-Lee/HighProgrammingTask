#ifndef _KEYIN_H_
#define _KEYIN_H_

#define N_KEY		12  // K_UNDEFINED �� �� Ű ����

#define K_ARROW		224
#define K_UP		72
#define K_DOWN		80
#define K_LEFT		75
#define K_RIGHT		77
#define K_QUIT		'q'
#define K_DIALOG	'd'
#define K_SELECT	' '
#define K_LEFTPULL  'z'
#define K_RIGHTPULL	'/'
#define K_LEFTLiEDOWN	'x'
#define K_RIGHTLiEDOWN	'.'
#define K_UNDEFINED	'\0'



typedef int key_t;

key_t get_key(void);

#endif
