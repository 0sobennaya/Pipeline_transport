#include <iostream>
#include <fstream>
#include <string>

#include "utilities.h"
#include "station.h"

void Station::Add_station() {

	std::cout << "Add the station name\n";
	std::cin >> std::ws;
	std::getline(std::cin, _station_name);

	std::cout << "Add the number of workshops\n";
	num_workshop = Check_enter(1, 50);

	std::cout << "Add the number of workshops in work\n";
	num_workshop_in_work = Check_enter(0, num_workshop);
	
	std::cout << "Add the station efficiency (from 0.0 to 1.0)\n";
	station_efficiency = Check_enter(0.0, 1.0);

}

void Station::Print_station() {
	std::cout << "Station name:                            " << _station_name << "\n";
	std::cout << "Number of workshops:                     " << num_workshop << "\n";
	std::cout << "Number of workshops in work:             " << num_workshop_in_work << "\n";
	std::cout << "Station efficiency:                      " << station_efficiency << "\n\n";
	
}

bool Station::Has_station() {
	return (num_workshop != -1) ? true : false;
}

void Station::Import_station(std::ostream& out) {
	out << _station_name << "\n"
		<< num_workshop << "\n"
		<< num_workshop_in_work << "\n"
		<< station_efficiency << "\n";
}

void Station::Export_station(std::ifstream& in) {
	in.ignore(1000, '\n');
	std::getline(in, _station_name);
	in >> num_workshop >> num_workshop_in_work >> station_efficiency;
}


void Station::Edit_station() {
	if (Has_station()) {
		std::cout << "\nIf you want to start the workshop press 1, stop - 0" << "\n";
		int option = Check_enter(0, 1);
		if (num_workshop_in_work >= 1 && option == 0) {
			num_workshop_in_work--;
		}
		else if (num_workshop_in_work < num_workshop && option == 1) {
			num_workshop_in_work++;
		}
		else {
			std::cout << "Error, you cannot start/stop one more workshop\n";
		}
	}
	else {
		std::cout << "Erorr: there is no station to edit\n";
	}
}
