#pragma once
#include <iostream>
#include <unordered_map>

class Pipe {
	
public:

	void Add_pipe();
	void Add_pipe_without_diameter(int diameter);
	
	void Import_pipe(std::ostream& out);
	void Export_pipe(std::ifstream& in);

	void Print_pipe();

	const std::string getName() const;
	bool getStatus() const;
	int getDiameter() const;
	double getLength() const;

	double getWeight() const;

	double getCapacity();

	void setName(std::string name);
	void setStatus(bool status);
	void setDiameter(int diameter);
	void setLength(double length);

private:
	std::string _pipe_name;
	bool _status = false;
	int _pipe_diameter = 0;
	double _pipe_length = -1;
};


