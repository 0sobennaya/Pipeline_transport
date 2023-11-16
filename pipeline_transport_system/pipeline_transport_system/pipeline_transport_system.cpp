﻿#include <iostream>
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

void print_menu() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Add the pipe\n";
	std::cout << "2. Add the station\n";
	std::cout << "3. Show all objects\n";
	std::cout << "4. Search pipes\n";
	std::cout << "5. Search stations\n";
	std::cout << "6. Save the info\n";
	std::cout << "7. Download the info\n";
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

void Delete_pipe_by_id(int id, App& app) {
	app.Delete_pipe(id);
}

void Delete_station_by_id(int id, App& app) {
	app.Delete_station(id);
}

std::vector<int> Search_pipe_by_status(bool status, App& app) {
	return app.Search_by_status(status);
}

std::vector<int> Search_station_by_workshops(float low_percent, float high_percent, App& app) {
	return app.Search_by_workshops(low_percent, high_percent);
}

void search_station_menu(App& app) {
	print_station_search();
	int option = Check_enter(0, 3);
	std::vector<int> result_id;

	switch (option) {
	case 1: {
		std::string name;
		std::cout << "Enter name: ";
		std::cin.ignore(100, '\n');
		INPUT_LINE(std::cin, name);
		result_id = Search_by_name(name, app.getStations());
		break;
	}
	case 2:
		float low_percent, high_percent;
		std::cout << "Enter low percent: ";
		low_percent = Check_enter(0.0, 100.0);
		std::cout << "Enter high percent: ";
		high_percent = Check_enter(low_percent, (float)100.0);
		result_id = Search_station_by_workshops(low_percent, high_percent, app);
		break;
	case 3: {
		std::cout << "Enter a sequence ending with the word 'end'" << std::endl;
		std::cout << "Ids: ";
		std::unordered_set<int> ids = Input_sequence();
		result_id = Search_by_id(ids, app.getStations());
		break;
	}
	}

	std::cout << "Found: " << result_id.size() << " objects" << std::endl;

	do {
		print_search_menu();
		option = Check_enter(0, 3);
		switch (option) {
		case 1:
			for (int id : result_id) {
				Station station = app.getStationByID(id);
				std::cout << "ID: " << id << std::endl;
				station.Print_station();
				std::cout << std::endl;
			}
			break;
		case 2:
			for (int id : result_id) {
				Delete_station_by_id(id, app);
			}
			return;
		case 3:
			float percent;
			std::cout << "Enter percent: ";
			percent = Check_enter(0.0, 100.0);
			for (int id : result_id) {
				Station& station = app.getStationByID(id);
				int new_number = station.getNumWorkshops() * percent / 100;
				station.setNumWorkhopsInWork((int)new_number);
			}
			break;
		}
	} while (option != 0);
}

void search_pipe_menu(App& app) {
	print_pipe_search();
	int option = Check_enter(0, 3);
	std::vector<int> result_id;

	switch (option) {
	case 1: {
		std::string name;
		std::cout << "Enter name: ";
		std::cin.ignore(100, '\n');
		INPUT_LINE(std::cin, name);
		result_id = Search_by_name(name, app.getPipes());
		break;
	}
	case 2: {
		bool status;
		std::cout << "Enter status ( 1 - work, 0 - in repair ): ";
		status = Check_enter(0, 1);
		result_id = Search_pipe_by_status(status, app);
		break;
	}
	case 3: {
		std::cout << "Enter a sequence ending with the word 'end'" << std::endl;
		std::cout << "Ids: ";
		std::unordered_set<int> ids = Input_sequence();
		result_id = Search_by_id(ids, app.getPipes());
		break;
	}
	}

	std::cout << "Found: " << result_id.size() << std::endl;

	do {
		print_search_menu();
		option = Check_enter(0, 3);
		switch (option) {
		case 1:
			for (int id : result_id) {
				Pipe pipe = app.getPipeByID(id);
				std::cout << "ID: " << id << std::endl;
				pipe.Print_pipe();
				std::cout << std::endl;
			}
			break;
		case 2:
			for (int id : result_id) {
				Delete_pipe_by_id(id, app);
			}
			return; 
		case 3:
			bool status;
			std::cout << "Enter status ( 1 - works, 0 - in repair ): ";
			status = Check_enter(0, 1);
			for (int id : result_id) {
				app.getPipeByID(id).setStatus(status);
			}
			break;
		}
	
	} while (option != 0);
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

		variant = Check_enter(0, 7);

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
			Save_data(app);
			break;
		case 7:
			Load_data(app);
			break;
		}
	} while (variant != 0);
	return 0;
}




