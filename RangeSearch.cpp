#include <iostream>
#include "RangeSearch.h"

RedBlackTreePnt make_range_tree_y(std::vector<Node*> nodes) {
	RedBlackTreePnt range_tree_y(1);
	Point pnt_temp;

	for (int n_i = 0; n_i < nodes.size(); n_i++) {
		for (int p_i = 0; p_i < nodes[n_i]->pnt.size(); p_i++) {
			pnt_temp = nodes[n_i]->pnt[p_i];
			range_tree_y.rb_insert_y(nodes[n_i]->index[p_i], nodes[n_i]->pnt[p_i]);
		}
		//range_tree_y.print_tree();
		//std::cout << "=======================================================================" << std::endl;
	}

	return range_tree_y;
}
std::pair<int, int> range_search(RedBlackTreePnt range_tree_x, Point pnt_center, int radius) {
	int x_min = pnt_center.x - radius;
	int x_max = pnt_center.x + radius;
	int y_min = pnt_center.y - radius;
	int y_max = pnt_center.y + radius;

	std::cout << "x : " << x_min << " - " << x_max << std::endl;
	std::cout << "y : " << y_min << " - " << y_max << std::endl;

	std::pair<int, int> range_x = std::make_pair(x_min, x_max);
	std::pair<int, int> range_y = std::make_pair(y_min, y_max);

	std::vector<Node *> nodes = find_nodes_in_range_x(range_tree_x, range_x, range_y);
	std::vector<int> idxs;
	std::vector<Point> pnts;

	for (int n_i = 0; n_i < nodes.size(); n_i++) {
		for (int p_i = 0; p_i < nodes[n_i]->pnt.size(); p_i++) {
			idxs.push_back(nodes[n_i]->index[p_i]);
			pnts.push_back(nodes[n_i]->pnt[p_i]);
		}
	}

	int p_i = 0;
	int max_dist_i = -1;
	int max_dist_sq = -1;
	std::vector<int> max_i_list;

	while (p_i < pnts.size()) {
		 double dist_sq = pow(pnts[p_i].x - pnt_center.x, 2) + pow(pnts[p_i].y - pnt_center.y, 2);

		if (dist_sq > pow(radius, 2)) {
			idxs.erase(idxs.begin() + p_i);
			pnts.erase(pnts.begin() + p_i);
			continue;
		}

		if (max_dist_i == -1 || dist_sq >= max_dist_sq) {
			max_dist_i = idxs[p_i];

			if (dist_sq > max_dist_sq) {
				max_dist_sq = dist_sq;
				max_i_list.clear();
			}
			max_i_list.push_back(max_dist_i);
		}
		p_i++;
	}

	int min_i = -1;

	while (max_i_list.size() > 0) {
		if (min_i == -1 || max_i_list[max_i_list.size() - 1] < min_i)		
			min_i = max_i_list[max_i_list.size() - 1];

		max_i_list.pop_back();
	}

	std::vector<int>().swap(idxs);
	std::vector<Point>().swap(pnts);
	std::vector<int>().swap(max_i_list);

	int N_pnts = pnts.size();

	for (int i = 0; i < nodes.size(); i++)
		delete nodes[i];

	nodes.clear();

	return std::make_pair(N_pnts, min_i);
}
std::vector<Node *> find_nodes_in_range_x(RedBlackTreePnt range_tree_x, std::pair<int, int> range_x, std::pair<int, int> range_y) {
	std::vector<Node *> nodes;
	Node *cur = range_tree_x.get_root();

	if (cur == NULL) {
		//for (int i = 0; i < nodes.size(); i++)		delete nodes[i];
		//delete cur;

		return nodes;
	}

	
	range_tree_x.print_points();
	range_tree_x.print_tree();
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
	

	Node *splitv = NULL;

	while (cur != NULL) {
		if (cur->pnt[0].x < range_x.first)
			cur = cur->right;
		else if (cur->pnt[0].x > range_x.second)
			cur = cur->left;
		else {
			splitv = cur;
			break;
		}
	}

	if (splitv == NULL) {
		//for (int i = 0; i < nodes.size(); i++)		delete nodes[i];
		//delete cur;
		//delete splitv;
		return nodes;
	}

	nodes.push_back(splitv);

	Node *t_l = splitv->left;
	Node *t_r = splitv->right;
	std::vector<Node *> nodes_subtree;

	while (t_l != NULL) {
		if (t_l->pnt[0].x < range_x.first)
			t_l = t_l->right;
		else {
			nodes_subtree.clear();
			nodes.push_back(t_l);
			nodes_subtree = get_nodes_in_subtree(t_l->right, nodes_subtree);

			while (nodes_subtree.size() > 0) {
				nodes.push_back(nodes_subtree[nodes_subtree.size() - 1]);
				nodes_subtree.pop_back();
			}

			if (t_l->pnt[0].x == range_x.first)
				break;
			else
				t_l = t_l->left;
		}
	}

	while (t_r != NULL) {
		if (t_r->pnt[0].x > range_x.second)		
			t_r = t_r->left;
		else {
			nodes_subtree.clear();
			nodes.push_back(t_r);
			nodes_subtree = get_nodes_in_subtree(t_r->left, nodes_subtree);

			while (nodes_subtree.size() > 0) {
				nodes.push_back(nodes_subtree[nodes_subtree.size() - 1]);
				nodes_subtree.pop_back();
			}

			if (t_r->pnt[0].x == range_x.second)		
				break;
			else										
				t_r = t_r->right;
		}
	}

	RedBlackTreePnt range_tree_y = make_range_tree_y(nodes);

	
	range_tree_y.print_points();
	range_tree_y.print_tree();
	std::cout << "====================================================================================" << std::endl;
	

	std::vector<Node *> nodes_final = find_nodes_in_range_y(range_tree_y, range_y);
	range_tree_y.delete_tree();

	//for (int i = 0; i < nodes.size(); i++)			delete nodes[i];
	//for (int i = 0; i < nodes_empty.size(); i++)	delete nodes_empty[i];
	//for (int i = 0; i < nodes_subtree.size(); i++)	delete nodes_subtree[i];
	//delete cur;
	//delete splitv;
	//delete t_l;
	//delete t_r;

	return nodes_final;
}
std::vector<Node *> find_nodes_in_range_y(RedBlackTreePnt range_tree_y, std::pair<int, int> range_y) {
	std::vector<Node *> nodes;
	Node *cur = range_tree_y.get_root();

	if (cur == NULL)		
		return nodes;

	Node *splitv = NULL;

	while (cur != NULL) {
		if (cur->pnt[0].y < range_y.first)			
			cur = cur->right;
		else if (cur->pnt[0].y > range_y.second)	
			cur = cur->left;
		else {
			splitv = cur;
			break;
		}
	}

	if (splitv == NULL)		
		return nodes;

	for (int p_i=0; p_i<splitv->pnt.size(); p_i++)
		nodes.push_back(new Node(splitv->index[p_i], splitv->pnt[p_i]));

	Node *t_l = splitv->left;
	Node *t_r = splitv->right;
	Node *node_temp;
	std::vector<Node *> nodes_subtree;

	while (t_l != NULL) {
		if (t_l->pnt[0].y < range_y.first)		
			t_l = t_l->right;
		else {
			nodes_subtree.clear();
			nodes.push_back(t_l);
			nodes_subtree = get_nodes_in_subtree(t_l->right, nodes_subtree);

			while (nodes_subtree.size() > 0) {
				node_temp = nodes_subtree[nodes_subtree.size() - 1];
				for (int p_i=0; p_i<node_temp->pnt.size(); p_i++)
					nodes.push_back(new Node(node_temp->index[p_i], node_temp->pnt[p_i]));
				nodes_subtree.pop_back();
			}

			if (t_l->pnt[0].y == range_y.first)		
				break;
			else									
				t_l = t_l->left;
		}
	}

	while (t_r != NULL) {
		if (t_r->pnt[0].y > range_y.second)		
			t_r = t_r->left;
		else {
			nodes_subtree.clear();
			nodes.push_back(t_r);
			nodes_subtree = get_nodes_in_subtree(t_r->left, nodes_subtree);

			while (nodes_subtree.size() > 0) {
				nodes.push_back(nodes_subtree[nodes_subtree.size() - 1]);
				nodes_subtree.pop_back();
			}

			if (t_r->pnt[0].y == range_y.second)		
				break;
			else										
				t_r = t_r->right;
		}
	}

	return nodes;
}
std::vector<Node *> get_nodes_in_subtree(Node *cur, std::vector<Node *> nodes) {
	if (cur == NULL) {
		//std::vector<Node*> nodes_null;

		//return nodes_null;
		//return std::vector<Node*>();

		nodes.clear();
		return nodes;
	}

	if (cur->right != NULL)
		nodes = get_nodes_in_subtree(cur->right, nodes);

	nodes.push_back(cur);

	if (cur->left != NULL)
		nodes = get_nodes_in_subtree(cur->left, nodes);

	return nodes;
}