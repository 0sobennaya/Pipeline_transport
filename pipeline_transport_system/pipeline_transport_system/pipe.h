#pragma once
#include <iostream>
#include <unordered_map>

class Pipe {
	

public:

	double pipe_length = -1;
	int pipe_diameter = 0;
	bool status = false;

	bool Has_pipe();

	void Add_pipe();
	
	void Edit_pipe();
	void Import_pipe(std::ostream& out);
	void Export_pipe(std::ifstream& in);
	void Print_pipe();

	const std::string getName() const {
		return _pipe_name;
	}

	void setName(std::string name) {
		_pipe_name = name;
	}
	
private:
	std::string _pipe_name;

};


