#include "Node.h"

Node::Node(int index, Point pnt, int color = 1) {
    this->index.push_back(index);
    this->pnt.push_back(pnt);
    this->color = color;
}