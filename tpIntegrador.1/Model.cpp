#include "Model.h"
#include <iostream>
#include <string>

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
	cantOfFiles = 0;
	cantOfBlocks = 0;
}

void Model::reInitSearchFileFromFolder() {
	for (int a = 0; a < 50; a++)
		pathLabel[a] = false;
}

void Model::fileChoosen(int position) {
	for (int i = 0; i < cantOfFiles; i++)
		if (i != position)
			pathLabel[i] = false;
}

void Model::setFileChosen(int position) {
	fileElected = position;
	findNumberOfBlocks();
}

void Model::blockChoosen(int position) {
	blockElected = position;
	getBlockOfGroup(blockElected)->actualizeProperties();
}

void Model::noShowBlock(int position) {
	blocksLabel[position] = false;
}

void Model::getFilesFromFolder(std::string path_t) {

	boost::filesystem::path p(path_t);

	if (path != path_t) {
		path = path_t;
		for (int a = 0; a < 50; a++)
			pathLabel[a] = false;
		fileRoute.clear();
		pathnames.clear();
		if (exists(p) && is_directory(p)) {
			for (directory_iterator it{ p }; it != directory_iterator{}; it++) {
				if ((*it).path().extension().string() == ".json") {
					if (validateBlockchainFile((*it).path().string())) {
						fileRoute.push_back((*it).path().string());
						pathnames.push_back((*it).path().filename().string());
					}
				}
			}
			cantOfFiles = pathnames.size();
		}
		else
			cantOfFiles = 0;
	}
}

bool Model::validateBlockchainFile(std::string fileName) {
	jsonHandl.jsonStartHandler(fileName);
	return (jsonHandl.existJsonBlock());
}

void Model::addBlocks() {
	vector<route>* groupOfBlocks = jsonHandl.getRoutesOfBlocks();
	for (int i = 0; i < (*groupOfBlocks).size(); i++) {
		Block newBlock((*groupOfBlocks)[i].begin, (*groupOfBlocks)[i].end, i);
		blocks.push_back(newBlock);
	}
}

void Model::findNumberOfBlocks() {
	blocks.clear();
	for (int a = 0; a < 50; a++)
		blocksLabel[a] = false;
	jsonHandl.jsonStartHandler(fileRoute[fileElected]);
	jsonHandl.setRouteOfJsonBlock();
	addBlocks();
	cantOfBlocks = jsonHandl.getCantOfBlocksFounded();
}

void Model::viewInformation() {
	information = "El merkleRoot es: " + (getBlockOfGroup(blockElected)->getMerkleRoot()) + "\n" +
		"La cantidad de transaccciones es: " + (std::to_string(getBlockOfGroup(blockElected)->getNtx())) + "\n" +
		"El ID es: " + (getBlockOfGroup(blockElected)->getId()) + "\n" +
		"El ID del anterior bloque es: " + (getBlockOfGroup(blockElected)->getPreviousId()) + "\n" +
		"El nonce es: " + (std::to_string(getBlockOfGroup(blockElected)->getNonce())) + "\n" +
		"El height del bloque es: " + (std::to_string(getBlockOfGroup(blockElected)->getHeight())) + "\n";
				
}

std::string Model::calculateMerkle() {
	std::vector<std::string> txidElements = jsonHandl.getTxidTransformed(blockElected);
	return(tree.calculateMerkle(txidElements, jsonHandl.getCantOfTxid()));
}

void Model::serMerkle(std::string value) {
	calculatedMerkle = value;
}

void Model::validateMerkle() {
	std::string actual = getBlockOfGroup(blockElected)->getMerkleRoot();
	std::string calculated = calculateMerkle();
	if (calculated == actual)
		validMessage =  "The actual merkleTree is valid";
	else {
		changeMerkle(calculated);
		validMessage = "The merkleTree was invalid. Modification updated";
	}
}

void Model::changeMerkle(std::string calculated) {
	 jsonHandl.changeMerkle(calculated, blockElected);
	 serMerkle(calculated);
}

void Model::watchMerkle() {
	calculateMerkle();
	//setOutputImage(tree.watchMerkle(calculateMerkle()));
	this->notifyAllObservers();
}