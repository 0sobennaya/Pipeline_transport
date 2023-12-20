#pragma once
#include <unordered_map>

#include "pipe.h"
#include "station.h"

struct Edge {
	int start;
	int end;
	double weight;
	double capacity;
};

class App {
	public:
		void Add_pipe();
		void Add_pipe_withiout_diameter(int diameter);
		void Add_station();
		void Print_data();

		void Save();
		void Load();

		bool Data_emptpy();

		Pipe& getPipeByID(int id);
		Station& getStationByID(int id);

		void Add_edge(int pipe_id, int start, int end);
		void Delete_edge(int id);

		void Print_edges();

		std::vector<int> getFreePipes(std::vector<int>& ids);

		void Print_free_pipes(std::vector<int>& ids);

		void Delete_pipe(int id);
		void Delete_station(int id);

		template<typename Type>
		const std::unordered_map<int, Type>& getAll() const;

		std::unordered_map<int, Pipe> getPipes() const;
		std::unordered_map<int, Station> getStations() const;

		std::unordered_map<int, Edge>& getEdges();

		const int getPipeID() const;
		
		const int getStationID() const;

		
	private:
		unsigned int _PipeID = 1;
		unsigned int _StationID = 1;

		std::unordered_map<int, Pipe> _pipes;
		std::unordered_map<int, Station> _stations;
		std::unordered_map<int, Edge> _edges;
};

template <>
const std::unordered_map<int, Pipe>& App::getAll<Pipe>() const;

template <>
const std::unordered_map<int, Station>& App::getAll<Station>() const;
