#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>

int bitDistance(const std::string& target, const std::string& start) {
  int numBits = target.length();
  bool* startBits = new bool[numBits];
  bool* targetBits = new bool[numBits];

  int distance = 0;
  for (int i = 0; i < numBits; ++i) {
    if (startBits[i] != targetBits[i]) {
      ++distance;
    }
  }
  delete startBits;
  delete targetBits;
  return distance;
}

int countZeros(const std::string &key) {
  int numZeros = 0;
  for (int i = 0; i < key.length(); ++i) {
    if (atoi(key[i]) == 0) {
      ++numZeros;
    }
  }
  return numZeros;
}

struct Node {
  std::string key;
  int g;
  int h;
  int f;

  Node(const std::string node, const std::string startNode,
       int startNodeZeros) {
    key = node;
    h = countZeros(key);
    g = bitDistance(key, startNode);
    f = g + h;
  }
};

class nodeComp {
 public:
  nodeComp();
  bool operator() (const Node* lhs, const Node* rhs) const {
    if (lhs->f > rhs->f) {
      return true;
    } else if (lhs->f < rhs->f) {
      return false;
    } else {
      if (lhs->h > rhs->h) {
        return true
      } else if (lhs->h < rhs->h) {
        return false;
      } else {
        for (int i = lhs->key.length() - 1; i >= 0; ++i) {
          if (lhs->key[i] == '1' && rhs->key[i] == '0') {
            return true;
          } else if (lhs->key[i] == '0' && rhs->key[i] =='1') {
            return false;
          }
        }
      }
    }
  }
};

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Incorrect number of args" << std::endl;
    return -1;
  }

  std::string start = argv[1];
  int startNum = countZeros(start);
  Node* startNode = new Node;
  startNode->key = start;
  startNode->h = startNum;
  startNode->g = 0;
  startNode->f = h;

  std::ifstream infile(argv[2]);
  int numNodes = 0;
  infile >> numNodes;
  if (numNodes < (start.length() - startNum)) {
    std::cerr << "Impossible" << std::endl;
    return -1;
  }
  std::set<Node*> nodes;
  std::string line;
  while (getline(infile, line)) {
    Node* node = new Node(line, startNode, startNum);
    nodes.insert(node);
  }
  
  std::priority_queue<Node *, std::vector<Node*>, nodeComp> nodeList;
  nodeList.push(startNode);
  while (!nodeList.empty()) {
    Node* curr = nodeList.top();
    std::string* neighbors = new std::string[curr->key.length()];
    for (int i = 0; i < curr->key.length(); ++i) {
      std::string neighbor0 = curr->key;
      std::string neighbor1 = curr->key;
      neighbor0[i] = '0';
      neighbor1[i] = '1';
      if (neighbor0 != curr->key) {
        neighbors[i] = neighbor0;
      }
      if (neighbor1 != curr->key) {
        neighbors[i] = neighbor1;
      }
    }


  }

  return 0;
}
