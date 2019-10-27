#include "Model.h"
#include <iostream>

Model::Model() {
	timer = 0;
	cargar[0] = "1";
	cargar[1] = ".";
	cargar[2] = "..";
	cargar[3] = "...";
	finishSending = false;
	contSents = 0;
	currentTweet = 0;
	tweetAmount = 0;
	charIndex = 0;
	speed = 1;
	inProcess = false;
	finished = false;
	failed = false;
	errors.clear();
	tweets.clear();
}

void Model::startDownload() {
	if (inProcess == false) {
		if (tweetAmount <= 0) {
			cout << "Descarga iniciada. Parametro por defecto" << endl;
			tweetAmount = 10;
		}
		else {
			cout << "Descarga iniciada. Parametro = " << tweetAmount << endl;
		}
		inProcess = true;
		this->notifyAllObservers();
	}
}

void Model::changeTweetAmount(int amount) {
	if (!finished) {
		cout << "Cambio cantidad de tuits solicitada: " << amount << endl;
		tweetAmount = amount;
		this->notifyAllObservers();
	}
}

void Model::finishDownload() {
	inProcess = false;
	finished = true;
	timer = 0;
	this->notifyAllObservers();
}

void Model::sendWhileOutput() {
	if (timer > 58) {
		timer = 0;
		sendOutput();
	}
	else
		timer++;
}

void Model::setErrors(vector<string> e) {
	errors = e;
	if (e.size() > 0) {
		failed = true;
		inProcess = false;
	}
	this->notifyAllObservers();
}

void Model::readyForDownload() {
	currentTweet = 0;
	tweetAmount = 0;
	speed = 1;
	finished = false;
	inProcess = false;
	failed = false;
	contSents = 0;
	errors.clear();
	tweets.clear();
	this->notifyAllObservers();
}

void Model::showPreviousTweet() {
	if(currentTweet > 0)
		currentTweet--;
	//currentTweet %= tweetAmount;
	charIndex = 0;
	contSents = 0;
	timer = 0;
	this->notifyAllObservers();
}

void Model::showNextTweet() {
	if (currentTweet < (tweetAmount-1))
		currentTweet++;
	//currentTweet %= tweetAmount;
	charIndex = 0;
	contSents = 0;
	timer = 0;
	this->notifyAllObservers();
}

void Model::resetTweet() {
	charIndex = 0;
	contSents = 0;
	timer = 0;
	this->notifyAllObservers();
}

void Model::changeSpeed(int newspeed) {
	speed = newspeed;
	this->notifyAllObservers();
}

void Model::manageOutputWhile() {
	output.clear();
	output.push_back(getUser());
	this->notifyAllObservers();
}

void Model::displayTuits() {
	if (timer > 500) {
		timer = 0;
		if (finishSending) {
			contSents = 0;
			finishSending = false;
			if ((currentTweet + 1) < tweetAmount)
				currentTweet++;
		}
		else
			sendOutput();
	}
	else {
		timer += speed;
	}
	this->notifyAllObservers();
}

void Model::manageOutputDo() {
	output.clear();
	string date, name;
	int i, j;
	size_t found;
	int recort;
	for (i = 0; i < tweets.size(); i++) {
		found = (tweets[i]).find("http");
		recort = ((tweets[i]).size()) - found;
		(tweets[i]).erase(found, recort);

		found = (dates[i]).find(' ', 6);
		found++;
		for (j = 0; j < 2; j++)
			date += (dates[i]).at(found + j);
		date += '/';
		found = (dates[i]).find("Jan");
		if (found == string::npos) {
			found = (dates[i]).find("Feb");
			if (found == string::npos) {
				found = (dates[i]).find("Mar");
				if (found == string::npos) {
					found = (dates[i]).find("Apr");
					if (found == string::npos) {
						found = (dates[i]).find("May");
						if (found == string::npos) {
							found = (dates[i]).find("Jun");
							if (found == string::npos) {
								found = (dates[i]).find("Jul");
								if (found == string::npos) {
									found = (dates[i]).find("Aug");
									if (found == string::npos) {
										found = (dates[i]).find("Sep");
										if (found == string::npos) {
											found = (dates[i]).find("Oct");
											if (found == string::npos) {
												found = (dates[i]).find("Nov");
												if (found == string::npos) {
													found = (dates[i]).find("Dic");
													if (found == string::npos)
														std::cout << "Error with the month" << std::endl;
													else
														date += "12";
												}
												else
													date += "11";
											}
											else
												date += "10";
										}
										else
											date += "09";
									}
									else
										date += "08";
								}
								else
									date += "07";
							}
							else
								date += "06";
						}
						else
							date += "05";
					}
					else
						date += "04";
				}
				else
					date += "03";
			}
			else
				date += "02";
		}
		else
			date += "01";
		date += "/";
		date += "19 - ";
		found = (dates[i]).find(' ', 9);
		found++;
		for (j = 0; j < 5; j++)
			date += (dates[i]).at(found + j);
		name += getUser();
		name += ": - ";
		name += tweets[i];
		name += " -";
		//tuits[i] = name;
		output.push_back(name);
		output.push_back(date);
		date.clear();
		name.clear();
	}
	this->notifyAllObservers();
}

void Model::sendOutput() {
	string message[2];
	if (!getInProcess()) {
		if (isFinished()) {
			message[0].clear();
			message[1].clear();
			for (int i = 0; i < 16; i++)
				message[0] += (output[(currentTweet * 2)]).at(i + contSents);
			if (contSents >= ((output[(currentTweet * 2)].size()) - 16)) {
				contSents = 0;
				finishSending = true;
			}
			else
				contSents++;
			message[1] = output[(currentTweet * 2) + 1];
		}
		else {
			message[0].clear();
			message[1].clear();
			message[0] = "Waiting for action";
			message[1] = "EDA 2019";
		}
	}
	else {
		message[0].clear();
		message[1].clear();
		message[0] = output[0];
		int pos = atoi((cargar[0]).c_str());
		message[1] = "Descargando" + cargar[pos];
		if (pos >= 3)
			pos = 1;
		else
			pos++;
		cargar[0] = to_string(pos);
	}
	lineUp = message[0];
	lineDown = message[1];
	this->notifyAllObservers();
}