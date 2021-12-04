#include <iostream>
#include <bitset>
#include <map>
#include <queue>

using Grid = short int;

void dump(Grid grid) {
  std::cerr << std::endl;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      std::cerr << ((grid & 1 << r * 3 + c) ? '*' : '.');
    }
    std::cerr << std::endl;
  }
}


void dump(Grid a, Grid b) {
  std::cerr << std::endl;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      std::cerr << ((a & 1 << r * 3 + c) ? '*' : '.');
    }
    std::cerr << "  ==>  ";
    for (int c = 0; c < 3; ++c) {
      std::cerr << ((b & 1 << r * 3 + c) ? '*' : '.');
    }
    std::cerr << std::endl;
  }
}


int idx(int row, int col) {
  if (row < 0 || row > 2 || col < 0 || col > 2) return -1;
  return row * 3 + col;
}

Grid click(Grid grid, int i) {
  int row = i / 3;
  int col = i % 3;
  for (int i : { idx(row - 1, col), idx(row, col - 1), idx(row, col), idx(row, col + 1), idx(row + 1, col) }) {
    if (i >= 0 && i < 9) {
      grid = grid ^ (1 << i);
    }
  }
  return grid;
}

struct Search {

  std::map<Grid, Grid> parent;

  bool go(Grid start) {
    std::queue<Grid> waiting;
    bool looking = true;
    waiting.push(start);

    while (!waiting.empty()) {
      Grid next = waiting.front();
      waiting.pop();

      for (int i = 0; i < 9; ++i) {
        Grid g = click(next, i);
        if (parent.count(g) == 0) {
          parent[g] = next;
          waiting.push(g);
          // dump(next, g);
        }
        if (g == 0) {
          return true;
        }
      }

    }
    return false;
  }

  int count(Grid begin, Grid end) {
    int n = 0;
    Grid cur = begin;
    while (cur != end) {
      ++n;
      cur = parent[cur];
    }
    return n;
  }
};

int main() {
  int N;
  std::cin >> N;
  for (int prob = 0; prob < N; ++prob) {
    Grid grid = 0;
    for (int i = 0; i < 9; ++i) {
      char c;
      std::cin >> c;
      if (c == '*') {
        grid = grid | 1 << i;
      }
    }
    Search search;
    if (search.go(grid)) {
      std::cout << search.count(0, grid) << std::endl;;
    }
    else {
      std::cout << 0 << std::endl;
    }
  }
}