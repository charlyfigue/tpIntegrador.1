#pragma once
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class jsonHandler;

using json = nlohmann::json;
using namespace std;

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
	vector<string> getDate(void);
	vector<string> getTweet(void);
	void printTweet(void);
	void printDate(void);

private:
	json j;
	vector<string> blocks;
	vector<string> tweet;
	vector<string> date;
};
