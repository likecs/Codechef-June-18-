#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> matrix;

const int MAX = 50001;
const int LN = 31;
const int MOD = 163577857;
const long long MOD2 = (long long)MOD * MOD;

int N, H, X, K, sz;
int P[MAX];
int A[MAX];
int C[MAX];
int S[MAX];
matrix pre[LN];
map<int,int> store;

int add(int a, int b) {
  long long r = a + b;
  return (r >= MOD ? r - MOD : r);
}

int sub(int a, int b) {
  int r = a - b;
  return (r < 0 ? r + MOD : r);
}

int mul(int a, int b) {
  long long r = (long long)a * b;
  return (r >= MOD ? r % MOD : r);
}

int power(int a, int b) {
  int x = 1, y = a;
  while(b) {
    if (b & 1) {
      x = mul(x, y);
    }
    y = mul(y, y);
    b >>= 1;
  }
  return x;
}

int inv(int a) {
  return power(a, MOD - 2);
}

matrix special_square_multiply(matrix &a) {
  matrix c(sz, vector<int>(sz, 0));
  for(int i = 0; i < K; ++i) {
    for(int j = 0; j < sz; ++j) {
      long long temp = 0;
      for(int k = 0; k < sz; ++k) {
        temp += (long long)a[i][k] * a[k][j];
        if (temp >= MOD2) {
          temp -= MOD2;
        }
      }
      c[i][j] = temp %= MOD;
    }
  }
  for(int i = 0; i < K; ++i) {
    c[i + K][i + K] = 1;
  }
  return c;
}

vector<int> special_recurrent_multiply(matrix &a, vector<int> &b) {
  vector<int> c(sz, 0);
  for(int i = 0; i < K; ++i) {
    long long temp = 0;
    for(int j = 0; j < sz; ++j) {
      temp += (long long)a[i][j] * b[j];
      if (temp >= MOD2) {
        temp -= MOD2;
      }
    }
    c[i] = temp % MOD;
  }
  for(int i = 0; i < K; ++i) {
    c[i + K] = b[i + K];
  }
  return c;
}

void init() {
  sz = 2 * K;
  pre[0] = matrix(sz, vector<int>(sz, 0));
  pre[1] = matrix(sz, vector<int>(sz, 0));
  for(int i = 0; i < sz; ++i) {
    pre[0][i][i] = 1;
  }
  for(int i = 0; i < K; ++i) {
    pre[1][0][i] = C[i + 1];
  }
  for(int i = 1; i < K; ++i) {
    pre[1][i][i-1] = 1;
  }
  for(int i = 0; i < K; ++i) {
    pre[1][i][i + K] = 1;
    pre[1][i + K][i + K] = 1;
  }
  for(int i = 2; i < LN; ++i) {
    pre[i] = special_square_multiply(pre[i - 1]);
  }
}

int get_prefix_sum(int x) {
  if (x <= K) {
    return S[x];
  }
  else if (store.find(x) != store.end()) {
    return store[x];
  }
  x -= (K - 1);
  vector<int> res(2 * K, 0);
  for(int i = 0; i < K; ++i) {
    res[i + K] = A[K - i];
  }
  for(int i = 0; i < LN; ++i) {
    if (x & (1 << i)) {
      res = special_recurrent_multiply(pre[i + 1], res);
    }
  }
  return (store[x + K - 1] = add(S[K - 1], res[0]));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> N >> H >> X >> K;
  for(int i = 1; i <= N; ++i) {
    cin >> P[i];
  }
  for(int i = 1; i <= K; ++i) {
    cin >> A[i];
    A[i] %= MOD;
  }
  for(int i = 1; i <= K; ++i) {
    cin >> C[i];
    C[i] %= MOD;
  }
  init();
  for(int i = 1; i <= K; ++i) {
    S[i] = add(S[i-1], A[i]);
  }
  long long num = 0, den = get_prefix_sum(H);
  for(int i = 1; i <= N; ++i) {
    if (P[i] >= X) {
      num = add(num, sub(get_prefix_sum(P[i]), get_prefix_sum(P[i] - X)));
    }
    else {
      num = add(num, get_prefix_sum(P[i]));
      num = add(num, sub(den, get_prefix_sum(H - (X - P[i]))));
    }
  }
  cout << mul(num, inv(den)) << "\n";
  return 0;
}