#include "merkleTree.h"

static unsigned int generateID(unsigned char *str);

MerkleTree::MerkleTree() {
	numberOfLeafs = 0;
	separator = SEPARADOR;
}

void MerkleTree::viewInformation() {

}

std::string MerkleTree::calculateMerkle(std::vector<std::string> txidElements, int cantidad) {
	leafs.clear();
	merkle.clear();
	if (cantidad) {
		for (int i = 0; i < cantidad; i++) {
			unsigned int newId = generateID((unsigned char*)(txidElements[i].c_str()));
			char change[20];
			sprintf(change, "%x", newId);
			std::string idChanged(change);
			leafs.push_back(idChanged);
		}
		leafs.push_back(separator);
		std::vector<std::string> resultado = recursiveTree(leafs);
		merkle = resultado;
		return resultado.back();
	}
	else {
		std::cout << "No hay transacciones para generar el arbol" << std::endl;
		merkle.push_back(NO_TRANSACTION);
		return NO_TRANSACTION;
	}
}

std::vector<std::string> MerkleTree::recursiveTree(std::vector<std::string> rama) {
	int cantidad = rama.size();
	int i = 0;
	std::vector<std::string> rama_sig;
	cantidad--;
	
	if (cantidad == 1) {
		rama_sig.push_back(rama[0]);
		return rama_sig;
	}
	else {
		if ((cantidad % 2) == 0) {
			while (i < cantidad) {
				unsigned int newId = generateID(((unsigned char*)((rama[i] + rama[i + 1]).c_str())));
				char change[20];
				sprintf(change, "%x", newId);
				std::string idChanged(change);
				rama_sig.push_back(idChanged);
				i = i + 2;
			}
		}
		else {
			std::string copia = rama[cantidad - 1];
			rama.insert(rama.end() - 1, copia);
			while (i < (cantidad+1)) {
				unsigned int newId = generateID(((unsigned char*)((rama[i] + rama[i + 1]).c_str())));
				char change[20];
				sprintf(change, "%x", newId);
				std::string idChanged(change);
				rama_sig.push_back(idChanged);
				i = i + 2;
			}
		}
		rama_sig.push_back(separator);
		std::vector<std::string> result = recursiveTree(rama_sig);
		
		int length = result.size();
		for (int ii = 0; ii < length; ii++)
			rama.push_back(result[ii]);

		return rama;
	}
}

static unsigned int generateID(unsigned char *str)
{
	unsigned int ID = 0;
	int c;
	while (c = *str++)
		ID = c + (ID << 6) + (ID << 16) - ID;
	return ID;
}