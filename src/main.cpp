#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../include/track.hpp"
#include "../include/token.hpp"

int parse_cue_file(char const * path);
std::vector<std::string> parse_line(std::string line);
std::vector<token> tokenize(std::vector<std::string> words);
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

std::vector<token> tokenize(std::vector<std::string> parsed_line)
{
	using namespace std;
	vector<token> result;
	for (string s: parsed_line) {
		if (s[0] == '"')
			result.push_back(token(false, s.substr(1, s.length() - 2)));
		else if (s[0] >= '0' && s[0] <= '9')
			result.push_back(token(false, s));
		else
			result.push_back(token(true, s));
	}

}

int parse_cue_file(char const * path)
{
	std::ifstream cue_file;
	cue_file.open(path);
	std::cout << path << std::endl;
	for (std::string line; std::getline(cue_file, line); ) {
		for (auto s: parse_line(line)) {
			std::cout << s << std::endl;
		}
	}

	return 0;
}

std::vector<std::string> parse_line(std::string line)
{
	using namespace std;

	vector<string> results;

	string current;
	bool in_string = false;

	for (auto c: line) {
		if (!in_string) {
			if (c == ' ' || c == '\n' || c == '\t') {
				if (current != "")
					results.push_back(current);
				current = "";
			}
		   	else if (c == '"') {
				in_string = true;
				current += c;
			}
		   	else {
				current += c;
			}
		}
		else {
			current += c;
			if (c == '"') {
				in_string = false;
				results.push_back(current);
				current = "";
			}
		}
	}
	
	if (current != "")
		results.push_back(current);

	return results;
}
