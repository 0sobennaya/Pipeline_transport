#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>

#include "log.h"
#include "app.h"

template <typename Type>
Type Check_enter(Type low, Type high) {
	Type x;
	std::cin >> x;
	while (std::cin.fail() || std::cin.peek() != '\n' || x<low || x > high) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Error, please, try again\n";
		std::cin >> x;
	}
	std::cerr << x << std::endl;
	return x;
}

template <typename Type>
std::vector<int> Search_by_id(std::unordered_set<int>& ids, const std::unordered_map<int, Type>& objects) {
	std::vector<int> result;
	for (int id : ids) {
		if (objects.find(id) != objects.end()) {
			result.push_back(id);
		}
	}
	return result;
}

template<typename Type>
using Filter = std::function<bool(const Type& obj)>;

template <typename Type>
static std::vector<int> search_by_filter(const App& app, const Filter<Type>& f) {
	std::vector<int> result;
	const auto& objects = app.getAll<Type>();
	for (const auto& [id, obj] : objects) {
		if (f(obj)) {
			result.push_back(id);
		}
	}
	return result;
}