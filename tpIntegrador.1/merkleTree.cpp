#include "merkleTree.h"

static unsigned int generateID(unsigned char *str);

MerkleTree::MerkleTree() {
	numberOfLeafs = 0;
}

void MerkleTree::viewInformation() {

}

std::string MerkleTree::calculateMerkle(std::vector<std::string> txidElements, int cantidad) {
	numberOfLeafs = 0;
	if (cantidad) {
		for (int i = 0; i < cantidad; i++) {
			unsigned int newId = generateID((unsigned char*)(txidElements[i].c_str()));
			char change[20];
			sprintf(change, "%x", newId);
			std::string idChanged(change);
			numberOfLeafs++;
			leafs.push_back(idChanged);
		}
		return leafs.back();
	}
	else {
		std::cout << "No hay transacciones para generar el arbol" << std::endl;
		return NO_TRANSACTION;
	}
	
}

//std::vector<unsigned int>* MerkleTree::getTxidTransformed() {

//}

void MerkleTree::validateMerkle() {

}

void MerkleTree::watchMerkle() {

}

static unsigned int generateID(unsigned char *str)
{
	unsigned int ID = 0;
	int c;
	while (c = *str++)
		ID = c + (ID << 6) + (ID << 16) - ID;
	return ID;
}