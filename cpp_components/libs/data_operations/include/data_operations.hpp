#ifndef DATA_OPERATIONS_HPP_
#define DATA_OPERATIONS_HPP_

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <string>

namespace data_ops {

bool checkCycle(int node, std::vector<std::set<int>> &, std::vector<int> &, std::vector<int> &);

bool isCycle(int n, std::vector<std::set<int>> &);

void topologicalSort(std::vector<int> &, std::vector<std::set<int>> &, int);

void removeSpace(std::string &);

}  // namespace data_ops

#endif  // DATA_OPERATIONS_HPP_
