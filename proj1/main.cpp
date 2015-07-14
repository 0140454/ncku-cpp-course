#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "SnakeGame.h"
#include "Menu.h"

bool ConfirmExit()
{
	/// Initialize
	int height, width, ch;

	getmaxyx(stdscr, height, width);
	clear();
	/// Display Confirm Message
	char confirm[] = "Are you sure to exit? (y/n) ";

	mvaddstr(height / 2, (width - strlen(confirm)) / 2, confirm);

	while(true)
	{
		while((ch = getch()) == ERR)
			;

		if (tolower(ch) == 'y')
			return true;
		else if (tolower(ch) == 'n')
			return false;
	}

	return false;
}

int main()
{
	/// Initialize Environment
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	/// Initialize Color Pair
	init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
	init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
	/// Create Class Object
	CMenu menu;
	CSnakeGame snake;
	// Setup Menu
	menu.SetTitle("Welcome to SnakeGame");
	menu.SetPrompt("Please choose a item:");
	menu.AddItem("1. New Game");
	menu.AddItem("2. Load Game");
	menu.AddItem("3. Score Board");
	menu.AddItem("4. Help");
	menu.AddItem("5. Exit");
	// Wait for user
	while(true)
	{
		int select = menu.WaitChoice();

		if (select == 1)
			snake.NewGame();
		else if (select == 2)
			snake.LoadGame();
		else if (select == 3)
			snake.ShowScoreBoard();
		else if (select == 4)
			snake.ShowHelp();
		else if (select == 5)
		{
			if (ConfirmExit())
				break;
		}
	}
	/// Clean Up
	endwin();

    return 0;
}
