#include <iostream>
#include "pipe.h"
#include <string>
#include "Utilities.h"

Pipe Add_pipe() {

	std::cin.ignore(1000, '\n');
	Pipe pipe;

	std::cout << "Add the pipe name\n";
	std::getline(std::cin, pipe.pipe_name);

	std::cout << "Add the pipe length\n";
	pipe.pipe_length = Check_enter(1.0, 1000.0);

	std::cout << "Add the pipe diameter\n";
	pipe.pipe_diameter = Check_enter(10, 5000);

	std::cout << "Add the pipe status (1 - works, 0 - in repair)\n";
	pipe.repair = Check_enter(0, 1);

	//std::cout << pipe.pipe_name << pipe.pipe_length << pipe.pipe_diameter;
	return pipe;
}
void Show_pipe(Pipe pipe) {
	std::cout << "Pipe name: " << pipe.pipe_name << '\n';
	std::cout << "Pipe length: " << pipe.pipe_length << '\n';
	std::cout << "Pipe diameter:  " << pipe.pipe_diameter << '\n';
	std::cout << "Pipe status (1 - works, 0 - in repair):  " << pipe.repair << '\n';
}