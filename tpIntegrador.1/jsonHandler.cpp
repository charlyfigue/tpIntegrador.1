#include "jsonHandler.h"

//using json = nlohmann::json;
//using namespace std;

void jsonHandler::jsonStartHandler(string route)
{
	string readString;
	char c;
	std::ifstream i(route);
	i >> j;
	i.close();
}

bool jsonHandler::existJsonElementBlock(json::iterator begin, json::iterator end) {

	int result = 0;
	bool isValid;
	json::iterator etBegin;
	json::iterator etEnd;
	//for (json::iterator it = j.begin(); it != j.end(); it++) {
	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "tx") {
			if (((*it).empty() == false) && ((*it).is_array())) {
				for (auto& x : (*it).items()) {
					if ((x.value()).is_object()) {
						isValid = existJsonTransactionBlock((x.value()).begin(), (x.value()).end());
					}
					else
						isValid = false;
				}
				if(isValid)
					result++;
			}
			else if (((*it).empty() == true) && ((*it).is_array())) {
				result++;
			}
			else
				isValid = false;
		}
		else if (it.key() == "height") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
		else if (it.key() == "nonce") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
		else if (it.key() == "blockid") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
		else if (it.key() == "previousblockid") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
		else if (it.key() == "merkleroot") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
		else if (it.key() == "nTx") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
	}
	if (result != 7)
		isValid = false;
	else
		isValid = true;
	return isValid;
}

bool jsonHandler::existJsonTransactionBlock(json::iterator begin, json::iterator end) {
	int result = 0;
	bool isValid;

	if (begin == end)
		isValid = true;
	else {
		for (json::iterator it = begin; it != end; it++) {
			if (it.key() == "txid") {
				if ((*it).empty() == false)
					result++;
				else
					isValid = false;
			}
			else if (it.key() == "nTxin") {
				if ((*it).empty() == false)
					result++;
				else
					isValid = false;
			}
			else if (it.key() == "nTxout") {
				if ((*it).empty() == false)
					result++;
				else
					isValid = false;
			}
			else if (it.key() == "vin") {
				if (((*it).empty() == false) && ((*it).is_array())) {
					int cont = 0;
					for (auto& x : (*it).items()) {
						cont++;
						if ((x.value()).is_object()) {
							isValid = existJsonTransactonVinBlock((x.value()).begin(), (x.value()).end());
						}
						else {
							isValid = false;
							break;
						}
					}
					if (isValid && (cont == 1))
						result++;
				}
				else
					isValid = false;
			}
			else if (it.key() == "vout") {
				if (((*it).empty() == false) && ((*it).is_array())) {
					int cont = 0;
					for (auto& x : (*it).items()) {
						cont++;
						if ((x.value()).is_object()) {
							isValid = existJsonTransactonVoutBlock((x.value()).begin(), (x.value()).end());
						}
						else {
							isValid = false;
							break;
						}
					}
					if (isValid && (cont == 1))
						result++;
				}
				else
					isValid = false;
			}
		}
		if (result != 5)
			isValid = false;
		else
			isValid = true;
	}
	return isValid;
}

bool jsonHandler::existJsonTransactonVoutBlock(json::iterator begin, json::iterator end) {
	int result = 0;
	bool isValid;

	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "publicid") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
		else if (it.key() == "amount") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
	}
	if (result != 2)
		isValid = false;
	else
		isValid = true;
	return isValid;
}

bool jsonHandler::existJsonTransactonVinBlock(json::iterator begin, json::iterator end) {
	int result = 0;
	bool isValid;

	for (json::iterator it = begin; it != end; it++) {
		if (it.key() == "blockid") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
		else if (it.key() == "txid") {
			if ((*it).empty() == false)
				result++;
			else
				isValid = false;
		}
	}
	if (result != 2)
		isValid = false;
	else
		isValid = true;
	return isValid;
}

bool jsonHandler::existJsonBlock()
{
	int result = 0;
	bool isValid;
	blocks.clear();
	if (j.empty() == false) {
		if (j.is_array()) {
			for (auto& x : j.items()){
				if ((x.value()).is_object()) {
					isValid = existJsonElementBlock((x.value()).begin(), (x.value()).end());
				}
				else
					isValid = false;
			}
		}
		else if (j.is_object()) {
			isValid = existJsonElementBlock(j.begin(), j.end());
			/*if (!isValid) {
				for (auto& x : j.items()){
					if ((x.value()).is_object()) {
						isValid = existJsonElementBlock(j.begin(), j.end());
					}
				}
				isValid = false;
			}*/
		}
		else
			isValid = false;
	}
	else
		isValid = false;
	return isValid;
}

void jsonHandler::getJson(void)
{
	if (!j.empty() && j.is_array())
	{
		for (auto& element : j)
		{
			auto tw = element["text"];
			auto d = element["created_at"];
			
			tweet.push_back(tw);
			date.push_back(d);
		}
	}
}

void jsonHandler::setRouteOfJsonBlock() {
	int result = 0;
	bool isValid;
	
	blocksFounded = 0;
	routesOfBlocks.clear();

	if (j.is_array()) {
		for (auto& x : j.items()) {
			if ((x.value()).is_object()) {
				if (existJsonElementBlock((x.value()).begin(), (x.value()).end())) {
					blocksFounded++;
					route electedBlockRoute;
					electedBlockRoute.begin = (x.value()).begin();
					electedBlockRoute.end = (x.value()).end();
					routesOfBlocks.push_back(electedBlockRoute);
				}
			}
		}
	}
	else if (j.is_object()) {
		blocksFounded = 1;
		route electedBlockRoute;
		electedBlockRoute.begin = j.begin();
		electedBlockRoute.end = j.end();
		routesOfBlocks.push_back(electedBlockRoute);
	}
}

vector<string> jsonHandler::getTweet(void)
{
	return tweet;
}

vector<string> jsonHandler::getDate(void)
{
	return date;
}

void jsonHandler::printTweet(void)
{
	for (int i = 0; i < getTweet().size(); i++)
		cout << getTweet().at(i) << ' ' << endl;
}

void jsonHandler::printDate(void)
{
	for (int i = 0; i < getDate().size(); i++) 
		cout << getDate().at(i) << ' ' << endl;
}