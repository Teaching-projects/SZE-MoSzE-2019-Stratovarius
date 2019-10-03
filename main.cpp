#include "Header.h"

void main() {
	cout << "Welcome in the terminal. Press 'q' to exit." << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;

	while (parancs != "q") {
		string autotext = "C:/" + CurrentFolder + ">";
		cout << autotext;
		cin >> parancs;
		if (parancs != "mkdir" && parancs != "q" && parancs != "ls" && parancs != "cd" && parancs != "cd.." && parancs != "rm") {
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
		if (parancs == "rm") {
			string dirname;
			cin >> dirname;
			d.rm(dirname, CurrentFolder);
		}
	}
}