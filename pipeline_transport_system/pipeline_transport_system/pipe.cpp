#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utilities.h"
#include "pipe.h"

void Pipe::Add_pipe() {
	std::cout << "Add the pipe name\n";
	std::cin >> std::ws;
	std::getline(std::cin, _pipe_name);

	std::cout << "Add the pipe length(km)\n";
	pipe_length = Check_enter(1.0, 1000.0);

	std::cout << "Add the pipe diameter(mm)\n";
	pipe_diameter = Check_enter(10, 5000);

	std::cout << "Add the pipe status (1 - works, 0 - in repair)\n";
	status = Check_enter(0, 1);
}

void Pipe::Print_pipe() {
	std::cout << "Pipe name:                               " << _pipe_name << "\n";
	std::cout << "Pipe length:                             " << pipe_length << "\n";
	std::cout << "Pipe diameter:                           " << pipe_diameter << "\n";
	std::cout << "Pipe status (1 - works, 0 - in repair):  " << status << "\n\n" ;
}

bool Pipe::Has_pipe() {
	return (pipe_length != -1) ? true : false;
}

void Pipe::Edit_pipe() {
	if (Has_pipe()){
		std::cout << "\nDo you want to change the pipe status? (1 - yes, 0 - no)\n";
			if (Check_enter(0, 1) == 1) {
				status = !status;
			}
	}
	else {
		std::cout << "Erorr: there is no pipe to edit\n";
	}
}

void Pipe::Import_pipe(std::ostream& out) {
	out	<< _pipe_name << "\n"
		<< pipe_length << "\n"
		<< pipe_diameter << "\n"
		<< status << "\n";
}

void Pipe::Export_pipe(std::ifstream& in) {
	in.ignore(1000, '\n');
	std::getline(in, _pipe_name);
	in >> pipe_length >> pipe_diameter >> status;
}
