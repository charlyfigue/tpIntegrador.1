#pragma once
#include "Subject.h"
#include "merkleTree.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "jsonHandler.h"

class Model : public Subject {
public:
	Model();
	void getFilesFromFolder(std::string newpath);
	void validateBlockchainFiles(void);
	bool isFinished() { return finish; }
	void reInitSearchFileFromFolder(void);
	void reInitSearchBlockFromFile(void);
	void fileChoosen(int position);
	void blockChoosen(int position);
	void findNumberOfBlocks(void);
	void setFileChoseen(int position);
	void viewInformation();
	void calculateMerkle();
	void validateMerkle();
	void watchMerkle();

	int getCantOfFiles() { return cantOfFiles; }
	std::vector<bool>* getLabels() { return &labels; }
	bool* getPathLabel() { return pathLabel; }
	bool* getBlocksLabel() { return blocksLabel; }
	std::vector<std::string>* getPathnames() { return &pathnames; }
	int getNumberOfBlocks() { return cantOfBlocks; }
	std::vector<std::string>* getBlockNames() { return &blockNames; }

private:
	MerkleTree tree;
	jsonHandler jsonHandl;
	std::string path;
	std::vector<std::string> fileRoute;
	std::vector<std::string> pathnames;
	std::vector<bool> labels;
	std::vector<std::string> blockNames;
	std::vector<route>* blockRoute;//std::vector<std::string> blockRoute;
	bool pathLabel[50];
	bool blocksLabel[50];
	int cantOfBlocks;
	int cantOfFiles;
	bool finish;
	int fileElected;

	bool validateBlockchainFile(std::string fileName);
};