#include <iostream>
#include "station.h"
#include <string>
#include "Utilities.h"

Station Add_station() {
	std::cin.ignore(1000, '\n');
	Station station;

	std::cout << "Add the station name\n";
	std::getline(std::cin, station.station_name);

	std::cout << "Add the number of workshops\n";
	station.num_workshop = Check_enter(1, 50);

	std::cout << "Add the number of workshops in work\n";
	station.num_workshop_in_work = Check_enter(1, 50);
	
	std::cout << "Add the station efficiency (from 0.0 to 1.0)\n";
	station.station_efficiency = Check_enter(0.0, 1.0);

	//std::cout << station.num_workshop << station.num_workshop_in_work << station.station_name;
	return station;
}
void Show_station(Station station) {
	std::cout << "Station name: " << station.station_name << '\n';
	std::cout << "Number of workshops: " << station.num_workshop<< '\n';
	std::cout << "Number of workshops in work:  " << station.num_workshop_in_work << '\n';
	std::cout << "Station efficiency:  " << station.station_efficiency << '\n';
}