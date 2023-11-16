#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utilities.h"
#include "pipe.h"

void Pipe::Add_pipe() {
	std::cout << "Add the pipe name\n";
	std::cin >> std::ws;
	INPUT_LINE(std::cin, _pipe_name);

	std::cout << "Add the pipe length(km)\n";
	_pipe_length = Check_enter(1.0, 10000.0);

	std::cout << "Add the pipe diameter(mm)\n";
	_pipe_diameter = Check_enter(10, 5000);

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


void Pipe::setStatus(bool status) {
	_status = status;
}

void Pipe::setName(std::string name) {
	_pipe_name = name;
}

void Pipe::setDiameter(int diameter) {
	_pipe_diameter = diameter;
}

void Pipe::setLength(double length) {
	_pipe_length = length;
}