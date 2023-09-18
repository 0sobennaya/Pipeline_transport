#include <iostream>
#include "pipe.h"
#include"station.h"
#include "Utilities.h"


void print_menu() {

	system("cls");
	std::cout << "Choose an action:\n";
	std::cout << "1. Add the pipe\n";
	std::cout << "2. Add the station\n";
	std::cout << "3. Show all objects\n";
	std::cout << "4. Edit the pipe\n";
	std::cout << "5. Edit the pipe\n";
	std::cout << "6. Save the info\n";
	std::cout << "7. download the info\n";
	std::cout << "0. Exit\n";
	std::cout << ">\n";
}

int get_variant() {
	int variant = Check_enter(0, 9);
	return variant;
}


int main()
{
	int variant;
	Pipe pipe;
	Station station;


	do {
		print_menu();
		variant = get_variant();

		switch (variant) {
		case 1:
			pipe = Add_pipe();
			break;
		case 2:
			station = Add_station();
			break;
		case 3:
			Show_pipe(pipe);
			Show_station(station);
			break;
		}
		if (variant != 0) {
			system("pause");
		}
	
	} while (variant != 0);
	return 0;
}




