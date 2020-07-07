#include <iostream>
#include "RedBlackTree.h"
using namespace std;

RedBlackTreePnt::RedBlackTreePnt(int xy_idx) {
	this->root = NULL;
	this->xy_idx = xy_idx;
	this->N_dup = 0;
	this->N_pnt = 0;
	this->N_del = 0;
	this->N_del_fail = 0;
}
Node *RedBlackTreePnt::rb_search_x(Point pnt) {
	Node *cur = this->root;

	while (cur != NULL) {
		if (pnt.x < cur->pnt[0].x)
			cur = cur->left;
		else if (pnt.x > cur->pnt[0].x)
			cur = cur->right;
		else {
			for (int p_i = 0; p_i < cur->pnt.size(); p_i++) {
				if (cur->pnt[p_i].y == pnt.y)
					return cur;
			}
			break;
		}
	}
	return NULL;
}
Node *RedBlackTreePnt::rb_search_y(Point pnt) {
	Node *cur = this->root;

	while (cur != NULL) {
		if (pnt.y < cur->pnt[0].y)          
			cur = cur->left;
		else if (pnt.y > cur->pnt[0].y)     
			cur = cur->right;
		else {
			for (int p_i = 0; p_i < cur->pnt.size(); p_i++) {
				if (cur->pnt[p_i].x == pnt.x)       
					return cur;
			}
			break;
		}
	}
	//delete cur;

	return NULL;
}
Node *RedBlackTreePnt::rotate_left(Node *node) {
	if (node->right == NULL)    
		return NULL;

	Node *parent_temp = NULL;
	int child_f;

	if (node == this->root)
		child_f = -1;
	else {
		parent_temp = node->parent;

		if (node == parent_temp->left)      
			child_f = 0;
		else                                
			child_f = 1;
	}

	Node *new_subroot = node->right;

	if (child_f == -1) {
		this->root = new_subroot;
		this->root->parent = NULL;
	}
	else {
		new_subroot->parent = parent_temp;

		if (child_f == 0)       
			parent_temp->left = new_subroot;
		else if (child_f == 1)  
			parent_temp->right = new_subroot;
	}

	Node *sub_child = new_subroot->left;

	new_subroot->left = node;
	new_subroot->left->right = sub_child;

	// 추가한 부분
	new_subroot->left->parent = new_subroot;

	if (sub_child != NULL)      
		sub_child->parent = new_subroot->left;

	//delete parent_temp;
	//delete sub_child;

	return new_subroot;
}
Node *RedBlackTreePnt::rotate_right(Node *node) {
	if (node->left == NULL)
		return NULL;

	int child_f;
	Node *parent_temp = NULL;

	if (node == this->root)     
		child_f = -1;
	else {
		parent_temp = node->parent;

		if (node == parent_temp->left)     
			child_f = 0;
		else                               
			child_f = 1;
	}

	Node *new_subroot = node->left;

	if (child_f == -1) {
		this->root = new_subroot;
		this->root->parent = NULL;
	}
	else {
		new_subroot->parent = parent_temp;

		if (child_f == 0)       
			parent_temp->left = new_subroot;
		else if (child_f == 1)  
			parent_temp->right = new_subroot;
	}

	Node *child_temp = new_subroot->right;

	new_subroot->right = node;
	new_subroot->right->left = child_temp;

	// 추가한 부분
	new_subroot->right->parent = new_subroot;

	if (child_temp != NULL)      
		child_temp->parent = new_subroot->right;

	//delete parent_temp;
	//delete sub_child;

	return new_subroot;
}
Node *RedBlackTreePnt::get_predecessor(Node *node) {
	if (node == NULL)       return NULL;

	Node *pre = node->left;
	int depth = 0;

	while (pre->right != NULL) {
		pre = pre->right;
		depth += 1;
	}
	pre->depth = depth;

	return pre;
}
Node *RedBlackTreePnt::get_successor(Node *node) {
	if (node == NULL)       return NULL;

	Node *suc = node->right;
	int depth = 0;

	while (suc->left != NULL) {
		suc = suc->left;
		depth++;
	}
	suc->depth = depth;

	return suc;
}
Node *RedBlackTreePnt::replace_to_predecessor(Node *target, Node *pre) {
	if (target == pre->parent) {
		pre->right = target->right;

		if (pre->right != NULL)     pre->right->parent = pre;
	}
	else {
		pre->left = target->left;
		pre->right = target->right;

		if (pre->left != NULL)      pre->left->parent = pre;
		if (pre->right != NULL)     pre->right->parent = pre;

		pre->parent->right = NULL;
	}

	if (target == this->root) {
		pre->parent = NULL;
		this->root = pre;
	}
	else {
		if (target == target->parent->left)     target->parent->left = pre;
		else                                    target->parent->right = pre;

		pre->parent = target->parent;
	}

	return pre;
}
Node *RedBlackTreePnt::replace_to_successor(Node *target, Node *suc) {
	if (target == suc->parent) {
		suc->left = target->left;

		if (suc->left != NULL)      suc->left->parent = suc;
	}
	else {
		suc->left = target->left;
		suc->right = target->right;

		if (suc->left != NULL)      suc->left->parent = suc;
		if (suc->right != NULL)     suc->right->parent = suc;

		suc->parent->left = NULL;
	}

	if (target == this->root) {
		suc->parent = NULL;
		this->root = suc;
	}
	else {
		if (target == target->parent->left)        target->parent->left = suc;
		else                                       target->parent->right = suc;

		suc->parent = target->parent;
	}

	return suc;
}
Node *RedBlackTreePnt::get_root() { return this->root; }
void RedBlackTreePnt::rb_insert_x(int index, Point pnt) {
	// 중복 허용
	/*
	Node *node_searched = this->rb_search_x(pnt);

	if (node_searched != NULL) {
		node_searched->index.push_back(index);
		node_searched->pnt.push_back(pnt);
		this->N_pnt++;
		this->N_dup++;

		return;
	}
	*/

	// 중복 비허용
	if (this->rb_search_x(pnt) != NULL) {
		this->N_pnt++;
		this->N_dup++;

		return;
	}

	if (this->root == NULL) {
		Node *node = new Node(index, pnt);
		this->root = node;
		this->N_pnt++;

		//delete node;
	}
	else {
		if (this->rb_search_x(pnt) == NULL) {
			Node *cur = this->root;
			Node *parent = NULL;
			bool dup_f = false;

			while (cur != NULL) {
				parent = cur;
				if (pnt.x < cur->pnt[0].x)
					cur = cur->left;
				else if (pnt.x > cur->pnt[0].x)
					cur = cur->right;
				else {
					dup_f = true;
					break;
				}
			}

			if (dup_f) {
				cur->index.push_back(index);
				cur->pnt.push_back(pnt);
			}
			else {
				Node *node = new Node(index, pnt, 0);

				if (pnt.x < parent->pnt[0].x)
					parent->left = node;
				else
					parent->right = node;

				node->parent = parent;

				if (node->parent->color == 0)       
					this->balance(node);
			}
			this->N_pnt++;

			//delete cur;
			//delete parent;
			//delete node;
		}
	}
}
void RedBlackTreePnt::rb_insert_y(int index, Point pnt) {
	// 중복 허용
	/*
	Node *node_searched = this->rb_search_y(pnt);

	if (node_searched != NULL) {
		node_searched->index.push_back(index);
		node_searched->pnt.push_back(pnt);
		this->N_pnt++;
		this->N_dup++;

		return;
	}
	*/

	// 중복 비허용
	if (this->rb_search_y(pnt) != NULL) {
		this->N_dup++;

		return;
	}

	if (this->root == NULL) {
		Node *node = new Node(index, pnt);
		this->root = node;
		this->N_pnt++;

		//delete node;
	}
	else {
		if (this->rb_search_y(pnt) == NULL) {
			Node *cur = this->root;
			Node *parent = NULL;
			bool dup_f = false;

			while (cur != NULL) {
				parent = cur;
				if (pnt.y < cur->pnt[0].y)      
					cur = cur->left;
				else if (pnt.y > cur->pnt[0].y) 
					cur = cur->right;
				else {
					dup_f = true;
					break;
				}
			}
			Node *node = new Node(index, pnt, 0);

			if (dup_f) {
				cur->index.push_back(index);
				cur->pnt.push_back(pnt);
			}
			else {
				if (pnt.y < parent->pnt[0].y)       
					parent->left = node;
				else                                
					parent->right = node;

				node->parent = parent;

				//this->print_tree();
				//std::cout << "---------------------------------------------------------------" << std::endl;

				if (node->parent->color == 0)       
					this->balance(node);
			}
			this->N_pnt++;

			//delete cur;
			//delete parent;
			//delete node;
		}
	}
}
void RedBlackTreePnt::rb_delete(Point pnt) {
	Node *target = this->rb_search_x(pnt);

	if (target == NULL) {
		this->N_del_fail++;

		return;
	}

	if (target->pnt.size() > 1) {
		int del_i;
		
		for (del_i = 0; del_i < target->pnt.size(); del_i++) {
			if (target->pnt[del_i].x == pnt.x and target->pnt[del_i].y == pnt.y)
				break;
		}
		target->index.erase(target->index.begin() + del_i);
		target->pnt.erase(target->pnt.begin() + del_i);
		this->N_del++;
		this->N_pnt--;
		
		return;
	}

	Node *parent = target->parent;
	int child_f;

	if (target == this->root)
		child_f = -1;
	else if (target == parent->left)
		child_f = 0;
	else
		child_f = 1;

	int target_color = target->color;
	bool double_black_f = false;

	// When target is a leaf node
	if (target->left == NULL && target->right == NULL) {
		double_black_f = true;
		
		if (child_f == 0)
			parent->left = NULL;
		else if (child_f == 1)
			parent->right = NULL;
	}
	// When target only has left child
	else if (target->left != NULL && target->right == NULL) {
		if (child_f == 0) {
			parent->left = target->left;

			if (parent->left != NULL) {
				if (parent->left->color == 1)
					double_black_f = true;

				parent->left->color = 1;
				parent->left->parent = parent;
			}
			else
				double_black_f = true;
		}
		else if (child_f == 1) {
			parent->right = target->left;

			if (parent->right != NULL) {
				if (parent->right->color == 1)
					double_black_f = true;

				parent->right->color = 1;
				parent->right->parent = parent;
			}
			else
				double_black_f = true;
		}
	}
	// When target only has right child
	else if (target->left == NULL && target->right != NULL) {
		if (child_f == 0) {
			parent->left = target->right;

			if (parent->left != NULL) {
				if (parent->left->color == 1)
					double_black_f = true;

				parent->left->color = 1;
				parent->left->parent = parent;
			}
			else
				double_black_f = true;
		}
		else if (child_f == 1) {
			parent->right = target->right;

			if (parent->right != NULL) {
				if (parent->right->color == 1)
					double_black_f = true;

				parent->left->color = 1;
				parent->right->parent = parent;
			}
			else
				double_black_f = true;
		}
	}
	// When target has both children
	else {
		Node *pre = this->get_predecessor(target);
		Node *suc = this->get_successor(target);

		if (pre->depth < suc->depth) {
			if (suc->color == 1)
				double_black_f = true;

			suc->color = 1;
			target = this->replace_to_successor(target, suc);
		}
		else {
			if (pre->color == 1)
				double_black_f = true;

			pre->color = 1;
			target = this->replace_to_predecessor(target, pre);
		}
	}

	// When target's color is red, just delete it
	if (target->color == 0) {
		this->N_pnt--;
		this->N_del++;
		
		return;
	}
	// When target's color is black
	else {
		if (!double_black_f) {
			this->N_pnt--;
			this->N_del++;

			return;
		}

		Node *sib;

		if (child_f == 0)
			sib = parent->right;
		else if (child_f == 1)
			sib = parent->left;
		else {
			this->N_pnt--;
			this->N_del++;

			return;
		}

		this->update_after_delete(target, parent, sib, child_f);
		this->N_del++;
		this->N_pnt--;
	}
}
void RedBlackTreePnt::update_after_delete(Node *target, Node *parent, Node *sib, int child_f) {
	if (parent == NULL)
		return;

	if (sib == NULL)
		return;

	// When sibling's color is red
	if (sib->color == 0) {
		sib->color = 1;
		target->color = 0;

		if (child_f == 0)
			this->rotate_left(parent);
		else if (child_f == 1)
			this->rotate_right(parent);
	}
	// When sibling's color is black (complicated)
	else {
		bool double_black_f = false;

		// When target is parent's left child
		if (child_f == 0) {
			// When sibling's left and right are both black
			if ((sib->left == NULL || (sib->left != NULL && sib->left->color == 1))
				&& (sib->right == NULL || (sib->right != NULL && sib->right->color == 1))) {
				sib->color = 0;
				double_black_f = (parent->color == 1);
				parent->color = 1;

				if (double_black_f) {
					target = parent;
					parent = parent->parent;

					if (target == this->root)
						return;

					if (target == parent->left) {
						child_f = 0;
						sib = parent->right;
					}
					else {
						child_f = 1;
						sib = parent->left;
					}

					this->update_after_delete(target, parent, sib, child_f);
				}
			}
			// when sibling's left is red and right is black
			else if ((sib->left != NULL && sib->left->color == 0) && (sib->right == NULL || (sib->right != NULL && sib->right->color == 1))) {
				sib->color = 0;
				sib->left->color = 1;
				this->rotate_left(sib);
			}
			// When sibling's right is red
			else {
				sib->color = parent->color;
				parent->color = 1;
				if (sib->right != NULL)
					sib->right->color = 1;
				this->rotate_left(parent);
			}
		}
		// When target is parent's right child
		else if (child_f == 1) {
			// When sibling's left and right are both black
			if ((sib->left == NULL || (sib->left != NULL && sib->left->color == 1))
				&& (sib->right == NULL || (sib->right != NULL && sib->right->color == 1))) {
				sib->color = 0;
				double_black_f = (parent->color == 1);
				parent->color = 1;
				if (double_black_f) {
					target = parent;
					parent = parent->parent;

					if (target == this->root)
						return;

					if (target == parent->left) {
						child_f = 0;
						sib = parent->right;
					}
					else {
						child_f = 1;
						sib = parent->left;
					}

					this->update_after_delete(target, parent, sib, child_f);
				}
			}
			// When sibling's left is black and right is red
			else if ((sib->left == NULL || (sib->left != NULL && sib->left->color == 1)) && (sib->right != NULL && sib->right->color == 1)) {
				sib->color = 0;
				sib->right->color = 1;
				this->rotate_right(sib);
			}
			// When sibling's left is red
			else {
				sib->color = parent->color;
				parent->color = 1;

				if (sib->left != NULL)
					sib->left->color = 1;
				this->rotate_right(parent);
			}
		}
	}
}
void RedBlackTreePnt::balance(Node *node) {
	if (node->parent == this->root || node->parent == NULL)     
		return;

	Node *parent = node->parent;
	Node *gparent = parent->parent;
	Node *uncle = NULL;

	if (parent == gparent->left)
		uncle = gparent->right;
	else if (parent == gparent->right)
		uncle = gparent->left;

	if (uncle == NULL || (uncle != NULL && uncle->color == 1)) {
		this->reconstruct(node);

		//this->print_tree();
		//std::cout << "---------------------------------------------------------------" << std::endl;

	}
	else if (uncle != NULL && uncle->color == 0)
		this->recolor(node);

	//delete parent;
	//delete gparent;
	//delete uncle;
}
void RedBlackTreePnt::reconstruct(Node *node) {
	Node *parent = node->parent;
	Node *gparent = parent->parent;

	if (parent == NULL)     
		return;

	if (parent == gparent->left) {
		if (node == parent->right)      
			parent = this->rotate_left(parent);

		//this->print_tree();
		//std::cout << "---------------------------------------------------------------" << std::endl;

		gparent = parent->parent;
		gparent = this->rotate_right(gparent);

		gparent->color = 1;
		gparent->right->color = 0;
	}
	else if (parent == gparent->right) {
		if (node == parent->left)       
			parent = this->rotate_right(parent);

		//this->print_tree();
		//std::cout << "---------------------------------------------------------------" << std::endl;

		gparent = parent->parent;
		gparent = this->rotate_left(gparent);

		gparent->color = 1;
		gparent->left->color = 0;
	}

	//delete parent;
	//delete gparent;
}
void RedBlackTreePnt::recolor(Node *node) {
	Node *parent = node->parent;
	Node *gparent = parent->parent;
	Node *uncle = NULL;

	if (parent == gparent->left)
		uncle = gparent->right;
	else if (parent == gparent->right)
		uncle = gparent->left;

	parent->color = 1;
	
	if (uncle != NULL)
		uncle->color = 1;

	if (gparent == this->root)
		gparent->color = 1;
	else {
		gparent->color = 0;

		if (gparent->parent != NULL && gparent->parent->color == 1)
			this->balance(gparent);
	}

	//delete parent;
	//delete gparent;
	//delete uncle;
}
void RedBlackTreePnt::print_tree() {
	if (this->root == NULL)		return;
	this->print_tree_util(this->root, 0);
}
void RedBlackTreePnt::print_tree_util(Node *node, int depth) {
	if (node->right != NULL)		this->print_tree_util(node->right, depth + 1);
	for (int i = 0; i < depth; i++)		cout << "                      ";
	cout << "(" << node->pnt[0].x << "," << node->pnt[0].y << "):";
	if (node->color == 0)		cout << "r";
	else						cout << "b";
	cout << "(" << node->pnt.size() << ")" << endl;
	if (node->left != NULL)			this->print_tree_util(node->left, depth + 1);
}
void RedBlackTreePnt::print_points() {
	if (this->xy_idx == 0)
		cout << "<Points - X sorted>" << endl;
	if (this->xy_idx == 1)
		cout << "<Points - Y sorted>" << endl;
	this->print_points_util(this->root);
	cout << "<Points end>" << endl << endl;;
}
void RedBlackTreePnt::print_points_util(Node *cur) {
	if (cur->right != NULL)		this->print_points_util(cur->right);
	for (int i = 0; i < cur->pnt.size(); i++)
		cout << cur->pnt[i].x << " " << cur->pnt[i].y << endl;
	if (cur->left != NULL)		this->print_points_util(cur->left);
}
void RedBlackTreePnt::delete_tree() {
	this->delete_tree_util(this->root);
}
void RedBlackTreePnt::delete_tree_util(Node* node) {
	if (node->right != NULL)
		this->delete_tree_util(node->right);
	if (node->left != NULL)
		this->delete_tree_util(node->left);
	delete node;
}
int RedBlackTreePnt::count_nodes() {
	return this->count_nodes_util(this->root, 0);
}
int RedBlackTreePnt::count_nodes_util(Node *node, int count) {
	if (node->right != NULL)        count = this->count_nodes_util(node->right, count);
	count += (int)node->pnt.size();
	if (node->left != NULL)         count = this->count_nodes_util(node->left, count);

	return count;
}