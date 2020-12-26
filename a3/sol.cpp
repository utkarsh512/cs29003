#include <iostream>
#include <cstdio>

using namespace std;

#define ninf double(-1e52)
#define inf double(1e52)

struct point {
	double x;
	double y;
};

struct line {
	int n;
	double m;
	double c;
};

struct ds {
	line l;
	point from;
	point to;
};

point get(line l1, line l2) {
	point p;
	p.x = -(l2.c - l1.c) / (l2.m - l1.m);
	p.y = ((l2.m) * (l1.c) - (l1.m) * (l2.c)) / (l2.m - l1.m);
	return p;
}

bool searchL(ds flag[], int len, int index) {
	// Search whether line with given index have already been registered
	for (int i = 0; i < len; i++) {
		if (flag[i].l.n == index) return true;
	}
	return false;
}

int method1 (ds flag[], line lines[], int n) {
	int k; // index for current line
	int last; // index of line with largest slope

	//ds flag[n];
	int ctr = 0;

	double _min = inf;
	double _max = ninf;

	// Finding smallest and largest slope line
	for (int i = 0; i < n; i++) {
		if (_min > lines[i].m) {
			k = i;
			_min = lines[i].m;
		}

		if (_max < lines[i].m) {
			last = i;
			_max = lines[i].m;
		}
	}

	// Till this, smallest and largest sloped linbes hgave been identified

	point Q;
	Q.x = ninf;
	Q.y = 0;
	flag[ctr].l = lines[k];
	flag[ctr].from = Q;
	flag[ctr].to = Q; // temp
	ctr++;
	// not yet sure of the termination

	while (1) {
		point P;
		int jIndex; // to store index of J*
		_min = inf;

		for (int j = 0; j < n; j++) {
			bool c = searchL(flag, ctr, j);
			// if c is found, restart the loop
			if (c) continue;
			// j has not been registered

			point temp = get(lines[k], lines[j]);
			if (temp.x < Q.x) continue;
			if (temp.x < _min) {
				_min = temp.x;
				jIndex = j;
				P.x = temp.x; P.y = temp.y;
			}
		}
		flag[ctr-1].to = P;
		flag[ctr].l = lines[jIndex];
		flag[ctr].from = P;
		flag[ctr].to = P;

		if (jIndex == last) {
			point Y;
			Y.x = inf;
			Y.y = 0;
			flag[ctr].to = Y;
			ctr++;
			break;
		}
		ctr++;
		Q.x = P.x;
		Q.y = P.y;
		k = jIndex;
	}
	return ctr;
}

void merge (line arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	line L[n1], R[n2];

	for (i = 0; i < n1; i++) {
		L[i] = arr[l+i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}

	i = 0; j = 0;
	k = l;

	while (i < n1 && j < n2) {
		if (L[i].m <= R[j].m) {
			arr[k] = L[i];
			i++;
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

void mergesort(line arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergesort(arr, l, m);
		mergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

int method2(int a[], line lines[], int n) {
    int ctr = 0;
    a[ctr++] = 0;
    a[ctr++] = 1;
    point p, q;

    for (int i = 2; i < n; i++) {
        int j = ctr-1;
        while (j != 0) {
            p = get(lines[a[j-1]], lines[i]);
            q = get(lines[a[j-1]], lines[a[j]]);
            if (p.x > q.x) {
                a[ctr++] = i;
                break;
            }
            j = --ctr - 1;
        }
    }
    return ctr;
}

int main() {
	int n;
	cout << "n = ";
	cin >> n;

	line lines[n];
	for (int i = 0; i < n; i++) {
		double x, y;
		cout << "    ";
		cin >> x >> y;
		lines[i].n = i;
		lines[i].m = x;
		lines[i].c = y;
	}

	cout << "+++ Lines before sorting\n";
	for (int i = 0; i < n; i++) {
		printf("Lines %3d: y = %16.10lf x + %16.10lf\n", lines[i].n, lines[i].m, lines[i].c);
	}

	cout << endl;

	ds flag[n];
	int ctr = method1(flag, lines, n);

	cout << "+++ Method 1\n";
	printf("Lines %3d: From MINUS_INFINITY to (%.10lf, %.10lf)\n", flag[0].l.n, flag[0].to.x, flag[0].to.y);
	for (int i = 1; i < ctr-1; i++) {
		printf("Lines %3d: From (%.10lf, %.10lf) to (%.10lf, %.10lf)\n", flag[i].l.n, flag[i].from.x, flag[i].from.y, flag[i].to.x, flag[i].to.y);
	}
	printf("Lines %3d: From (%.10lf, %.10lf) to PLUS_INFINITY\n", flag[ctr-1].l.n, flag[ctr-1].from.x, flag[ctr-1].from.y);

	cout << endl;

	mergesort(lines, 0, n-1);

	cout << "+++ Lines after sorting\n";
	for (int i = 0; i < n; i++) {
		printf("Lines %3d: y = %16.10lf x + %16.10lf\n", lines[i].n, lines[i].m, lines[i].c);
	}

    int a[n];
    int len = method2(a, lines, n);
    point points[len];
    for (int i = 0; i < len - 1; i++) {
        points[i] = get(lines[a[i]], lines[a[i+1]]);
    }
    cout << "+++ Method2\n";
    printf("Lines %3d: From MINUS_INFINITY to (%.10lf, %.10lf)\n", lines[a[0]].n, points[0].x, points[0].y);
    for (int i = 1; i < len - 1; i++) {
        printf("Lines %3d: From (%.10lf, %.10lf) to (%.10lf, %.10lf)\n", lines[a[i]].n, points[i-1].x, points[i-1].y, points[i].x, points[i].y);
    }
    printf("Lines %3d: From (%.10lf, %.10lf) to PLUS_INFINITY\n", lines[a[len-1]].n, points[len-2].x, points[len-2].y);
    cout << endl;

    return 0;
}
