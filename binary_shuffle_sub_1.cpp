// Brute force solution based on Floyd warshall alorithm.
#include <bits/stdc++.h>
using namespace std;

const int LN = 8;
const int INF = 10000;
const int MAX = 1 << LN;

int adj[MAX][MAX];

int count_ones(int x) {
  int r = 0;
  while(x > 0) {
    if (x & 1) {
      r += 1;
    }
    x >>= 1;
  }
  return r;
}

vector<int> to_bin(int &x) {
  vector<int> v;
  for(int i = LN - 1; i >= 0; --i) {
    if (x & (1 << i)) {
      v.push_back(1);
    }
    else {
      v.push_back(0);
    }
  }
  return v;
}

int to_num(vector<int> &x) {
  int v = 0;
  for(int i = 0; i < LN; ++i) {
    if (x[i] == 1) {
      v |= (1 << (LN - i - 1));
    }
  }
  return v;
}

void add_edges(int x) {
  vector<int> bin = to_bin(x);
  sort(bin.begin(), bin.end());
  do {
    int num = to_num(bin);
    if (num + 1 < MAX) {
      adj[x][num + 1] = 1;
    }
  }while(next_permutation(bin.begin(), bin.end()));
}

int main() {
  for(int i = 0; i < MAX; ++i) {
    for(int j = 0; j < MAX; ++j) {
      adj[i][j] = INF;
    }
  }
  for(int i = 0; i < MAX; ++i) {
    add_edges(i);
    adj[i][i] = 0;
  }
  for(int i = 0; i < MAX; ++i) {
    for(int j = 0; j < MAX; ++j) {
      for(int k = 0; k < MAX; ++k) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }
  int t;
  long long a, b;
  cin >> t;
  while(t--) {
    cin >> a >> b;
    cout << (adj[a][b] == INF ? -1 : adj[a][b]) << "\n";
  }
  return 0;
}