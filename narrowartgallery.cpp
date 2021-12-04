#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

struct Score {
  int neitherClosed = 0;
  int firstClosed = 0;
  int secondClosed = 0;
};

pair<int, int> gallery[201];
Score scores[201][201];
int numRows, numToClose;

int go() {
  scores[0][0] = { 0, -1, -1 };
  for (int r = 1; r <= numRows; ++r) {
    scores[0][r] = { scores[0][r - 1].neitherClosed + gallery[r].first + gallery[r].second, -1, -1 };
  }

  for (int k = 1; k <= numToClose; ++k) {
    scores[k][0] = { -1, -1, -1 };
    for (int r = 1; r <= numRows; ++r) {
      int best = max({
        scores[k][r - 1].firstClosed,
        scores[k][r - 1].secondClosed,
        scores[k][r - 1].neitherClosed
        });
      scores[k][r].neitherClosed = best > -1 ? best + gallery[r].first + gallery[r].second : -1;

      best = max(
        scores[k - 1][r - 1].firstClosed,
        scores[k - 1][r - 1].neitherClosed
      );
      scores[k][r].firstClosed = best > -1 ? best + gallery[r].second : -1;

      best = max(
        scores[k - 1][r - 1].secondClosed,
        scores[k - 1][r - 1].neitherClosed
      );
      scores[k][r].secondClosed = best > -1 ? best + gallery[r].first : -1;
    }
  }

  return max({
    scores[numToClose][numRows].neitherClosed,
    scores[numToClose][numRows].firstClosed,
    scores[numToClose][numRows].secondClosed
    });
}

bool readInput() {
  cin >> numRows >> numToClose;
  if (numRows == 0) return false;
  gallery[0] = { 0, 0 };
  for (int r = 1; r <= numRows; ++r) {
    cin >> gallery[r].first >> gallery[r].second;
  }
  return true;
}

int main() {
  while (readInput()) {
    cout << go() << endl;
  }
}
