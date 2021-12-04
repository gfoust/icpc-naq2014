#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

bool eq1(int i) {
  return i == 1;
}

bool le1(int i) {
  return i <= 1;
}

int main() {
  vector<int> rows(8);
  vector<int> cols(8);
  vector<int> forward(15);
  vector<int> backward(15);

  for (int r = 0; r < 8; ++r) {
    for (int c = 0; c < 8; ++c) {
      char x;
      cin >> x;
      if (x == '*') {
        rows[r]++;
        cols[c]++;
        forward[r + c]++;
        backward[7 + r - c]++;
      }
    }
  }

  bool valid =
    std::all_of(rows.begin(), rows.end(), eq1) &&
    std::all_of(cols.begin(), cols.end(), eq1) &&
    std::all_of(forward.begin(), forward.end(), le1) &&
    std::all_of(backward.begin(), backward.end(), le1);

  if (!valid) {
    cout << "in";
  }
  cout << "valid" << endl;
}