#include "ZipCode.h"
#include <cstdio>

ZipCode::ZipCode(string szCode)
{
	if (!isValid(szCode))
	{
		printf("\nInvalid ZipCode!\n");
		return;
	}

	savedCode = szCode;
}

ZipCode::ZipCode(int nCode)
{
	if (!isValid(nCode))
	{
		printf("\nInvalid ZipCode!\n");
		return;
	}

	string table[] = { "11000", "00011", "00101", "00110", "01001", "01010", "01100", "10001", "10010", "10100" };
	string tmp;

	savedCode = "1";

	tmp.resize(5);
	sprintf(&tmp[0], "%05d", nCode);
	for (int i = 0; i < 5; i++)
		savedCode.append(table[ tmp[i] - '0' ]);

	savedCode.append("1");
}

int ZipCode::getZipCode()
{
	int value = 0;

	if (!isValid()) return value;

	for (int i = 1; i < savedCode.length() - 1; i += 5)
	{
		int tmp;

		tmp = (savedCode[i] - '0') * 7;
		tmp += (savedCode[i+1] - '0') * 4;
		tmp += (savedCode[i+2] - '0') * 2;
		tmp += (savedCode[i+3] - '0') * 1;

		if (tmp == 11)
			tmp = 0;

		value = value * 10 + tmp;
	}

	return value;
}

string ZipCode::getZipCodeString()
{
	return savedCode;
}

bool ZipCode::isValid()
{
	return (savedCode.length());
}

bool ZipCode::isValid(int nCode)
{
	return (nCode >= 0 && nCode <= 99999);
}

bool ZipCode::isValid(string szCode)
{
	if (szCode.length() != 27 || szCode[0] != '1' || szCode[szCode.length() - 1] != '1')
		return false;
	else
	{
		for (int i = 1; i < szCode.length() - 1; i += 5)
		{
			string tmp = szCode.substr(i, 5);
			int n_one = 0;

			for (int k = 0; k < tmp.length(); k++)
				if (tmp[k] == '1') n_one++;

			if (n_one != 2) return false;
		}

		return true;
	}
}
