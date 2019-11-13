#include "cmd.h"
#include <iostream>
#include <fstream>
using namespace std;

void Dictionary::mkdir(string dirName, string currentFolder) {
	bool found = false;
	if (this->checkIfNameIsValid(dirName)) cout << "Name cannot contain special characters" << endl;
	else {
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (currentFolder == this->system[i].folder && dirName == this->system[i].subfolder) {
				found = true;
			}
		}
		for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
			if (dirName == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
				found = true;
			}
		}
		if (found) {
			cout << "This file/directory already exists" << endl;
		}
		else
		{
			if (dirName != "..") {
				this->addPairToVector(currentFolder, dirName);
			}
			else {
				cout << "Invalid foldername" << endl;
			}
		}
	}
	
}

void Dictionary::ls(string currentFolder) {
	
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (currentFolder == this->system[i].folder) {
			if(this->system[i].subfolder != "root")
			cout  <<this->system[i].subfolder << endl;
		}
	}
	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (currentFolder == this->fileDescriptorVector[i].filePath) {
			cout << this->fileDescriptorVector[i].fileName << endl;
		}
	}
}
string Dictionary::cd(string dirName, string currentFolder) {
	bool found = false;
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if ((currentFolder == this->system[i].folder) && (dirName == this->system[i].subfolder)) {
			currentFolder += "/" + dirName;
			found = true;
			break;
		}
	}
	if (found == false) {
		cout << "No such file in this directory." << endl;
	}
	return currentFolder;
}

void Dictionary::rm(string toDelete, string currentFolder) {
	bool found = false;

	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (toDelete == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
			found = true;
			this->fileDescriptorVector.erase(this->fileDescriptorVector.begin() + i);
			cout << "File has been deleted!" << endl;
		}
	}

	if (!found) {
		bool hasContent = false;
		string toDeleteAsFolder = currentFolder + "/" + toDelete;

		// vagy ha van file a mappaban
		for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
			if (toDeleteAsFolder == this->fileDescriptorVector[i].filePath) {
				hasContent = true;
			}
		}
		// vagy ha van almappaja
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (toDeleteAsFolder == this->system[i].folder) {
				hasContent = true;
			}
		}

		if (hasContent) {
			cout << "Cannot delete folder, it has content in it!" << endl;
		}
		else {
			// mappakent probaljuk megtalalni es torolni
			for (unsigned int i = 0; i < this->system.size(); i++) {
				if (currentFolder == this->system[i].folder && toDelete == this->system[i].subfolder) {
					found = true;
					this->system.erase(this->system.begin() + i);
				}
			}
			if (!found) {
				cout << "No such file/directory in this directory" << endl;
			}
		}
	}
}

void Dictionary::deleteRecursively(string toDelete, string currentFolder) {
	cout << "Directory is not empty, deleting content recursively ..." << endl;

	string toDeleteAsFolder = currentFolder + "/" + toDelete;

	// Fileokat
	vector<FileDescriptor> fileDescriptorVectorNew;
	for (unsigned int i = this->fileDescriptorVector.size(); i > 0; i--) {
		if (this->fileDescriptorVector[i - 1].filePath.find(toDeleteAsFolder) != std::string::npos) {
			cout << "Deleted:" << this->fileDescriptorVector[i - 1].fileName << endl;
		}
		else {
			FileDescriptor currentFileData;
			currentFileData.fileName = this->fileDescriptorVector[i - 1].fileName;
			currentFileData.filePath = this->fileDescriptorVector[i - 1].filePath;
			fileDescriptorVectorNew.push_back(currentFileData);
		}
	}
	this->fileDescriptorVector = fileDescriptorVectorNew;

	// Almappakat
	vector<Pair> subFolderVectorNew;
	for (unsigned int i = this->system.size(); i > 0; i--) {
		if (this->system[i - 1].folder.find(toDeleteAsFolder) != std::string::npos) {
			cout << "Deleted:" << this->system[i - 1].subfolder << endl;
		}
		else {
			Pair folderNew;
			folderNew.folder = this->system[i - 1].folder;
			folderNew.subfolder = this->system[i - 1].subfolder;
			subFolderVectorNew.push_back(folderNew);
		}
	}
	this->system = subFolderVectorNew;

	// Vegul a torlendo mappat
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (currentFolder == this->system[i].folder && toDelete == this->system[i].subfolder) {
			cout << "Deleted:" << this->system[i].subfolder << endl;
			this->system.erase(this->system.begin() + i);
		}
	}
}

void Dictionary::rmForce(string toDelete, string currentFolder) {
	bool found = false;

	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (toDelete == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
			found = true;
			this->fileDescriptorVector.erase(this->fileDescriptorVector.begin() + i);
			cout << "File has been deleted!" << endl;
		}
	}

	if (!found) {
		bool hasContent = false;
		string toDeleteAsFolder = currentFolder + "/" + toDelete;

		// vagy ha van file a mappaban
		for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
			if (toDeleteAsFolder == this->fileDescriptorVector[i].filePath) {
				hasContent = true;
			}
		}
		// vagy ha van almappaja
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (toDeleteAsFolder == this->system[i].folder) {
				hasContent = true;
			}
		}

		if (hasContent) {
			deleteRecursively(toDelete, currentFolder);
		}
		else {
			// mappakent probaljuk megtalalni es torolni
			for (unsigned int i = 0; i < this->system.size(); i++) {
				if (currentFolder == this->system[i].folder && toDelete == this->system[i].subfolder) {
					found = true;
					this->system.erase(this->system.begin() + i);
				}
			}
			if (!found) {
				cout << "No such file/directory in this directory" << endl;
			}
		}
	}
}
void Dictionary::touch(string fileName, string currentFolder) {
	bool found = false;
	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (fileName == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
			found = true;
		}
	}
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (fileName == this->system[i].subfolder && currentFolder == this->system[i].folder) {
			found = true;
		}
	}
	if (found) {
		cout << "This file/directory already exists" << endl;
	}
	else
	{
		if (fileName != "..") {
			FileDescriptor currentFileData;
			currentFileData.fileName = fileName;
			currentFileData.filePath = currentFolder;
			this->fileDescriptorVector.push_back(currentFileData);
		}
		else {
			cout << "Invalid filename" << endl;
		}
	}
	
}

void Dictionary::writeToFile(string fsname) {
	ofstream systemStructure;
	systemStructure.open(fsname + ".txt");
	for (unsigned int i = 0; i < this->system.size(); i++) {
		systemStructure << this->system[i].folder << "/" << this->system[i].subfolder << "\n";
	}
	systemStructure.close();
}

void Dictionary::loadFromFile(string fsname) {
	string line;
	Pair p;
	ifstream systemStructure(fsname+".txt");
	if (systemStructure.is_open())
	{
		while (getline(systemStructure, line))
		{
			p = this->splitStringFirstSlash(line);
			this->system.push_back(p);
		}
		systemStructure.close();
	}
}

void Dictionary::splitString(string &str, vector<string>& out, string delim) {
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void Dictionary::addPairToVector(string folder, string subfolder) {
	Pair p;
	p.folder = folder;
	p.subfolder = subfolder;
	this->system.push_back(p);
}

Pair Dictionary::splitStringFirstSlash(string line) {
	Pair p;
	string path = line;
	int cut = line.find_last_of("/");
	line = line.substr(cut + 1, line.size());
	path = path.substr(0, cut);
	p.subfolder = line;
	p.folder = path;
	return p;
}

bool Dictionary::checkIfNameIsValid(string dirName) {
	int i = 0;
	while (dirName[i]) {
		if (isalpha(dirName[i])) return false;
		i++;
	}
}
