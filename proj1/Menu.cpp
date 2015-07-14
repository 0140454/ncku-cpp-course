#include "Menu.h"

CMenu::CMenu()
{
	getmaxyx(stdscr, height, width);
}

CMenu::~CMenu()
{
}

void CMenu::SetTitle(const char *title_text)
{
    title = title_text;
}

void CMenu::SetPrompt(const char *prompt_text)
{
    prompt = prompt_text;
}


void CMenu::ClearItem()
{
	items.clear();
}


void CMenu::AddItem(const char *item_text)
{
	items.push_back(item_text);
}


int CMenu::WaitChoice()
{
	clear();

	/// Display Title
	attrset(A_BOLD);
	mvaddstr(0, (width - title.length()) / 2, title.c_str());
	attrset(A_NORMAL);
	/// Display Prompt
	mvaddstr((height - items.size() - 1) / 2, (width - prompt.length()) / 2, prompt.c_str());
	/// Display Items
	for (size_t i = 0; i < items.size(); i++)
	{
		if (!i) attrset(A_REVERSE);
		mvaddstr((height - items.size() - 1) / 2 + i+1, (width - prompt.length()) / 2 + 2, items[i].c_str());
		if (!i) attrset(A_NORMAL);
	}
	/// Wait for user
	int bound_down, bound_up, cur_x, cur_y;
	int select;

	cur_y = bound_up = (height - items.size() - 1) / 2 + 1;
	bound_down = bound_up + items.size() - 1;
	cur_x = (width - prompt.length()) / 2 + 2 + items[0].length();
	move(cur_y, cur_x);

	while(true)
	{
		while((ch = getch()) == ERR)
			;

		select = cur_y - bound_up;

		if (ch == KEY_ENTER)
			break;
		else if (ch == KEY_UP)
		{
			// un-highlight current line
			mvaddstr(cur_y, cur_x - items[select].length(), items[select].c_str());
			// move and check bound
			cur_y--;
			if (cur_y < bound_up) cur_y = bound_down;
		}
		else if (ch == KEY_DOWN)
		{
			// un-highlight current line
			mvaddstr(cur_y, cur_x - items[select].length(), items[select].c_str());
			// move and check bound
			cur_y++;
			if (cur_y > bound_down) cur_y = bound_up;
		}

		move(cur_y, cur_x);
		select = cur_y - bound_up;
		cur_x = (width - prompt.length()) / 2 + 2 + items[select].length();

		attrset(A_REVERSE);
		mvaddstr(cur_y, cur_x - items[select].length(), items[select].c_str());
		attrset(A_NORMAL);
	}

	return select+1;
}
