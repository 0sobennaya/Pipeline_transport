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
		std::cout << "Error: no file" << std::endl;
		return;
	}
	std::string s = ""; 
	if (s != "END") {
		for (s; s != "END"; std::getline(file, s)) {
			unsigned int id = 0;
			if (file.eof()) {
				std::cout << "Error: file is empty\n";
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
				std::cout<<"Unexpected error"<<std::endl;
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


Pipe& App::getPipeByID(int id) {
	auto it = _pipes.find(id);
	if (it == _pipes.end()) {
		std::cout << "Error: pipe is not found" << std::endl;
	}
	return it->second;
}

Station& App::getStationByID(int id) {
	auto it = _stations.find(id);
	if (it == _stations.end()) {
		std::cout << "Error: station is not found" << std::endl;
	}
	return it->second;
}

void App::Delete_pipe(int id) {
	auto it = _pipes.find(id);
	if (it == _pipes.end()) {
		std::cout << "Error: pipe is not found" << std::endl;
		return;
	}
	_pipes.erase(it);
}

void App::Delete_station(int id) {
	auto it = _stations.find(id);
	if (it == _stations.end()) {
		std::cout << "Error: station is not found" << std::endl;
		return;
	}
	_stations.erase(it);
}

std::vector<int> App::Search_by_status(bool status) {
	std::vector<int> result;

	for (const std::pair<int, Pipe> pair : _pipes) {
		if (pair.second.getStatus() == status) {
			result.push_back(pair.first);
		}
	}
	return result;
} 

std::vector<int> App::Search_by_workshops(float low_percent, float high_percent) {
	std::vector<int> result;
	for (std::pair<int, Station> pair : _stations) {
		float percent = getStationByID(pair.first).getNumWorkshopsInWork() * 100 / getStationByID(pair.first).getNumWorkshops();
		if (percent >= low_percent && percent <= high_percent) {
			result.push_back(pair.first);
		}
	}
	return result;
}

const std::unordered_map<int, Pipe> App::getPipes() const {
	return _pipes;
}
const std::unordered_map<int, Station> App::getStations() const {
	return _stations;
}
