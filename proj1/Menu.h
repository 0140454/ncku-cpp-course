#ifndef MENU_INCLUDED_H
#define MENU_INCLUDED_H

#include <vector>
#include <string>

#ifdef WIN32
#include "curses.h"
#else
#include "ncurses.h"
#endif // WIN32

#include "Common.h"

using namespace std;

class CMenu {
public:
	CMenu();
	~CMenu();

	void SetTitle(const char *title_text);
	void SetPrompt(const char *prompt_text);
	void ClearItem();
	void AddItem(const char *item_text);
	int WaitChoice();

private:
	/// Window
	int width, height;
	int ch;
	string prompt;
	string title;
	/// Item
	vector<string> items;
};

#endif // MENU_INCLUDED_H
