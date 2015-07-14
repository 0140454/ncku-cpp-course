#ifndef COMMON_INCLUDED_H
#define COMMON_INCLUDED_H

#define MAX_STR_LENGTH		100
#define MAX_PLAYER_NAME		20
#define MAX_FOOD_CNT		3
#define INIT_SNAKE_LENGTH	10
#define SUPER_TIME			25

#define WHITE_BLACK			0
#define RED_BLACK			1
#define GREEN_BLACK			2
#define BLUE_BLACK			3
#define YELLOW_BLACK		4

#define REAL_Y(x) RealPosValue(x, true)
#define REAL_X(x) RealPosValue(x, false)

#undef KEY_ENTER
#define KEY_ENTER			'\n'
#define SECTION_SCORE		0xFF
#define SECTION_GAME		0xAA

#define GAME_SAVE_FILE		"snkgme.save"
#define GAME_SCORE_FILE		"snkgme.scr"

#endif // COMMON_INCLUDED_H
