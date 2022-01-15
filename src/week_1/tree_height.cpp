#include <assert.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <string>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::cout;

time_t t_start, t_end;

/**
 * Compute tree height
 * Given a rooted tree, compute its height.
 * Input:
 *      Integer n - number of nodes, a_i \in {-1,0,...n-1},
 *      if a_i = -1, node i is the root, else is 0-based index
 * Output:
 *      Integer h - height of the tree.
 * Constraints:
 *      1<=n<=10^5
 * Time limit: 1 sec
 * Memory limit: 512 mb
 */
void tic(int mode = 0) {
  if (mode == 0)
    t_start = time(0);
  else {
    t_end = time(0);
    cout << "Elapsed time is " << difftime(t_end, t_start) << " seconds\n";
  }
}
void toc() { tic(1); }

class Node;

class Node {
 public:
  int key;
  Node *parent;
  std::vector<Node *> children;

  Node() { this->parent = NULL; }

  void setParent(Node *theParent) {
    parent = theParent;
    parent->children.push_back(this);
  }
};

int tree_height_naive(std::vector<Node> &nodes) {
  int maxHeight = 0;
  int n = nodes.size();
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent) height++;
    maxHeight = std::max(maxHeight, height);
  }

  return maxHeight;
}
int tree_height_fast(Node *root) {
  std::queue<Node *> node_queue;
  node_queue.push(root);

  int height = 0;
  int node_count = 0;

  while (!node_queue.empty()) {
    height++;
    node_count = node_queue.size();
    while (node_count > 0) {
      Node *node = node_queue.front();
      node_queue.pop();
      for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i] != NULL) node_queue.push(node->children[i]);
      }
      node_count--;
    }
  }

  return height;
}

void run_tests() {
  std::string filename_base = std::string(
      "/mnt/c/Users/naimakov/Desktop/edx/data_structures/starter_files/"
      "week1_basic_data_structures_starters/tree_height/tests/");
  std::string input_file, output_file;
  std::ifstream input, output;
  std::vector<int> data;
  std::vector<Node> nodes;
  int root_index, parent_index, numNodes;
  int height1 = 0, height2 = 0, height_true = 0;
  for (int i = 1; i < 25; i++) {
    std::cout << "test " << i << "\n";
    if (i < 10) {
      input_file = filename_base + std::string("0") + std::to_string(i);
    } else {
      input_file = filename_base + std::to_string(i);
    }
    output_file = input_file + std::string(".a");
    input.open(input_file);

    input >> numNodes;
    data.resize(numNodes);
    for (int j = 0; j < numNodes; j++) {
      input >> data[j];
    }

    nodes.resize(numNodes);
    for (int child_index = 0; child_index < numNodes; child_index++) {
      parent_index = data[child_index];
      if (parent_index >= 0)
        nodes[child_index].setParent(&nodes[parent_index]);
      else
        root_index = child_index;
      nodes[child_index].key = child_index;
    }
    output.open(output_file);
    output >> height_true;
    tic();
    height1 = tree_height_naive(nodes);
    toc();
    tic();
    height2 = tree_height_fast(&nodes[root_index]);
    toc();
    if (height1 != height2) {
      std::cout << "Error: heights not equal - test case " << i << "\n";
    }
    if (height_true != height1) {
      std::cout << "Error: naive height is not correct - test case " << i
                << "\n";
    }
  }
  return;
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);

  run_tests();

  int numNodes, root_index;
  std::cin >> numNodes;

  std::vector<Node> nodes;
  nodes.resize(numNodes);
  for (int child_index = 0; child_index < numNodes; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root_index = child_index;
    nodes[child_index].key = child_index;
  }

  std::cout << tree_height_naive(nodes) << "\n";
  std::cout << tree_height_fast(&nodes[root_index]) << "\n";

  return 0;
}

int main(int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;  // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0) {
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }

#endif
  return main_with_large_stack_space();
}
