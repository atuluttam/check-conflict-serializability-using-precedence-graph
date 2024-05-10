#include "interface.hpp"

#include <iostream>
#include <cstring>
#include <ios>
#include <set>
#include <utility>
#include <vector>
#include <fstream>

#include "/home/atuluttam/work/git-remake/code-dump-cmake-code/common_expt/check-conflict-serializability-using-precedence-graph/cpp_components/libs/data_operations/include/data_operations.hpp"

int main() {
  std::ifstream file("../input/inputfile.txt");
  std::string mystring;
  int count = 0;
  int num_trans = 0;
  if (file.is_open()) {
    while (file.good() && count < 3) {
      std::getline(file, mystring);
      data_ops::removeSpace(mystring);
      if (!count) {
        num_trans = (mystring.length() + 1 - 6) / 3;
      }

      count++;
    }

    std::vector<std::pair<int, std::string>> trans;

    while (file) {
      std::getline(file, mystring);

      data_ops::removeSpace(mystring);
      trans.push_back(std::make_pair((mystring[1] - 48),
                                     mystring.std::string::substr(3, 5)));
    }
    trans.resize(trans.size() - 1);
    std::cout << "-----------------Schedule-------------------\n";
    for (auto i : trans) {
      std::cout << "T" << i.first << " " << i.second << "\n";
    }
    if (num_trans == 1) {
      std::cout << "This is Conflict Serializable Schedule\n";
      std::cout << "Its Equivalent Serial Schedule :" << "\n";
      return 0;
    }

    std::vector<std::set<int>> edges(num_trans + 1);
    std::pair<int, int> x;
    for (int i = 0; i < (int)trans.size(); i++) {
      for (int j = i + 1; j < (int)trans.size(); j++) {
        if (trans[i].second[0] == 'R') {
          if (trans[i].first != trans[j].first && trans[j].second[0] == 'W' &&
              trans[i].second[2] == trans[j].second[2])
            edges[trans[i].first].insert(trans[j].first);
        }
        if (trans[i].second[0] == 'W') {
          if (trans[i].first != trans[j].first &&
              trans[j].second[2] == trans[i].second[2])
            edges[trans[i].first].insert(trans[j].first);
        }
      }
    }
    std::vector<int> indeg(num_trans + 1, 0);
    indeg[0] = -1;
    std::cout << "\n-------------Conflicting Operations--------------\n";
    std::cout << "From -->  To\n";
    for (int i = 1; i <= num_trans; i++) {
      std::cout << "  " << i << "  -->  ";
      for (auto it : edges[i]) {
        indeg[it]++;
        std::cout << it << " ";
      }
      std::cout << "\n";
    }

    bool flag = data_ops::isCycle(num_trans, edges);
    flag ? std::cout << "\n This isn't a Conflict Serializable Schedule\n"
         : std::cout << "\nThis is Conflict Serilizable Schedule\n";

    if (flag == 1) {
      std::cout << "\n\n\n\n";
      return 0;
    }
    data_ops::topologicalSort(indeg, edges, num_trans);
    // data_ops::topologicalSort(indeg, edges, num_trans);
    std::cout << "\n\n\n\n";
  } else {
    std::cout << "Can't open file!!";
  }

  return 0;
}
