#pragma once
#ifndef RANGE_SEARCH
#include "RedBlackTree.h"

RedBlackTreePnt make_range_tree_y(std::vector<Node*> nodes);
std::pair<int, int> range_search(RedBlackTreePnt range_tree_x, Point pnt_center, int radius);
std::vector<Node *> find_nodes_in_range_x(RedBlackTreePnt range_tree_x, std::pair<int, int> range_x, std::pair<int, int> range_y);
std::vector<Node *> find_nodes_in_range_y(RedBlackTreePnt range_tree_y, std::pair<int, int> range_y);
std::vector<Node *> get_nodes_in_subtree(Node *cur, std::vector<Node*> nodes);

#endif
