#pragma once
#include <iostream>
#include <vector>

class Station {

public:

	static int MAXID;

	std::string station_name;
	int num_workshop = -1;
	int num_workshop_in_work;
	double station_efficiency; 

	Station();
	bool Has_station();

	void Edit_station();
	void Import_station(std::ostream& out);
	void Export_station(std::istream& in);

	int getId() {
		return id;
	}


private:
	int id;
};
Station Add_station();
void Show_stations(std::vector<Station>& stations);