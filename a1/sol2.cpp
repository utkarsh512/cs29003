#include <iostream>
using namespace std;

int linearSearch(int s[], int n, int x) {
	// returns index of x in s
	for (int i = 0; i < n; i++) {
		if (s[i] == x) return i;
	}
	return -1; // not found
}

bool isDecreasing(int s[], int n) {
	// return true if s is strictly decreasing
	for (int i = 0; i < n-1; i++) {
		if (s[i] < s[i+1]) return false;
	}
	return true;
}

bool method0(int s[], int n) {
	for (int i = 1; i <= n-2; i++) {
		for (int j = i+1; j <= n-1; j++) {
			for (int k = j+1; k <= n; k++) {
				int x = linearSearch(s, n, i);
				int y = linearSearch(s, n, j);
				int z = linearSearch(s, n, k);
				if (z < x && x < y) return false;
			}
		}
	}
	return true;
}

bool method1(int s[], int n) {
	for (int i = 0; i < n-2; i++) {
		for (int j = i+1; j < n-1; j++) {
			for (int k = j+1; k < n; k++) {
				int c = s[i], a = s[j], b = s[k];
				if (a < b && b < c) return false;
			}
		}
	}
	return true;
}

bool method2(int s[], int n) {
	for (int i = 0; i < n-2; i++) {
		int c = s[i];
		int subsLength = 0;
		int subs[n - i];
		for (int j = i+1; j < n; j++) {
			if (s[j] < c) subs[subsLength++] = s[j];
		}
		bool co = isDecreasing(subs, subsLength);
		if (!co) return false;
	}
	return true;
}

bool method3(int s[], int n) {
	bool occured[n+1];

	for (int i = 1; i <=n; i++) {
		occured[i] = false;
	}

	for (int i = 0; i < n-2; i++) {
		occured[s[i]] = true;
		if (s[i+1] > s[i]) continue;
		if (s[i] - s[i+1] == 1) continue;
		for (int p = s[i+1] + 1; p < s[i]; p++) {
			if ( occured[p] == false ) return false;
		}
	}
	return true;
}

int main() {
	cout << "n = ";
	int n;
	cin >> n;
	int s[n];

	cout << "+++ Sequence: ";
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}

	bool ans = method0(s, n);
	cout << "    Method 0:";
	if (ans) cout << "Algolicious\n";
	else cout << "Unalgolicious\n";

	ans = method1(s, n);
	cout << "    Method 1:";
	if (ans) cout << "Algolicious\n";
	else cout << "Unalgolicious\n";

	ans = method2(s, n);
	cout << "    Method 2:";
	if (ans) cout << "Algolicious\n";
	else cout << "Unalgolicious\n";

	ans = method3(s, n);
	cout << "    Method 3:";
	if (ans) cout << "Algolicious\n";
	else cout << "Unalgolicious\n";

	return 0;
}
