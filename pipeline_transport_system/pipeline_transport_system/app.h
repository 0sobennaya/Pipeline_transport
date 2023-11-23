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

		template<typename Type>
		const std::unordered_map<int, Type>& getAll() const;

		const std::unordered_map<int, Pipe> getPipes() const;
		const std::unordered_map<int, Station> getStations() const;

		
	private:
		unsigned int _PipeID = 1;
		unsigned int _StationID = 1;

		std::unordered_map<int, Pipe> _pipes;
		std::unordered_map<int, Station> _stations;
};

template <>
const std::unordered_map<int, Pipe>& App::getAll<Pipe>() const;

template <>
const std::unordered_map<int, Station>& App::getAll<Station>() const;
