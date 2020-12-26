/**
 * Author : Utkarsh Patel
 * Roll   : 18EC30048
 * Topic  : Shortest path problems in graphs
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define inf 1e9

struct graph { 
  int n;     // no. of cities
  char **c;  // character array
  int **p;   // price array
};

graph readgraph () {
  int n;
  cin >> n;
  graph G;
  G.n = n;
  G.c = (char **) malloc (n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    G.c[i] = (char *) malloc (n * sizeof(char));
    for (int j = 0; j < n; j++) G.c[i][j] = '-';
  }
  for (int i = 0; i < n; i++) G.c[i][i] = 's';
  G.p = (int **) malloc (n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    G.p[i] = (int *) malloc (n * sizeof(int));
    for (int j = 0; j < n; j++) G.p[i][j] = inf;
  }
  for (int i = 0; i < n; i++) G.p[i][i] = 0;
  int i, j, c;
  string a;
  cin >> i;
  while (i != -1) {
    cin >> j >> c >> a;
    G.c[i][j] = a[0];
    G.p[i][j] = c;
    cin >> i;
  }
  return G;
}

graph getAIgraph(graph G) {
  graph AI;
  int n = G.n;
  AI.n = n;
  AI.c = (char **) malloc (n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    AI.c[i] = (char *) malloc (n * sizeof(char));
    for (int j = 0; j < n; j++) {
      if (G.c[i][j] == 'n') AI.c[i][j] = '-';
      else AI.c[i][j] = G.c[i][j];
    }
  }
  AI.p = (int **) malloc (n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    AI.p[i] = (int *) malloc (n * sizeof(int));
    for (int j = 0; j < n; j++) {
      if (AI.c[i][j] == 'a') AI.p[i][j] = G.p[i][j];
      else if (AI.c[i][j] == 's') AI.p[i][j] = 0;
      else AI.p[i][j] = inf;
    }
  }
  return AI;
}

int **APSP (graph H) {
  /* Time Complexity: O(n^3) */
  int n = H.n;
  int **C = (int **) malloc (n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    C[i] = (int *) malloc (n * sizeof(int));
    for (int j = 0; j < n; j++) {
      C[i][j] = H.p[i][j];
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (C[i][j] > C[i][k] + C[k][j]) {
          C[i][j] = C[i][k] + C[k][j];
        }
      }
    }
  }
  return C;
}

int **APSPone (graph G, int **C1) {
  /* Time Complexity: O(n^4) */
  int n = G.n;
  int **C2 = (int **) malloc (n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    C2[i] = (int *) malloc (n * sizeof(int));
  }
  for (int i = 0; i < n; i++) {       // for this loop system, overall complexity is O(n^4)
    for (int j = 0; j < n; j++) {
      if (C1[i][j] != inf) {
        C2[i][j] = C1[i][j];
        continue;
      }
      C2[i][j] = inf;
      for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
          if (G.c[k][l] == 'n') {
            C2[i][j] = min(C2[i][j], C1[i][k] + G.p[k][l] + C1[l][j]);
          }
        }
      }
    }
  }
  return C2;
}

int **APSPany (graph G, int **C1) {
  /* Time Complexity : O(n^3) */
  int n = G.n;
  int **C3 = (int **) malloc (n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    C3[i] = (int *) malloc (n * sizeof(int));
  }

  int **C4 = APSP(G);                          // ---> complexity is O(n^3)

  for (int i = 0; i < n; i++) {                // ---> complexity is O(n^2)
    for (int j = 0; j < n; j++) {
      if (C1[i][j] != inf) {
        C3[i][j] = C1[i][j];
        continue;
      }
      C3[i][j] = C4[i][j];
    }
  }
  return C3;
}

void prngraph(graph G) {
  int n = G.n;
  for (int i = 0; i < n; i++) {
    printf("   %2d    -> ", i);
    for (int j = 0; j < n; j++) {
      if (G.p[i][j] == 0 || G.p[i][j] == inf) continue;
      printf("%2d (%4d, %c)  ", j, G.p[i][j], G.c[i][j]);
    }
    cout << "\n";
  }
}

void prnchart (int **C, int n) {
  cout << "            ";
  for (int i = 0; i < n; i++) printf("%5d ", i);
  cout << "\n\n";
  for (int i = 0; i < n; i++) {
    printf("   %2d    -> ", i);
    for (int j = 0; j < n; j++) {
      if (C[i][j] == inf) cout << "    - ";
      else printf("%5d ", C[i][j]);
    }
    cout << "\n";
  }
}

int main() {
  graph G = readgraph();
  cout << "\n+++ Original Graph\n";
  prngraph(G);
  graph H = getAIgraph(G);
  cout << "\n+++ AI subgraph\n";
  prngraph(H);
  int **C1 = APSP(H);
  cout << "\n+++ Cheapest AI prices\n";
  prnchart(C1, H.n);
  int **C2 = APSPone(G, C1);
  cout << "\n+++ Cheapest prices with at most one non-AI leg\n";
  prnchart(C2, H.n);
  int **C3 = APSPany(G, C1);
  cout << "\n+++ Cheapest prices with any number of non-AI legs\n";
  prnchart(C3, G.n);
  cout << "\n";
  return 0;
}
