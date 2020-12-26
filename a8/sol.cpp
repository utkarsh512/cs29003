/**
 * Author: Utkarsh Patel
 * Roll  : 18EC30048
 * Topic : Heaps and priority queues
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct node {
  int length;
  int *a;
  int MAX;
  int MIN;
};

struct heap {
  int n; // number of keys
  int N; // no. of nodes
  int p;
  int nmax;
  node *nodes;
};

#define mtype int

void merge (mtype arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    mtype L[n1], R[n2];
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] > R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergesort(mtype arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

heap initheap(int p, int nmax) {
  int SIZE = (nmax + p - 1) / p + 1;
  heap h;
  h.nodes = (node *) malloc (SIZE * sizeof(node));
  for (int i = 1; i < SIZE; i++) {
    h.nodes[i].length = 0;
    h.nodes[i].a = (int *) malloc (p * sizeof(int));
  }
  h.n = 0;
  h.N = 0;
  h.p = p;
  h.nmax = nmax;
  return h;
}

void insert(heap& h, int x) {
  if (h.N == 0) (h.N)++;
  else if (h.nodes[h.N].length == h.p) (h.N)++;
  (h.n)++;
  h.nodes[h.N].a[(h.nodes[h.N].length)++] = x;
  if ((h.nodes[h.N].length) == 1) {
    h.nodes[h.N].MAX = x;
    h.nodes[h.N].MIN = x;
  } else {
    if (x > h.nodes[h.N].MAX) h.nodes[h.N].MAX = x;
    if (x < h.nodes[h.N].MIN) h.nodes[h.N].MIN = x;
  }

  // moving the disturbance
  int q = h.N;
  bool c = true;
  while (q != 1 && c) {
    int r = q / 2; // parent node index
    int rmin = h.nodes[r].MIN;
    int qmax = h.nodes[q].MAX;
    if (rmin >= qmax) {
      c = false;
    }
    if (rmin < qmax) {
      int l1 = h.nodes[r].length;
      int l2 = h.nodes[q].length;
      int arr[l1+l2];
      for (int i = 0; i < l1; i++) {
        arr[i] = h.nodes[r].a[i];
      }
      for (int i = 0; i < l2; i++) {
        arr[l1+i] = h.nodes[q].a[i];
      }
      mergesort(arr, 0, l1+l2-1);
      for (int i = 0; i < l1; i++) {
        h.nodes[r].a[i] = arr[i];
      }
      for (int i = 0; i < l2; i++) {
        h.nodes[q].a[i] = arr[i+l1];
      }
      h.nodes[r].MAX = h.nodes[r].a[0];
      h.nodes[r].MIN = h.nodes[r].a[l1-1];
      h.nodes[q].MAX = h.nodes[q].a[0];
      h.nodes[q].MIN = h.nodes[q].a[l2-1];
      q = r;
    }
  }
}

int findmax(heap& h) {
  if (h.N == 0) {
    cout << "Error: Heap is empty!!\n";
    return -1;
  }
  return h.nodes[1].MAX;
}

void heapify(heap& h, int i) {
  if (i > (h.N) / 2) return;
  int qmin = h.nodes[i].MIN;
  int lmax = h.nodes[2*i].MAX;
  int rmax = ((2*i+1) > (h.N))? -1: h.nodes[2*i+1].MAX;
  bool lc = true;
  if (rmax > lmax) lc = false;
  if (lc) {
    if (qmin >= lmax) return;
    else {
      int ind_of_qmin = -1, ind_of_lmax = -1;
      for (int j = 0; j < h.nodes[i].length; j++) {
        if (h.nodes[i].a[j] == qmin) {
          ind_of_qmin = j;
          break;
        }
      }
      for (int j = 0; j < h.nodes[2*i].length; j++) {
        if (h.nodes[2*i].a[j] == lmax) {
          ind_of_lmax = j;
          break;
        }
      }
      // swapping
      int temp = h.nodes[i].a[ind_of_qmin];
      h.nodes[i].a[ind_of_qmin] = h.nodes[2*i].a[ind_of_lmax];
      h.nodes[2*i].a[ind_of_lmax] = temp;

      // Recalculating MIN and MAX
      int MIN = h.nodes[i].a[0];
      int MAX = h.nodes[i].a[0];
      for (int j = 0; j < h.nodes[i].length; j++) {
        if (h.nodes[i].a[j] > MAX) MAX = h.nodes[i].a[j];
        if (h.nodes[i].a[j] < MIN) MIN = h.nodes[i].a[j];
      }
      h.nodes[i].MAX = MAX;
      h.nodes[i].MIN = MIN;

      MIN = h.nodes[2*i].a[0];
      MAX = h.nodes[2*i].a[0];
      for (int j = 0; j < h.nodes[2*i].length; j++) {
        if (h.nodes[2*i].a[j] > MAX) MAX = h.nodes[2*i].a[j];
        if (h.nodes[2*i].a[j] < MIN) MIN = h.nodes[2*i].a[j];
      }
      h.nodes[2*i].MAX = MAX;
      h.nodes[2*i].MIN = MIN;

      heapify(h, 2*i);
    }
  } else {
    if (qmin >= rmax) return;
    else {
      int ind_of_qmin = -1, ind_of_rmax = -1;
      for (int j = 0; j < h.nodes[i].length; j++) {
        if (h.nodes[i].a[j] == qmin) {
          ind_of_qmin = j;
          break;
        }
      }
      for (int j = 0; j < h.nodes[2*i+1].length; j++) {
        if (h.nodes[2*i+1].a[j] == rmax) {
          ind_of_rmax = j;
          break;
        }
      }
      // swapping
      int temp = h.nodes[i].a[ind_of_qmin];
      h.nodes[i].a[ind_of_qmin] = h.nodes[2*i+1].a[ind_of_rmax];
      h.nodes[2*i+1].a[ind_of_rmax] = temp;

      // Recalculating MIN and MAX
      int MIN = h.nodes[i].a[0];
      int MAX = h.nodes[i].a[0];
      for (int j = 0; j < h.nodes[i].length; j++) {
        if (h.nodes[i].a[j] > MAX) MAX = h.nodes[i].a[j];
        if (h.nodes[i].a[j] < MIN) MIN = h.nodes[i].a[j];
      }
      h.nodes[i].MAX = MAX;
      h.nodes[i].MIN = MIN;

      MIN = h.nodes[2*i+1].a[0];
      MAX = h.nodes[2*i+1].a[0];
      for (int j = 0; j < h.nodes[2*i+1].length; j++) {
        if (h.nodes[2*i+1].a[j] > MAX) MAX = h.nodes[2*i+1].a[j];
        if (h.nodes[2*i+1].a[j] < MIN) MIN = h.nodes[2*i+1].a[j];
      }
      h.nodes[2*i+1].MAX = MAX;
      h.nodes[2*i+1].MIN = MIN;

      heapify(h, 2*i+1);
    }
  }
}

void delmax(heap& h) {
  int rootmax = h.nodes[1].MAX;
  int ind_of_rootmax = -1;
  int aux[h.p];
  int al = 0;
  for (int j = 0; j < h.nodes[1].length; j++) {
    if (ind_of_rootmax == -1 && h.nodes[1].a[j] == rootmax) {
      ind_of_rootmax = j;
    } else {
      aux[al++] = h.nodes[1].a[j];
    }
  }
  h.nodes[1].length = al;
  for (int j = 0; j < al; j++) {
    h.nodes[1].a[j] = aux[j];
  }
  if (h.N == 1) {
    int MIN = h.nodes[1].a[0];
    int MAX = h.nodes[1].a[0];
    for (int j = 0; j < h.nodes[1].length; j++) {
      if (h.nodes[1].a[j] > MAX) MAX = h.nodes[1].a[j];
      if (h.nodes[1].a[j] < MIN) MIN = h.nodes[1].a[j];
    }
    h.nodes[1].MAX = MAX;
    h.nodes[1].MIN = MIN;
  }
  else {
    int le = h.nodes[h.N].length;
    int ele = h.nodes[h.N].a[le-1];
    (h.nodes[h.N].length)--;
    if ((h.nodes[h.N].length) == 0) (h.N)--;
    else {
      int MIN = h.nodes[h.N].a[0];
      int MAX = h.nodes[h.N].a[0];
      for (int j = 0; j < h.nodes[h.N].length; j++) {
        if (h.nodes[h.N].a[j] > MAX) MAX = h.nodes[h.N].a[j];
        if (h.nodes[h.N].a[j] < MIN) MIN = h.nodes[h.N].a[j];
      }
      h.nodes[h.N].MAX = MAX;
      h.nodes[h.N].MIN = MIN;
    }
    h.nodes[1].a[(h.nodes[1].length)++] = ele;
    int MIN = h.nodes[1].a[0];
    int MAX = h.nodes[1].a[0];
    for (int j = 0; j < h.nodes[1].length; j++) {
      if (h.nodes[1].a[j] > MAX) MAX = h.nodes[1].a[j];
      if (h.nodes[1].a[j] < MIN) MIN = h.nodes[1].a[j];
    }
    h.nodes[1].MAX = MAX;
    h.nodes[1].MIN = MIN;
    heapify(h, 1);
  }
}

void prnheap (heap& h) {
  for (int i = 1; i <= h.N; i++) {
    cout << "    [ ";
    for (int j = 0; j < h.nodes[i].length; j++) {
      printf("%4d ", h.nodes[i].a[j]);
    }
    for (int j = h.nodes[i].length; j < h.p; j++) {
      cout << "     ";
    }
    cout << "]\n";
  }
}

int main() {
  int p, n;
  cin >> p;
  cin >> n;
  int A[n];
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }
  heap h = initheap(p, n);
  for (int i = 0; i < n; i++) {
    insert(h, A[i]);
  }
  cout << "\n+++ " << h.n << " insertions made\n";
  prnheap(h);
  for (int i = n-1; i >= 0; i--) {
    A[i] = findmax(h);
    delmax(h);
  }
  cout << "\n+++ " << n << " deletions made\n\n";
  cout << "+++ Input array sorted";
  for (int i = 0; i < n; i++) {
    if (i % 20 == 0) cout << "\n";
    printf("%4d ", A[i]);
  }
  cout << "\n";
  return 0;
}
