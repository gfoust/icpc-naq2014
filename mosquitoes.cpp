#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::tuple;
using std::sqrt;

struct Point {
  double x, y;
};

array<Point, 32> points;
array<array<Point, 32>, 32> distances;
int numPoints;
double d;
double r;

tuple<Point, Point> centers(Point p1, Point p2) {
  double xa = (p2.x - p1.x) / 2;
  double ya = (p2.y - p1.y) / 2;
  Point p0 = { p1.x + xa, p1.y + ya };
  double a = sqrt(xa * xa + ya * ya);
  double b = sqrt(r * r - a * a);

  double m = b / a;
  Point p3 = { p0.x + m * ya, p0.y - m * xa };
  Point p4 = { p0.x - m * ya, p0.y + m * xa };

  return { p3, p4 };
}

double distance(Point a, Point b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

void assertDistance(Point p, Point q) {
  double dst = distance(p, q);
  if (std::abs(dst - r) > 0.000001) {
    std::cerr << "ERROR\n";
  }
}

int numPointsWithin(Point center) {
  int count = 0;
  for (int i = 0; i < numPoints; ++i) {
    double dst = distance(points[i], center);
    //std::cerr << dst << endl;
    if (dst - r <= 0) {
      ++count;
    }
  }
  //std::cerr << "----\n";
  return count;
}

int maxNumPointsWithin() {
  int best = 1;
  for (int i = 0; i < numPoints; ++i) {
    for (int j = i + 1; j < numPoints; ++j) {
      if (distance(points[i], points[j]) <= 2*r) {
        auto [p, q] = centers(points[i], points[j]);
        //assertDistance(points[i], p);
        //assertDistance(points[i], q);
        //assertDistance(points[j], p);
        //assertDistance(points[j], q);

        best = std::max(best, numPointsWithin(p));
        best = std::max(best, numPointsWithin(q));
      }
    }
  }
  return best;
}

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> numPoints >> d;
    r = d / 2;
    for (int j = 0; j < numPoints; ++j) {
      cin >> points[j].x >> points[j].y;
    }
    cout << maxNumPointsWithin() << endl;
  }
}
