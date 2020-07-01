#pragma once
#ifndef NODE
#include <vector>
#include "Point.cpp"

class Node {
public:
	std::vector<int> index;
	std::vector<Point> pnt;

    int color;    // 0: Red, 1: Black
    int depth;

    Node *left;
    Node *right;
    Node *parent;

    Node(int index, Point pnt, int color = 1);
};

#endif
