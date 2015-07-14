#ifndef LIST_INCLUDED_H
#define LIST_INCLUDED_H

#include <vector>
#include <string>
#include <utility>

#ifdef WIN32
#include "curses.h"
#else
#include "ncurses.h"
#endif // WIN32

#include "Common.h"

using namespace std;

class CList {
public:
	CList();
	~CList();

	void AddColumn(const char *name, int width);
	void ClearColumns();

	void AddItem(const char *text, const char *split);
	void ClearItems();

	void Sort(int id = 0, bool descending = false);
	void SetShowCount(int cnt = -1);
	void Display(int y = 1, int x = 2);

private:
	/// Window
	int width, height;
	int ch;
	/// List
	vector< pair<string, int> > columns;
	vector< vector<string> > items;
	int show_cnt;
};

#endif // LIST_INCLUDED_H
