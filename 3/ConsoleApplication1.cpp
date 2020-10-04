#include <iostream>
#include <string>
#include <vector>
long long fibonachi(int number) {
	using namespace std;
	long long first{ 0 }, second{ 1 };
	for (int i{ 2 }; i <= number; ++i) {
		(i % 2 == 0) ? first += second : second += first;
	}
	return (second > first) ? second: first;
}

long long fibonachiRec(int number) {
	if (number < 2) {
		return 1;
	}
	long long temp{ 0 };
	temp = fibonachiRec(number - 1) + fibonachiRec(number - 2);
	return  temp;
}

std::string translate(std::string num, int b, int c) { //b - нач   c - кон
	using namespace std;
	int decNum{ 0 };
	bool noError{ true };
	for (int i{ 0 }; i < num.size(); ++i) {
		if (num[i] - '0' > b) {
			noError = false;
			break;
		}
	}
	if (c > 1 && b > 1 && noError) {
		if (b != 10 && num.size() > 0) {
#pragma region В 10-чную
			for (int i{ 0 }; i < (int)num.size(); ++i) {
				decNum = decNum * b + num[i] - '0';
			}
			num = to_string(decNum);
		}
#pragma endregion
#pragma region Из 10-чной
		vector<char> finNum;
		
			for (int i{ 0 }; stoi(num) > 1; ++i) {
				finNum.push_back((stoi(num) % c) + '0');
				num = to_string(stoi(num) / c);
			}
		
		if (finNum[finNum.size() - 1] == '0') {
			finNum.push_back('1');
		}
		reverse(finNum.begin(), finNum.end()); //Переворачиваем массив
		string str(finNum.begin(), finNum.end()); //Vector to String
		return str;
#pragma endregion
	}
	return "Error";
}
//https://numsys.ru/
int main() {
	using namespace std;
	const int number = 11;
	//cout << fibonachi(number) << endl;
	//cout << fibonachiRec(number - 1);
	string number2{ "80" };
	cout << translate(number2, 10, 2) << endl;
	cout << translate(number2, 10, 8) << endl;
	cout << translate(number2, 10, 6) << endl;
	cout << translate(number2, 10, 1) << endl;
	cout << translate("52", 8, 10) << endl;
	cout << translate("85", 6, 8) << endl;
	cout << translate("35", 6, 8) << endl;
}
