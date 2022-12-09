#pragma once

#include "test_insert_delete.hpp"
#include "test_aufgabe.hpp"

#include <stdexcept>


void test_all() {
	try {
		test_insert_delete();
		// test_aufgabe();
	} catch (const std::exception& e) {
		std::cout << "\n#### Testing Failed: " << e.what() << "\n";
	}
}