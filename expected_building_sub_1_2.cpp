// Brute solution for basic testing.
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 6;
const long long MOD = 163577857; // FFT friendly-prime.

long long add(long long a, long long b) {
  long long r = a + b;
  return (r >= MOD ? r % MOD : r);
}

long long sub(long long a, long long b) {
  long long r = (a - b) % MOD;
  return (r < 0 ? r + MOD : r);
}

long long mul(long long a, long long b) {
  long long r = a * b;
  return (r >= MOD ? r % MOD : r);
}

long long power(long long a, long long b) {
  long long x = 1, y = a;
  while(b) {
    if (b & 1) {
      x = mul(x, y);
    }
    y = mul(y, y);
    b >>= 1;
  }
  return x;
}

long long inv(long long a) {
  long long ans = power(a, MOD - 2);
  assert(mul(a, ans) == 1);
  return ans;
}

int pos[MAX];
long long a[MAX];
long long coef[MAX];
long long prefix[MAX];

int main() {
  int n, h, x, k;
  cin >> n >> h >> x >> k;
  for(int i = 1; i <= n; ++i) {
    cin >> pos[i];
  }
  for(int i = 1; i <= k; ++i) {
    cin >> a[i];
  }
  for(int i = 1; i <= k; ++i) {
    cin >> coef[i];
  }
  for(int i = k+1; i <= h; ++i) {
    a[i] = 0;
    for(int j = 1; j <= k; ++j) {
      a[i] = add(a[i], mul(coef[j], a[i - j]));
    }
  }
  for(int i = 1; i <= h; ++i) {
    prefix[i] = add(prefix[i - 1], a[i]);
  }
  long long num = 0, den = 0;
  for(int i = 1; i <= n; ++i) {
    if (pos[i] >= x) {
      num = add(num, sub(prefix[pos[i]], prefix[pos[i] - x]));
    }
    else {
      num = add(num, prefix[pos[i]]);
      num = add(num, sub(prefix[h], prefix[h - (x - pos[i])]));
    }
  }
  for(int i = 1; i <= h; ++i) {
    den = add(den, a[i]);
  }
  cout << mul(num, inv(den)) << "\n";
  return 0;
}