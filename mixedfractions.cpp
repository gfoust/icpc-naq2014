#include <iostream>
using namespace std;

int main() {
  int num, den;
  while (cin >> num >> den && num > 0 && den > 0) {
    cout << num / den << ' ' << num % den << " / " << den << endl;
  }
}