#include <iostream>
struct Station {
	std::string station_name;
	int num_workshop;
	int num_workshop_in_work;
	double station_efficiency;

};
Station Add_station();
void Show_station(Station station);