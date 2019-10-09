#include "cmd.h"

bool validcommand(string command) {
	bool valid = false;
	vector<string> commands = { "mkdir","q","ls","cd","rm","touch" };
	for (unsigned int i = 0; i < commands.size(); i++) {
		if (command == commands[i]) {
			valid = true;
		}
	}
	return valid;
}

int main() {
	cout << "Welcome in the terminal. Press 'q' to exit." << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;

	while (parancs != "q") {
		string autotext = "C:/" + CurrentFolder + ">";
		cout << autotext;
		cin >> parancs;
		if (!validcommand(parancs)) {
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
			if (dirname == "-rf") {
				cin >> dirname;
				d.rmForce(dirname, CurrentFolder);
			}
			else d.rm(dirname, CurrentFolder);
		}
		if (parancs == "touch") {
			string fileName;
			cin >> fileName;
			d.touch(fileName, CurrentFolder);
		}
	}
	return 0;
}