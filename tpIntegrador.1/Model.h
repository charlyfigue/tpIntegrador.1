#pragma once
#include "Subject.h"
#include "merkleTree.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "jsonHandler.h"
#include "Block.h"

class Model : public Subject {
public:
	Model();
	void getFilesFromFolder(std::string newpath);
	bool isFinished() { return finish; }
	void reInitSearchFileFromFolder(void);
	
	void fileChoosen(int position);
	void blockChoosen(int position);
	void setFileChosen(int position);
	void viewInformation();
	std::string calculateMerkle();
	void validateMerkle();
	void watchMerkle();
	void changeMerkle(std::string calculated);
	void noShowBlock(int j);

	void setOutputImage(ALLEGRO_BITMAP* output_t) { output = output_t; }

	int getCantOfFiles() { return cantOfFiles; }
	std::vector<bool>* getLabels() { return &labels; }
	bool* getPathLabel() { return pathLabel; }
	bool* getBlocksLabel() { return blocksLabel; }
	std::vector<std::string>* getPathnames() { return &pathnames; }

	int getNumberOfBlocks() { return cantOfBlocks; }
	std::string getMerkle() { return calculatedMerkle; }
	std::vector<std::string> getMerkleVector() { return tree.getMerkleVector(); }
	std::string getValidMessage() {return validMessage;}
	std::string getInformationMessage() { return information; }
	ALLEGRO_BITMAP* getOutputImage() { return output; }
	Block* getBlockOfGroup(int position) { return &(blocks[position]); }

	void serMerkle(std::string);

private:
	std::string path;									//Path de la carpeta en la cual estoy
	std::vector<std::string> fileRoute;					//Vector con las rutas de acceso a cada archivo que se peuede abrir
	std::vector<std::string> pathnames;					//Vector con el nombre de cada archivo que puede abirse
	
	MerkleTree tree;
	jsonHandler jsonHandl;

	ALLEGRO_BITMAP* output;
	std::string calculatedMerkle;
	std::string validMessage;
	std::string information;
	std::vector<bool> labels;
	std::vector<Block> blocks;
	bool pathLabel[50];
	bool blocksLabel[50];
	int cantOfBlocks;
	int cantOfFiles;
	bool finish;
	int fileElected;
	int blockElected;

	bool validateBlockchainFile(std::string fileName);
	void findNumberOfBlocks(void);
	void addBlocks(void);
};