#include "SnakeGame.h"
#include <cstring>
#include <cstdlib>
#include "List.h"

CSnakeGame::CSnakeGame()
{
	getmaxyx(stdscr, height, width);
	Player.resize(MAX_PLAYER_NAME);
}

CSnakeGame::~CSnakeGame()
{
}

void CSnakeGame::LoadGame()
{
	/// Initialize
	FILE *fp;

	food.clear();
	snake.clear();
	srand(time(NULL));
	is_playing = true;
	last_update = time(NULL);
	nxt_color = COLOR_PAIR(WHITE_BLACK);
	/// Read File
	if (fp = fopen(GAME_SAVE_FILE, "r"))
	{
		int position_cnt;

		// [Player][Money][Score][Velocity][SuperTime][ElapsedTime][Direction][PositionCnt][Position]
		fscanf(fp, "%[^\t]", &Player[0]);
		fscanf(fp, "%d%d%lf%d%d%d", &money, &score, &velocity, &super_time, &elapsed_time, &direction);
		fscanf(fp, "%d", &position_cnt);
		for (int i = 0; i < position_cnt; i++)
		{
			double y, x;
			fscanf(fp, "%lf%lf", &y, &x);
			snake.push_back(NODE(y, x));
		}

		fclose(fp);

		Play();
	}
	else
	{
		clear();
		mvprintw(1, 2, "There is no saved game...");
		WaitForKey();
	}
}

void CSnakeGame::NewGame()
{
	/// Initialize
	velocity = 0.5;
	super_time = 0;
	elapsed_time = 0;
	is_playing = true;
	money = score = 0;
	last_update = time(NULL);
	nxt_color = COLOR_PAIR(WHITE_BLACK);

	food.clear();
	srand(time(NULL));
	/// New Snake
	SnakeInit();
	/// Set Player Name
	SetPlayerName();
	/// Start Game
	Play();
}

void CSnakeGame::Pause()
{
	/// Initialize
	char pause_message[][MAX_STR_LENGTH+1] = {
		" _______  _______  __   __  _______  _______  ______  ",
		"|       ||   _   ||  | |  ||       ||       ||      | ",
		"|    _  ||  |_|  ||  | |  ||  _____||    ___||  _    |",
		"|   |_| ||       ||  |_|  || |_____ |   |___ | | |   |",
		"|    ___||       ||       ||_____  ||    ___|| |_|   |",
		"|   |    |   _   ||       | _____| ||   |___ |       |",
		"|___|    |__| |__||_______||_______||_______||______| ",
		"                                                      ",
		"               Press <p> to continue...               "
	};
	int n_pause_message = sizeof(pause_message) / sizeof(pause_message[0]);
	/// Display Message
	attrset(COLOR_PAIR(RED_BLACK));
	for (int i = 0; i < n_pause_message; i++)
		mvaddstr((height - n_pause_message + 4) / 2 + i, (width - strlen(pause_message[0])) / 2, pause_message[i]);
	attrset(A_NORMAL);
	/// Wait for user
	WaitForKey('p');
	/// Clear Message
	for (int i = 0; i < n_pause_message; i++)
	{
		move((height - n_pause_message + 4) / 2 + i, 0);
		clrtoeol();
	}
}

void CSnakeGame::GameOver()
{
	/// Initialize
	char game_over[][MAX_STR_LENGTH+1] = {
		" _______  _______  __   __  _______ ",
		"|       ||   _   ||  |_|  ||       |",
		"|    ___||  |_|  ||       ||    ___|",
		"|   | __ |       ||       ||   |___ ",
		"|   ||  ||       ||       ||    ___|",
		"|   |_| ||   _   || ||_|| ||   |___ ",
		"|_______||__| |__||_|   |_||_______|",
		" _______  __   __  _______  ______  ",
		"|       ||  | |  ||       ||    _ | ",
		"|   _   ||  |_|  ||    ___||   | || ",
		"|  | |  ||       ||   |___ |   |_|| ",
		"|  |_|  ||       ||    ___||    __ |",
		"|       | |     | |   |___ |   |  ||",
		"|_______|  |___|  |_______||___|  ||",
		"                                    ",
		"      Press <q> to continue...      "
	};
	int n_game_over = sizeof(game_over) / sizeof(game_over[0]);
	/// Display Message
	attrset(COLOR_PAIR(RED_BLACK));
	for (int i = 0; i < n_game_over; i++)
		mvaddstr((height - n_game_over + 4) / 2 + i, (width - strlen(game_over[0])) / 2, game_over[i]);
	attrset(A_NORMAL);
	/// Wait for user
	WaitForKey('q');
}

void CSnakeGame::DrawFood()
{
	for (vector<FOOD>::iterator i = food.begin(); i != food.end(); i++)
		mvaddch(i->y, i->x, (((i->color == BLUE_BLACK) ? '?' : '$') | COLOR_PAIR(i->color)));
}

void CSnakeGame::UpdateFood()
{
	/// Remove Obsoleted Food
	for (vector<FOOD>::iterator i = food.begin(); i != food.end(); )
	{
		chtype food_prop = mvinch(i->y, i->x);
		if ((PAIR_NUMBER(food_prop & A_COLOR) == RED_BLACK && (time(NULL) - i->start_time) >= 5)
			|| (PAIR_NUMBER(food_prop & A_COLOR) == WHITE_BLACK || PAIR_NUMBER(food_prop & A_COLOR) == YELLOW_BLACK))
		{
			if (PAIR_NUMBER(food_prop & A_COLOR) == RED_BLACK)
				mvaddch(i->y, i->x, ' ');
			i = food.erase(i);
		}
		else
			i++;
	}

	/// Add Food
	if (food.size() == MAX_FOOD_CNT) return;
	int y, x, color;

	do
	{
		y = rand() % (height - 4) + 4;
		x = rand() % width;
		color = rand() % 3 + 1;
	} while(mvinch(y, x) != ' ');

	if (color == BLUE_BLACK)
		mvaddch(y, x, ('?' | COLOR_PAIR(color)));
	else
		mvaddch(y, x, ('$' | COLOR_PAIR(color)));

	food.push_back(FOOD(y, x, color, time(NULL)));
}

void CSnakeGame::BuildObstacles()
{
	int ob_height = height - 4 - 10;

	for (int i = 0; i < ob_height; i++)
	{
		if (mvinch(4+5 + i, width / 4 - ob_height / 2 + i) == ' ')
			mvaddch(4+5 + i, width / 4 - ob_height / 2 + i, '#');
		if (mvinch(4+5 + i, width / 4 - ob_height / 2 + ob_height - 1 - i) == ' ')
			mvaddch(4+5 + i, width / 4 - ob_height / 2 + ob_height - 1 - i, '#');
	}

	for (int i = 0; i < ob_height; i++)
		if (mvinch(4+5 + i, width / 2) == ' ')
			mvaddch(4+5 + i, width / 2, '#');

	for (int i = 0; i < ob_height; i++)
	{
		if (mvinch(4+5 + i, 3 * width / 4 - ob_height / 2 + i) == ' ')
			mvaddch(4+5 + i, 3 * width / 4 - ob_height / 2 + i, '#');
		if (mvinch(4+5 + i, 3 * width / 4 - ob_height / 2 + ob_height - 1 - i) == ' ')
			mvaddch(4+5 + i, 3 * width / 4 - ob_height / 2 + ob_height - 1 - i, '#');
	}
}

void CSnakeGame::Play()
{
	/// Initialize
	clear();
	/// Display Basic Information
	mvprintw(0, 0, "  Player: %s", Player.c_str());
	mvprintw(0, width - 37, "Status: ");
	mvchgat(0, 0, -1, A_REVERSE, 0, NULL);
	mvprintw(1, 0, "  Time: ");
	mvchgat(1, 0, -1, A_REVERSE, 0, NULL);
	mvprintw(2, 0, "  Money / Score: ");
	mvprintw(2, width - 37, "Press <p/q/s> to pause/quit/save ");
	mvchgat(2, 0, -1, A_REVERSE, 0, NULL);
	mvprintw(3, 0, "  Speed / Length: ");
	mvprintw(3, width - 37, "Watch \"Help\" for other shortcut keys");
	mvchgat(3, 0, -1, A_REVERSE, 0, NULL);
	/// Start Game
	while(is_playing)
	{
		ch = getch();

		// Update Game Data
		if (time(NULL) != last_update)
		{
			if (elapsed_time % 5 == 0) score += velocity * 2 + snake.size() * 0.05;
			if (elapsed_time != 0 && elapsed_time % 10 == 0) velocity += 0.05;
			if (elapsed_time != 0 && elapsed_time % 60 == 0) SnakeAddLength(1), score++;

			last_update = time(NULL);
			elapsed_time++;
			if (super_time > 0) super_time--;
		}
		// Update Basic Information
		attrset(A_REVERSE);
		mvprintw(1, 8, "%02d:%02d", elapsed_time / 60, elapsed_time % 60);
		mvprintw(2, 17, "%d / %d", money, score);
		mvprintw(3, 18, "%.2f / %d", velocity, snake.size());
		if (super_time)
			mvprintw(0, width - 29, "Super (%d) ", super_time);
		else
			mvprintw(0, width - 29, "Normal    ");
		attrset(A_NORMAL);
		// Move Snake
		is_playing = SnakeMove();
		BuildObstacles();
		UpdateFood();

		if (ch == KEY_LEFT && direction != KEY_RIGHT) direction = KEY_LEFT, is_playing = SnakeMove(true);
		else if (ch == KEY_RIGHT && direction != KEY_LEFT) direction = KEY_RIGHT, is_playing = SnakeMove(true);
		else if (ch == KEY_DOWN && direction != KEY_UP) direction = KEY_DOWN, is_playing = SnakeMove(true);
		else if (ch == KEY_UP && direction != KEY_DOWN) direction = KEY_UP, is_playing = SnakeMove(true);
		else if (tolower(ch) == 'q') is_playing = false;
		else if (tolower(ch) == 'p')
		{
			Pause();
			DrawFood();
		}
		else if (tolower(ch) == 's')
		{
			SaveGame();
		}
	}
	/// Game Over
	GameOver();
	SavePlayerScore();
}

void CSnakeGame::SaveGame()
{
	/// Initialize
	FILE *fp;
	/// Read File
	if (fp = fopen(GAME_SAVE_FILE, "w"))
	{
		// [Player][Money][Score][Velocity][SuperTime][ElapsedTime][Direction][PositionCnt][Position]
		fprintf(fp, "%s\t%d\t%d\t%f\t%d\t%d\t%d\t%d\t", Player.c_str(), money, score, velocity, super_time, elapsed_time, direction, snake.size());
		for (int i = 0; i < snake.size(); i++)
			fprintf(fp, "%s%f %f", (!i) ? "" : " ", snake[i].y, snake[i].x);
		fprintf(fp, "\n");

		fclose(fp);
	}
}

void CSnakeGame::SavePlayerScore()
{
	/// Initialize
	FILE *fp;
	/// Read File
	if (fp = fopen(GAME_SCORE_FILE, "a+"))
	{
		time_t utc;
		struct tm *timeinfo;
		char buffer[50];

		time(&utc);
		timeinfo = localtime(&utc);
		strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M", timeinfo);

		fprintf(fp, "%s\t%d\t%d\t%s\n", Player.c_str(), score, (int)elapsed_time, buffer);

		fclose(fp);
	}
	/// Display Board
	ShowScoreBoard();
}

void CSnakeGame::SnakeInit()
{
	snake.clear();

	for (int i = 0; i < INIT_SNAKE_LENGTH; i++)
		snake.push_back(NODE(5, 2 + i));

	direction = KEY_RIGHT;
}

void CSnakeGame::SnakeAddLength(int max_add_length)
{
	int offset_x = (int)snake[0].x - (int)snake[1].x;
	int offset_y = (int)snake[0].y - (int)snake[1].y;
	NODE node = snake.front();

	for (int i = 0; i < max_add_length; i++)
	{
		node.x += offset_x;
		node.y += offset_y;

		if (mvinch(REAL_Y(node.y), REAL_X(node.x)) != ' ')
			break;

		snake.insert(snake.begin(), node);
	}
}

bool CSnakeGame::SnakeMove(bool force)
{
	/// Prepare To Update Snake
	NODE node = snake.back();
	chtype food_prop = 0;
	double offset = velocity / 10000;

	for (; (int)node.x == (int)snake.back().x && (int)node.y == (int)snake.back().y;)
	{
		if (direction == KEY_LEFT || direction == KEY_RIGHT)
			node.x += (direction == KEY_LEFT) ? -offset : offset;

		if (direction == KEY_UP || direction == KEY_DOWN)
			node.y += (direction == KEY_UP) ? -offset : offset;

		if (!force) break;
	}
	/// Touch Itself or Obstacles
	if (mvinch(REAL_Y(node.y), REAL_X(node.x)) == 'o') return false;
	if (mvinch(REAL_Y(node.y), REAL_X(node.x)) == '#' && !super_time) return false;
	/// Update Snake
	if (REAL_X(node.x) != REAL_X(snake.back().x) || REAL_Y(node.y) != REAL_Y(snake.back().y))
	{
		mvaddch(REAL_Y(snake.front().y), REAL_X(snake.front().x), ' ');
		if (mvinch(REAL_Y(node.y), REAL_X(node.x)) != ' ' && mvinch(REAL_Y(node.y), REAL_X(node.x)) != '#')
			food_prop = mvinch(REAL_Y(node.y), REAL_X(node.x));

		if (super_time > 0)
			nxt_color = (PAIR_NUMBER(mvinch(REAL_Y(snake.back().y), REAL_X(snake.back().x)) & A_COLOR) == YELLOW_BLACK) ? COLOR_PAIR(WHITE_BLACK) : COLOR_PAIR(YELLOW_BLACK);
		else
			nxt_color = COLOR_PAIR(WHITE_BLACK);

		snake.erase(snake.begin());
		snake.push_back(node);
	}
	else
	{
		snake.back() = node;
	}
	/// Display New Snake
	for (int i = snake.size() - 1; i >= 0; i--)
	{
		if (i == snake.size() - 1) mvaddch(REAL_Y(snake[i].y), REAL_X(snake[i].x), '@' | nxt_color);
		else mvaddch(REAL_Y(snake[i].y), REAL_X(snake[i].x), 'o' | nxt_color);
	}

	if (food_prop)
	{
		if (PAIR_NUMBER(food_prop & A_COLOR) == RED_BLACK) return false;
		else if (PAIR_NUMBER(food_prop & A_COLOR) == GREEN_BLACK) money++, score += 5;
		else if (PAIR_NUMBER(food_prop & A_COLOR) == BLUE_BLACK)
		{
			if (rand() % 3 == 0)
				super_time = SUPER_TIME;
			else
				SnakeAddLength(rand() % 1 + 4);
		}
	}

	return true;
}

void CSnakeGame::SetPlayerName()
{
	/// Initialize
	char prompt[] = "Please enter your name: ";
	int cur_x, bound_left, bound_right;
	Player = "";

	clear();
	curs_set(1);
	/// Sisplay Prompt
	mvaddstr(1, 2, prompt);
	/// display Text Box
	for (int i = 0; i <= MAX_PLAYER_NAME; i++)
		mvaddch(1, 2 + strlen(prompt) + i, ' ' | A_REVERSE);
	cur_x = bound_left = 2 + strlen(prompt);
	bound_right = bound_left + MAX_PLAYER_NAME;
	move(1, cur_x);
	/// Wait for user
	attrset(A_REVERSE);
	while(true)
	{
		while((ch = getch()) == ERR)
			;

		if (ch == KEY_ENTER) break;
		switch(ch)
		{
		case KEY_LEFT:
			if (cur_x > bound_left) move(1, --cur_x);
			break;
		case KEY_RIGHT:
			if (cur_x < bound_left + Player.length()) move(1, ++cur_x);
			break;
		case KEY_DC:
			mvaddch(1, bound_right + 1, ' ' | A_REVERSE);
			mvdelch(1, cur_x);
			Player.erase(cur_x - bound_left, 1);
			break;
#ifdef WIN32
		case 8:
#else
		case KEY_BACKSPACE:
#endif // WIN32
			if (cur_x == bound_left) break;
			mvaddch(1, bound_right + 1, ' ' | A_REVERSE);
			mvdelch(1, --cur_x);
			Player.erase(cur_x - bound_left, 1);
			break;
		case KEY_HOME:
			move(1, cur_x = bound_left);
			break;
		case KEY_END:
			move(1, cur_x = (bound_left + Player.length()));
			break;
		default:
			if (ch < 32 || ch > 126) break;
			if (cur_x == bound_right) break;
			mvdelch(1, bound_right);
			mvinsch(1, cur_x, ch);
			Player.insert(cur_x - bound_left, 1, ch);
			move(1, ++cur_x);
			break;
		}
	}
	attrset(A_NORMAL);
	curs_set(0);
	/// Check Player Name
	if (!Player.length()) Player = " ";
}

void CSnakeGame::ShowScoreBoard()
{
	/// Initialize
	clear();
	FILE *fp;
	CList board;

	board.AddColumn("Player", 20+4);
	board.AddColumn("Score", 5+4);
	board.AddColumn("Elapsed Time", 16+4);
	board.AddColumn("Created Time", 16+4);
	/// Read File
	if (fp = fopen(GAME_SCORE_FILE, "r"))
	{
		int read;
		string text;

		while(read = fgetc(fp))
		{
			if (read == '\n' || read == '\r')
			{
				if (text.length())
					board.AddItem(text.c_str(), "\t"), text = "";
			}
			else if (read == EOF || (!isprint(read) && read != '\t'))
			{
				if (text.length())
					board.AddItem(text.c_str(), "\t"), text = "";
				break;
			}
			else
				text += read;;
		}
		fclose(fp);
	}
	/// Display Board
	mvprintw(1, 2, "Press <c> to clear all records.");
	board.SetShowCount(height - 3 - 2);
	board.Sort(1, true);
	board.Display(3, 2);
	/// Wait for user
	while((ch = getch()) == ERR)
		;
	if (tolower(ch) == 'c')
	{
		remove(GAME_SCORE_FILE);

		ShowScoreBoard();
	}
}

void CSnakeGame::ShowHelp()
{
	/// Initialize
	clear();
	/// Display Help Message
	mvprintw(1, 1, "1. Using arrow key to control your snake.");
	mvprintw(2, 4, "By the way, your snake can cross the border of the map.");
	mvprintw(4, 1, "2. There are three types of food");
	mvprintw(5, 4, "$: Good money. The snake gets some rewarded scores.");
	mvaddch(5, 4, '$' | COLOR_PAIR(GREEN_BLACK));
	mvprintw(6, 4, "$: Poisoned money. It makes the snake die.");
	mvaddch(6, 4, '$' | COLOR_PAIR(RED_BLACK));
	mvprintw(7, 4, "?: Random. One of the following effects occurs:");
	mvaddch(7, 4, '?' | COLOR_PAIR(BLUE_BLACK));
	mvprintw(8, 7, "* The snake can go through the obstacles in a short period (%d seconds).", SUPER_TIME);
	mvprintw(9, 7, "* The snake becomes longer.");
	mvprintw(11, 1, "3. Game Over Conditions");
	mvprintw(12, 4, "* The snake hits the obstacles.");
	mvprintw(13, 4, "* The snake eats the poisoned food.");
	mvprintw(14, 4, "* The snake touches its own body.");
	mvprintw(16, 1, "4. Shortcut Keys");
	mvprintw(17, 4, "* <arrow key> : speed up your snake in a short period.");

	mvprintw(19, 1, "Press any key to continue...");
	/// Wait for user
	curs_set(1);
	WaitForKey();
	curs_set(0);
}

void CSnakeGame::WaitForKey(int wait)
{
	while(true)
	{
		while((ch = getch()) == ERR)
			;

		if (tolower(ch) == tolower(wait) || wait == -1)
			break;
	}
}

int CSnakeGame::RealPosValue(int val, bool is_height)
{
	if (is_height)
	{
		while(val >= height) val -= height - 4;
		while(val < 4) val += height - 4;
	}
	else
	{
		while(val >= width) val -= width;
		while(val < 0) val += width;
	}

	return val;
}

