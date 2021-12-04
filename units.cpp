#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <cstdint>

using namespace std;

struct Conversion {
  string a;
  uint64_t qty;
  string b;
};

int gcf(int a, int b) {
  if (a % b == 0) {
    return b;
  }
  else {
    return (b, a % b);
  }
}

int lcm(int a, int b) {
  return a / gcf(a, b) * b;
}

bool solve() {
  uint64_t n;
  cin >> n;
  if (n == 0) return false;

  vector<string> units(n);
  for (auto& u : units) {
    cin >> u;
  }

  vector<Conversion> conv(n - 1);
  for (auto& c : conv) {
    char eq;
    cin >> c.a >> eq >> c.qty >> c.b;
  }

  map<string, uint64_t> scale;
  scale[conv.back().a] = 1;
  scale[conv.back().b] = conv.back().qty;
  conv.pop_back();
  while (!conv.empty()) {
    vector<Conversion> nconv;
    for (auto const& c : conv) {
      if (scale[c.a] != 0) {
        scale[c.b] = c.qty * scale[c.a];
      }
      else {
        int s = scale[c.b];
        if (s != 0) {
          int x = lcm(c.qty, s);
          if (x != s) {
            for (auto& p : scale) {
              p.second *= x / s;
            }
          }
          scale[c.a] = scale[c.b] / c.qty;
        }
        else {
          nconv.push_back(c);
        }
      }
    }
    swap(conv, nconv);
  }

  sort(units.begin(), units.end(),
    [&](string const& a, string const& b) {
      return scale[a] < scale[b];
    }
  );

  bool first = true;
  for (auto& u : units) {
    if (first) first = false;
    else cout << " = ";
    cout << scale[u] << u;
  }
  cout << endl;
  return true;

}

int main() {
  while (solve());
}