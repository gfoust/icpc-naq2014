#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

int numNodes;
array<array<bool, 12>, 12> redEdges;
array<array<bool, 12>, 12> blackEdges;
array<array<bool, 1 << 12>, 12> safeStates;

bool isFrontRed(int queue) {
  return queue & 1;
}

int shift(int queue, int queueSize, bool red) {
  int next = queue >> 1;
  if (red) {
    next |= 1 << (queueSize - 1);
  }
  return next;
}

bool findMoreFailStates(const int queueSize) {
  bool found = false;
  for (int n = 0; n < numNodes; ++n) {
    for (int q = 0; q < 1 << queueSize; ++q) {
      if (!safeStates[n][q]) continue;
      auto& edges = isFrontRed(q) ? redEdges : blackEdges;
      auto safe = false;
      for (int edge = 0; edge < numNodes; ++edge) {
        if (
          edges[n][edge] &&
          safeStates[edge][shift(q, queueSize, true)] &&
          safeStates[edge][shift(q, queueSize, false)]
        ) {
          safe = true;
        }
      }
      if (!safe) {
        safeStates[n][q] = false;
        found = true;
      }
    }
  }
  return found;
}

bool isTrue(bool b) { return b; }

bool cannotLose(const int queueSize) {
  for (auto& row : safeStates) row.fill(true);
  while (findMoreFailStates(queueSize));
  return all_of(&safeStates[0][0], &safeStates[0][1 << queueSize], isTrue);
}

int firstSafeSize() {
  for (int i = 1; i <= numNodes; ++i) {
    if (cannotLose(i)) {
      return i;
    }
  }
  return 0;
}

int main() {
  int numTestCases;
  cin >> numTestCases;
  for (int i = 0; i < numTestCases; ++i) {
    cin >> numNodes;
    for (int src = 0; src < numNodes; ++src) {
      for (int dst = 0; dst < numNodes; ++dst) {
        cin >> redEdges[src][dst];
      }
    }
    for (int src = 0; src < numNodes; ++src) {
      for (int dst = 0; dst < numNodes; ++dst) {
        cin >> blackEdges[src][dst];
      }
    }
    cout << firstSafeSize() << endl;
  }
}