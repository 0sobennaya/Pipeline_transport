#include <unordered_map>
#include <fstream>

#include "utilities.h"
#include "app.h"


std::string get_filename() {
	std::string filename;
	std::cout << "Enter filename (filename.txt): " << std::endl;
	INPUT_LINE(std::cin, filename);
	return filename;
}

void App::Add_pipe() {
	Pipe pipe;
	pipe.Add_pipe();
	_pipes.insert({ _PipeID++, pipe });
}

void App::Add_pipe_withiout_diameter(int diameter) {
	Pipe pipe;
	pipe.Add_pipe_without_diameter(diameter);
	_pipes.insert({ _PipeID++,pipe });
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
		std::cout << "Error: cannot open file" << std::endl; 
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

	for (auto& [id, edge] : _edges) {
		file << "EDGE" << "\n";
		file << id << std::endl;
		file << edge.start << std::endl;
		file << edge.end << std::endl;
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
			else if (s == "EDGE") {
				Edge edge;
				file >> id;
				file >> edge.start >> edge.end;
				_edges.insert({ id,edge });
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
	if (_edges.contains(id)) {
		_edges.erase(id);
	}
	_pipes.erase(it);
}

void App::Delete_station(int id) {
	auto it = _stations.find(id);
	if (it == _stations.end()) {
		std::cout << "Error: station is not found" << std::endl;
		return;
	}
	std::vector<int> edges;
	for (auto& [edge_id, edge] : _edges) {
		if (edge.start == id || edge.end == id) {
			edges.push_back(edge_id);
		}
	}

	for (int id : edges) {
		Delete_edge(id);
	}
	_stations.erase(it);
}


const std::unordered_map<int, Pipe> App::getPipes() const {
	return _pipes;
}
const std::unordered_map<int, Station> App::getStations() const {
	return _stations;
}

template <>
const std::unordered_map<int, Pipe>& App::getAll<Pipe>() const {
	return _pipes;
}

template <>
const std::unordered_map<int, Station>& App::getAll<Station>() const {
	return _stations;
}