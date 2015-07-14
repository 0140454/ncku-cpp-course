#include <string>

using namespace std;

class ZipCode {
public:
	ZipCode(int nCode);
	ZipCode(string szCode);

	int getZipCode();
	string getZipCodeString();

	bool isValid();

private:
	bool isValid(string szCode);
	bool isValid(int nCode);

	string savedCode;
};
