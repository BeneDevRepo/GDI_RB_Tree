#include <iostream>

// #include "SearchTree.hpp"
#include "SearchTree.hpp"

// #include "tests/test_all.hpp"


int main(int argc, char** argv) {
	// test_all();
	// return 0;
	
	{
		// TreeNode<int> tree(5);
		SearchTree<int> tree;

		// Einfuegen:
		tree.insert(5);
		tree.insert(7);
		tree.insert(8);
		tree.insert(10);
		tree.insert(2);
		tree.insert(4);
		tree.insert(3);
		tree.insert(9);

		// tree.print();
		// return 0;


		// Ausdrucken:

		std::cout << "Tree: " << tree << "\n"; // erwartet: 2, 3, 4, <5>, 7, 8, 9, 10,
		// std::cout << "Tree:\n";
		// tree.print();

		std::cout << "Rotate Left around 5:\n";
		tree.rotateLeft(tree.search(5));
		std::cout << "Tree: " << tree << "\n"; // erwartet: 2, 3, 4, <5>, 7, 8, 9, 10,
		// tree.print();

		std::cout << "Rotate Left around 7:\n";
		tree.rotateLeft(tree.search(7));
		std::cout << "Tree: " << tree << "\n"; // erwartet: 2, 3, 4, <5>, 7, 8, 9, 10,
		// tree.print();

		// Suchen:
		std::cout << "Searching 3, found: " << tree.search(3)->key << "\n";
		std::cout << "Searching 21 (not in list), found: " << (void*)tree.search(21) << "\n"; // Falls element nicht in Liste: nullptr

		// Loeschen:
		// std::cout << "removing 8\n";
		// tree.deleteNode(tree.search(8));
		// std::cout << tree << "\n";

		// std::cout << "removing 10\n";
		// tree.deleteNode(tree.search(10));
		// std::cout << tree << "\n";

		// // Sonderfall: Wurzel loeschen:
		// std::cout << "removing 5 (root node)\n";
		// tree.deleteNode(tree.search(5));
		// std::cout << tree << "\n";

		// Predecessor testen:
		// std::cout << "removing element before 4 (3)\n";
		// tree.deleteNode(tree.search(4)->predecessor());
		// std::cout << tree << "\n";

		// Successor testen:
		// std::cout << "removing element after 4 (7)\n";
		// tree.deleteNode(tree.search(4)->successor());
		// std::cout << tree << "\n";

		// <<--  Hier wird aufgrund des Scope-Endes automatisch der destruktor von tree aufgerufen
	}

	std::cout << "deleted tree, no errors occurred\n"; // Falls dieser text NICHT erscheint, dann ist das Programm im Destruktor von tree abgestuerzt

	return 0;
}