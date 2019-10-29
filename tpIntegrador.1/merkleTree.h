#pragma once
#include <iostream>
#include <vector>

#define NO_TRANSACTION "Error en la transaccion"

class MerkleTree {
public:
	MerkleTree();
	void viewInformation(void);
	std::string calculateMerkle(std::vector<std::string>, int);
	void validateMerkle(void);
	void watchMerkle(void);

private:
	std::vector<std::string> leafs;
	int numberOfLeafs;

	//std::vector<unsigned int>* getTxidTransformed();
};