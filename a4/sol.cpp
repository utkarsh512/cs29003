/**
 * @author utkarshpatel (https://github.com/utkarshiitkgp)
 * Solution to Part(4) - but better - O(kn)
 */

#include <bits/stdc++.h>
 
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int logn = (int)log2(n);
    int a[k];
    for (int i = 0; i < k; i++) cin >> a[i];
    int limit = n + logn;
    int memo[limit + 1];
    for (int i = 0; i <= limit; i++) memo[i] = -1;
    memo[1] = 0;
    for (int i = 1; i <= limit; i++) {
        if (i*2 <= limit) memo[i*2] = memo[i] + 1;
        for (int j = 0; j < k; j++) {
            int x = i - a[j];
            if (x < 1 || x > limit) continue;
            if (memo[x] == -1) {
                memo[x] = memo[i] + 1;
                continue;
            }
            memo[x] = min(memo[x], memo[i] + 1);
        }
    }
    int y = n;
    int ctr = 0;
    while (y > 1) {
        cout << y << " => ";
        int miin = y;
        int pivot;
        for (int i = 0; i < k; i++) {
            if (memo[y + a[i]] <= miin) {
                miin = memo[y + a[i]];
                pivot = y + a[i];
            }
        }
        if (y % 2 == 0) {
            if (memo[y/2] <= miin) {
                pivot = y/2;
            }
        }
        y = pivot;
        ctr++;
    }
    cout << 1 << endl << "Optimal steps : " << ctr << endl;
    return 0;
}
