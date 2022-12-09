#pragma once

#include "SearchTree.hpp"

#include <random>
#include <cstdint>
#include <unordered_set>


template<typename KEY_TYPE>
bool test_all_present(SearchTree<KEY_TYPE>& tree, const std::unordered_set<KEY_TYPE>& keys) {
	for(const KEY_TYPE& key : keys)
		if(tree.search(key) == nullptr)
			return false;
	return true;
}


// integer variant:
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
T generateKey() {
	static std::default_random_engine generator;
	std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	return distribution(generator);
}

// IEEE 754 variant:
template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
T generateKey() {
	static std::default_random_engine generator;
	std::uniform_real_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	return distribution(generator);
}