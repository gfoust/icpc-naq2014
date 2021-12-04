#include <cmath>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <queue>
using namespace std;

//================================================
struct Point {
  double x, y;
};

bool operator <(Point p, Point q) {
  return p.x < q.x || p.x == q.x && p.y < q.y;
}

bool operator ==(Point p, Point q) {
  return p.x == q.x && p.y == q.y;
}

bool operator !=(Point p, Point q) {
  return p.x != q.x || p.y != q.y;
}

istream& operator >>(istream& in, Point& p) {
  return in >> p.x >> p.y;
}

ostream& operator <<(ostream& out, Point& p) {
  return out << '(' << p.x << ", " << p.y << ')';
}

//================================================
struct Vector {
  double x, y;
};

Vector scaleTo(Vector v, double d) {
  double length = sqrt(v.x * v.x + v.y * v.y);
  return { v.x / length * d, v.y / length * d };
}

Vector operator -(Point p, Point q) {
  return { p.x - q.x, p.y - q.y };
}

Point operator +(Point p, Vector v) {
  return { p.x + v.x, p.y + v.y };
}


//================================================
struct Node {
  Point p;
  double t;
};

bool operator <(const Node& a, const Node& b) {
  return a.t > b.t;
}


//================================================
Point start;
Point goal;
vector<Point> cannons;
priority_queue<Node> nodes;
map<Point, double> shortest;

double distance(Point p, Point q) {
  double dx = p.x - q.x;
  double dy = p.y - q.y;
  return sqrt(dx * dx + dy * dy);
}

void add(Point p, double t) {
  auto [itr, inserted] = shortest.insert({ p, t });
  if (inserted) {
    nodes.push({ p, t });
    cerr << "Adding " << p << " @ " << t << endl;
  }
  else if (t < itr->second) {
    itr->second = t;
    nodes.push({ p, t });
    cerr << "Adding " << p << " @ " << t << endl;
  }
}

double runTo(Point from, Point to) {
  return distance(from, to) / 5.0;
}

double shootTo(Point cannon, Point to) {
  Point land = cannon + scaleTo((to - cannon), 50);
  return 2.0 + runTo(land, to);
}

double go() {
  for (auto& c : cannons) {
    add(c, runTo(start, c));
  }
  add(goal, runTo(start, goal));

  while (!nodes.empty()) {
    Node next = nodes.top();
    nodes.pop();
    if (next.p == goal) {
      return next.t;
    }
    if (next.t != shortest[next.p]) continue;

    for (auto& c : cannons) {
      if (next.p != c) {
        add(c, next.t + shootTo(next.p, c));
      }
    }
    add(goal, next.t + shootTo(next.p, goal));
  }
  return -1;
}

int main() {
  cin >> start;
  cin >> goal;
  int numCannons;
  cin >> numCannons;
  cannons.resize(numCannons);
  for (auto& c : cannons) {
    cin >> c;
  }
  cout << fixed << setprecision(6);
  cout << go() << endl;
}