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
        if (pnt.x < cur->pnt[0].x)          cur = cur->left;
        else if (pnt.x > cur->pnt[0].x)     cur = cur->right;
        else {
            for (int p_i = 0; p_i < cur->pnt.size(); p_i++) {
                if (cur->pnt[p_i].y == pnt.y)       return cur;
            }
            break;
        }
    }
    return NULL;
}
Node *RedBlackTreePnt::rb_search_y(Point pnt) {
    Node *cur = this->root;
    while (cur != NULL) {
        if (pnt.y < cur->pnt[0].y)          cur = cur->left;
        else if (pnt.y > cur->pnt[0].y)     cur = cur->right;
        else {
            for (int p_i = 0; p_i < cur->pnt.size(); p_i++) {
                if (cur->pnt[p_i].x == pnt.x)       return cur;
            }
            break;
        }
    }
    return NULL;
}
Node *RedBlackTreePnt::rotate_left(Node *node) {
    if (node->right == NULL)    return NULL;

    Node *parent_temp = NULL;
    int child_f;

    if (node == this->root)     
        child_f = -1;
    else {
        parent_temp = node->parent;

        if (node == parent_temp->left)      child_f = 0;
        else                                child_f = 1;
    }
    
    Node *new_subroot = node->right;

    if (child_f == -1) {
        this->root = new_subroot;
        this->root->parent = NULL;
    }
    else {
        new_subroot->parent = parent_temp;

        if (child_f == 0)       parent_temp->left = new_subroot;
        else if (child_f == 1)  parent_temp->right = new_subroot;
    }

    Node *sub_child = new_subroot->left;

    new_subroot->left = node;
    new_subroot->left->right = sub_child;

    if (sub_child != NULL)      sub_child->parent = new_subroot->left;

    return new_subroot;
}
Node *RedBlackTreePnt::rotate_right(Node *node) {
    int child_f;

    if (node->left == NULL)     return NULL;

    Node *parent_temp = NULL;

    if (node == this->root)     child_f = -1;
    else {
        parent_temp = node->parent;

        if (node == parent_temp->left)     child_f = 0;
        else                               child_f = 1;
    }

    Node *new_subroot = node->left;

    if (child_f == -1) {
        this->root = new_subroot;
        this->root->parent = NULL;
    }
    else {
        new_subroot->parent = parent_temp;

        if (child_f == 0)       parent_temp->left = new_subroot;
        else if (child_f == 1)  parent_temp->right = new_subroot;
    }

    Node *sub_child = new_subroot->right;

    new_subroot->right = node;
    new_subroot->right->left = sub_child;

    if (sub_child != NULL)      sub_child->parent = new_subroot->right;

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
    if (this->rb_search_x == NULL) {
        this->N_pnt++;
        this->N_dup++;

        return;
    }

    if (this->root == NULL) {
        Node *node = new Node(index, pnt);
        this->root = node;
        this->N_pnt++;
    }
    else {
        if (this->rb_search_x(pnt) == NULL) {
            Node *cur = this->root;
            Node *parent = NULL;
            bool dup_f = false;

            while (cur != NULL) {
                parent = cur;
                if (pnt.x < cur->pnt[0].x)      cur = cur->left;
                else if (pnt.x > cur->pnt[0].x) cur = cur->right;
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
                if (pnt.x < parent->pnt[0].x)       parent->left = node;
                else                                parent->right = node;

                node->parent = parent;

                if (node->parent->color == 0)       this->balance(node);
            }
            this->N_pnt++;
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
    if (this->rb_search_y == NULL) {
        this->N_pnt++;
        this->N_dup++;

        return;
    }

    if (this->root == NULL) {
        Node *node = new Node(index, pnt);
        this->root = node;
        this->N_pnt++;
    }
    else {
        if (this->rb_search_x(pnt) == NULL) {
            Node *cur = this->root;
            Node *parent = NULL;
            bool dup_f = false;

            while (cur != NULL) {
                parent = cur;
                if (pnt.y < cur->pnt[0].y)      cur = cur->left;
                else if (pnt.y > cur->pnt[0].y) cur = cur->right;
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
                if (pnt.y < parent->pnt[0].y)       parent->left = node;
                else                                parent->right = node;

                node->parent = parent;

                if (node->parent->color == 0)       this->balance(node);
            }
            this->N_pnt++;
        }
    }
}
void RedBlackTreePnt::rb_delete(Point pnt) {
    // 보류
}
void RedBlackTreePnt::update_after_delete(Node *target, Node *parent, Node *sib, int child_f) {
    // 보류
}
void RedBlackTreePnt::balance(Node *node) {
    if (node->parent == this->root || node->parent == NULL)     return;

    Node *parent = node->parent;
    Node *gparent = parent->parent;
    Node *uncle = NULL;

    if (parent == gparent->left)        uncle = gparent->right;
    else if (parent == gparent->right)  uncle = gparent->left;

    if (uncle == NULL || (uncle != NULL && uncle->color == 1))      this->reconstruct(node);
    else if (uncle != NULL && uncle->color == 1)                    this->recolor(node);
}
void RedBlackTreePnt::reconstruct(Node *node) {
    Node *parent = node->parent;
    Node *gparent = parent->parent;

    if (parent == NULL)     return;

    if (parent == gparent->left) {
        if (node == parent->right)      parent = this->rotate_left(parent);

        gparent = parent->parent;
        gparent = this->rotate_right(gparent);

        gparent->color = 1;
        gparent->right->color = 0;
    }
    else if (parent == gparent->right) {
        if (node == parent->left)       parent = this->rotate_right(parent);

        gparent = parent->parent;
        gparent = this->rotate_right(gparent);

        gparent->color = 1;
        gparent->left->color = 0;
    }
}
void RedBlackTreePnt::recolor(Node *node) {
    Node *parent = node->parent;
    Node *gparent = parent->parent;
    Node *uncle = NULL;

    if (parent == gparent->left)        uncle = gparent->right;
    else if (parent == gparent->right)  uncle = gparent->left;

    parent->color = 1;
    uncle->color = 1;

    if (gparent == this->root)      gparent->color = 1;
    else {
        gparent->color = 0;

        if (gparent->parent->color == 1)        this->balance(gparent);
    }
}
void RedBlackTreePnt::replace_to_predecessor(Node *target, Node *pre) {
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
}
void RedBlackTreePnt::replace_to_successor(Node *target, Node *suc) {
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
}
int RedBlackTreePnt::count_nodes() {
    return this->count_nodes_util(this->root, 0);
}
int RedBlackTreePnt::count_nodes_util(Node *node, int count) {
    if (node->right != NULL)        count = this->count_nodes_util(node->right, count);
    count += node->pnt.size();
    if (node->left != NULL)         count = this->count_nodes_util(node->left, count);

    return count;
}