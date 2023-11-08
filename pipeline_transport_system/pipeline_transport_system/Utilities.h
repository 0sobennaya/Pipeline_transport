#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

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
	return x;
}

template <typename T>
std::vector<int> Search_by_id(std::unordered_set<int>& ids, const std::unordered_map<int, T>& objects) {
	std::vector<int> result;
	for (int id : ids) {
		if (objects.find(id) != objects.end()) {
			result.push_back(id);
		}
	}
	return result;
}

template <typename T>
std::vector<int> Search_by_name(std::string& name, const std::unordered_map<int, T>& objects) {
	std::vector<int> result;
	std::string::size_type n;

	for (const std::pair<int, T> pair : objects) {
		n = pair.second.getName().find(name);
		if (std::string::npos != n) {
			result.push_back(pair.first);
		}
	}

	return result;
}



