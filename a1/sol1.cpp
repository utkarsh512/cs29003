#include <iostream>
#include <math.h>

using namespace std;


typedef struct _pair {
	double h;
	double l;
} Pair;


double hirec(int);
double lorec(int);
Pair hilorec(int);
Pair hiloformula(int);

// Method0 starts here

double hirec(int n) {
	// Returns H(n) only
	if (n == 0) return 1.0;
	return 2 * hirec(n-1) + lorec(n-1);
}

double lorec(int n) {
	// Return L(n) only
	if (n == 0) return 0.0;
	return hirec(n-1) + lorec(n-1);
}

// Method1 starts here

Pair hilorec(int n) {
	Pair p;
	if (n == 0) {
		p.h = 1.0;
		p.l = 0.0;
		return p;
	}
	Pair prev = hilorec(n-1);
	p.h = 2 * prev.h + prev.l;
	p.l = prev.h + prev.l;
	return p;
}

// Method2 starts here

Pair hiloformula(int n) {
	Pair p;
	p.h = ((5 + sqrt(5)) / 10) * pow(((3 - sqrt(5)) / 2), n+1);
	p.h += ((5 - sqrt(5)) / 10) * pow(((3 + sqrt(5)) / 2), n+1);
	p.l = ((-5 - 3 * sqrt(5)) / 10) * pow(((3 - sqrt(5)) / 2), n+1);
	p.l += ((-5 + 3 * sqrt(5)) / 10) * pow(((3 + sqrt(5)) / 2), n+1);
	return p;
}


int main() {
	int n;
	double h, l;
	Pair p;

	cout.precision(10);
	cout << scientific;
	
	cout << "n = ";
	cin >> n;
	h = hirec(n);
	l = lorec(n);
	cout << "+++ Method 0" << "\n";
	cout << "    hi (" << n << ") = " << h << ", lo (" << n << ") = " << l << "\n\n";

	p = hilorec(n);
	cout << "+++ Method 1" << "\n";
	cout << "    hi (" << n << ") = " << p.h << ", lo (" << n << ") = " << p.l << "\n\n";

	p = hiloformula(n);
	cout << "+++ Method 2" << "\n";
	cout << "    hi (" << n << ") = " << p.h << ", lo (" << n << ") = " << p.l << "\n\n";

	return 0;
}
