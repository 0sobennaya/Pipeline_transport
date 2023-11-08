#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>

#include "app.h"
#include "pipe.h"
#include "station.h"
#include "utilities.h"

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

void print_search_menu() {
	std::cout << "Choose an action:\n";
	std::cout << "-----------------------\n";
	std::cout << "1. Search by name\n";
	std::cout << "2. Search by status\n";
	std::cout << "3. Search by id\n";
	std::cout << "0. Cancel\n";
	std::cout << ">\n";
}

void print_pipe_search() {
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
		if (input == "end") {
			break;
		}
		std::istringstream ss(input);
		int new_item;
		ss >> new_item;
		ids.insert(new_item);
	}
	return ids;
}

void search_pipe_menu(App& app) {
	print_search_menu();
	int option = Check_enter(0, 3);
	std::vector<int> result_id;

	switch (option) {
	case 1: {
		std::string name;
		std::cout << "Enter name: ";
		std::cin.ignore(100, '\n');
		std::getline(std::cin, name);
		result_id = Search_by_name(name, app.getPipes());
		break;
	}
	case 2:
		break;
	case 3: {
		std::cout << "Enter ids: ";
		std::unordered_set<int> ids = Input_sequence();
		result_id = Search_by_id(ids, app.getPipes());
		break;
	}
	
	}

	std::cout << "Found: " << result_id.size() << std::endl;

	do {
		print_pipe_search();
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
		case 2:{
			for (int id : result_id) {
				
				app.Delete_pipe(id);
			}
			return; 
		}
		case 3:
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
	std::cout << "\nSave successfully" << std::endl;
}

void Load_data(App& app) {
	app.Load();
	std::cout << "\nLoad successfully" << std::endl;
}


int main()
{
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
			//station.Edit_station();
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




