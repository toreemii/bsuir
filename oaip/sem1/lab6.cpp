#include <iostream>
using namespace std;

int main() {
	char* text = new char [100];
	cin >> text;

	for (int i = 0; text[i] != '\0'; i++) 
	{
		if ((i+1) % 3 == 0) {
			text[i] = '%';
		}
		if ((i + 1) % 4 == 0) {
			text[i] = '&';
		}
		if (((i + 1) % 3 == 0) && ((i + 1) % 4 == 0)) {
			text[i] = '#';
		}
	}

	cout << text;

	delete[] text;
}
