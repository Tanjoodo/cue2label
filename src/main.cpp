#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "../include/track.hpp"
#include "../include/token.hpp"
#include "../include/interpreter.hpp"

std::vector<track>  parse_cue_file(char const *path);
void write_label_file(std::vector<track> track_list,
                      char const *path,
					  int total_length_min,
					  int total_length_sec);

int main(int argc, char **argv)
{
	if (argc < 5) {
		std::cout << 
			"usage: cue2label <cue file location> <label file location> <length of sound file in the format mm ss>\n";
		return -1;
	}

	int min, sec;
	std::istringstream ss(argv[3]);
	ss >> min;

	ss = std::istringstream(argv[4]);
	ss >> sec;

	std::vector<track> track_list = parse_cue_file(argv[1]);
	write_label_file(track_list, argv[2], min, sec);
		
	return  0;
}


std::vector<track> parse_cue_file(char const *path)
{
	std::ifstream cue_file;
	cue_file.open(path);
	std::vector<std::string> file;
	for (std::string line; std::getline(cue_file, line);)
		file.push_back(line);

	cue_file.close();

	interpreter interp(file);


	return interp.track_list;
}

void write_label_file(std::vector<track> track_list,
                      char const *path,
					  int total_length_min,
					  int total_length_sec)
{
	std::ofstream label_file;
	label_file << std::fixed << std::setprecision(5);
	label_file.open(path);
	for (unsigned int i = 0; i < track_list.size(); ++i) {
		label_file << track_list[i].ind.seconds + track_list[i].ind.frames / 75.0 
                   << '\t';

			if ( i + 1 < track_list.size())
				label_file << track_list[i+1].ind.seconds
								+ track_list[i+1].ind.frames / 75.0
						   << '\t';
			else
				label_file << (double)total_length_min * 60 + total_length_sec << '\t';
		label_file << track_list[i].title << '\n';

	}

	label_file.close();
}
