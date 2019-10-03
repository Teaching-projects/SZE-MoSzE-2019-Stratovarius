#include "cmd.h"
using namespace std;

	void Dictionary::mkdir(string dirName, string currentFolder) {
		bool found = false;
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (currentFolder == this->system[i].folder && dirName == this->system[i].subfolder) {
				found = true;
			}
		}
		if (found) {
			cout << "This directory already exist" << endl;
		}
		if (dirName != "..") {
			Pair p;
			p.folder = currentFolder;
			p.subfolder = dirName;
			this->system.push_back(p);
		}
		else {
			cout << "Invalid foldername" << endl;
		}
	}

	void Dictionary::ls(string currentFolder) {
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (currentFolder == this->system[i].folder) {
				cout << this->system[i].subfolder << endl;
			}
		}
	}
	string Dictionary::cd(string dirName, string currentFolder) {
		bool found = false;
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (currentFolder == this->system[i].folder && dirName == this->system[i].subfolder) {
				currentFolder += "/" + dirName;
				found = true;
			}
		}
		if (found == false) {
			cout << "No such file in this directory" << endl;
		}
		//Todo ha a mappanev ua, akkor irja ki, hogy a mappanev ua
		return currentFolder;
	}
	void Dictionary::rm(string dirName, string currentFolder) {
		bool found = false;
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (currentFolder == this->system[i].folder && dirName == this->system[i].subfolder) {
				this->system.erase(this -> system.begin() + i);
				found = true;
			}
		}
		if (found == false) {
			cout << "No such file in this directory" << endl;
		}
	}



