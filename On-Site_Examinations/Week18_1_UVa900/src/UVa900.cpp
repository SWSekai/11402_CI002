#include <iostream>
#include <vector>

using namespace std;

class Brick_Wall_Patterns {
public:
	static long long countPatterns(int input) {
		if (!initialized) {
			dp.resize(51);
			dp[1] = 1;
			dp[2] = 2;

			for (int i = 3; i <= 50; ++i) {
				dp[i] = dp[i - 1] + dp[i - 2];
			}

			initialized = true;
		}

		return dp[input];
	}
private:
	static vector <long long> dp;
	static bool initialized;


};

vector<long long> Brick_Wall_Patterns::dp;
bool Brick_Wall_Patterns::initialized = false;

int main() {
	int input;
	while (cin >> input) {
		if (input == 0) {
			break;
		}
		cout << Brick_Wall_Patterns::countPatterns(input) << endl;
	}
}