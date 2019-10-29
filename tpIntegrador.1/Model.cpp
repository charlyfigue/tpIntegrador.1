#include "Model.h"
#include <iostream>
#include <string>
//#include "json.hpp"

using namespace boost::filesystem;

Model::Model() {
	for (int a = 0; a < 50; a++) {
		pathLabel[a] = false;
		blocksLabel[a] = false;
	}
	fileElected = -1;
	blockElected = -1;
	finish = false;
	fileRoute.clear();
	pathnames.clear();
	labels.clear();
	blockNames.clear();
	//blockRoute.clear();
	cantOfFiles = 0;
	cantOfBlocks = 0;
}

void Model::reInitSearchFileFromFolder() {
	for (int a = 0; a < 50; a++) {
		pathLabel[a] = false;
		blocksLabel[a] = false;
	}
	fileElected = -1;
	blockElected = -1;
	cantOfBlocks = 0;
}

void Model::reInitSearchBlockFromFile() {
	//
}

void Model::fileChoosen(int position) {
	for (int i = 0; i < cantOfFiles; i++)
		if (i != position)
			pathLabel[i] = false;
}

void Model::blockChoosen(int position) {
	for (int i = 0; i < cantOfBlocks; i++)
		if (i != position)
			blocksLabel[i] = false;
	blockElected = position;
}

void Model::setFileChoseen(int position) {
	fileElected = position;
}

void Model::getFilesFromFolder(std::string path_t) {

	boost::filesystem::path p(path_t);

	if (path != path_t) {
		path = path_t;
		for (int a = 0; a < 50; a++)
			pathLabel[a] = false;
		fileRoute.clear();
		pathnames.clear();
		labels.clear();
		if (exists(p) && is_directory(p)) {
			for (directory_iterator it{ p }; it != directory_iterator{}; it++) {
				if ((*it).path().extension().string() == ".json") {
					fileRoute.push_back ((*it).path().string());
					pathnames.push_back((*it).path().filename().string());
				}
			}
			cantOfFiles = pathnames.size();
			for (int j = 0; j < cantOfFiles; j++) {
				labels.push_back(false);
			}
		}
		else
			cantOfFiles = 0;
		validateBlockchainFiles();
	}
}

void Model::validateBlockchainFiles() {
	int cont = 0;
	for (int j = cantOfFiles; j > 0; j--) {
		if (!validateBlockchainFile(fileRoute[j-1])) {
			if (j != 0) {
				fileRoute.erase(fileRoute.begin() + j - 1);
				pathnames.erase(pathnames.begin() + j - 1);
				labels.erase(labels.begin() + j - 1);
			}
			else {
				fileRoute.clear();
				pathnames.clear();
				labels.clear();
			}
			cont++;
		}
	}

	cantOfFiles -= cont;
}

bool Model::validateBlockchainFile(std::string fileName) {
	jsonHandl.jsonStartHandler(fileName);
	return (jsonHandl.existJsonBlock());
}

void Model::findNumberOfBlocks() {

	blockNames.clear();
	
	for (int a = 0; a < 50; a++)
		blocksLabel[a] = false;

	jsonHandl.jsonStartHandler(fileRoute[fileElected]);
	jsonHandl.setRouteOfJsonBlock();

	cantOfBlocks = jsonHandl.getCantOfBlocksFounded();
	//blockRoute = jsonHandl.getRoutesOfBlocks();
	
	//Para debuggear le digo que encontro 10, 20 o 30 bloques y que la ruta es simplemente un numero
	for (int i = 0; i < cantOfBlocks; i++) {
		std::string name = "Block " + std::to_string(i);
		blockNames.push_back(name);
	}
}

void Model::viewInformation() {
	information = jsonHandl.viewInformation(blockElected);
}

std::string Model::calculateMerkle() {
	std::vector<std::string> txidElements = jsonHandl.getTxidTransformed(blockElected);
	std::cout << "La cantidad de txid es: " << txidElements.size() << std::endl;
	return(tree.calculateMerkle(txidElements, jsonHandl.getCantOfTxid()));
}

void Model::validateMerkle() {
	std::string actual = getMerkle();
	std::string calculated = calculateMerkle();
	if (calculated == actual)
		validMessage =  "The actual merkleTree is valid";
	else {
		changeMerkle(calculated);
		validMessage = "The actual merkleTree is invalid. Proceeding to change it";
	}
}

void Model::changeMerkle(std::string calculated) {
	 jsonHandl.changeMerkle(calculated, blockElected);
}

std::string Model::getMerkle(void) {
	return (jsonHandl.findMerkle(blockElected));
}

void Model::watchMerkle() {
	tree.watchMerkle();
}