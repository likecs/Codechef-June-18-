#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct point {
  double x, y, z;
  point() {}
  point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  friend istream &operator >> (istream &input, point &a) {
    input >> a.x >> a.y >> a.z;
    return input;
  }
  point operator + (const point &other) const {
    return point(this->x + other.x, this->y + other.y, this->z + other.z);
  }
  point operator - (const point &other) const {
    return point(this->x - other.x, this->y - other.y, this->z - other.z);
  }
  double abs() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
  }
  double dist(point &other) {
    point temp = (*this) - other;
    return temp.abs();
  }
  point cross(point &other) {
    return point(
        this->y * other.z - this->z * other.y,
        this->z * other.x - this->x * other.z,
        this->x * other.y - this->y * other.x);
  }
};

double distance_point_to_line(point &a, point &b, point &c) {
  point ca = c - a, cb = c - b;
  point area = ca.cross(cb);
  double distance = area.abs() / a.dist(b);
  return distance;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--) {
    point p, q, d, c;
    long long r;
    cin >> p >> q >> d >> c >> r;
    double l = 0, h = 1e18;
    for(int iter = 0; iter < 100; ++iter) {
      long double m = (l + h) / 2;
      point qt(q.x + m * d.x, q.y + m * d.y, q.z + m * d.z);
      if (distance_point_to_line(p, qt, c) < r) {
        l = m;
      }
      else {
        h = m;
      }
    }
    double ans = (l + h) / 2;
    cout << fixed << setprecision(10) << ans << "\n";
  }
  return 0;
}