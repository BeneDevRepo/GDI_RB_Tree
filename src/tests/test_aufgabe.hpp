#include "SearchTree.hpp"

#include "testing_general.hpp"

#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <random>
// #include <queue>


int test_aufgabe() {
	using KEY_TYPE = int;

	static constexpr size_t NUM_ENTRIES = 1000; // anzahl der Elemente, die gleichzietig im suchbaum sind
	static constexpr size_t NUM_REPEATS = 5 * 1000 * 1000; // anzahl der insert-delete zyklen

	size_t index = 0;
	KEY_TYPE zahlspeicher[NUM_ENTRIES]; // "queue"

	SearchTree<KEY_TYPE> tree;
	const auto genKey = generateKey<KEY_TYPE>; // quelle für Zufallszahlen


	// insert <NUM_ENTRIES> unique numbers into tree:
	for (size_t i = 0; i < NUM_ENTRIES; ) {
		const KEY_TYPE zufallszahl = genKey();

		bool doppelt = false;
		for (size_t j = 0; j < i; j++) { // alles nach i ist uninitialisierter Speicher
			if (zahlspeicher[j] == zufallszahl) {
				doppelt = true;
				break;
			}
		}

		if (doppelt == false) {
			zahlspeicher[i++] = zufallszahl;
			tree.insert(zufallszahl);
		}
	}

	std::cout << "Erste Ausgabe: " << tree << "\n";

	// replace a single element of the tree by a fresh random number <NUM_REPEATS> times:
	for (size_t k = 0; k < NUM_REPEATS; k++) {
		const KEY_TYPE zufallszahl = genKey();

		bool doppelt = false;
		for (size_t j = 0; j < NUM_ENTRIES; j++) {
			if (zahlspeicher[j] == zufallszahl) {
				doppelt = true;
				break;
			}
		}

		if (doppelt == false) {
			tree.deleteNode(tree.search(zahlspeicher[index]));
			zahlspeicher[index] = zufallszahl;
			tree.insert(zufallszahl);
			index++;
			index %= NUM_ENTRIES;
		}
	}

	std::cout << "Zweite Ausgabe: " << tree << "\n";
	return 0;
}