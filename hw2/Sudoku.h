#define UNDETERMINED	-1
#define UNSOLVABLE		0
#define ONE_SOULUTION	1
#define MULTI_SOLUTION	2
#define EMPTY_CELL		0

class Sudoku {
public:
	Sudoku();

	void GiveQuestion();
	void ReadIn();
	void Solve();

private:
	static const int section_map[81];
	static const int sudoku_template[][81];

	int cnt_template;
	int status;

	int table[81];
	int answer[81];
	bool x_used[10][10], y_used[10][10]
		 , section_used[10][10];

	void backtracking(int cur);
	void Init();
	void Analyze();
};
