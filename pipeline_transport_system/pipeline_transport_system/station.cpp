#include <iostream>
#include <fstream>
#include <string>

#include "utilities.h"
#include "station.h"

void Station::Add_station() {

	std::cout << "Add the station name\n";
	std::cin >> std::ws;
	INPUT_LINE(std::cin, _station_name);

	std::cout << "Add the number of workshops\n";
	_num_workshop = Check_enter(1, 500);

	std::cout << "Add the number of workshops in work\n";
	_num_workshop_in_work = Check_enter(0, _num_workshop);
	
	std::cout << "Add the station efficiency (from 0.0 to 100.0)\n";
	_station_efficiency = Check_enter(0.0, 100.0);

}

void Station::Print_station() {
	std::cout << "Station name:                            " << _station_name << "\n";
	std::cout << "Number of workshops:                     " << _num_workshop << "\n";
	std::cout << "Number of workshops in work:             " << _num_workshop_in_work << "\n";
	std::cout << "Station efficiency:                      " << _station_efficiency << "\n\n";
}

void Station::Import_station(std::ostream& out) {
	out << _station_name << "\n"
		<< _num_workshop << "\n"
		<< _num_workshop_in_work << "\n"
		<< _station_efficiency << "\n";
}

void Station::Export_station(std::ifstream& in) {
	in.ignore(1000, '\n');
	std::getline(in, _station_name);
	in >> _num_workshop >> _num_workshop_in_work >> _station_efficiency;
}

const std::string Station::getName() const {
	return _station_name;
}
int Station::getNumWorkshops() const {
	return _num_workshop;
}
int Station::getNumWorkshopsInWork() const {
	return _num_workshop_in_work;
}
double Station::getEfficiency() const {
	return _station_efficiency;
}

void Station::setName(std::string name) {
	if (name.empty()) {
		std::cout << "Error, name should be not empty" << std::endl;
		return;
	}
	_station_name = name;
}

void Station::setNumWorkhopsInWork(int workshops_in_work) {
	if (workshops_in_work < 0 || workshops_in_work > _num_workshop) {
		std::cout << "Error, number of workshops in work should be between 0 & stated number of workshops " << std::endl;
		return;
	}
	_num_workshop_in_work = workshops_in_work;
}

void Station::setNumWorkshops(int workshops) {
	if (workshops < 0 || workshops > 500 ) {
		std::cout << "Error, number of workshops in work should be between 0 & 500 " << std::endl;
		return;
	}
	_num_workshop = workshops;
}
void Station::setEfficiency(double efficiency) {
	if (efficiency < 0 || efficiency > 100.0) {
		std::cout << "Error, efficiency should be between 0.0 & 100.0 " << std::endl;
		return;
	}
	_station_efficiency = efficiency;
}
