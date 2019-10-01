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
	void mkdir(string dirName, string currentFolder) {
		bool found = false;
		for (int i = 0; i < this->system.size(); i++) {
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

	void ls(string currentFolder) {
		for (int i = 0; i < this->system.size(); i++) {
			if (currentFolder == this->system[i].folder) {
				cout << this->system[i].subfolder << endl;
			}
		}
	}
	string cd(string dirName, string currentFolder) {
		bool found = false;
		for (int i = 0; i < this->system.size(); i++) {
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

};

void main() {
	cout << "Welcome in the terminal. Press 'q' to exit." << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;
	
	while (parancs != "q") {
		string autotext = "C:/" + CurrentFolder + ">";
		cout << autotext;
		cin >> parancs;
		if (parancs != "mkdir" && parancs != "q" && parancs != "ls" && parancs != "cd" && parancs != "cd..") {
			cout << "'" << parancs << "' is not recognized as an internal or external command, operable program or batch file." << endl;
		}
		if (parancs == "mkdir") {
			string dirname;
			cin >> dirname;
			d.mkdir(dirname, CurrentFolder);
		}
		if (parancs == "cd") {
			string dirname;
			cin >> dirname;
			if (dirname == "..") {
				if (CurrentFolder != "root") {
					int cut = CurrentFolder.find_last_of("/");
					CurrentFolder = CurrentFolder.substr(0, cut);
					cout << "\n ----------- \n" << CurrentFolder << "\n ------------ \n"; //Kizárólag debugolásra készült sor.
				}
				else {
					cout << "You're already in the root directory." << endl;
				}
			}
			else {
				CurrentFolder = d.cd(dirname, CurrentFolder);
			}
		}

		if (parancs == "ls") {
			d.ls(CurrentFolder);
		}
	}
}