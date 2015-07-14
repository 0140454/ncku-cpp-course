#include "Sudoku.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define DEBUG 1

const int Sudoku::section_map[81] = {
	1, 1, 1, 2, 2, 2, 3, 3, 3,
	1, 1, 1, 2, 2, 2, 3, 3, 3,
	1, 1, 1, 2, 2, 2, 3, 3, 3,
	4, 4, 4, 5, 5, 5, 6, 6, 6,
	4, 4, 4, 5, 5, 5, 6, 6, 6,
	4, 4, 4, 5, 5, 5, 6, 6, 6,
	7, 7, 7, 8, 8, 8, 9, 9, 9,
	7, 7, 7, 8, 8, 8, 9, 9, 9,
	7, 7, 7, 8, 8, 8, 9, 9, 9 };

const int Sudoku::sudoku_template[][81] = {
{ 7, 2, 8, 9, 4, 6, 3, 1, 5,
9, 3, 4, 2, 5, 1, 6, 7, 8,
5, 1, 6, 7, 3, 8, 2, 4, 9,
1, 4, 7, 5, 9, 3, 8, 2, 6,
3, 6, 9, 4, 8, 2, 1, 5, 7,
8, 5, 2, 1, 6, 7, 4, 9, 3,
2, 9, 3, 6, 1, 5, 7, 8, 4,
4, 8, 1, 3, 7, 9, 5, 6, 2,
6, 7, 5, 8, 2, 4, 9, 3, 1 }
,
{ 8, 5, 1, 4, 7, 2, 3, 9, 6,
3, 9, 4, 6, 5, 8, 2, 7, 1,
7, 2, 6, 9, 3, 1, 4, 5, 8,
1, 4, 3, 8, 9, 6, 5, 2, 7,
9, 6, 5, 2, 1, 7, 8, 3, 4,
2, 8, 7, 5, 4, 3, 6, 1, 9,
4, 3, 8, 7, 2, 9, 1, 6, 5,
6, 1, 9, 3, 8, 5, 7, 4, 2,
5, 7, 2, 1, 6, 4, 9, 8, 3 }
,
{ 4, 1, 8, 2, 3, 9, 6, 7, 5,
6, 5, 3, 8, 7, 1, 9, 4, 2,
2, 9, 7, 5, 4, 6, 1, 3, 8,
5, 3, 9, 1, 8, 4, 7, 2, 6,
8, 4, 2, 6, 5, 7, 3, 9, 1,
7, 6, 1, 9, 2, 3, 8, 5, 4,
1, 8, 4, 7, 9, 5, 2, 6, 3,
9, 2, 5, 3, 6, 8, 4, 1, 7,
3, 7, 6, 4, 1, 2, 5, 8, 9 }
};

Sudoku::Sudoku()
{
	Init();
}

void Sudoku::Init()
{
	status = UNDETERMINED;
	cnt_template = sizeof(sudoku_template) / (sizeof(int) * 81);

	memset(x_used, 0, sizeof(x_used));
	memset(y_used, 0, sizeof(y_used));
	memset(section_used, 0, sizeof(section_used));
}

void Sudoku::Analyze()
{
	for (int i = 0; status != UNSOLVABLE && i < 81; i++)
	{
		if (table[i] == EMPTY_CELL) continue;
		if (table[i] < EMPTY_CELL)
		{
			status = UNSOLVABLE;
			continue;
		}

		int x = i / 9, y = i % 9;

		if (!x_used[x][table[i]]) x_used[x][table[i]] = true;
		else status = UNSOLVABLE;
		if (!y_used[y][table[i]]) y_used[y][table[i]] = true;
		else status = UNSOLVABLE;
		if (!section_used[section_map[i]][table[i]]) section_used[section_map[i]][table[i]] = true;
		else status = UNSOLVABLE;
	}
}

void Sudoku::GiveQuestion()
{
	srand(time(NULL));

	const int *pTemplate = sudoku_template[rand() % cnt_template];
	int question[81], trans[10] = { 0 };

	/// random
	for (int i = 1; i <= 9; i++)
	{
		int num;

		do
		{
			num = rand() % 9 + 1;
		}while(trans[num]);

		trans[num] = i;
	}
	/// fill
	for (int i = 0; i < 81; i++)
		question[i] = trans[pTemplate[i]];
	/// dig
	for (int c = 0; c < 55; c++)
	{
		int pos;

		memcpy(table, question, sizeof(table));
		do
		{
			pos = rand() % 81;
		} while(table[pos] == EMPTY_CELL);

		table[pos] = EMPTY_CELL;

		Init();
		Analyze();
		backtracking(0);

		if (status == ONE_SOULUTION)
			memcpy(question, table, sizeof(question));
	}

	/*for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (!k) printf("%d", question[i*9+k]);
			else printf(" %d", question[i*9+k]);
		}
		putchar('\n');
	}*/
}

void Sudoku::ReadIn()
{
	status = UNDETERMINED;

	for (int i = 0; i < 81; i++)
		scanf("%d", &table[i]);

	Analyze();
}

void Sudoku::Solve()
{
	if (status == UNSOLVABLE)
		printf("0\n");
	else
	{
		backtracking(0);

		if (status == MULTI_SOLUTION)
			printf("2\n");
		else if (status == ONE_SOULUTION)
		{
			printf("1\n");
			for (int i = 0; i < 9; i++)
			{
				for (int k = 0; k < 9; k++)
				{
					if (!k) printf("%d", answer[i*9+k]);
					else printf(" %d", answer[i*9+k]);
				}
				putchar('\n');
			}
		}
		else
		{
			status = UNSOLVABLE;
			printf("0\n");
		}
	}
}

void Sudoku::backtracking(int cur)
{
	if (cur == 81)
	{
		if (status == ONE_SOULUTION) status = MULTI_SOLUTION;
		else if (status == UNDETERMINED)
		{
			status = ONE_SOULUTION;

			memcpy(answer, table, sizeof(answer));
		}

		return;
	}

	while(cur < 81 && table[cur])
		cur++;

	if (cur == 81)
	{
		backtracking(cur);
		return;
	}

	int x = cur / 9, y = cur % 9;
	for (int i = 1; i <= 9 && status != MULTI_SOLUTION; i++)
	{
		if (x_used[x][i] || y_used[y][i] || section_used[section_map[cur]][i]) continue;

		x_used[x][i] = y_used[y][i] = section_used[section_map[cur]][i] = true;
		table[cur] = i;

		backtracking(cur+1);

		table[cur] = EMPTY_CELL;
		x_used[x][i] = y_used[y][i] = section_used[section_map[cur]][i] = false;
	}
}
