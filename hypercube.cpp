#include <queue>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

// START HELP FCNS
int bitDistance(const std::string &target, const std::string &start) {
  int numBits = target.length();
  bool *startBits = new bool[numBits];
  bool *targetBits = new bool[numBits];

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

bool isAdjacent(const std::string &node1, const std::string &node2) {
  int distance = bitDistance(node1, node2);
  return (distance == 1);
}

int countZeros(const std::string &key) {
  int numZeros = 0;
  for (int i = 0; i < key.length(); ++i) {
    char c = key[i];
    if (atoi(&c) == 0) {
      ++numZeros;
    }
  }
  return numZeros;
}
// END HELP FCNS

struct Node {
  int f, g, h;
  std::string key;
  Node* parent;

  Node(const std::string &binString) {
    key = binString;
    std::string target = "";
    for (int i = 0; i < binString.length(); ++i) {
      target += "1";
    }
    h = bitDistance(key, target);
    g = 0;
    parent = NULL;
  }
};

class nodeComp {
public:
  bool operator()(const Node *lhs, const Node *rhs) const {
    if (lhs->f > rhs->f) {
      return true;
    } else if (lhs->f < rhs->f) {
      return false;
    } else {
      if (lhs->h > rhs->h) {
        return true;
      } else if (lhs->h < rhs->h) {
        return false;
      } else {
        for (int i = lhs->key.length() - 1; i >= 0; ++i) {
          if (lhs->key[i] == '1' && rhs->key[i] == '0') {
            return true;
          } else if (lhs->key[i] == '0' && rhs->key[i] == '1') {
            return false;
          }
        }
      }
    }
  }
};


int main(int argc, char *argv[]) {
  if (argc < 3) {
    return -1;
  }

  std::string startNodeKey = argv[1];
  std::string endNodeKey = "";
  for (unsigned int i = 0; i < startNodeKey.length(); ++i) {
    endNodeKey += "1";
  }

  Node *start = new Node(startNodeKey);
  start->g = 0;
  start->f = start->g + start->h;

  std::ifstream infile(argv[2]);
  int numNodes;
  infile >> numNodes;
  if (numNodes < start->h) {
    return -1;
  }

  std::map<std::string, Node *> allNodes;
  std::string currKey;
  while (getline(infile, currKey)) {
    Node *currNode = new Node(currKey);
    allNodes.insert(std::pair<std::string, Node *>(currKey, currNode));
  }
  allNodes.insert(std::pair<std::string, Node*>(startNodeKey, start));

  std::map<Node *, std::set<Node *>> adjacent;

  std::map<std::string, Node *>::iterator it = allNodes.begin();
  while (it != allNodes.end()) {
    std::set<Node *> neighbors;
    for (unsigned int i = 0; i < it->first.size(); ++i) {
      std::string permutation1 = it->first;
      std::string permutation2 = it->first;
      permutation1[i] = '1';
      permutation2[i] = '0';
      if (allNodes.find(permutation1) != allNodes.end()) {
        neighbors.insert(allNodes[permutation1]);
      }
      if (allNodes.find(permutation2) != allNodes.end()) {
        neighbors.insert(allNodes[permutation2]);
      }
    }
    adjacent.insert(std::pair<Node*, std::set<Node*>>(it->second, neighbors));
  }

  std::priority_queue<Node*, std::vector<Node*>, nodeComp> queue;

  queue.push(start);
  int expansions = 0;
  while (!queue.empty() && queue.top()->key != endNodeKey) {
    std::set<Node*> neighbors = adjacent[queue.top()];
    std::set<Node*>::iterator it = neighbors.begin();
    while (it != neighbors.end()) {
      (*it)->g = queue.top()->g + bitDistance(queue.top()->key, (*it)->key);
      (*it)->f = (*it)->g + (*it)->h;
      (*it)->parent = queue.top();
    }
    ++expansions;
    queue.pop();
  }
  if (queue.empty()) {
    return -1;
  } else {
    Node* end = queue.top();
    std::vector<std::string> nodePath;
    while (end != NULL) {
      nodePath.push_back(end->key);
      end = end->parent;
    }
    std::vector<std::string>::iterator nodeKey = nodePath.begin();
    std::cout << expansions << std::endl;
    while (nodeKey != nodePath.end()) {
      std::cout << (*nodeKey) << std::endl;
    }
  }
  return 0;
}
