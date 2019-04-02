#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int n;
vector<int> ans;

int main() {
	cin >> n;
	for (int i = 2; i < n; i++) {
		if (n < i) break;
		while (n % i == 0 && n) {
			ans.push_back(i);
			n /= i;
		}
	}
	if (n > 1) ans.push_back(n);
	for (vector<int>::iterator it = ans.begin(); it != ans.end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
	return 0;
}
