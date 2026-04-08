#include<iostream>
#include<string>

using namespace std;

class CarryCalculator {
public:
	static int calculateCarryCount(unsigned int a, unsigned int b, int base= 10) {
		int total_carries = 0;
		int carry = 0;

		while (a!=0 || b!=0) {
			if ((a % base) + (b % base) + carry >= base) {
				total_carries++;
				carry= 1;
			}
			else carry = 0;

			a /= base;
			b /= base;
		}
		return total_carries;
	}
};

class ResultFormatter {
public:
	static string formatCarryCount(int count) {
		if (count == 0) return "No carry operation.";
		else if (count == 1) return "1 carry operation.";
		else return to_string(count) + " carry operations.";
	}
};

int main() {
	unsigned int num1, num2;

	while (cin >> num1 >> num2 && (num1 != 0 || num2 != 0)) {
		int result = CarryCalculator::calculateCarryCount(num1, num2);

		cout << ResultFormatter::formatCarryCount(result) << endl;
	}
}