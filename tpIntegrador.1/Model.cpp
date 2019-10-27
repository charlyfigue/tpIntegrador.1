#include "Model.h"
#include <iostream>

using namespace boost::filesystem;

Model::Model() {
	for (int a = 0; a < 50; a++)
		label[a] = false;
	finish = false;
	fileRoute.clear();
	pathnames.clear();
	labels.clear();
	cantOfFiles = 0;
}

void Model::reInitSearchFileFromFolder() {
	for (int a = 0; a < 50; a++)
		label[a] = false;
}

void Model::fileChoosen(int position) {
	for (int i = 0; i < cantOfFiles; i++)
		if (i != position)
			label[i] = false;
}

void Model::getFilesFromFolder(std::string path_t) {

	boost::filesystem::path p(path_t);

	if (path != path_t) {
		path = path_t;
		for (int a = 0; a < 50; a++)
			label[a] = false;
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

