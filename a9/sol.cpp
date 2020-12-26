/**
 * Author: Utkarsh Patel
 * Roll  : 18EC30048
 * Topic : Application of Graph traversal
 */

#include <bits/stdc++.h>

using namespace std;

#define trace(x) cerr << #x << ": " << x << "\n"

typedef vector<int> vi;
typedef vector<char> vc;

struct graph {
  int n;                 // no. of vertices
  char *c;               // array of colors
  int *v;                // array of vertex numbers
  vector<vector<int>> g; // adjacency list representation of graph
};

graph readgraph() {
  graph p;
  int n; cin >> n;
  p.n = n;
  p.c = (char *) malloc (n * sizeof(char));
  p.v = (int *) malloc (n * sizeof(int));
  p.g.resize(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    p.v[i] = i;
    p.c[i] = s[0];
  }
  int u, v;
  cin >> u;
  while (u != -1) {
    cin >> v;
    p.g[u].push_back(v);
    p.g[v].push_back(u);
    cin >> u;
  }
  return p;
}

void prngraph(graph& p) {
  for (int i = 0; i < p.n; ++i) {
    cout << "    ";
    printf("[%c] %3d -> ", p.c[i], p.v[i]);
    for (auto j : p.g[i]) {
      printf("%3d, ", p.v[j]);
    }
    cout << "\n";
  }
}

int findindex (graph&p, int val) {
  int i;
  for (int i = 0; i < p.n; i++) {
    if (p.v[i] == val) return i;
  }
  return -1;
}

graph getcolgraph (graph& G, char color) {
  graph p; // reqd subgraph
  int n = 0;
  for (int i = 0; i < G.n; i++) {
    if (G.c[i] == color) ++n;
  }
  p.n = n;
  p.c = (char *) malloc (n * sizeof(char));
  p.v = (int *) malloc (n * sizeof(int));
  p.g.resize(n);
  int k = 0;
  for (int i = 0; i < G.n; i++) {
    if (G.c[i] == color) {
      p.c[k] = color;
      p.v[k] = i;
      k++;
    }
  }
  for (int i = 0; i < p.n; i++) {
    int val = p.v[i];
    for (auto j : G.g[val]) {
      if (G.c[j] == color) {
        int ind = findindex(p, j);
        p.g[i].push_back(ind);
      }
    }
  }
  return p;
}

void prnbackedges(graph& p, vi& parent, int i, int j) {
  vi nodes;
  vc colors;
  int k = j;
  while (k != i) {
    nodes.push_back(k);
    colors.push_back(p.c[k]);
    k = parent[k];
  }
  nodes.push_back(i);
  colors.push_back(p.c[i]);
  cout << "    (";
  for (auto r : nodes) cout << p.v[r] << ", ";
  cout << "), Color : (";
  for (auto r : colors) cout << r << ", ";
  cout << ")\n";
}

void dfs (int i, graph& p, vi& visited, vi& level, vi& parent) {
  visited[i] = 1;
  for (auto j : p.g[i]) {
    if (visited[j] == 0) {
      parent[j] = i;
      level[j] = level[i] + 1;
      dfs(j, p, visited, level, parent);
    } else {
      if (level[i] - level[j] > 1) {
        prnbackedges(p, parent, j, i);
      }
    }
  }
}

vi multidfs (graph& p) {
  vi visited(p.n, 0);
  vi level(p.n, 0);
  vi parent(p.n, -1);
  for (int i = 0; i < p.n; i++) {
    if (visited[i] == 0) dfs(i, p, visited, level, parent);
  }
  return parent;
}

void prnedges(set<pair<int, int>>& s) {
  for (auto e : s) {
    cout << e.first << " <-> " << e.second << "\n";
  }
}

graph getrbgraph (graph& G, graph& GR, graph& GB, vi& p1, vi& p2) {
  set<pair<int, int>> edges;
  int n = G.n;
  int rn = GR.n;
  int bn = GB.n;
  for (int i = 0; i < bn; i++) {
    if (p2[i] == -1) continue;
    int j = p2[i];
    int MIN = min(GB.v[i], GB.v[j]);
    int MAX = max(GB.v[i], GB.v[j]);
    edges.insert({MIN, MAX});
  }
  for (int i = 0; i < rn; i++) {
    if (p1[i] == -1) continue;
    int j = p1[i];
    int MIN = min(GR.v[i], GR.v[j]);
    int MAX = max(GR.v[i], GR.v[j]);
    edges.insert({MIN, MAX});
  }
  for (int i = 0; i < n; i++) {
    for (auto j : G.g[i]) {
      if (G.c[i] == G.c[j]) continue;
      int MIN = min(i, j);
      int MAX = max(i, j);
      edges.insert({MIN, MAX});
    }
  }
  graph GRB;
  GRB.n = G.n;
  GRB.c = G.c;
  GRB.v = G.v;
  GRB.g.resize(GRB.n);
  for (auto e : edges) {
    GRB.g[e.first].push_back(e.second);
    GRB.g[e.second].push_back(e.first);
  }
  return GRB;
}

int main() {
  graph G = readgraph();
  cout << "\n+++ Original Graph (G)\n";
  prngraph(G);
  graph GR = getcolgraph(G, 'r');
  graph GB = getcolgraph(G, 'b');
  cout << "\n+++ Red subgraph (GR)\n";
  prngraph(GR);
  cout << "\n+++ Blue subgraph (GB)\n";
  prngraph(GB);
  cout << "\n+++ Red cycles\n";
  vi p1 = multidfs(GR);
  cout << "\n+++ Blue cycles\n";
  vi p2 = multidfs(GB);
  graph GRB = getrbgraph(G, GR, GB, p1, p2);
  cout << "\n+++ Nonmonochromatic graph (GRB)\n";
  prngraph(GRB);
  cout << "\n+++ Multi-color cycles\n";
  vi p3 = multidfs(GRB);
  cout << "\n";
  return 0;
}
