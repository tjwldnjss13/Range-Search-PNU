#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	int key;
	Node *next;
	Node(int key) {
		this->key = key;
	}
};

void change_vector(vector<Node *> v, int index, int value) {
	if (v.size() >= index)
		return;
}

vector<Node *> make_vector1(vector<Node *> v) {
	//vector<Node*> v;

	v.push_back(new Node(1));
	v.push_back(new Node(2));
	v.push_back(new Node(3));

	return v;
}

vector<Node *> make_vector2(vector<Node *> v) {
	//vector<Node*> v;

	v.push_back(new Node(10));
	v.push_back(new Node(20));
	v.push_back(new Node(30));

	return v;
}

/*
int main() {
	int a = 0;
	bool b = false;
	cout << b << endl;
}
*/