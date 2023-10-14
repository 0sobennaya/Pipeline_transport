#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "pipe.h"
#include "station.h"
#include "Utilities.h"


void print_menu() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Add the pipe\n";
	std::cout << "2. Add the station\n";
	std::cout << "3. Show all objects\n";
	std::cout << "4. Edit the pipe\n";
	std::cout << "5. Edit the station\n";
	std::cout << "6. Save the info\n";
	std::cout << "7. Download the info\n";
	std::cout << "0. Exit\n";
	std::cout << ">\n";
}



void Save(Pipe& pipe, Station& station) {
	std::ofstream file("data.txt");
	if (!file) {
		std::cout << "Error";
		return;
	}
	if (pipe.Has_pipe()) {
		file << "PIPES" << "\n";
		pipe.Import_pipe(file);
	}
	if (station.Has_station()) {	
		file << "STATIONS" << "\n";
		station.Import_station(file);
	}
	file << "END";

	file.close();
}

void View_all(std::vector<Pipe>& pipes, std::vector<Station>& stations) {
	std::cout << "\tPipes\n";
	if (pipes.size() != 0) {
		Show_pipes(pipes);
	}
	else {
		std::cout << "there is no pipes\n";
	}

	std::cout << "\tStations\n";
	if (stations.size() != 0) {
		Show_stations(stations);
	}
	else {
		std::cout << "there is no stations\n";
	}
}

void Load(Pipe& pipe, Station& station) {
	std::ifstream file("data.txt");
	std::string s = ""; std::getline(file, s);
	if ( s!= "END") {
		for (s; s != "END"; std::getline(file, s)) {
			if (file.eof()) {
				std::cout << "Error\n";
				return;
			}
			if (s == "") {
				continue;
			}
			if (s == "PIPES") {
				pipe.Export_pipe(file);
			}
			if (s == "STATIONS") {
				station.Export_station(file);
			}

		}
	}
	else {
		std::cout << "Error\n";
	}

	file.close();
}


int main()
{
	int variant;
	std::vector<Pipe> pipes;
	std::vector<Station> stations;
	
	do {
		print_menu();

		variant = Check_enter(0, 7);

		switch (variant) {
		case 1:
			pipes.push_back(Add_pipe());
			break;
		case 2:
			stations.push_back(Add_station());
			break;
		case 3:
			View_all(pipes, stations);
			break;
		case 4:
			//pipe.Edit_pipe();
			break;
		case 5:
			//station.Edit_station();
			break;
		case 6:
			//Save(pipe, station);
			break;
		case 7:
			//Load(pipe, station);
			break;
		}
	} while (variant != 0);
	return 0;
}




