#pragma once
#include <iostream>
#include <unordered_map>

class Station {

public:

	bool Has_station();
	void Add_station();

	void Import_station(std::ostream& out);
	void Export_station(std::ifstream& in);

	void Print_station();

	const std::string getName() const;
	int getNumWorkshops() const;
	int getNumWorkshopsInWork() const;
	double getEfficiency() const;

	void setName(std::string name);
	void setNumWorkhopsInWork(int workshops_in_work) ;
	void setNumWorkshops(int wokrshops);
	void setEfficiency(double efficiency);
	
private:
	std::string _station_name;
	int _num_workshop;
	int _num_workshop_in_work;
	double _station_efficiency;
};
