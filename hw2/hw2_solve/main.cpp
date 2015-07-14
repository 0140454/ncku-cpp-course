#include <cstdio>
#include "..\Sudoku.h"
#include <ctime>

unsigned long long begin, end;

static inline unsigned long long rdtscp(void)
{
	unsigned long long int ret;

	__asm__ volatile ("rdtscp" : "=A" (ret));

	return ret;
}

int main()
{
    freopen("output.txt", "r", stdin);

    begin = rdtscp();
	Sudoku ss;
	end = rdtscp();
	printf("Declaration clock cycle: %I64u\n", (end - begin) / 100llu);

	begin = rdtscp();
	ss.ReadIn();
	end = rdtscp();
	printf("ReadIn clock cycle: %I64u\n", (end - begin) / 100llu);

	begin = rdtscp();
	ss.Solve();
	end = rdtscp();
	printf("Solve clock cycle: %I64u\n", (end - begin) / 100llu);

    return 0;
}
