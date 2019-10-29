#pragma once
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>

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
	vector<string> getDate(void);
	vector<string> getTweet(void);
	void printTweet(void);
	void printDate(void);
	std::vector<std::string> getTxidTransformed(int blockElected);
	
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
