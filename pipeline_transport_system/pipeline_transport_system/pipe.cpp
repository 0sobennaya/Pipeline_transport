#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utilities.h"
#include "pipe.h"


void Pipe::Add_pipe_without_diameter(int diameter) {
	std::cout << "Add the pipe name\n";
	std::cin >> std::ws;
	INPUT_LINE(std::cin, _pipe_name);

	std::cout << "Add the pipe length(km)\n";
	_pipe_length = Check_enter(1.0, 10000.0);

	_pipe_diameter = diameter;

	std::cout << "Add the pipe status (1 - works, 0 - in repair)\n";
	_status = Check_enter(0, 1);
}

void Pipe::Add_pipe() {
	std::cout << "Add the pipe name\n";
	std::cin >> std::ws;
	INPUT_LINE(std::cin, _pipe_name);

	std::cout << "Add the pipe length(km)\n";
	_pipe_length = Check_enter(1.0, 10000.0);

	std::cout << "Add the pipe diameter(mm)\n";
	int diameter = 0;
	std::cin >> diameter;
	std::cerr << diameter << std::endl;
	while (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
		std::cout << "Diameter should be 500,700,1000 or 1400" << std::endl;
		std::cin.ignore(1000, '\n');
		std::cin >> diameter;
		std::cerr << diameter << std::endl;
	}
	_pipe_diameter = diameter;

	std::cout << "Add the pipe status (1 - works, 0 - in repair)\n";
	_status = Check_enter(0, 1);
}

void Pipe::Print_pipe() {
	std::cout << "Pipe name:                               " << _pipe_name << "\n";
	std::cout << "Pipe length:                             " << _pipe_length << "\n";
	std::cout << "Pipe diameter:                           " << _pipe_diameter << "\n";
	std::cout << "Pipe status (1 - works, 0 - in repair):  " << _status << "\n\n" ;
}

void Pipe::Import_pipe(std::ostream& out) {
	out	<< _pipe_name << "\n"
		<< _pipe_length << "\n"
		<< _pipe_diameter << "\n"
		<< _status << "\n";
}

void Pipe::Export_pipe(std::ifstream& in) {
	in.ignore(1000, '\n');
	std::getline(in, _pipe_name);
	in >> _pipe_length >> _pipe_diameter >> _status;
}

const std::string Pipe::getName() const {
	return _pipe_name;
}

bool Pipe::getStatus() const {
	return _status;
}

int Pipe::getDiameter() const {
	return _pipe_diameter;
}

double Pipe::getLength() const {
	return _pipe_length;
}

double Pipe::getWeight() const {
	return _status ? _pipe_length : 0.0;
}
double Pipe::getCapacity() {
	int lenght = _pipe_length;
	double diameter = _pipe_diameter / 1000.0;
	int V = 10;

	double capacity = (V * 3.14 * diameter * diameter) * lenght / 4;

	return (_status ? capacity : 0.0);
}

void Pipe::setStatus(bool status) {
	if (status != 0 && status != 1) {
		std::cout << "Error, status should be 1 (works) or 0 (in repair)" << std::endl;
	}
	_status = status;
}

void Pipe::setName(std::string name) {
	if (name.empty()) {
		std::cout << "Error, name should be not empty" << std::endl;
		return;
	}
	_pipe_name = name;
}

void Pipe::setDiameter(int diameter) {
	if(diameter < 10  || diameter > 5000) {
		std::cout << "Error, diameter should be between 10 & 5000 mm" << std::endl;
	}
	_pipe_diameter = diameter;
}

void Pipe::setLength(double length) {
	if (length < 1.0 || length > 10000.0) {
		std::cout << "Error, length should be between 1.0 & 10000.0 km" << std::endl;
	}
	_pipe_length = length;
}