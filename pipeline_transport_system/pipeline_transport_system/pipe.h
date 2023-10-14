#pragma once
#include <iostream>


class Pipe {


public:
	std::string pipe_name;
	double pipe_length = -1;
	int pipe_diameter;
	bool repair;

	void Add_pipe();
	bool Has_pipe();
	void Show_pipe();
	void Edit_pipe();
	void Import_pipe(std::ostream& out);
	void Export_pipe(std::istream& in);

private:
	

};


