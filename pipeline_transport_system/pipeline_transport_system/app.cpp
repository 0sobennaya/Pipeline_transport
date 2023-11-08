#include <unordered_map>
#include <fstream>

#include "utilities.h"
#include "app.h"


std::string get_filename() {
	std::string filename;
	std::cout << "Enter filename (filename.txt): " << std::endl;
	std::cin >> filename;
	return filename;
}

void App::Add_pipe() {
	Pipe pipe;
	pipe.Add_pipe();
	_pipes.insert({ _PipeID++, pipe });
}

void App::Add_station() {
	Station station;
	station.Add_station();
	_stations.insert({ _StationID++, station });
}

void App::Print_data() {
	
	for (std::pair<int, Pipe> pair : _pipes) {
		std::cout << "Pipe\n" << std::endl;
		std::cout << "ID: " << pair.first << std::endl;
		pair.second.Print_pipe();
	}
		
	for (std::pair<int, Station> pair : _stations) {
		std::cout << "Station\n" << std::endl;
		std::cout << "ID: " << pair.first << std::endl;
		pair.second.Print_station();
	}
		
}

void App::Save() {
	std::ofstream file(get_filename());
	if (!file) {
		std::cout << "Error";
		return;
	}

	for (std::pair<int, Pipe> pair : _pipes) {
		file << "PIPES" << "\n";
		file << pair.first << std::endl;
		pair.second.Import_pipe(file);
	}
	
	for (std::pair<int, Station> pair : _stations) {
		file << "STATIONS" << "\n";
		file << pair.first << std::endl;
		pair.second.Import_station(file);
	}
	
	file << "END";

	file.close();
}
                                                                                                        






void App::Load(){
	std::ifstream file(get_filename());
	if (!file) {
		std::cout << "Error" << std::endl;
		return;
	}
	std::string s = ""; 
	if (s != "END") {
		for (s; s != "END"; std::getline(file, s)) {
			unsigned int id = 0;
			if (file.eof()) {
				std::cout << "Error\n";
				return;
			}
			if (s == "") {
				continue;
			}
			if (s == "PIPES") {
				Pipe pipe;
				file >> id;
				pipe.Export_pipe(file);
				_pipes.insert({ id, pipe });
				_PipeID = std::max(_PipeID, id) + 1;
			}
			else if (s == "STATIONS") {
				Station station;
				file >> id;
				station.Export_station(file);
				_stations.insert({ id, station });
				_StationID = std::max(_StationID, id) + 1;
			}
			else {
				std::cout<<"error"<<std::endl;
			}
		}
	}
	
	else {
		std::cout << "Error\n" << std::endl;
		return;
	}

	file.close();
}

bool App::Data_emptpy() {
	return (_pipes.empty() && _stations.empty());
}
