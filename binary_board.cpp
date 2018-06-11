#include <bits/stdc++.h>
using namespace std;

#define fi first
#define sec second

const int MAX = 25005;
const long long INF = (long long)1e14;

//Complexity : O(V^2E)
struct Dinic {
  struct edge {
    int a, b;
    long long cap, flow;
  };
  int n, source, sink;
  int dis[MAX];
  int ptr[MAX];
  int color[MAX];
  vector<edge> e;
  vector<edge> min_cut;
  vector<int> adj[MAX];
  Dinic(int a, int b, int c) {
    n = a;
    source = b;
    sink = c;
    e.clear();
    min_cut.clear();
    for(int i = 1; i <= n; ++i) {
      adj[i].clear();
    }
  }
  void add_edge(int a, int b, long long cap) {
    edge e1 = {a, b, cap, 0};
    edge e2 = {b, a, 0, 0};
    adj[a].push_back((int)e.size());
    e.push_back(e1);
    adj[b].push_back((int)e.size());
    e.push_back(e2);
  }
  bool bfs() {
    queue<int> q;
    q.push(source);
    fill(dis + 1, dis + n + 1, -1);
    dis[source] = 0;
    while(!q.empty() && dis[sink] == -1) {
      int from = q.front();
      q.pop();
      for(int id : adj[from]) {
        int to = e[id].b;
        if (dis[to] == -1 && e[id].flow < e[id].cap) {
          dis[to] = dis[from] + 1;
          q.push(to);
        }
      }
    }
    while(!q.empty()) {
      q.pop();
    }
    return dis[sink] != -1;
  }
  long long dfs(int v, long long flow) {
    if (!flow) {
      return 0;
    }
    if (v == sink) {
      return flow;
    }
    for(; ptr[v] < adj[v].size(); ++ptr[v]) {
      int id = adj[v][ptr[v]];
      int to = e[id].b;
      if (dis[to] != dis[v] + 1) {
        continue;
      }
      long long pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
      if (pushed) {
        e[id].flow += pushed;
        e[id^1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }
  long long max_flow() {
    long long flow = 0, pushed;
    while(bfs()) {
      fill(ptr + 1, ptr + n + 1, 0);
      while((pushed = dfs(source, INF))) {
        flow += pushed;
      }
    }
    return flow;
  }
  void build_min_cut() {
    for(int i = 0; i < e.size(); i += 2) {
      if (e[i].flow == e[i].cap) {
        if (dis[e[i].a] != -1 && dis[e[i].b] == -1) {
          min_cut.push_back(e[i]);
        }
      }
    }
  }
  bool edge_in_min_cut(int a, int b) {
    for(int i = 0; i < min_cut.size(); ++i) {
      if (min_cut[i].a == a && min_cut[i].b == b) {
        return true;
      }
    }
    return false;
  }
  #define red   1
  #define blue  2
  void build_partition() {
    for(int i = 1; i <= n; ++i) {
      color[i] = dis[i] == -1 ? red : blue;
    }
  }
  void print_graph() {
    for(int i = 0; i < e.size(); ++i) {
      printf("from: %d to : %d flow : %lld cap : %lld\n", e[i].a, e[i].b, e[i].flow, e[i].cap);
      ++i;
    }
  }
  void print_min_cut() {
    printf("Edges in min cut are : \n");
    for(int i = 0; i < min_cut.size(); ++i) {
      printf("from : %d to : %d\n", min_cut[i].a, min_cut[i].b);
    }
  }
  void print_partition() {
    printf("Vertices in 1st partition are : \n");
    for(int i = 1; i <= n; ++i) {
      if (color[i] == red) {
        printf("%d ", i);
      }
    }
    printf("\n");
    printf("Vertices in 2nd partition are : \n");
    for(int i = 1; i <= n; ++i) {
      if (color[i] == blue) {
        printf("%d ", i);
      }
    }
    printf("\n");
  }
};

string s[MAX];
long long cb[MAX];
long long cw[MAX];

int main() {
  ios_base::sync_with_stdio(false);
  int t, n, m, k;
  cin >> t;
  while(t--) {
    cin >> n >> m;
    k = min(n, m);
    for(int i = 0; i < n; ++i) {
      cin >> s[i];
    }
    for(int i = 1; i <= k; ++i) {
      cin >> cw[i];
    }
    for(int i = 1; i <= k; ++i) {
      cin >> cb[i];
    }
    long long ans = 0;
    vector<pair<pair<int,int>, int>> white, black;
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < m; ++j) {
        int L = min(n - i, m - j);
        for(int l = 1; l <= L; ++l) {
          bool type[3] = {0, 0, 0}; // white, black, question
          for(int x = i; x < i + l; ++x) {
            for(int y = j; y < j + l; ++y) {
              if (s[x][y] == '?') {
                type[2] = 1;
              }
              else {
                type[s[x][y] - '0'] = 1;
              }
            }
          }
          if (type[0] && type[1]) {
            continue;
          }
          if (type[2]) {
            if (type[0]) {
              ans += cw[l];
              white.push_back({{i, j}, l});
            }
            else if (type[1]) {
              ans += cb[l];
              black.push_back({{i, j}, l});
            }
            else {
              ans += cw[l] + cb[l];
              white.push_back({{i, j}, l});
              black.push_back({{i, j}, l});
            }
          }
          else {
            if (type[0]) {
              ans += cw[l];
            }
            else {
              ans += cb[l];
            }
          }
        }
      }
    }
    int nodes = white.size() + black.size() + n * m + 2;
    int source = nodes - 1, sink = nodes;
    Dinic dnc(nodes, source, sink);
    for(int i = 0; i < white.size(); ++i) {
      int ID = i + 1;
      dnc.add_edge(source, ID, cw[white[i].sec]);
      for(int x = white[i].fi.fi; x < white[i].fi.fi + white[i].sec; ++x) {
        for(int y = white[i].fi.sec; y < white[i].fi.sec + white[i].sec; ++y) {
          if (s[x][y] == '?') {
            dnc.add_edge(ID, white.size() + x * m + y + 1, INF);
          }
        }
      }
    }
    for(int i = 0; i < black.size(); ++i) {
      int ID = white.size() + n * m + i + 1;
      dnc.add_edge(ID, sink, cb[black[i].sec]);
      for(int x = black[i].fi.fi; x < black[i].fi.fi + black[i].sec; ++x) {
        for(int y = black[i].fi.sec; y < black[i].fi.sec + black[i].sec; ++y) {
          if (s[x][y] == '?') {
            dnc.add_edge(white.size() + x * m + y + 1, ID, INF);
          }
        }
      }
    }
    ans -= dnc.max_flow();
    cout << ans << "\n";

    // Print one possible solution.
    dnc.build_min_cut();
    for(int i = 0; i < white.size(); ++i) {
      int ID = i + 1;
      if (dnc.edge_in_min_cut(sink, ID)) {
        continue;
      }
      for(int x = white[i].fi.fi; x < white[i].fi.fi + white[i].sec; ++x) {
        for(int y = white[i].fi.sec; y < white[i].fi.sec + white[i].sec; ++y) {
          s[x][y] = '0';
        }
      }
    }
    for(int i = 0; i < black.size(); ++i) {
      int ID = white.size() + n * m + i + 1;
      if (dnc.edge_in_min_cut(ID, sink)) {
        continue;
      }
      for(int x = black[i].fi.fi; x < black[i].fi.fi + black[i].sec; ++x) {
        for(int y = black[i].fi.sec; y < black[i].fi.sec + black[i].sec; ++y) {
          s[x][y] = '1';
        }
      }
    }
    for(int i = 0; i < n; ++i) {
      cerr << s[i] << "\n";
    }

    // Verify solution.
    long long cost = 0;
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < m; ++j) {
        int L = min(n - i, m - j);
        for(int l = 1; l <= L; ++l) {
          bool uniform = true;
          for(int x = i; x < i + l; ++x) {
            for(int y = j; y < j + l; ++y) {
              if (s[x][y] != s[i][j]) {
                uniform = false;
              }
            }
          }
          if (uniform) {
            if (s[i][j] == '0') {
              cost += cw[l];
            }
            else {
              cost += cb[l];
            }
          }
        }
      }
    }
    assert(ans == cost);
  }
  return 0;
}