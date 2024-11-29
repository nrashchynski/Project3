#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <iomanip>


// Общая Задача 2 по деревьям


struct Node {
	int key;
	Node* left;
	Node* right;
	Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class Tree {
public:
	Tree() : root(nullptr){}
	void insert(int key) {
		if (!root) {
			root = new Node(key);
		}
		else {
			insertNode(root, key);
		}
	}
	void TreeTraversal(std::vector<int>& result) {
		leftTraversal(root, result);
	}
	void TreeRightRemove(int key) {
		root = rightRemove(root, key);
	}

private:
	Node* root;
	void insertNode(Node* node, int key) {
		if (key < node->key) {
			if (node->left) {
				insertNode(node->left, key);
			}
			else {
				node->left = new Node(key);
			}
		}
		else if (key > node->key) {
			if (node->right) {
				insertNode(node->right, key);
			}
			else {
				node->right = new Node(key);
			}
		}
	}

	void leftTraversal(Node* node, std::vector<int>&result) {
		if (node) {
			result.push_back(node->key);
			leftTraversal(node->left, result);
			leftTraversal(node->right, result);
		}
	}

	Node* rightRemove(Node* node, int key) {
		if (!node){
			return nullptr;
		}
		else if (key < node->key) {
			node->left = rightRemove(node->left, key);
		}
		else if (key > node->key) {
			node->right = rightRemove(node->right, key);
		}
		else {
			if (!node->left) {
				Node* rightChild = node->right;
				delete node;
				return rightChild;
			}
			else if (!node->right) {
				Node* leftChild = node->left;
				delete node;
				return leftChild;
			}
			else {
				Node* minInRight = findMin(node->right);
				node->key = minInRight->key;
				node->right = rightRemove(node->right, minInRight->key);
			}
		}
		return node;
	}

	Node* findMin(Node* node) {
		while (node && node->left) {
			node = node->left;
		}
		return node;
	}


};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	int x;
	fin >> x;

	Tree tree;
	std::set<int>keysSet;
	int key;
	std::string line;
	while (!fin.eof()) {
		fin >> key;
		if (keysSet.insert(key).second) {
			tree.insert(key);
		} 
	}

	tree.TreeRightRemove(x);

	std::vector<int>answer;
	tree.TreeTraversal(answer);

	for (int k : answer) {
		fout << k << std::endl;
	}

	return 0;
}