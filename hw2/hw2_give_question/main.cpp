#include <cstdio>
#include "..\Sudoku.h"

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

    for (int i = 0; i < 10000; i++)
	{
		begin = rdtscp();
		Sudoku ss;

		ss.GiveQuestion();
		end = rdtscp();
		if (((end - begin) / 100llu) > 500000llu)
			puts("WOW");
	}

	/*begin = rdtscp();
	Sudoku ss;
	end = rdtscp();
	printf("Declaration clock cycle: %I64u\n", (end - begin) / 100llu);

	begin = rdtscp();
	ss.GiveQuestion();
	end = rdtscp();
	printf("GiveQuestion clock cycle: %I64u\n", (end - begin) / 100llu);*/

    return 0;
}
