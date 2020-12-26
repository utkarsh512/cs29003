/**
 * Roll No: 18EC30048
 */
 
// Issue #1: Need to store values (i.e. dynamic programming)

#include <iostream>
#include <string>

using namespace std;

#define SIZE 6000

typedef struct {
	string p;
	int oneCount;
} expr;

typedef struct {
	int n;
	int val;
	expr pattern[SIZE];
} ds;

bool search(ds x, string pat) {
	for (int i = 0; i < x.val; i++) {
		string d = x.pattern[i].p;
		if (d == pat) return true;
	}
	return false;
}

ds findallexpr (int n) {
	ds x;
	x.n = n;
	if (n == 1) {
		x.val = 1;
		for (int i = 0; i < x.val; i++) {
			x.pattern[i].p = "1";
			x.pattern[i].oneCount = 1;
		}
		return x;
	}

	x.val = 0;

	for (int i = 1; i <= (n/2); i++) {
		int j = n - i;
		ds abc = findallexpr(i);
		ds xyz = findallexpr(j);
		

		for (int u = 0; u < abc.val; u++) {
			for (int v = 0; v < xyz.val; v++) {
				string d = abc.pattern[u].p + "+" + xyz.pattern[v].p;
				bool c = search(x, d);
				if (!c) {
					x.pattern[x.val].p = d;
					x.pattern[x.val].oneCount = abc.pattern[u].oneCount + xyz.pattern[v].oneCount;
					(x.val)++;
				}
			}
		}
		
	}
	
	for (int i = 2; i*i <= n; i++) {
		if (n % i == 0) {
			int j = n / i;
			ds abc = findallexpr(i);
			ds xyz = findallexpr(j);
			for (int u = 0; u < abc.val; u++) {
				for (int v = 0; v < xyz.val; v++) {
					string qwe = abc.pattern[u].p;
					if (qwe[0] != '(') qwe = "(" + qwe + ")";
					string pot = xyz.pattern[v].p;
					if (pot[0] != '(') pot = "(" + pot + ")";
					string d = qwe + "*" + pot;
					bool c = search(x, d);
					if (!c) {
						x.pattern[x.val].p = d;
						x.pattern[x.val].oneCount = abc.pattern[u].oneCount + xyz.pattern[v].oneCount;
						(x.val)++;
					}
				}
			}
		}
	}
	return x;
}

void merge (expr arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	expr L[n1], R[n2];

	for (i = 0; i < n1; i++) {
		L[i] = arr[l+i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}

	i = 0; j = 0;
	k = l;

	while (i < n1 && j < n2) {
		if (L[i].oneCount > R[j].oneCount) {
			arr[k] = L[i];
			i++;
		} 
		else if (L[i].oneCount == R[j].oneCount) {
			if (L[i].p.length() >= R[j].p.length()) {
				arr[k] = L[i];
				i++;
			} else {
				arr[k] = R[j];
				j++;
			}
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(expr arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergesort(arr, l, m);
		mergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

void printallexpr (ds x) {
	cout << x.n << "  = " << x.pattern[0].p << endl;
	for (int i = 1; i < x.val; i++) {
		cout << "    = " << x.pattern[i].p << endl;
	}
	cout << "... " << x.val << " expressions" << endl;
}

int main() {
	int n;
	cout << endl << "n = ";
	cin >> n;
	ds x = findallexpr(n);
	cout << endl << "+++ Before sorting" << endl;
	printallexpr(x);
	mergesort(x.pattern, 0, x.val-1);
	cout << endl << "+++ After sorting" << endl;
	printallexpr(x);
	return 0;
}
