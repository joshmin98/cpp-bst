#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>

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
  std::set<Node *> adjacent;
  Node *parent;

  Node(){};

  Node(const std::string node, const std::string startNode,
       int startNodeZeros) {
    key = node;
    h = countZeros(key);
    g = bitDistance(key, startNode);
    f = g + h;
  }

  Node(const std::string node, int gVal, int hVal) {
    key = node;
    g = gVal;
    h = hVal;
    f = g + h;
  }
};

// COMPARATOR FOR PRIORITY QUEUE
class nodeComp {
public:
  nodeComp();
  bool operator()(const Node *lhs, const Node *rhs) const {
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
    std::cerr << "Incorrect number of args" << std::endl;
    return -1;
  }

  std::string start = argv[1];
  int startNum = countZeros(start);
  Node *startNode = new Node;
  startNode->key = start;
  startNode->h = startNum;
  startNode->g = 0;
  startNode->f = h;

  // READ EVERY NODE && STORE IN SET
  std::ifstream infile(argv[2]);
  int numNodes = 0;
  infile >> numNodes;
  if (numNodes < (start.length() - startNum)) {
    std::cerr << "Impossible" << std::endl;
    return -1;
  }
  std::string line;
  std::set<Node *> nodes;
  while (getline(infile, line)) {
    Node *node = new Node(line, startNode, startNum);
    nodes.insert(node);
  }
  nodes.insert(startNode);

  // STORE NODES IN MAP. KEY IS NUMZEROS. VALUE IS A SET OF NODES WITH THAT NUM
  // ZEROS.
  std::map<int, std::set<Node *>> nodeMap;
  std::set<Node *>::iterator it = nodes.begin();
  while (it != nodes.end()) {
    Node *node = *it;
    if (nodeMap.find(node->h) == nodes.end()) {
      nodeMap.insert(std::pair<int, std::set<Node *>>(
          node->h, std::set<Node *> neighbors));
    }
    nodeMap[node->h].insert(node);
  }

  std::set<Node *>::iterator it = nodes.begin();
  while (it != nodes.end()) {
    Node *node = *it;
    std::set<Node *>::iterator it2 = nodeMap[node->h].begin();
    while (it2 != nodeMap[node->h].end()) {
      Node *prospective = *it2;
      if (isAdjacent(node, prospective)) {
        node->adjacent.insert(prospective);
      }
    }
  }

  // A STAR WITH QUEUE
  // DONT CREATE A NEW NODE FOR UPDATING VALUES JUST PUSH THE NODE AGAIN
  std::priority_queue<Node *, std::vector<Node *>, nodeComp> nodeList;
  nodeList.push(startNode);
  int expansions = 0;
  while (!nodeList.empty() &&
         nodeList.top()->key != ('1' * nodeList.top()->key.length())) {
    expansions++;
    Node *curr = nodeList.top();
    nodeList.pop();
    std::set<Node *>::iterator neighbor = curr->adjacent.begin();
    while (neighbor != curr->adjacent.end()) {
      Node *newNode = new Node();
      newNode->key = (*neighbor)->key;
      newNode->parent = *curr;
      newNode->h = (*neighbor)->h;
      newNode->g =
          newNode->parent->g + bitDistance(newNode->key, newNode->parent->key);
      newNode->adjacent = (*neighbor)->adjacent;
      nodeList.push(newNode);
    }
  }

  // FOUND PATH TO END. BACKTRACE.
  if (nodeList.top()->key == ('1' * nodeList.top()->key.length())) {
    Node *end = nodeList.top();
    std::vector<std::string> list;
    list.push_back(end->key);
    while (end != startNode) {
      end = end->parent;
      list.push_back(end->key);
    }
    list.push_back(end->key);
    for (unsigned int i = list.size() - 1; i >= 0; ++i) {
      std::cout << list[i] << std::endl;
    }
  }
  return 0;

  // Map each node to predecessor?
}
