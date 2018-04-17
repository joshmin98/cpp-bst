#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>

int numOnes(const std::string &key) {
  int nodeNum = atoi(key.c_str());
  int startNum = 0;
  while (nodeNum != 0) {
    startNum += nodeNum % 10;
    nodeNum /= 10;
  }
  return startNum;
}

struct Node {
  std::string key;
  int weight;
  int distance;
  int numOnes;
  std::set<Node *> adjacent;

  Node(const std::string &readKey) { key = readKey; }
};

int main(int argc, char *argv[]) {
  if (argc < 3) {
    return -1;
  }

  std::string startKey = argv[1];
  int startNum = numOnes(startKey);

  int lowerBound = startNode.length() - startNum;

  std::ifstream infile(argv[2]);
  std::string line = "";
  infile >> line;
  int maxNumNodes = atoi(line.c_str());
  if (maxNumNodes < lowerBound) {
    return -1;
  }

  return 0;
}
