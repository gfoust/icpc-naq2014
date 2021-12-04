#include <iostream>
#include <cmath>
using namespace std;

struct Point {
  double x, y;
};

struct Vector {
  double x, y;
};

Point operator +(Point p, Vector v) {
  return { p.x + v.x, p.y + v.y };
}

Vector operator *(Vector v, double s) {
  return { v.x * s, v.y * s };
}

double dot(Vector v, Vector w) {
  return v.x * w.x + v.y * w.y;
}

double length(Vector v) {
  return sqrt(dot(v, v));
}

Vector scaleTo(Vector v, double d) {
  double l = length(v);
  return { v.x / l * d, v.y / l * d };
}

double atZero(Point p, Vector v) {
  return p.x + v.x * (-p.y / v.y);
}

double dogSpeed;
double bikeSpeed;
double D;
double T;

void go() {
  Point dog = { D, -5.5 };
  dog.x -= T * bikeSpeed;
  Vector slope = { -bikeSpeed, dogSpeed };
  Point dogFast = dog + scaleTo({ slope.y, -slope.x }, 0.5);
  Point dogSlow = dog + scaleTo({ -slope.y, slope.x }, 0.5);

  double fast = atZero(dogFast, slope);
  double slow = atZero(dogSlow, slope);
 
  if (slow > 0) {
    cout << "Max beats the first bicycle\n";
  }
  else if (fast < -38) {
    cout << "Max crosses safely after bicycle 10\n";
  }
  else {
    int fastInt = (int)(fast - 1e-9) / -2;
    int slowInt = (int)(slow - 1e-9) / -2;
    if (fastInt == slowInt && fastInt % 2 == 1) {
      cout << "Max crosses safely after bicycle " << fastInt / 2 + 1 << endl;
    }
    else if (fastInt < 0) {
      cout << "Collision with bicycle 1" << endl;
    }
    else {
      cout << "Collision with bicycle " << fastInt / 2 + 1 + fastInt % 2 << endl;
    }
  }
}

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> dogSpeed >> bikeSpeed >> D >> T;
    go();
  }
}