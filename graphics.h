#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <random>
class Graphics {
public:
	Graphics(sf::RenderWindow* mainw);
	~Graphics();
	void stars();
	void menu();
	void abcs();
	void loser(int score);
	void moveabcs();
	void blackhole();
	void prpe(bool exit);
	void paused();
	void showscore(int score);
	void dletters(std::vector<int>* buttons, std::vector<sf::Vector2f>* positions, std::vector<sf::Color> color); //Draw letters
	
private:
	sf::RenderWindow* main;
	sf::Font defaultfont;
	sf::Text abc[26];
	std::vector<sf::Text> targets;
	sf::Clock abcclock;
	sf::Clock simdelay;
};