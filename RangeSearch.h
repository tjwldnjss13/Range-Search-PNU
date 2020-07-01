#pragma once
#ifndef RANGE_SEARCH
#include "RedBlackTree.h"

void range_search(RedBlackTreePnt range_tree_x, Point pnt_center, int radius);
void find_nodes_in_range(RedBlackTreePnt range_tree, int **ranges, int xy_idx = 0);
void make_range_tree_y();

#endif
