/**
 * Author : Utkarsh Patel
 * Roll   : 18EC30048
 * Topic  : Lab Test
 * Date   : 28-APR-2020
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <math.h>

using namespace std;

bool Ask (int x, int y, int p, int q, int r, int s) {
  bool c1 = (x >= p) && (x <= q);
  bool c2 = (y >= r) && (y <= s);
  if (c1 && c2) return true;
  return false;
}

void prnWB (int F[51][51], int m, int n, int p, int q, int r, int s) {
  for (int i = 1; i <= m; i++) {
    cout << "    ";
    for (int j = 1; j <= n; j++) {
      if (Ask(i, j, p, q, r, s)) {
        printf("%c ", (F[i][j] == 0)? 'W':'B');
      } else {
        printf(". ");
      }
    }
    cout << "\n";
  }
}

int min(int a, int b) {
  return (a < b)? a : b;
}

int max(int a, int b) {
  return (a > b)? a : b;
}

bool ischessboard (int F[51][51], int m, int n, int i, int j, int k, int l) {
  int p = i + k - 1;
  int q = j + l - 1;
  bool proceed = true;
  for (int x = i; x <= p && proceed; x++) {
    for (int y = j; y <= q && proceed; y++) {
      int x1 = x-1;
      int x2 = x+1;
      int y1 = y-1;
      int y2 = y+1;
      if (Ask(x, y1, i, p, j, q)) {
        if (F[x][y1] == F[x][y]) proceed = false;
      }
      if (Ask(x1, y, i, p, j, q)) {
        if (F[x1][y] == F[x][y]) proceed = false;
      }
      if (Ask(x, y2, i, p, j, q)) {
        if (F[x][y2] == F[x][y]) proceed = false;
      }
      if (Ask(x2, y, i, p, j, q)) {
        if (F[x2][y] == F[x][y]) proceed = false;
      }
    }
  }
  return proceed;
}

void essquare (int F[51][51], int m, int n) {
  int M[51][51]; // to store the length of largest sq that has the pattern
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      int p = m - i + 1;
      int q = n - j + 1;
      int r = min(p, q);
      for (int l = r; l >= 1; l--) {
        bool c = ischessboard(F, m, n, i, j, l, l);
        if (c) {
          M[i][j] = l;
          break;
        }
      }
    }
  }
  int i1, j1;
  int mx = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (M[i][j] >= mx) {
        i1 = i;
        j1 = j;
        mx = M[i][j];
      }
    }
  }
  cout << "\n+++ Exhaustive search: Square\n";
  prnWB(F, m, n, i1, i1 + mx - 1, j1, j1 + mx - 1);
  printf("    Area = %d\n", mx*mx);
}

void esrectangle(int F[51][51], int m, int n) {
  int M[51][51];
  int A[51][51];
  int B[51][51];
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      int K = m - i + 1;
      int L = n - j + 1;
      int mx = 1;
      int k1 = 1;
      int l1 = 1;
      for (int k = 1; k <= K; k++) {
        for (int l = 1; l <= L; l++) {
          bool c = ischessboard(F, m, n, i, j, k, l);
          if (c) {
            int p = k*l;
            if (p >= mx) {
              mx = p;
              k1 = k;
              l1 = l;
            }
          }
        }
      }
      M[i][j] = mx;
      A[i][j] = k1;
      B[i][j] = l1;
    }
  }
  int i1, j1, i2, j2;
  int mx = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (M[i][j] >= mx) {
        mx = M[i][j];
        i1 = i;
        j1 = j;
        i2 = i1 + A[i][j] - 1;
        j2 = j1 + B[i][j] - 1;
      }
    }
  }
  cout << "\n+++ Exhaustive search: Rectangle\n";
  prnWB(F, m, n, i1, i2, j1, j2);
  printf("    Area = %d\n", mx);
}

void dpsquare (int F[51][51], int m, int n) {
  int T[m+1][n+1];
  for (int i = 1; i <= m; i++) T[i][n] = 1;
  for (int j = 1; j <= n; j++) T[m][j] = 1;
  for (int i = m-1; i >= 1; i--) {
    for (int j = n-1; j >= 1; j--) {
      if (F[i][j] == F[i+1][j] || F[i][j] == F[i][j+1]) {
        T[i][j] = 1;
        continue;
      }
      int l1 = T[i+1][j];
      int l2 = T[i][j+1];
      if (l1 != l2) {
        T[i][j] = min(l1, l2) + 1;
        continue;
      }
      int i1 = i + l1;
      int j1 = j + l1;
      bool c1 = (F[i1][j1] != F[i1-1][j1]);
      bool c2 = (F[i1][j1] != F[i1][j1-1]);
      if (c1 && c2) T[i][j] = l1 + 1;
      else T[i][j] = l1;
    }
  }
  int i1, j1;
  int mx = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (T[i][j] >= mx) {
        i1 = i;
        j1 = j;
        mx = T[i][j];
      }
    }
  }
  cout << "\n+++ Dynamic Programming: Square\n";
  prnWB(F, m, n, i1, i1 + mx - 1, j1, j1 + mx - 1);
  printf("    Area = %d\n", mx*mx);
}

void dprectangle (int F[51][51], int m, int n) {
  /**
   * T[i][j] stores the maximum area of rectangle with top-left corner at (i, j)
   * L[i][j] = p implies that horizontal row formed by (i, j), (i, j+1), ..., (i, j+p) is a chess pattern, here p is maximal of given (i, j)
   * D[i][j] = q implies that vertical column formed by (i, j), (i+1, j), ..., (i+q, j) is a chess pattern, here q is maximal for given (i, j)
   * P[i][j] stores the length required for maximum area of rectangle
   * Q[i][j] stores the width required for maximum area of rectangle
   * 
   * Overall complexity is O(N^3) as max possible value for L[i][j] and D[i][j] for any (i, j) is less than N = max(m, n)
   */
  int T[51][51];
  int L[51][51];
  int D[51][51];
  int P[51][51];
  int Q[51][51];
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      L[i][j] = 0;
      D[i][j] = 0;
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = n-1; j >= 1; j--) {
      if (F[i][j] == F[i][j+1]) L[i][j] = 0;
      else L[i][j] = L[i][j+1] + 1;
    }
  }
  for (int j = 1; j <= n; j++) {
    for (int i = m-1; i >= 1; i--) {
      if (F[i][j] == F[i+1][j]) D[i][j] = 0;
      else D[i][j] = D[i+1][j] + 1;
    }
  }

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      T[i][j] = 1;
      int mn = 50;
      for (int p = 0; p <= L[i][j]; p++) {
        mn = min(mn, D[i][j+p]);
        int area = (p+1)*(mn+1);
        if (area >= T[i][j]) {
          T[i][j] = area;
          P[i][j] = p + 1;
          Q[i][j] = mn + 1;
        }
      }
      mn = 50;
      for (int p = 0; p <= D[i][j]; p++) {
        mn = min(mn, L[i+p][j]);
        int area = (mn + 1) * (p+1);
        if (area >= T[i][j]) {
          T[i][j] = area;
          P[i][j] = mn + 1;
          Q[i][j] = p + 1;
        }
      }
    }
  }
  int i1, j1, i2, j2;
  int mx = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (T[i][j] >= mx) {
        mx = T[i][j];
        i1 = i;
        j1 = j;
        i2 = i1 + Q[i][j] - 1;
        j2 = j1 + P[i][j] - 1;
      }
    }
  }
  cout << "\n+++ Dynamic Programming: Rectangle\n";
  prnWB(F, m, n, i1, i2, j1, j2);
  printf("    Area = %d\n", mx);
}

int main () {
  int F[51][51];
  int m, n;
  cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> F[i][j];
    }
  }
  essquare(F, m, n);
  esrectangle(F, m, n);
  dpsquare(F, m, n);
  dprectangle(F, m, n);
  return 0;
}
