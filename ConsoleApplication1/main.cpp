#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
long long fibonacci(int number) {
	using namespace std;
	long long first{ 0 }, second{ 1 };
	for (int i{ 2 }; i <= number; ++i) {
		(i % 2 == 0) ? first += second : second += first;
	}
	return (second > first) ? second: first;
}

long long fibonacciRec(int number) {
	if (number < 2) {
		return 1;
	}
	long long result{ 0 };
	result = fibonacciRec(number - 1) + fibonacciRec(number - 2);
	return  result;
}

//Перевод в другую систему счисления
std::string translate(std::string num, int b, int c) { //b - нач   c - кон
	using namespace std;
	bool noError{ true }; //Корректность введенного числа
	for (int i{ 0 }; i < num.size(); ++i) {
		if (num[i] - '0' >= b || //Цифра должна быть меньше основания
				(num[i] < 46 || num[i] == 47 || (num[i] > 57 && num[i] < 65) || num[i] > 90)) {
			if (num[i] > 96 && num[i] < 123) { //uppercase
				num[i] -= 32;
					continue;
			}
			noError = false;
			break;
		}
	}
	if (c > 1 && b > 1 && noError) {
		string inputIntegerPart{ "" }; //Целая часть
		string inputRealPartString{"0."}; //Дробная часть
		int counter{ 0 };

		while (counter < num.size() && num[counter] != '.') { //Получение целой части
			inputIntegerPart += num[counter];
			++counter;
		}
		++counter;
		while (counter < num.size()) { //Получение дробной части
			inputRealPartString += num[counter];
			++counter;
		}

		unsigned long long decIntegerPart{ stoull(inputIntegerPart) }; //Число в десятичной форме
		double decRealPart{ stod(inputRealPartString) }; //Дробная часть
		//В 10-чную---------------------
		if (b != 10) {
			decIntegerPart = 0;
			decRealPart = 0;
			//Целая часть
			if (inputIntegerPart.size() > 0) {
				for (int i{ 0 }; i < inputIntegerPart.size(); ++i) {
					decIntegerPart *= b;
					(inputIntegerPart[i] < 55) ?
						decIntegerPart += inputIntegerPart[i] - '0' :
						decIntegerPart += inputIntegerPart[i] - 55;
				}
			}
		//Дробная часть
			for (int i{ (int)inputRealPartString.size() - 1 }; i > 1; --i) {
				(inputRealPartString[i] < 55) ?
				decRealPart = double(decRealPart + inputRealPartString[i] - '0') / b :
					decRealPart = double(decRealPart + inputRealPartString[i] - 55) / b;
			}
		}

		//Из 10-чной---------------------
		//Целая часть
		string integerPart{ "" };
		vector<char> finNum; //Финальное число как массив символов
		integerPart = to_string(decIntegerPart);
		int numeral{ 0 }; //цифра итогового цисла
		for (int i{ 0 }; stoull(integerPart) > 0; ++i) {
			numeral = stoull(integerPart) % c;
			(numeral < 10) ? finNum.push_back((numeral) + '0') :
				finNum.push_back((numeral) + 55); //Буквы
			integerPart = to_string(stoull(integerPart) / c);
		}
		reverse(finNum.begin(), finNum.end()); //Переворачиваем массив
		string str(finNum.begin(), finNum.end()); //Vector to String

		//Дробная часть
		if (decRealPart > 0) {
			str += '.';
			for (int i{ 0 }; i < 15; ++i) {
				decRealPart *= c;
				numeral = (int)trunc(decRealPart);
				(numeral < 10) ?
					str += to_string(numeral) :
					str += (char)numeral + 55; //Буквы
				decRealPart = (decRealPart - trunc(decRealPart));
				if (decRealPart == 0.0)
					break;
			}
		}
		return str;
	}
	return "Error";
}
void main1() {
	std::cout << "Enter Number: ";
	int number{ 0 };
	std::cin >> number;
	std::cin.get();
	std::cout << fibonacci(number);
}

void main2() {
	std::cout << "Enter Number: ";
	int number{ 0 };
	std::cin >> number;
	std::cin.get();
	std::cout << fibonacciRec(number);
}

void main3() {
	std::cout << "Enter Number: ";
	std::string number{ "" };
	std::getline(std::cin, number);
	std::cout << "Enter intial Numeral System: ";
	int initial{ 0 };
	std::cin >> initial;
	std::cin.get();
	std::cout << "Enter final Numeral System: ";
	int final{ 0 };
	std::cin >> final;
	std::cin.get();
	std::cout << translate(number, initial, final);
}

//https://numsys.ru/
int main() {
	using namespace std;
	cout << "Enter Task:\n" <<
		"1) Fibbonacci (circle)\n" <<
		"2) Fibbonacci (recursion)\n" <<
		"3) Numeral System Converter\n";
	int taskNum{ 0 };
	cin >> taskNum;
	cin.get();
	switch (taskNum) {
	case 1: {main1(); break; }
	case 2: {main2(); break; }
	case 3: {main3(); break; }
	case 0: {
		int number = 11;
		//cout << fibonacci(number) << endl;
		//cout << fibonacciRec(number - 1);
		cout << "Enter a Number";
		cout << "350.ff\t16 -> 32\t= " << translate("350.ff", 16, 32) << endl;
		cout << "80\t10 -> 8\t= " << translate("80", 10, 8) << endl;
		cout << "-80\t10 -> 2\t= " << translate("-80", 10, 2) << endl;
		cout << "80\t10 -> 2\t= " << translate("80", 10, 2) << endl;
		cout << "80\t10 -> 1\t= " << translate("80", 10, 1) << endl;
		cout << "80\t10 -> 10\t= " << translate("80", 10, 10) << endl;
		cout << "52\t8 -> 10\t= " << translate("52", 8, 10) << endl;
		cout << "85\t6 -> 8\t= " << translate("85", 6, 8) << endl;
		cout << "35\t6 -> 8\t= " << translate("35", 6, 8) << endl;
		cout << "32.259\t10 -> 8\t= " << translate("35.259", 10, 8) << endl;
		cout << "35.200000087\t10 -> 8\t= " << translate("35.200000087", 10, 8) << endl;
		cout << "35.29\t10 -> 5\t= " << translate("35.29", 10, 5) << endl;
		cout << "35.29\t6 -> 10\t= " << translate("35.29", 6, 10) << endl;
		cout << "35D\t16 -> 10\t= " << translate("35D", 16, 10) << endl;
		cout << "35D.F\t16 -> 8\t= " << translate("35D.F", 16, 8) << endl;
		cout << "350\t8 -> 16\t= " << translate("350", 8, 16) << endl;
		cout << "350FF\t16 -> 32\t= " << translate("350FF", 16, 32) << endl;
		cout << "350.FF\t16 -> 32\t= " << translate("350.FF", 16, 32) << endl;
		cout << "35.246\t7 -> 10\t= " << translate("35.246", 7, 10) << endl;
		cout << "35.817\t9 -> 10\t= " << translate("35.817", 9, 10) << endl;
		cout << "45.5\t6 -> 4\t= " << translate("45.5", 6, 4) << endl;
		cout << "55.5\t6 -> 4\t= " << translate("55.5", 6, 4) << endl;
		break;
	}
	default: {break; }
	}
	return 0;
}
