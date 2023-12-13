#pragma once
#include <unordered_map>

#include "pipe.h"
#include "station.h"

struct Edge {
	int start;
	int end;
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

		void Add_edge(int pipe_id, int start, int end) {
			Edge edge{ start,end };
			_edges.insert({ pipe_id,edge });
		}

		void Delete_edge(int id) {
			auto it = _edges.find(id);
			if (it == _edges.end()) {
				std::cout << "There are no edges with this id" << std::endl;
				return;
			}
			_edges.erase(id);
		}

		void Print_edges() {
			if (!_edges.empty()) {
				for (auto& [id, edge] : _edges) {
					std::cout << "Edge ID = " << id << std::endl;
					std::cout << "Source : " << edge.start << "   Sink : " << edge.end << std::endl;
					std::cout << std::endl;
				}
			}
			else{
				std::cout << "There are no edges" << std::endl;

			}
		}

		std::vector<int> getFreePipes(std::vector<int>& ids) {
			std::vector<int> free_pipes;
			for (int id : ids) {
				if (!_edges.contains(id)) {
					free_pipes.push_back(id);
				}
			}
			return free_pipes;
		}

		void Print_free_pipes(std::vector<int>& ids) {
			for (int id : ids) {
				auto it = _pipes.find(id);
				if (it != _pipes.end()) {
					std::cout << "ID: " << it->first << std::endl;
					Pipe pipe = it->second;
					pipe.Print_pipe();
				
				}
			}
		}

		void Delete_pipe(int id);
		void Delete_station(int id);

		template<typename Type>
		const std::unordered_map<int, Type>& getAll() const;

		const std::unordered_map<int, Pipe> getPipes() const;
		const std::unordered_map<int, Station> getStations() const;

		std::unordered_map<int, Edge>& getEdges() {
			return _edges;
		}

		const int getPipeID() const {
			return _PipeID;
		}
		const int getStationID() const {
			return _StationID;
		}

		
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
