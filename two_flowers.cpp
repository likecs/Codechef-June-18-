#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int MAX = 2001;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int n, m;
int a[MAX][MAX];
bool vis[MAX][MAX];
bool edge_vis[MAX][MAX][4];

void update(int x, int y, int c) {
  for(int i = 0; i < 4; ++i) {
    int _x = x + dx[i], _y = y + dy[i];
    if (_x >= 1 && _x <= n && _y >= 1 && _y <= m) {
      if (a[_x][_y] == c) {
        edge_vis[x][y][i] = 1;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> m;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      cin >> a[i][j];
    }
  }
  int ans = 0;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      for(int k = 0; k < 2; ++k) {
        int x = i + dx[k], y = j + dy[k];
        if (x > n || y > m) {
          continue;
        }
        if (edge_vis[i][j][k]) {
          continue;
        }
        int c1 = a[i][j], c2 = a[x][y];
        queue<pii> q;
        q.push({i, j});
        vis[i][j] = 1;
        vector<pii> restore;
        while(!q.empty()) {
          pii u = q.front();
          q.pop();
          restore.push_back(u);
          for(int l = 0; l < 4; ++l) {
            int _x = u.first + dx[l], _y = u.second + dy[l];
            if (_x >= 1 && _x <= n && _y >= 1 && _y <= m) {
              if (vis[_x][_y] == 0 && (a[_x][_y] == c1 || a[_x][_y] == c2)) {
                vis[_x][_y] = 1;
                update(u.first, u.second, c1 ^ c2 ^ a[u.first][u.second]);
                update(_x, _y, c1 ^ c2 ^ a[_x][_y]);
                q.push({_x, _y});
              }
            }
          }
        }
        // cout << i << " " << j << " : " << x << " " << y << " -> ";
        // cout << c1 << " " << c2 << " " << restore.size() << "\n";
        // cout << " ----" << "\n";
        ans = max(ans, (int)restore.size());
        for(auto it : restore) {
          vis[it.first][it.second] = 0;
        }
      }
    }
  }
  cout << ans << "\n";
  return 0;
}