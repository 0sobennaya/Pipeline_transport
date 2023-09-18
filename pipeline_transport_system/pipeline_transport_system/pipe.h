#include <iostream>

struct Pipe {
	std::string pipe_name;
	double pipe_length;
	int pipe_diameter;
	bool repair;
};

Pipe Add_pipe();
void Show_pipe(Pipe pipe);