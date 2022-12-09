#pragma once

#include <iostream>


template<typename T>
class SearchTree;


template<typename T>
class TreeNode {
	friend class SearchTree<T>;

public:
	TreeNode* parent = nullptr;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

public:
	const T key;

public:
	TreeNode(const T rootKey) : key(rootKey) {}
	virtual ~TreeNode() {
		if(left != this)
			delete left;
		if(right != this)
			delete right;
	}

	// Disallow (accidental) copying or moving:
	TreeNode(const TreeNode& copyFrom) = delete;
	TreeNode& operator=(const TreeNode& copyFrom) = delete;
	TreeNode(TreeNode&& moveFrom) = delete;
	TreeNode& operator=(TreeNode&& moveFrom) = delete;

public:
	void rotateLeft();
	TreeNode* minimum();
	TreeNode* maximum();
	TreeNode* predecessor();
	TreeNode* successor();

public:
	// optional, aber praktisch zum debuggen:
	friend std::ostream& operator<<(std::ostream& cout, const TreeNode* tree) {
		if(tree == nullptr) return cout; // nothing to print

		cout << tree->left << tree->key << ", " << tree->right;

		return cout;
	}

	bool isValid() const {
		if(left != nullptr) {
			if(left->parent != this)
				return false;
			
			if(!left->isValid())
				return false;
		}

		if(right != nullptr) {
			if(right->parent != this)
				return false;
			
			if(!right->isValid())
				return false;
		}

		return true;
	}
};


template<typename T>
class SearchTree {
	using Node = TreeNode<T>; // optional, Fuer uebersichtlichen Code

private:
	Node* root; // Wurzel (im Falle eines leeren Baumes: nullptr)

public:
	SearchTree(): root(nullptr) {	}
	virtual ~SearchTree() {
		delete root;
	}

	// Disallow (accidental) copying or moving:
	SearchTree(const SearchTree& copyFrom) = delete;
	SearchTree& operator=(const SearchTree& copyFrom) = delete;
	SearchTree(SearchTree&& moveFrom) = delete;
	SearchTree& operator=(SearchTree&& moveFrom) = delete;

private:
	void transplant(const Node *const nodeToReplace, Node *const replacementNode); // internally used by void delete_node(...)

public:
	void insert(const T key);
	void deleteNode(Node *const node); // "const Node *const node" nicht zulaessig, da node sonst nicht korrekt geloescht werden koennte
	Node* search(const T key);

	Node* minimum() { return root->minimum(); }
	Node* maximum() { return root->maximum(); }

public:
	// optional, aber praktisch zum debuggen:
	friend std::ostream& operator<<(std::ostream& cout, const SearchTree& tree) {
		// cout << tree.root; // markiert rootNode nicht
		cout << tree.root->left << "<" << tree.root->key << ">, " << tree.root->right; // markiert rootNode
		return cout;
	}

	// preorder-print:
	static void printSubtree(const Node* tree, const size_t depth) {
		if(tree == nullptr) return;

		for(size_t i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << tree->key << "\n";

		printSubtree(tree->right, depth + 1);

		printSubtree(tree->left, depth + 1);
	}

	// preorder-print:
	void print() const {
		printSubtree(root, 0);
	}

	bool isValid() const {
		if(root == nullptr)
			return true;

		if(root->parent != nullptr)
			return false;

		return root->isValid();
	}

	bool isEmpty() const {
		return root == nullptr;
	}
};

// Implementierungen der Funktionen koennen in separate Datei ausgelagert werden:
#include "SearchTree_impl.hpp"




/*
=======  Test-Programm  =======

#include <iostream>

#include "SearchTree.hpp"


int main(int argc, char** argv) {
	{
		// TreeNode<int> tree(5);
		SearchTree<int> tree;

		// Einfuegen:
		tree.insert(5);
		tree.insert(4);
		tree.insert(3);
		tree.insert(2);
		tree.insert(7);
		tree.insert(8);
		tree.insert(9);
		tree.insert(10);

		// Ausdrucken:
		std::cout << "Tree: " << tree << "\n"; // erwartet: 2, 3, 4, <5>, 7, 8, 9, 10,

		// Suchen:
		std::cout << "Searching 3, found: " << tree.search(3)->key << "\n";
		std::cout << "Searching 21 (not in list), found: " << (void*)tree.search(21) << "\n"; // Falls element nicht in Liste: nullptr

		// Loeschen:
		std::cout << "removing 8\n";
		tree.deleteNode(tree.search(8));
		std::cout << tree << "\n";

		std::cout << "removing 10\n";
		tree.deleteNode(tree.search(10));
		std::cout << tree << "\n";

		// Sonderfall: Wurzel loeschen:
		std::cout << "removing 5 (root node)\n";
		tree.deleteNode(tree.search(5));
		std::cout << tree << "\n";

		// Predecessor testen:
		std::cout << "removing element before 4 (3)\n";
		tree.deleteNode(tree.search(4)->predecessor());
		std::cout << tree << "\n";

		// Successor testen:
		std::cout << "removing element after 4 (7)\n";
		tree.deleteNode(tree.search(4)->successor());
		std::cout << tree << "\n";

		// <<--  Hier wird aufgrund des Scope-Endes automatisch der destruktor von tree aufgerufen
	}

	std::cout << "deleted tree, no errors occurred\n"; // Falls dieser text NICHT erscheint, dann ist das Programm im Destruktor von tree abgestuerzt

	return 0;
}

*/