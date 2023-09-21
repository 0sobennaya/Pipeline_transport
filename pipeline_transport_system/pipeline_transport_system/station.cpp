#include <iostream>
#include "station.h"
#include <string>
#include "Utilities.h"
#include <fstream>

Station Add_station() {
	std::cin.ignore(1000, '\n');
	Station station;

	std::cout << "Add the station name\n";
	std::getline(std::cin, station.station_name);

	std::cout << "Add the number of workshops\n";
	station.num_workshop = Check_enter(1, 50);

	std::cout << "Add the number of workshops in work\n";
	station.num_workshop_in_work = Check_enter(0, station.num_workshop);
	
	std::cout << "Add the station efficiency (from 0.0 to 1.0)\n";
	station.station_efficiency = Check_enter(0.0, 1.0);

	//std::cout << station.num_workshop << station.num_workshop_in_work << station.station_name;
	return station;
}
void Show_station(Station station) {
	std::cout << "\n---------------------Station--------------------\n";
	if (station.num_workshop != -1) {
		std::cout << "Station name:                            " << station.station_name << '\n';
		std::cout << "Number of workshops:                     " << station.num_workshop << '\n';
		std::cout << "Number of workshops in work:             " << station.num_workshop_in_work << '\n';
		std::cout << "Station efficiency:                      " << station.station_efficiency << '\n';
	}
	else {
		std::cout << "There is no station\n";
	}
}
void Edit_station(Station& station) {
	if ((station.num_workshop != -1)) {
		int start_stop;
		std::cout << "The number of workshops in work is " << station.num_workshop_in_work;
		std::cout << "\nIf you want to start the workshop press 1, stop - 0" << "\n";
		start_stop = Check_enter(0, 1);
		if (station.num_workshop_in_work >= 1 && start_stop == 0) {
			station.num_workshop_in_work--;
		}
		else if (station.num_workshop_in_work < station.num_workshop && start_stop == 1) {
			station.num_workshop_in_work++;
		}
		else {
			std::cout << "Error, you cannot start/stop one more workshop\n";
		}
		std::cout << "Now the number of workshops in work is " << station.num_workshop_in_work << "\n";
	}
	else {
		std::cout << "Erorr: there is no station to edit\n";
	}
}
void Save_station(Station& station) {
	if (station.num_workshop != -1) {
		std::ofstream file;
		file.open("station.txt", std::ios::out);
		if (file.is_open()) {
			file << station.station_name << "\n"
				<< station.num_workshop << "\n"
				<< station.num_workshop_in_work << "\n"
				<< station.station_efficiency;
		}
		file.close();
		std::cout << "The station was successfully saved\n";
	}
	else {
		std::cout << "Error: there is no station to save\n";
	}
}
void Load_station(Station& station) {
	std::ifstream file;
	file.open("station.txt", std::ios::in);
	if (file.is_open()) {
		if (file.peek() == EOF) {
			std::cout << "Error: there is no saved station\n";
		}
		else {
			std::string str;
			int i = 0;
			while (std::getline(file, str)) {
				if (i == 0) station.station_name = str;
				if (i == 1) station.num_workshop = std::stod(str);
				if (i == 2) station.num_workshop_in_work = std::stoi(str);
				if (i == 3) station.station_efficiency = std::stoi(str);
				i++;
			}

			file.close();
			std::cout << "The station was successfully loaded\n";
		}
		file.close();
	}
}