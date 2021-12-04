#include <iostream>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

int width;
int num_partitions;
vector<int> partitions;
set<int> sizes;

int main() {
  cin >> width >> num_partitions;
  int a = 0, b;
  for (int i = 0; i < num_partitions; ++i) {
    cin >> b;
    partitions.push_back(b - a);
    a = b;
  }
  partitions.push_back(width - a);
  for (int i = 0; i < partitions.size(); ++i) {
    for (int j = i + 1; j <= partitions.size(); ++j) {
      int size = accumulate(partitions.begin() + i, partitions.begin() + j, 0);
      sizes.insert(size);
    }
  }
  bool first = true;
  for (auto i : sizes) {
    if (first) first = false;
    else cout << ' ';
    cout << i;
  }
  cout << endl;
}