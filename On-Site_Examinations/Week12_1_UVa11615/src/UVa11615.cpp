#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

class Family_tree {
public:
	static int amount_of_family(int generation, int node_A, int node_B) {
		if (generation == 0) return 0;
		int total_node = 1, res;
		for (int i = 1; i <= generation; i++) {
			total_node *= 2;
		}
		total_node -= 1;

		if (node_A * 2 >= total_node || node_B * 2 >= total_node) return total_node;
		res = total_node - (del_node(node_A, total_node) >= del_node(node_B, total_node)? del_node(node_B, total_node): del_node(node_A, total_node));

		return res;
	}
private:
	static int del_node(int node, int total_node) {
		int num_of_del_node = 0;
		int next_generation = 2 * node + 1;
		int tmp = 1;

		if (next_generation > total_node) return 0;
		while (next_generation <= total_node) {
			num_of_del_node +=  tmp*2;
			tmp *= 2;
			next_generation = next_generation * 2 + 1;
		}

		return num_of_del_node;
	}
};

int main() {
	int test_case;
	cin >> test_case;
	while (test_case--) {
		int generation, node1, node2;
		cin >> generation >> node1 >> node2;
		cout << Family_tree::amount_of_family(generation, node1, node2) << endl;
	}
}