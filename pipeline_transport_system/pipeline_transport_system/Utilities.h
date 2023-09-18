#include <iostream>

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