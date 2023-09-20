#include <iostream>
#include "pipe.h"
#include"station.h"
#include "Utilities.h"


void print_menu() {

	system("cls");
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Add the pipe\n";
	std::cout << "2. Add the station\n";
	std::cout << "3. Show all objects\n";
	std::cout << "4. Edit the pipe\n";
	std::cout << "5. Edit the station\n";
	std::cout << "6. Save the info\n";
	std::cout << "7. Download the info\n";
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
	int var_save;
	int var_load;

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
		case 4:
			Edit_pipe(pipe);
			break;
		case 5:
			Edit_station(station);
			break;
		case 6:
			std::cout << "Press 1 to save the pipe, 2 - to save the station, 3 - to save all\n";
			var_save = Check_enter(1, 3);
			switch (var_save)
			{ case 1:
				Save_pipe(pipe);
				break;
			case 2:
				Save_station(station);
				break;
			case 3:
				Save_pipe(pipe);
				Save_station(station);
				break;
			}
			break;
		case 7:
			std::cout << "Press 1 to load the pipe, 2 - to load the station, 3 - to load all\n";
			var_load = Check_enter(1, 3);
			switch (var_load)
			{
			case 1:
				Load_pipe(pipe);
				break;
			case 2:
				Load_station(station);
				break;
			case 3:
				Load_pipe(pipe);
				Load_station(station);
				break;
			}
			break;
		}

		if (variant != 0) {
			system("pause");
		}
	
	} while (variant != 0);
	return 0;
}




