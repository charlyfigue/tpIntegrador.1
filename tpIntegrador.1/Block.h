#pragma once
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

class Block {
public:
	Block(json::iterator begin_t, json::iterator end_t, int number);
	void actualizeProperties(void);

	void setLookProperties(bool value) { lookBlocksProperties = value; }
	void setCalculatedMerkle(bool value) { calculateMerkleRoot = value; }
	void setValidatedMerkle(bool value) { validateMerkleRoot = value; }
	void setWatchMerkle(bool value) { watchMerkleRoot = value; }

	void setMerkleRoot(std::string value);
	void setNtx(int value);
	void setId(std::string value);
	void setPreviousId(std::string value);
	void setNonce(int value);
	void setHeight(int value);

	bool getLookProperties(void) { return lookBlocksProperties; }
	bool getCalculatedMerkle(void) { return calculateMerkleRoot; }
	bool getValidatedMerkle(void) { return validateMerkleRoot; }
	bool getWatchMerkle(void) { return  watchMerkleRoot; }

	std::string getMerkleRoot(void) { return merKleRoot; }
	int getNtx(void) { return ntx; }
	std::string getId(void) { return id; }
	std::string getPreviousId(void) { return previousId; }
	int getNonce(void) { return nonce; }
	int getHeight(void) { return height; }

	std::string getBlockName() { return name; }

private:
	bool lookBlocksProperties;
	bool calculateMerkleRoot;
	bool validateMerkleRoot;
	bool watchMerkleRoot;
	std::string name;
	json::iterator begin;
	json::iterator end;

	std::string merKleRoot;
	std::string id;
	std::string previousId;
	int nonce;
	int height;
	int ntx;
};