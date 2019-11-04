#include "Block.h"

Block::Block(json::iterator begin_t, json::iterator end_t, int number) {
	end = end_t;
	begin = begin_t;
	name = "Block" + std::to_string(number);
	lookBlocksProperties = false;
	calculateMerkleRoot = false;
	validateMerkleRoot = false;
	watchMerkleRoot = false;
	actualizeProperties();
}

void Block::actualizeProperties(void) {
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "merkleroot") {
			merKleRoot = (it.value()).get<std::string>();
		}
		else if (it.key() == "blockid") {
			id = (it.value()).get<std::string>();
		}
		else if (it.key() == "previousblockid") {
			previousId = (it.value()).get<std::string>();
		}
		else if (it.key() == "nonce") {
			nonce = atoi((std::to_string((it.value()).get<int>())).c_str());
		}
		else if (it.key() == "height") {
			height = atoi((std::to_string((it.value()).get<int>())).c_str());
		}
		else if (it.key() == "nTx") {
			ntx = atoi((std::to_string((it.value()).get<int>())).c_str());
		}
	}
}

void Block::setMerkleRoot(std::string value) {
	merKleRoot = value;
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "merkleroot") {
			it.value() = value;
		}
	}
}

void Block::setNtx(int value) {
	ntx = value;
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "nTx") {
			it.value() = std::to_string(value);
		}
	}
}

void Block::setId(std::string value) {
	id = value;
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "blockid") {
			it.value() = value;
		}
	}
}

void Block::setPreviousId(std::string value) {
	previousId = value;
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "previousblockid") {
			it.value() = value;
		}
	}
}

void Block::setNonce(int value) {
	nonce = value;
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "nonce") {
			it.value() = std::to_string(value);
		}
	}
}

void Block::setHeight(int value) {
	height = value;
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "height") {
			it.value() = std::to_string(value);
		}
	}
}