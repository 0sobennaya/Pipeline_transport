#include <iostream>
#include "pipe.h"
#include <string>
#include "Utilities.h"
#include <fstream>
//#include "conio.h"
//#include <sstream>

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
	std::cout << "---------------------Pipe-----------------------\n";
	if (pipe.pipe_length != -1) {
		std::cout << "Pipe name:                               " << pipe.pipe_name << '\n';
		std::cout << "Pipe length:                             " << pipe.pipe_length << '\n';
		std::cout << "Pipe diameter:                           " << pipe.pipe_diameter << '\n';
		std::cout << "Pipe status (1 - works, 0 - in repair):  " << pipe.repair << '\n';
	}
	else {
		std::cout << "There is no pipe";
	}
}
void Edit_pipe(Pipe& pipe) {
	std::cout << "The pipe status (1 - works, 0 - in repair):  " << pipe.repair;
	std::cout << "\nDo you want to change the pipe status? (1 - yes, 0 - no)\n";
	int choice;
	choice = Check_enter(0, 1);
	if (choice == 1) {
		pipe.repair = !pipe.repair;
	}
	std::cout << "New pipe status (1 - works, 0 - in repair):  " << pipe.repair << "\n";
}
void Save_pipe(Pipe& pipe) {
	if (pipe.pipe_length != -1) {
		std::ofstream file;
		file.open("pipe.txt", std::ios::out);
		if (file.is_open()) {
			file << pipe.pipe_name << "\n"
				<< pipe.pipe_length << "\n"
				<< pipe.pipe_diameter << "\n"
				<< pipe.repair;
		}
		file.close();
		std::cout << "The pipe was successfully saved\n";
	}
	else {
		std::cout << "Error: there is no pipe to save\n";
	}
}
void Load_pipe(Pipe& pipe) {
	std::ifstream file;
	file.open("pipe.txt", std::ios::in);
	
	if (file.is_open()) {
		if (file.peek() == EOF) {
			std::cout << "Error: there is no saved pipe\n";
		}
		else {
			std::string str;
			int i = 0;
			while (std::getline(file, str)) {
				if (i == 0) pipe.pipe_name = str;
				if (i == 1) pipe.pipe_length = std::stod(str);
				if (i == 2) pipe.pipe_diameter = std::stoi(str);
				if (i == 3) pipe.repair = std::stoi(str);
				i++;
			}

			file.close();
			std::cout << "The pipe was successfully loaded\n";
		}
		file.close();
	}
	
}