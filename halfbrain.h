#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
class Brain {
public:
	Brain(float _ctrx,float _ctry);
	~Brain();
	void genletters(); //Generate letters to press
	void moveletters(); //Move the letters position towards center
	void delletters(bool specific,int ifspecific); //Check if letters are past absolute-value position & delete all letter-data
	void chkkeypressed(int key);
	void chkctr();
	int difficulty(); //Get how fast letters will be generated, score is taken into consideration
 	std::vector<sf::Color> getrandomcolors(int colorsneeded); //Return a unique random color for each letter (red,white,blue)
	std::vector<int> topress; //Keys the user needs to press
	std::vector<sf::Vector2f> tppos; //Keys-to-press position
	int score;
	int mode; //0 = Menu, 1 = Pause, 2 = Play
private:
	std::vector<sf::Vector2f> tpspd; //Keys-to-press speeds
	std::vector<sf::Vector2f> tppos_init; //The initial starting position of a specific letter - Will not be changed
	sf::Clock gravitypulse;
	sf::Clock spawndelay;
	float ctrx, ctry;
};