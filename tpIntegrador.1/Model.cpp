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
	finish = false;
	fileRoute.clear();
	pathnames.clear();
	labels.clear();
	blockNames.clear();
	blockRoute.clear();
	cantOfFiles = 0;
	cantOfBlocks = 0;
}

void Model::reInitSearchFileFromFolder() {
	for (int a = 0; a < 50; a++) {
		pathLabel[a] = false;
		blocksLabel[a] = false;
	}
	fileElected = -1;
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
	for (int i = 0; i < cantOfFiles; i++)
		if (i != position)
			blocksLabel[i] = false;
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
				if ((*it).path().extension().string() == ".png") {
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
	}
}

void Model::validateBlockchainFiles() {
	for (int j = 0; j < cantOfFiles; j++) {
		if (!validateBlockchainFile(fileRoute[j])) {
			fileRoute.erase(fileRoute.begin() + j);
			pathnames.erase(pathnames.begin() + j);
			labels.erase(labels.begin() + j);	
		}
	}
}

bool Model::validateBlockchainFile(std::string fileName) {
	//Hacer toda la funcion de validacion
	return true;
}

void Model::findNumberOfBlocks() {

	blockNames.clear();
	blockRoute.clear();
	for (int a = 0; a < 50; a++)
		blocksLabel[a] = false;

	//Hacer la funcion que busca cantidad de bloque
	//Tiene que determinar:
	//					La cantidad de bloques(cantOfBlocks)
	//					Llenar un vector con la ruta de cada bloque para poder accederlos despues(blockRoute)
	//Estas dos cosas deben hacer sobre el elemento fileRoute[fileElected];


	//Para debuggear le digo que encontro 10, 20 o 30 bloques y que la ruta es simplemente un numero
	switch (fileElected) {
		case 0: case 1:case 2:case 3:case 4:
			cantOfBlocks = 10;
			break;
		case 5:case 6:case 7:case 8:
			cantOfBlocks = 20;
			break;
		case 9:case 10:case 11:case 12:
			cantOfBlocks = 30;
			break;
	}
	for (int i = 0; i < cantOfBlocks; i++) {
		std::string name = "Block " + std::to_string(i);
		blockNames.push_back(name);
		blockRoute.push_back(std::to_string(i));
	}
}

void Model::viewInformation() {

}

void Model::calculateMerkle() {

}

void Model::validateMerkle() {

}

void Model::watchMerkle() {

}