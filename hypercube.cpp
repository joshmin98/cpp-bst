#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
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
  Node *parent;

  Node(const std::string &binString) {
    key = binString;
    std::string target = "";
    for (int i = 0; i < binString.length(); ++i) {
      target += "1";
    }
    h = bitDistance(key, target);
    g = std::numeric_limits<int>::max();
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
        for (int i = lhs->key.length() - 1; i >= 0; --i) {
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
  int numNodes = 0;
  infile >> numNodes;
  if (numNodes < start->h) {
    return -1;
  }

  // Reading in all nodes
  std::map<std::string, Node *> allNodes;
  std::string currKey;
  while (getline(infile, currKey)) {
    Node *currNode = new Node(currKey);
    allNodes.insert(std::pair<std::string, Node *>(currKey, currNode));
  }
  allNodes.insert(std::pair<std::string, Node *>(startNodeKey, start));
  infile.close();

  std::map<std::string, std::set<Node *>> adjacent;

  // Handling neighbors
  std::map<std::string, Node *>::iterator it = allNodes.begin();
  while (it != allNodes.end()) {
    std::set<Node *> neighbors;
    for (unsigned int i = 0; i < it->first.size(); ++i) {
      std::string permutation = it->first;
      if (permutation[i] == '0') {
        permutation[i] = '1';
      } else {
        permutation[i] = '0';
      }
      if (allNodes.find(permutation) != allNodes.end()) {
        neighbors.insert(allNodes.find(permutation)->second);
      }
    }
    adjacent.insert(
        std::pair<std::string, std::set<Node *>>(it->first, neighbors));
    ++it;
  }

  std::priority_queue<Node *, std::vector<Node *>, nodeComp> queue;

  // A* priority queue
  queue.push(start);
  int expansions = 0;
  std::set<Node *> visitedNodes;
  while (!queue.empty() && queue.top()->key != endNodeKey) {
    std::set<Node *> neighbors = adjacent.find(queue.top()->key)->second;
    if (neighbors.empty()) {
      std::cout << "EMPTY" << std::endl;
    }
    std::set<Node *>::iterator it = neighbors.begin();
    while (it != neighbors.end()) {
      if ((*it)->g >
          (queue.top()->g + bitDistance(queue.top()->key, (*it)->key))) {
        (*it)->g = queue.top()->g + bitDistance(queue.top()->key, (*it)->key);
        (*it)->f = (*it)->g + (*it)->h;
        (*it)->parent = queue.top();
        queue.push(*it);
      }
      ++it;
    }
    if (visitedNodes.find(queue.top()) == visitedNodes.end()) {
      visitedNodes.insert(queue.top());
      ++expansions;
    }
    queue.pop();
  }
  --expansions;

  // Outputing results
  if (queue.empty()) {
    return -1;
  } else {
    Node *end = queue.top();
    std::vector<std::string> nodePath;
    while (end != NULL) {
      nodePath.push_back(end->key);
      end = end->parent;
    }
    std::vector<std::string>::iterator nodeKey = nodePath.end();
    nodeKey--;
    while (nodeKey != nodePath.begin() - 1) {
      std::cout << (*nodeKey) << std::endl;
      nodeKey--;
    }
    std::cout << "expansions = " << expansions << std::endl;
  }

  // Cleanup
  std::map<std::string, Node *>::iterator clean = allNodes.begin();
  while (clean != allNodes.end()) {
    if (clean->second != NULL) {
      Node *deleteNode = clean->second;
      delete deleteNode;
      clean->second = NULL;
    }
    ++clean;
  }
  return 0;
}
