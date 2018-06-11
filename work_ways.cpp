#include <bits/stdc++.h>
using namespace std;

int n, c, ptr;
vector<int> facts;
int ans[1000001];

bool check(int idx) {
  ptr = n;
  int prod = c;
  while(ptr > 0) {
    while(prod % facts[idx] != 0) {
      idx -= 1;
    }
    prod /= facts[idx];
    ans[ptr] = facts[idx] + ptr - 1;
    ptr -= 1;
    if (idx != (facts.size() - 1) && facts[idx] == (facts[idx + 1] - 1)) {
      // greedily chose the largest factor.
      idx += 1;
    }
    if (idx == 0 || prod == 1) {
      // string of 1 as factor so prod will remain same.
      break;
    }
  }
  return (prod == 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--) {
    cin >> n >> c;
    facts.clear();
    int x = sqrt(c);
    for(int i = 1; i <= x; ++i) {
      if (c % i == 0) {
        facts.push_back(i);
        if (i * i != c) {
          facts.push_back(c / i);
        }
      }
    }
    sort(facts.begin(), facts.end());
    for(int i = 0; i < facts.size(); ++i) {
      if (check(i)) {
        break;
      }
    }
    for(int i = 1; i <= ptr; ++i) {
      cout << i << " ";
    }
    for(int i = ptr+1; i <= n; ++i) {
      cout << ans[i] << " ";
    }
    cout << "\n";
  }
  return 0;
}