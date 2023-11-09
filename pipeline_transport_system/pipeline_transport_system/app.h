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

		Pipe& getPipeByID(int id);
		Station& getStationByID(int id);

		void Delete_pipe(int id);
		void Delete_station(int id);

		std::vector<int> Search_by_status(bool status);
		std::vector<int> Search_by_workshops(float low_percent, float high_percent);


		const std::unordered_map<int, Pipe> getPipes() const;
		const std::unordered_map<int, Station> getStations() const;

		
	private:
		unsigned int _PipeID = 0;
		unsigned int _StationID = 0;

		std::unordered_map<int, Pipe> _pipes;
		std::unordered_map<int, Station> _stations;
};

