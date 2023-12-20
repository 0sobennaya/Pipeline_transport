#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>

#include <chrono>
#include <format>

#include "app.h"
#include "pipe.h"
#include "station.h"
#include "utilities.h"
#include "log.h"
#include "graph.h"

void print_menu() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Add the pipe\n";
	std::cout << "2. Add the station\n";
	std::cout << "3. Show all objects\n";
	std::cout << "4. Search pipes\n";
	std::cout << "5. Search stations\n";
	std::cout << "6. Graph\n";
	std::cout << "7. Save the info\n";
	std::cout << "8. Download the info\n";
	std::cout << "0. Exit\n";
	std::cout << ">\n";
}

void print_pipe_search() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Search by name\n";
	std::cout << "2. Search by status\n";
	std::cout << "3. Search by id\n";
	std::cout << "0. Cancel\n";
	std::cout << ">\n";
}

void print_station_search() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Search by name\n";
	std::cout << "2. Search by workshops\n";
	std::cout << "3. Search by id\n";
	std::cout << "0. Cancel\n";
	std::cout << ">\n";
}

void print_search_menu() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Print\n";
	std::cout << "2. Delete\n";
	std::cout << "3. Edit\n";
	std::cout << "0. Cancel\n";
	std::cout << ">\n";
}

void print_graph_menu() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Add edge\n";
	std::cout << "2. View all edges\n";
	std::cout << "3. Delete edge\n";
	std::cout << "4. Clear graph" << std::endl;
	std::cout << "5. Topological sort" << std::endl;
	std::cout << "6. Shortest path" << std::endl;
	std::cout << "7. Max flow" << std::endl;
	std::cout << "0. Cancel\n";
	std::cout << ">\n";
}

std::vector<int> search_pipe_by_diameter(App& app,int diameter) {
	std::vector<int> ids = search_by_filter<Pipe>(app,
		[diameter](const Pipe& pipe)
		{return pipe.getDiameter() == diameter; });
	return ids;
}


void Add_edge(App& app) {
	if (app.getStations().empty()) {
		std::cout << "There are no stations" << std::endl;
		return;
	}
	std::cout << "Enter station source: ";
	int start = Check_enter(0, app.getStationID());

	std::cout << "Enter station sink: ";
	int end = Check_enter(0, app.getStationID());
	if (start == end) {
		std::cout << "Source should be != sink" << std::endl;
		return;
	}
	if (!app.getStations().contains(start) || !app.getStations().contains(end)) {
		std::cout << "There are no stations with this ids" << std::endl;
		return;
	}

	std::cout << "Enter diameter of pipe: ";
	int diameter = 0;
	std::cin >> diameter;
	while (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
		std::cin.ignore(1000, '\n');
		std::cout << "Diameter should be 500, 700, 1000 or 1400" << std::endl;
		std::cin >> diameter;
	}
	auto ids = search_pipe_by_diameter(app, diameter);
	std::vector<int> free_pipes = app.getFreePipes(ids);
	if (free_pipes.empty()) {
		std::cout << "Do you want add new pipe? (yes or no) " << std::endl;

		std::string s = "";
		std::cin >> s;
		while (s != "yes" && s != "no") {
			std::cout << "The answer should be yes or no" << std::endl;
			std::cin >> s;
		}
		if (s == "yes") {
			app.Add_pipe_withiout_diameter(diameter);
			ids = search_pipe_by_diameter(app, diameter);
			free_pipes = app.getFreePipes(ids);
		}
		else {
			return;
		}
	}
	std::cout << "Found pipes with diameter = " << diameter << "\n" << std::endl;
	app.Print_free_pipes(free_pipes);

	std::cout << "\nEnter id pipe: ";
	int id = -1;
	bool status = false;
	while (!status) {
		std::cout << "The id number must be from the list" << std::endl;
		id = Check_enter(0, app.getPipeID());
		//status = find_id_in_array(id, free_pipes);
		for (int i = 0; i < free_pipes.size(); i++) {
			if (free_pipes[i] == id) {
				status = true;
			}
		}
	}

	app.Add_edge(id, start, end);
}

void Delete_edge(App& app) {
	std::cout << "Enter edge id: " << std::endl;
	int id = Check_enter(0, app.getStationID());
	app.Delete_edge(id);
}

void View_all_edges(App& app) {
	app.Print_edges();
}

void work_with_graph_menu(App& app) {
	int option = 0;
	
	do {
		print_graph_menu();
		option = Check_enter(0, 7);
		switch (option)
		{
		case 1:
			Add_edge(app);
			break;
		case 2:
			View_all_edges(app);
			break;
		case 3:
			Delete_edge(app);
			break;
		case 4: {
			app.getEdges().clear();
			std::cout << "Graph is clear" << std::endl;
			break;
		}
		case 5: {
			Graph graph(app);
			std::vector<int> result = graph.topologicalSort();
			for (int i = 0; i < result.size(); i++) {
				std::cout << result[i] << " ";
			}
			std::cout << std::endl;
		}
		case 6:{
			Graph graph(app);
			std::cout << "Enter start station: ";
			int start = Check_enter<int>(0, app.getStations().size());
			std::cout << "Enter end station: ";
			int end = Check_enter<int>(0, app.getStations().size());
			std::cout << "Shortest path from " << start << " to " << end << " = " << graph.shortest_path(app, start, end) << std::endl;

			break;
		}
		case 7:{
			Graph graph(app);
			std::cout << "Enter start station: ";
			int start = Check_enter<int>(0, app.getStations().size());
			std::cout << "Enter end station: ";
			int end = Check_enter<int>(0, app.getStations().size());
			std::cout << "Max flow from " << start << " to " << end << " = " << graph.dinitz_algorithm(app,start,end) << std::endl;
			break;
		}
		default:
			break;
		}
		
	} while (option != 0);
}




std::unordered_set<int> Input_sequence() {

	std::unordered_set<int> ids;
	std::string input;
	while (true) {
		std::cin >> std::ws;
		std::cin >> input;
		std::cerr << input << " ";
		if (input == "end") {
			std::cerr << std::endl;
			break;
		}
		std::istringstream ss(input);
		int new_item;
		ss >> new_item;
		ids.insert(new_item);
	}
	return ids;
}


void Delete_station_by_id(int id, App& app) {
	app.Delete_station(id);
}

void Search_station_by_workshops(App& app,std::vector<int>& result_id) {
	float low_percent, high_percent;
	std::cout << "Enter low percent: ";
	low_percent = Check_enter(0.0, 100.0);
	std::cout << "Enter high percent: ";
	high_percent = Check_enter(low_percent, (float)100.0);
	result_id = search_by_filter<Station>(app,
		[low_percent, high_percent](const Station& station){
			float percent = station.getNumWorkshopsInWork() * 100 / station.getNumWorkshops();
			return (percent >= low_percent && percent <= high_percent); 
		});
}



void Search_station_by_name(App& app, std::vector<int>& result_id) {
	std::string name;
	std::cout << "Enter name: ";
	std::cin.ignore(100, '\n');
	INPUT_LINE(std::cin, name);
	result_id = search_by_filter<Station>(app,
		[&name](const Station& station)
		{return (station.getName().find(name) != std::string::npos); });
}

void Search_station_by_id(App& app, std::vector<int>& result_id) {
	std::cout << "Enter a sequence ending with the word 'end'" << std::endl;
	std::cout << "Ids: ";
	std::unordered_set<int> ids = Input_sequence();
	result_id = Search_by_id(ids, app.getStations());
}

void Print_stations(App& app, std::vector<int>& result_id) {
	for (int id : result_id) {
		Station station = app.getStationByID(id);
		std::cout << "ID: " << id << std::endl;
		station.Print_station();
		std::cout << std::endl;
	}
}

void Delete_stations_by_id(App& app, std::vector<int>& result_id) {
	for (int id : result_id) {
		Delete_station_by_id(id, app);
	}
}

void Edit_stations(App& app, std::vector<int>& result_id) {
	float percent;
	std::cout << "Enter percent: ";
	percent = Check_enter(0.0, 100.0);
	for (int id : result_id) {
		Station& station = app.getStationByID(id);
		int new_number = station.getNumWorkshops() * percent / 100;
		station.setNumWorkhopsInWork((int)new_number);
	}
}

void search_station_menu(App& app) {
	print_station_search();
	int option = Check_enter(0, 3);
	std::vector<int> result_id;

	switch (option) {
	case 1: {
		Search_station_by_name(app, result_id);
		std::cout << "Found: " << result_id.size() << " objects" << std::endl;
		break;
	}
	case 2:
		Search_station_by_workshops(app, result_id);
		std::cout << "Found: " << result_id.size() << " objects" << std::endl;
		break;
	case 3: {
		Search_station_by_id(app, result_id);
		std::cout << "Found: " << result_id.size() << " objects" << std::endl;
		break;
	}
	case 0:
	default: {
		return;
	}
	}

	

	do {
		print_search_menu();
		option = Check_enter(0, 3);
		switch (option) {
		case 1:
			Print_stations(app, result_id);
			break;
		case 2:
			Delete_stations_by_id(app, result_id);
			return;
		case 3:
			Edit_stations(app, result_id);
			break;
		}
	} while (option != 0);
}

void Search_pipe_by_name(App& app, std::vector<int>& result_id) {
	std::string name;
	std::cout << "Enter name: ";
	std::cin.ignore(100, '\n');
	INPUT_LINE(std::cin, name);
	result_id = search_by_filter<Pipe>(app,
		[&name](const Pipe& pipe)
		{return (pipe.getName().find(name) != std::string::npos); });
}


void Search_pipe_by_status(App& app, std::vector<int>& result_id) {
	bool status;
	std::cout << "Enter status ( 1 - work, 0 - in repair ): ";
	status = Check_enter(0, 1);
	result_id = search_by_filter<Pipe>(app,
		[status](const Pipe& pipe)
		{ return pipe.getStatus() == status; });
}

void Search_pipe_by_id(App& app, std::vector<int>& result_id){
	std::cout << "Enter a sequence ending with the word 'end'" << std::endl;
	std::cout << "Ids: ";
	std::unordered_set<int> ids = Input_sequence();
	result_id = Search_by_id(ids, app.getPipes());
}

void Print_pipes(App& app, std::vector<int>& result_id) {
	for (int id : result_id) {
		Pipe pipe = app.getPipeByID(id);
		std::cout << "ID: " << id << std::endl;
		pipe.Print_pipe();
		std::cout << std::endl;
	}
}

void Delete_pipes_by_id(App& app, std::vector<int>& result_id) {
	for (int id : result_id) {
		app.Delete_pipe(id);
	}
}

void Edit_pipes(App& app, std::vector<int>& result_id) {
	bool status;
	std::cout << "Enter status ( 1 - works, 0 - in repair ): ";
	status = Check_enter(0, 1);
	for (int id : result_id) {
		app.getPipeByID(id).setStatus(status);
	}
}

void search_pipe_menu(App& app) {

	print_pipe_search();
	int option = Check_enter(0, 3);
	std::vector<int> result_id;

	switch (option) {
	case 1: {
		Search_pipe_by_name(app, result_id);
		std::cout << "Found: " << result_id.size() << std::endl;
		break;
	}
	case 2: {
		Search_pipe_by_status(app, result_id);
		std::cout << "Found: " << result_id.size() << std::endl;
		break;
	}
	case 3: {
		Search_pipe_by_id(app, result_id);
		std::cout << "Found: " << result_id.size() << " objects" << std::endl;
		break;
	}
	case 0:
	default: {
		return;
	}
	}

	

	do {
		print_search_menu();
		option = Check_enter(0, 3);
		switch (option) {
		case 1:
			Print_pipes(app, result_id);
			break;
		case 2:
			Delete_pipes_by_id(app, result_id);
			return; 
		case 3:
			Edit_pipes(app, result_id);
			break;
		}
	
	} while (option != 0 );
}

void Add_pipe(App& app) {
	app.Add_pipe();
}

void Add_station(App& app) {
	app.Add_station();
}


void View_all(App& app) {
	if (app.Data_emptpy()) {
		std::cout << "Data is empty" << std::endl;
	}
	app.Print_data();
}

void Save_data(App& app) {
	app.Save();
	std::cout << "Data saved successfully" << std::endl;
}

void Load_data(App& app) {
	app.Load();
	std::cout << "Data loaded successfully" << std::endl;
}


int main()
{
	redirect_output_wrapper cerr_out(std::cerr);
	std::string time = std::format("{:%d_%m_%Y %H_%M_%OS}", std::chrono::system_clock::now());
	std::ofstream logfile("log_" + time + ".txt");
	if (logfile){
		cerr_out.redirect(logfile);
	}
	App app;
	int variant;
	using ID = int;
	
	
	do {
		print_menu();

		variant = Check_enter(0, 8);

		switch (variant) {
		case 1:
			Add_pipe(app);
			break;
		case 2:
			Add_station(app);
			break;
		case 3:
			View_all(app);
			break;
		case 4:
			search_pipe_menu(app);
			break;
		case 5:
			search_station_menu(app);
			break;
		case 6:
			work_with_graph_menu(app);
			break;
		case 7:
			Save_data(app);
			break;
		case 8:
			Load_data(app);
			break;
		}

	} while (variant != 0 );
	return 0;
}




