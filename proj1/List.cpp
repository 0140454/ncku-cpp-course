#include "List.h"
#include <cstdlib>
#include <cstring>

CList::CList()
{
	show_cnt = -1;
}

CList::~CList()
{
}

void CList::AddColumn(const char *name, int width)
{
	columns.push_back(make_pair(name, width));
}

void CList::ClearColumns()
{
	columns.clear();
}

void CList::AddItem(const char *text, const char *split)
{
	char *str = strdup(text);
	char *token = strtok(str, split);
	vector<string> new_item;

	while(token && new_item.size() < columns.size())
	{
		new_item.push_back(token);
		if (!strlen(token))
		if (new_item.back().length() >= columns[new_item.size() - 1].second)
			new_item.back() = new_item.back().substr(0, columns[new_item.size() - 1].second);

		token = strtok(NULL, split);
	}

	while(new_item.size() < columns.size())
		new_item.push_back("");

	items.push_back(new_item);

	free(str);
}

void CList::ClearItems()
{
	items.clear();
}

void CList::Sort(int id, bool descending)
{
	if (id >= columns.size() || id < 0)
		id = 0;

	bool is_number = true;
	for (int i = 0; i < items.size() && is_number; i++)
	{
		char *pEnd;
		strtol(items[i][id].c_str(), &pEnd, 10);
		is_number = (pEnd - items[i][id].c_str() == items[i][id].length());
	}

	// Sort O(n^2)
	for (int i = 0; i < items.size(); i++)
	{
		for (int k = 0; k < items.size(); k++)
		{
			bool need_change;
			if (is_number)
			{
				long int i_number = strtol(items[i][id].c_str(), NULL, 10);
				long int k_number = strtol(items[k][id].c_str(), NULL, 10);
				need_change = (descending) ? (k_number < i_number) : (k_number > i_number);
			}
			else
				need_change = (descending) ? (strcmp(items[k][id].c_str(), items[i][id].c_str()) < 0)
					: (strcmp(items[k][id].c_str(), items[i][id].c_str()) > 0);

			if (need_change)
			{
				vector<string> tmp = items[i];

				items[i] = items[k];
				items[k] = tmp;
			}
		}
	}
}

void CList::SetShowCount(int cnt)
{
	show_cnt = cnt;
}

void CList::Display(int y, int x)
{
	/// Display Columns
	attrset(A_REVERSE);
	for (int i = 0; i < columns.size(); i++)
	{
		if (!i)
			mvaddstr(y, x, columns[i].first.c_str());
		else
			addstr(columns[i].first.c_str());
		for (int k = 0; k < columns[i].second - columns[i].first.length(); k++)
			addch(' ');
	}
	attrset(A_NORMAL);
	/// Display Items
	for (int i = 0; i < items.size() && ((show_cnt < 0) ? true : (i < show_cnt)); i++)
	{
		for (int k = 0; k < items[i].size(); k++)
		{
			if (!k)
				mvaddstr(y + i + 1, x, items[i][k].c_str());
			else
				addstr(items[i][k].c_str());
			for (int p = 0; p < columns[k].second - items[i][k].length(); p++)
				addch(' ');
		}
	}
}
