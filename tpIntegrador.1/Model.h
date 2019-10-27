#pragma once
#include "Subject.h"
#include <string>
#include <vector>

class Model : public Subject {
public:
	Model();
	void startDownload(void);
	void changeTweetAmount(int cantidad);
	void finishDownload(void);
	void readyForDownload(void);
	void showPreviousTweet(void);
	void resetTweet(void);
	void showNextTweet(void);
	void changeSpeed(int velocidad);
	void manageOutputDo(void);
	void manageOutputWhile(void);
	void sendOutput(void);
	void sendWhileOutput(void);
	void displayTuits(void);

	void setErrors(vector<string> e);
	void setTweets(vector<string> t) { tweets = t; tweetAmount = tweets.size();}
	void setTweetsDates(vector<string> t) { dates = t; }
	void setUser(string name) { usuario = name; }

	string getUser() { return usuario; }
	string getCurrentTweet() { return tweets[currentTweet]; }
	int getCurrentTweetIndex() { return currentTweet; }
	bool getInProcess() { return inProcess; }
	int getTweetAmount() { return tweetAmount; }
	int getCharIndex() { return charIndex; }
	vector<string> getErrors() { return errors; }
	vector<string> getTweets() { return tweets; }
	vector<string> getDates() { return dates; }
	string getLineUp() { return lineUp; }
	string getLineDown() { return lineDown; }
	bool isFinished() { return finished; }
private:
	bool finishSending;
	int contSents;
	string usuario;
	int speed;
	int currentTweet;
	int tweetAmount;
	int charIndex;
	bool inProcess;
	bool finished;
	bool failed;
	int timer;
	string cargar[4];
	vector<string> errors;
	vector<string> tweets;
	vector<string> dates;
	vector<string> output;
	string lineUp;
	string lineDown;
};