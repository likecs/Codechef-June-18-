#include <bits/stdc++.h>
using namespace std;

const int LIM = 26;

struct node {
  vector<int> ids;
  node *child[LIM];
  int leaf_id;
  bool is_leaf;
};

char s[20];
node *trie;

node *get_node() {
  node *temp = new node;
  temp->ids.clear();
  temp->leaf_id = 1000000;
  temp->is_leaf = false;
  for(int i = 0; i < LIM; ++i) {
    temp->child[i] = NULL;
  }
  return temp;
}

void insert(node *root, int &id) {
  int L = strlen(s);
  for(int i = 0; i < L; ++i) {
    if (root->child[s[i] - 'a'] == NULL) {
      root->child[s[i] - 'a'] = get_node();
    }
    root = root->child[s[i] - 'a'];
    root->ids.push_back(id);
  }
  root->leaf_id = min(root->leaf_id, id);
  root->is_leaf = true;
}

void traverse_down(node *root, int r) {
  while(root != NULL && (root->is_leaf == false ||
        (root->is_leaf == true && root->leaf_id > r))) {
    // bool done = false;
    for(int i = 0; i < LIM; ++i) {
      if (root->child[i] != NULL && root->child[i]->ids[0] <= r) {
        // lowest character in range found.
        root = root->child[i];
        putchar(char(i + 'a'));
        // done = true;
        break;
      }
      // retry again till a complete word is found.
    }
    // assert(done);
  }
}

void query(node *root, int r) {
  int L = strlen(s);
  for(int i = 0; i < L; ++i) {
    if (root->child[s[i] - 'a'] != NULL) {
      if (root->child[s[i] - 'a']->ids[0] <= r) {
        // match found.
        root = root->child[s[i] - 'a'];
        putchar(s[i]);
        continue;
      }
    }
    // match not found.
    break;
  }
  // either match is not found or complete word is still not printed.
  traverse_down(root, r);
  putchar('\n');
}

int main() {
  int n, q, r;
  scanf("%d", &n);
  trie = get_node();
  for(int i = 1; i <= n; ++i) {
    scanf("%s", s);
    insert(trie, i);
  }
  scanf("%d", &q);
  for(int i = 1; i <= q; ++i) {
    scanf("%d %s", &r, s);
    query(trie, r);
  }
  return 0;
}