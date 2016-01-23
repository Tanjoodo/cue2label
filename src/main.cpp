#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../include/track.hpp"
#include "../include/token.hpp"
#include "../include/interpreter.hpp"

std::vector<track>  parse_cue_file(char const * path);
int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cout << 
			"usage: cue2label <cue file location> <label file location>\n";
		return -1;
	}

	parse_cue_file(argv[1]);

	return  0;
}


std::vector<track> parse_cue_file(char const * path)
{
	std::ifstream cue_file;
	cue_file.open(path);
	std::vector<std::string> file;
	for (std::string line; std::getline(cue_file, line);)
		file.push_back(line);

	interpreter interp(file);

	return interp.track_list;
}
