#pragma once
#include <iostream>


class Station {

public:

	std::string station_name;
	int num_workshop = -1;
	int num_workshop_in_work;
	double station_efficiency;

	void Add_station();
	void Show_station();
	bool Has_station();
	void Edit_station();
	void Import_station(std::ostream& out);
	void Export_station(std::istream& in);

private:

};
