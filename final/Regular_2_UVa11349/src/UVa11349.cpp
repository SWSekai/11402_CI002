#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <cmath>
#include <sstream>
#include <array>

using namespace std;

class Solution {
public:

private:

};

int main() {
	int test_case, n;
	char N, equal;

	cin >> test_case;
	for(int round = 1; round <=test_case; round++) {
		bool is_symmetric = true;
		cin >> N >> equal >> n;
		vector<int> matrix;

		for(int i = 0; i <= n*n; i++){
			int num;
			cin >> num;
			if (num <= 0) is_symmetric = false;
			matrix.push_back(num);
		}

		for (int i = 0; i < n*n; i++) {
			if (matrix[i] != matrix[n*n-i]) is_symmetric = false;
		}

		cout << "Test #" << round << ": ";
		if (is_symmetric == true) cout << "Symmetric." << endl;
		else cout << "Non-Symmetric." << endl;
	}
}