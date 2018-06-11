#include <bits/stdc++.h>
using namespace std;

int count_ones(long long x) {
  int ones = 0;
  while(x) {
    if (x & 1) {
      ones += 1;
    }
    x >>= 1;
  }
  return ones;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t, ans;
  long long a, b;
  cin >> t;
  while(t--) {
    cin >> a >> b;
    if (a == b) {
      ans = 0;
    }
    else if (b == 0) {
      ans = -1;
    }
    else if (b == 1) {
      if (a == 0) {
        ans = 1;
      }
      else {
        ans = -1;
      }
    }
    else {
      int ones_a = count_ones(a);
      int ones_b = count_ones(b - 1);
      if (ones_a > ones_b) {
        ans = 2;
      }
      else {
        ans = ones_b - ones_a + 1;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}