#include "data_operations.hpp"

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

// namespace data_ops
namespace data_ops {

bool checkCycle(int node, std::vector<std::set<int>> &edges,
                std::vector<int> &vis, std::vector<int> &dfsvis) {
  vis[node] = 1;
  dfsvis[node] = 1;
  for (auto i : edges[node]) {
    if (!vis[i]) {
      if (data_ops::checkCycle(i, edges, vis, dfsvis)) {
        return true;
      }
    } else if (dfsvis[i]) {
      std::cout << "\nCycle is present between node " << i << " & " << node
                << "\n";
      return true;
    }
  }
  dfsvis[node] = 0;
  return false;
}

bool isCycle(int n, std::vector<std::set<int>> &edges) {
  std::vector<int> vis(n + 1, 0);
  std::vector<int> dfsvis(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      if (data_ops::checkCycle(i, edges, vis, dfsvis)) return true;
    }
  }
  return false;
}

void topologicalSort(std::vector<int> &indeg, std::vector<std::set<int>> &edges,
                     int n) {
  std::queue<int> pq;
  for (int i = 1; i <= n; i++) {
    if (indeg[i] == 0) {
      pq.push(i);
    }
  }

  std::cout << "\nSerializability Order: ";
  while (!pq.empty()) {
    int x = pq.front();
    pq.pop();
    std::cout << "T" << x << " ";
    for (auto i : edges[x]) {
      indeg[i]--;
      if (indeg[i] == 0) pq.push(i);
    }
  }
}
void removeSpace(std::string &str) {
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  // str.erase(std::remove(str.begin(), str.end(), ::isspace), str.end());
}

}  // namespace data_ops
