#include "Node.h"

Node::Node(int index, Point pnt, int color) {
	this->index.push_back(index);
	this->pnt.push_back(pnt);
	this->color = color;
}