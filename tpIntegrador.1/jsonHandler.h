#pragma once
//#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Block.h"

class jsonHandler;

using json = nlohmann::json;
using namespace std;

typedef struct {
	json::iterator begin;
	json::iterator end;
} route;

class jsonHandler : public json
{
public:
	void jsonStartHandler(string route);
	void getJson(void);
	bool existJsonBlock();
	bool existJsonElementBlock(json::iterator begin, json::iterator end);
	bool existJsonTransactionBlock(json::iterator begin, json::iterator end);
	bool existJsonTransactonVoutBlock(json::iterator begin, json::iterator end);
	bool existJsonTransactonVinBlock(json::iterator begin, json::iterator end);
	void setRouteOfJsonBlock(void);
	std::vector<std::string> getTxidTransformed(int blockElected);
	std::string findMerkle(int blockElected);
	void changeMerkle(std::string calculated, int blockElected);
	
	std::string getInformation(std::string target, int position);
	int getCantOfBlocksFounded() { return blocksFounded; }
	vector<route>* getRoutesOfBlocks() { return &routesOfBlocks; }
	int getCantOfTxid() { return cantOfTxid; }

private:
	json j;
	vector<string> blocks;
	vector<route> routesOfBlocks;
	vector<string> tweet;
	vector<string> date;
	int blocksFounded;
	int cantOfTxid;
};
