#include <iostream>
#include <functional>
using std::cout;
using std::cin;

char* setStr(std::function<bool(char)> func) {
	int len = 0;
	cout << "Enter lenght of num(if you want it negative the '-' takes 1 char too!) ";
	cin >> len;
	if (len == 0)
		return nullptr;

	char* num = new char[len + 1];
	num[len] = '\0';

	for (size_t i = 0; num[i] != '\0'; i++) {
		char temp;
		cin >> temp;
		if (func(temp) || (i == 0 && temp == '-')) {
			if (i == 0 && temp == '0') {
				cout << "Not a decimal number, please enter again!";
				i--;
				continue;
			}
			num[i] = temp;
		}
		else {
			cout << "Not a digit, please enter again!";
			i--;
		}
	}
	return num;
}

int strToNum() {
	char* num = setStr([](char ch) {if (ch < 48 || ch > 58)
										return false;
									return true; });
	if (num == nullptr)
		return 0;
	int result = 0;
	bool negative = false;

	if (num[0] == '-')
		negative = true;

	for (size_t i = negative; num[i] != '\0'; i++) {
		result += num[i] - 48;
		result *= 10;
	}
	delete[] num;
	if(negative)
		return (result / 10)*-1;
	return result / 10;
}



int main()
{
	cout << strToNum();
}