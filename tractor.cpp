#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int width, height;

int go() {
  int distance = 1;
  int count = 0;
  int n = 1;
  while (n > 0) {
    count += n;
    distance <<= 1;
    n = distance;
    int x = distance - 1;
    if (width < x) {
      n -= x - width;
    }
    if (height < x) {
      n -= x - height;
    }
  }
  return count;
}

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> width >> height;
    cout << go() << endl;
  }
}