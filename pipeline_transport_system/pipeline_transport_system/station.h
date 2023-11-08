#pragma once
#include <iostream>
#include <unordered_map>

class Station {

public:

	int num_workshop = -1;
	int num_workshop_in_work;
	double station_efficiency; 

	bool Has_station();

	void Add_station();
	void Edit_station();
	void Import_station(std::ostream& out);
	void Export_station(std::ifstream& in);
	void Print_station();

	const std::string getName() {
		return _station_name;
	}

	void setName(std::string name) {
		_station_name = name;
	}

private:
	std::string _station_name;
};
