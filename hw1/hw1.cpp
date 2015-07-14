#include <cstdio>
#include "ZipCode.h"

int main()
{
	int op;
	ZipCode *pCode = NULL;

	printf("\n\t1. Input Integer\n\t2. Input String\n\nPlease select an operation: ");
	scanf("%d%*c", &op);

	if (op == 1)
	{
		int code;
		printf("\nPlease input Integer: ");
		scanf("%d%*c", &code);

		pCode = new ZipCode(code);
	}
	else if (op == 2)
	{
		char code[30];
		printf("\nPlease input String (Max length is 27): ");
		scanf("%27[01]", code);

		pCode = new ZipCode(code);
	}
	else
		printf("\nInvalid operation!\n");

	if (pCode && pCode->isValid())
	{
		printf("\n===================================\n");
		printf("Integer: %05d\nString: %s\n", pCode->getZipCode(), pCode->getZipCodeString().c_str());
		printf("===================================\n");

		delete pCode;
		pCode = NULL;
	}

	return 0;
}
