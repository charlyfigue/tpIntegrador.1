#pragma once
#include "Subject.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

class Model : public Subject {
public:
	Model();
	void getFilesFromFolder(std::string newpath);
	void validateBlockchainFiles(void);
	bool isFinished() { return finish; }
	void reInitSearchFileFromFolder(void);
	void fileChoosen(int position);

	int getCantOfFiles() { return cantOfFiles; }
	std::vector<bool>* getLabels() { return &labels; }
	bool* getLabel() { return label; }
	std::vector<std::string>* getPathnames() { return &pathnames; }

private:
	std::string path;
	std::vector<std::string> fileRoute;
	std::vector<std::string> pathnames;
	std::vector<bool> labels;
	bool label[50];
	//bool lookProperties;
	int cantOfFiles;
	bool finish;

	bool validateBlockchainFile(std::string fileName);
};