#ifndef CMD_H
#define CMD_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Pair {
	string folder;
	string subfolder;
};

class Dictionary {
private:
	vector<Pair> system;
public:
	void mkdir(string dirName, string currentFolder);
	void ls(string currentFolder);
	string cd(string dirName, string currentFolder);
	void rm(string dirName, string currentFolder);
	void rmForce(string dirName, string currentFolder);
};

#endif