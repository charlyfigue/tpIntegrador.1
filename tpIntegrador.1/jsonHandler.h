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
	bool existJsonElement(string target);
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
