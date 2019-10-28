#include "jsonHandler.h"

using json = nlohmann::json;
using namespace std;

void jsonHandler::jsonStartHandler(string route)
{
	std::ifstream i(route);
	i >> j;
	i.close();
}

bool jsonHandler::existJsonElement(string target)
{
	//HAY QUE REVISAR!!!!!!!!!!!!!!!!!!!!!!!!
	
	blocks.clear();
	for (json::iterator it = j.begin(); it != j.end(); it++)
		if (it.key() == "statuses")
			for (auto element : *it)
				for (json::iterator k = element.begin(); k != element.end(); k++)
					if (k.key() == target)
						blocks.push_back(k.value());
	
	/*for (json::iterator it = j.begin(); it != j.end(); it++)
		if (it.key() == target)
			blocks.push_back(it.value());
	*/
	if (blocks.size() == 0) {
		return false;
	}
	else
		return true;
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