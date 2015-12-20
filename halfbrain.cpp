#include "halfbrain.h"

Brain::Brain(float _ctrx,float _ctry) {
	gravitypulse.restart();
	spawndelay.restart();
	score = 0;
	mode = 0;
	ctrx = _ctrx;
	ctry = _ctry;
}


void Brain::genletters() {
	std::string random = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //A = 0,B = 1, it's an Enum
	std::default_random_engine numgen(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> uniform(0, random.size()-1);
	std::uniform_int_distribution<int> flip(0, 2);
	int minxmaxxminmaxy[4] = { 0,0,0,0 };
	switch (flip(numgen)) {
	case 0: {
		minxmaxxminmaxy[0] = 0;//X minimum
		minxmaxxminmaxy[1] = 800; //X Maximum
		minxmaxxminmaxy[2] = -20; // Y Minimum
		minxmaxxminmaxy[3] = 0; //Y Maximum
	}break;
	case 1: {
		minxmaxxminmaxy[0] = -20;
		minxmaxxminmaxy[1] = 0;
		minxmaxxminmaxy[2] = 0; 
		minxmaxxminmaxy[3] = 600;
	}break;
	default: {
		minxmaxxminmaxy[0] = -20;
		minxmaxxminmaxy[1] = 0;
		minxmaxxminmaxy[2] = 0;
		minxmaxxminmaxy[3] = 600;
	}break;
	}
	std::uniform_real_distribution<float> uposx(minxmaxxminmaxy[0], minxmaxxminmaxy[1]);
	std::uniform_real_distribution<float> uposy(minxmaxxminmaxy[2], minxmaxxminmaxy[3]);
	if (spawndelay.getElapsedTime().asMilliseconds() >= difficulty()) {
		topress.push_back(uniform(numgen));
		tppos.push_back(sf::Vector2f(uposx(numgen), uposy(numgen)));
		tppos_init.push_back(sf::Vector2f(uposx(numgen), uposy(numgen)));
		float slope = (ctry - tppos.at(tppos.size()-1).y) / (ctrx - tppos.at(tppos.size()-1).x); //Y2 - Y1 / X2 - X1
		tpspd.push_back(sf::Vector2f(cos(slope),sin(slope)));
		spawndelay.restart();
	}
}


void Brain::moveletters() {
	if (gravitypulse.getElapsedTime().asMilliseconds() >= 10&&topress.size()>0) {
		for (int x = 0; x < tpspd.size()-1; x++) {
			tppos.at(x).x += tpspd.at(x).x;
			tppos.at(x).y += tpspd.at(x).y;
		}
		gravitypulse.restart();
	}
}

int Brain::difficulty() {
	if (score >= 7 && score < 14) {
		return 1000;
	}
	else if (score >= 14 && score < 29) {
		return 800;
	}
	else if (score >= 29 && score < 45) {
		return 600;
	}
	else if (score >= 45) {
		return 475;
	}
	else if (score < 7) {
		return 1200;
	}
}

std::vector<sf::Color> Brain::getrandomcolors(int colorsneeded) {
	std::default_random_engine numgen((std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> limit(1,3);
	std::vector<sf::Color> colors;
	for (int x = 0; x < colorsneeded; x++) {
		switch (limit(numgen)) {
		case 1: {
			colors.push_back(sf::Color::Red);
		}break;
		case 2: {
			colors.push_back(sf::Color::White);
		}break;
		case 3: {
			colors.push_back(sf::Color::Blue);
		}break;
		default: {
			colors.push_back(sf::Color::White);
		}break;
		}
	}
	return colors;
}

void Brain::delletters(bool specific,int ifspecific) {
	if (specific) {
		tppos.erase(tppos.begin() + ifspecific);
		tppos_init.erase(tppos_init.begin() + ifspecific);
		tpspd.erase(tpspd.begin() + ifspecific);
		topress.erase(topress.begin() + ifspecific);
	}
	else if (ifspecific == 123456789) { //Delete all
		tppos.clear();
		tppos_init.clear();
		tpspd.clear();
		topress.clear();
	}
	else {
		for (int x = 0; x < tppos.size(); x++) {
			if (tppos.at(x).x >= (ctrx * 2) || tppos.at(x).y >= (ctry * 2) || tppos.at(x).x<-20 || tppos.at(x).y<-20) {
				tppos.erase(tppos.begin() + x);
				tppos_init.erase(tppos_init.begin() + x);
				tpspd.erase(tpspd.begin() + x);
				topress.erase(topress.begin() + x);
				x = 0;
			}
		}
	}
}

void Brain::chkctr() {
	for (int x = 0; x < tppos.size(); x++) {
		if (tppos.at(x).x <= (ctrx + 40) && tppos.at(x).x >= (ctrx - 40) && tppos.at(x).y <= (ctry + 40) && tppos.at(x).y >= (ctry - 40)) {
			mode = 3;
		}
	}
}

void Brain::chkkeypressed(int key) {
	bool keyexists = false;
	for (int x = 0; x < topress.size()-1; x++) {
		if (key == topress.at(x)) {
			score++;
			delletters(true, x);
			keyexists = true;
		}
	}
	if (!keyexists) { //Loser
		mode = 3;
	}
}

Brain::~Brain() {

}