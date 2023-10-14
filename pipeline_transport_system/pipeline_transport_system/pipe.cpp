#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Utilities.h"
#include "pipe.h"

int Pipe::MAXID = 0;

Pipe::Pipe() {
	id = MAXID++;
}

Pipe Add_pipe() {
	Pipe pipe;
	std::cout << "Add the pipe name\n";
	std::cin >> std::ws;
	std::getline(std::cin, pipe.pipe_name);

	std::cout << "Add the pipe length(km)\n";
	pipe.pipe_length = Check_enter(1.0, 1000.0);

	std::cout << "Add the pipe diameter(mm)\n";
	pipe.pipe_diameter = Check_enter(10, 5000);

	std::cout << "Add the pipe status (1 - works, 0 - in repair)\n";
	pipe.repair = Check_enter(0, 1);
	return pipe;
}

void Show_pipes(std::vector<Pipe>& pipes) {
	for (Pipe pipe : pipes) {
		std::cout << "ID:                                      " << pipe.getId() << "\n";
		std::cout << "Pipe name:                               " << pipe.pipe_name << "\n";
		std::cout << "Pipe length:                             " << pipe.pipe_length << "\n";
		std::cout << "Pipe diameter:                           " << pipe.pipe_diameter << "\n";
		std::cout << "Pipe status (1 - works, 0 - in repair):  " << pipe.repair << "\n\n" ;
	}
}

bool Pipe::Has_pipe() {
	return (pipe_length != -1) ? true : false;
}


void Pipe::Edit_pipe() {
	if (Has_pipe()){
		std::cout << "\nDo you want to change the pipe status? (1 - yes, 0 - no)\n";
			if (Check_enter(0, 1) == 1) {
				repair = !repair;
			}
	}
	else {
		std::cout << "Erorr: there is no pipe to edit\n";
	}
}

void Pipe::Import_pipe(std::ostream& out) {
	out << pipe_name << "\n"
		<< pipe_length << "\n"
		<< pipe_diameter << "\n"
		<< repair << "\n";
}

void Pipe::Export_pipe(std::istream& in) {
	std::getline(in, pipe_name);
	in >> pipe_length >> pipe_diameter >> repair;
}
