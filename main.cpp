#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(746851515);
const double mult = 100;

struct result {
  int cnt_gen;
  double ans;
};

struct Point {
  double x, y;
};

double dist(Point a, Point b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct Circle {
  Point o;
  double r;

  bool in_circle(Point a) { return dist(a, o) <= r * r; }
};

double rnd_01() { return (rnd() / (double)rnd.max()); }

Point gen_rnd_point(int a, int b, int c, int d) {
  Point ans = {a + (double)(rnd() % (b - a)) + rnd_01(),
               c + (double)(rnd() % (d - c)) + rnd_01()};
  return ans;
}

result solve_small(int gen_cnt, vector<Circle> &v) {
  int left = (v[0].o.x - v[0].r), right = (v[0].o.x + v[0].r), up = (v[0].o.y + v[0].r), down = (v[0].o.y - v[0].r);
  for (int i = 1; i < 3; ++i) {
    left = max(left, (int)(v[i].o.x - v[i].r));
    right = min(right, (int)(v[i].o.x + v[i].r));
    up = min(up, (int)(v[i].o.y + v[i].r));
    down = max(down, (int)(v[i].o.y - v[i].r));
  }
  if(left >= right) {
    cout << 0;
    return {gen_cnt, 0};
  }
  double cnt = 0;
  for (int i = 0; i < gen_cnt; ++i) {
    Point z = gen_rnd_point(left, right, down, up);
    bool flag = true;
    for (int i = 0; i < 3; ++i) {
      if (!v[i].in_circle(z)) {
        flag = false;
        break;
      }
    }
    if (flag) {
      cnt++;
    }
  }
  return {gen_cnt, (cnt / gen_cnt) * (double)(right - left) *
              (double)(up - down) / (mult * mult)};
}

result solve_big(int gen_cnt, vector<Circle> &v) {
  int left = (v[0].o.x - v[0].r), right = (v[0].o.x + v[0].r), up = (v[0].o.y + v[0].r), down = (v[0].o.y - v[0].r);
  for (int i = 1; i < 3; ++i) {
    left = min(left, (int)(v[i].o.x - v[i].r));
    right = max(right, (int)(v[i].o.x + v[i].r));
    up = max(up, (int)(v[i].o.y + v[i].r));
    down = min(down, (int)(v[i].o.y - v[i].r));
  }
  double cnt = 0;
  for (int i = 0; i < gen_cnt; ++i) {
    Point z = gen_rnd_point(left, right, down, up);
    bool flag = true;
    for (int i = 0; i < 3; ++i) {
      if (!v[i].in_circle(z)) {
        flag = false;
        break;
      }
    }
    if (flag) {
      cnt++;
    }
  }
  return {gen_cnt, (cnt / gen_cnt) * (double)(right - left) *
              (double)(up - down) / (mult * mult)};
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);
  cin.tie(0);
  cout << fixed << setprecision(5);
  vector<Circle> v(3);
  for (int i = 0; i < 3; ++i) {
    cin >> v[i].o.x >> v[i].o.y >> v[i].r;
    v[i].o.x *= mult;
    v[i].o.y *= mult;
    v[i].r *= mult;
  }
  vector<result> stat_small;
  vector<result> stat_big;
  for(int i = 100; i < 100000; i += 500) {
    stat_small.push_back(solve_small(i, v));
    stat_big.push_back(solve_big(i, v));
  }
  int m = stat_small.size();
  ofstream out;
  out.open("stat_big.txt");
  for(int i = 0; i < m; ++i) {
    out <<'{' << stat_big[i].cnt_gen << ", " << stat_big[i].ans << "}\n";
  }
  ofstream out2;
  out2.open("stat_small.txt");
  for(int i = 0; i < m; ++i) {
    out2 <<'{' << stat_small[i].cnt_gen << ", " << stat_small[i].ans << "}\n";
  }
}
