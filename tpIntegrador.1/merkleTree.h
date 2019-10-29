#pragma once
#include <iostream>
#include <vector>

class MerkleTree {
public:
	MerkleTree();
	void viewInformation(void);
	void calculateMerkle(std::vector<std::string>, int);
	void validateMerkle(void);
	void watchMerkle(void);

private:
	std::vector<std::string> leafs;
	int numberOfLeafs;

	//std::vector<unsigned int>* getTxidTransformed();
};