#pragma once
#ifndef REDBLACKTREE_PNT
#include "Node.h"

class RedBlackTreePnt {
private:
	Node *root;
	int xy_idx;
	int N_dup;
	int N_pnt;
	int N_del;
	int N_del_fail;
public:
	RedBlackTreePnt(int xy_idx = 1);
	Node *rb_search_x(Point pnt);
	Node *rb_search_y(Point pnt);
	Node *rotate_left(Node *node);
	Node *rotate_right(Node *node);
	Node *get_predecessor(Node *node);
	Node *get_successor(Node *node);
	Node *replace_to_predecessor(Node *target, Node *pre);
	Node *replace_to_successor(Node *target, Node *suc);
	Node *get_root();
	void rb_insert_x(int index, Point pnt);
	void rb_insert_y(int index, Point pnt);
	void rb_delete(Point pnt);
	void update_after_delete(Node *target, Node *parent, Node *sib, int child_f);
	void balance(Node *node);
	void reconstruct(Node *node);
	void recolor(Node *node);
	void print_tree();
	void print_tree_util(Node *node, int depth);
	void print_points();
	void print_points_util(Node *cur);
	void delete_tree();
	void delete_tree_util(Node* node);
	int count_nodes();
	int count_nodes_util(Node *node, int count);
};

#endif
