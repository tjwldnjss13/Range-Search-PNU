#include <iostream>
#include "RangeSearch.h"

RedBlackTreePnt make_range_tree_y(std::vector<Node> nodes) {
	RedBlackTreePnt range_tree_y(1);

	for (int n_i = 0; n_i < nodes.size(); n_i++) {
		for (int p_i=0; p_i < nodes[n_i].pnt.size(); p_i++) 
			range_tree_y.rb_insert_y(nodes[n_i].index[p_i], nodes[n_i].pnt[p_i]);
	}

	return range_tree_y;
}
std::vector<Node> range_search(RedBlackTreePnt range_tree_x, Point pnt_center, int radius)