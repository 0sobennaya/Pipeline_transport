#include <iostream>

struct Pipe {
	std::string pipe_name;
	double pipe_length = -1;
	int pipe_diameter;
	bool repair;

};

Pipe Add_pipe();
void Show_pipe(Pipe pipe);
void Edit_pipe(Pipe& pipe);
void Save_pipe(Pipe& pipe);
void Load_pipe(Pipe& pipe);
