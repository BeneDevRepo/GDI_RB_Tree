#pragma once

#include "SearchTree.hpp"

#include "testing_general.hpp"

#include <queue>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <stdexcept>
#include <string>



/**
 * this function tests Searchtree in 6 Steps:
 * 1. insert <NUM_INITIAL_KEYS> unique values
 * 2. test that all initial values are actually present in the tree
 * 3. insert, check, and delete <NUM_INSERT_DELETE_CYCLE_ENTRIES> values in a loop <NUM_INSERT_DELETE_CYCLES> times
 * 4. test that all initial values are still present in the tree
 * 5. remove all initial values from the tree in the order they were inserted
 * 6. check if the tree is completely empty, as it should be
*/
void test_insert_delete() {
	using KEY_TYPE = float; // Datentyp der Testwerte

	constexpr size_t NUM_INITIAL_KEYS = 1000 * 10; // Anzahl Start-elemente im Baum
	constexpr size_t NUM_INSERT_DELETE_CYCLES = 1000; // Anzahl insert-delete zyklen
	constexpr size_t NUM_INSERT_DELETE_CYCLE_ENTRIES = 1000;  // Anzahl an Elementen, die pro Zyklus eingefügt und wieder entfernt werden

	std::queue<KEY_TYPE> initial_values; // queue holding every initially inserted value in insertion order
	std::unordered_set<KEY_TYPE> all_values; // set containing every inserted value at any given point


	const auto genKey = generateKey<KEY_TYPE>;

	std::cout << "Running test_insert_delete...\n";


	std::cout << "Inserting initial data...\n";
	SearchTree<KEY_TYPE> tree;

	for(size_t i = 0; i < NUM_INITIAL_KEYS; ) {
		const KEY_TYPE key = genKey();

		if(all_values.find(key) != all_values.end()) // Zufallszahl wurde bereits verwendet
			continue; // try again

		i++;
		tree.insert(key);
		initial_values.push(key);
		all_values.insert(key);
	}

	// check if tree is in a valid state:
	if(!tree.isValid())
		throw std::runtime_error("test_queue failed: tree is invalid after inserting initial values!");


	std::cout << "Searching for every initially inserted value...  ";
	if(!test_all_present(tree, all_values))
		throw std::runtime_error("test_queue failed: 1 inserted item not found in tree");
	std::cout << "SUCCESS\n";


	std::cout << "Testing repeated random inserts and deletes...  ";
	KEY_TYPE cycle_values[NUM_INSERT_DELETE_CYCLE_ENTRIES];
	for(size_t cycle = 0; cycle < NUM_INSERT_DELETE_CYCLES; cycle++) {
		// insert:
		for(size_t i = 0; i < NUM_INSERT_DELETE_CYCLE_ENTRIES; i++) {
			const KEY_TYPE key = genKey();

			if(all_values.find(key) != all_values.end()) { // Zufallszahl wurde bereits verwendet
				i--;
				continue; // try again
			}

			cycle_values[i] = key;

			tree.insert(key);
			all_values.insert(key);
		}

		// delete:
		for(size_t i = 0; i < NUM_INSERT_DELETE_CYCLE_ENTRIES; i++) {
			const KEY_TYPE key = cycle_values[i];

			if(tree.search(key) == nullptr)
				throw std::runtime_error("test_queue failed: 2 inserted item not found in tree");

			tree.deleteNode(tree.search(key));
			all_values.erase(key);
		}

		// check if tree is in a valid state:
		if(!tree.isValid())
			throw std::runtime_error("test_queue failed: tree entered invalid state after " + std::to_string(cycle) + " insert-delete-cycles!");
	}
	std::cout << "SUCCESS\n";


	std::cout << "Searching for every initially inserted value...  ";
	if(!test_all_present(tree, all_values))
		throw std::runtime_error("test_queue failed: 3 inserted item not found in tree");
	std::cout << "SUCCESS\n";


	std::cout << "Removing initial items one by one...  ";
	for(; !initial_values.empty(); initial_values.pop()) {
		const KEY_TYPE key = initial_values.front();

		const auto node = tree.search(key);

		if(node == nullptr)
			throw std::runtime_error("test_queue: could not remove initial item because it got lost");

		tree.deleteNode(node);
		all_values.erase(key);
	}
	std::cout << "SUCCESS\n";



	std::cout << "Testing if tree is actually empty...  ";
	if(!tree.isEmpty())
		throw std::runtime_error("tree is not empty after deleting all elements");
	std::cout << "SUCCESS\n";


	std::cout << "Test \"random queue-set-checked inserts\" completed.\n";
}