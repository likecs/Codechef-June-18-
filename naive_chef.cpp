#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e4 + 4;

int freq[MAX];

int main() {
  int t, n, a, b, x;
  cin >> t;
  while(t--) {
    cin >> n >> a >> b;
    fill(freq, freq + n + 1, 0);
    for(int i = 1; i <= n; ++i) {
      cin >> x;
      freq[x] += 1;
    }
    int num = freq[a] * freq[b];
    int den = n * n;
    cout << ((double)num / den) << "\n";
  }
  return 0;
}