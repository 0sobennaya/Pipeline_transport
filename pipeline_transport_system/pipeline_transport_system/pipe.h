#pragma once
#include <iostream>
#include <vector>

class Pipe {
	

public:

	static int MAXID;

	std::string pipe_name = "";
	double pipe_length = -1;
	int pipe_diameter = 0;
	bool repair = false;

	Pipe();
	bool Has_pipe();
	
	void Edit_pipe();
	void Import_pipe(std::ostream& out);
	void Export_pipe(std::istream& in);


	int getId() {
		return id;
	}
	
private:
	int id;

};

Pipe Add_pipe();
void Show_pipes(std::vector<Pipe>& pipes);

