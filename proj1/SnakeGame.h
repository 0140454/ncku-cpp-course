#ifndef SNAKE_GAME_INCLUDED_H
#define SNAKE_GAME_INCLUDED_H

#include <vector>
#include <ctime>
#include <string>

#ifdef WIN32
#include "curses.h"
#else
#include "ncurses.h"
#endif // WIN32

#include "Common.h"

using namespace std;

typedef struct _node {
	double y, x;

	_node(double _y = 0, double _x = 0):
		y(_y),x(_x) {}
} NODE;

typedef struct _food {
	int y, x, color;
	time_t start_time;

	_food(int _y = 0, int _x = 0, int _color = 0, time_t _time = 0):
		y(_y), x(_x), color(_color), start_time(_time) {}
} FOOD;

class CSnakeGame {
public:
	CSnakeGame();
	~CSnakeGame();

	void NewGame();
	void LoadGame();
	void ShowHelp();
	void ShowScoreBoard();

private:
	void SetPlayerName();
	void Play();
	void Pause();
	void GameOver();

	void SavePlayerScore();
	void SaveGame();

	void SnakeInit();
	bool SnakeMove(bool force = false);
	void SnakeAddLength(int max_add_length);
	void BuildObstacles();
	void UpdateFood();
	void DrawFood();

	void WaitForKey(int wait = -1);
	int RealPosValue(int val, bool is_height);
	/// Window
	int width, height;
	int ch;
	/// Game
	string Player;
	bool is_playing;
	time_t elapsed_time, last_update;
	int money, score;

	vector<NODE> snake;
	vector<FOOD> food;
	time_t super_time;
	double velocity;
	int direction;
	chtype nxt_color;
};

#endif // SNAKE_GAME_INCLUDED_H
