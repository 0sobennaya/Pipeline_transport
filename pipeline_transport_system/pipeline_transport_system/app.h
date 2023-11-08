#pragma once
#include <unordered_map>

#include "pipe.h"
#include "station.h"

class App {
	public:
		void Add_pipe();
		void Add_station();
		void Print_data();

		void Save();
		void Load();

		bool Data_emptpy();

		Pipe getPipeByID(int id) {
			auto it = _pipes.find(id);
			if (it == _pipes.end()) {
				std::cout << "Error" << std::endl;
			}
			return it->second;
		}

		void Delete_pipe(int id) {
			auto it = _pipes.find(id);
			if (it == _pipes.end()) {
				std::cout << "Error" << std::endl;
				return;
			}
			_pipes.erase(it);
		}

		void Delete_station(int id) {
			auto it = _stations.find(id);
			if (it == _stations.end()) {
				std::cout << "Error" << std::endl;
				return;
			}
			_stations.erase(it);
		}

		const std::unordered_map<int, Pipe> getPipes() const {
			return _pipes;
		}
		const std::unordered_map<int, Station> getStations() const {
			return _stations;
		}

	private:
		unsigned int _PipeID = 0;
		unsigned int _StationID = 0;

		std::unordered_map<int, Pipe> _pipes;
		std::unordered_map<int, Station> _stations;
};

