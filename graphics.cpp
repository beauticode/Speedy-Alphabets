#include "graphics.h"

Graphics::Graphics(sf::RenderWindow* mainw)
{
	main = mainw;
	defaultfont.loadFromFile("fake receipt.ttf");
	abcs();
	abcclock.restart();
	simdelay.restart();
}

void Graphics::stars()
{
	sf::CircleShape star;
	star.setFillColor(sf::Color::White);
	star.setOutlineColor(sf::Color::Black);
	star.setRadius(1);
	star.setOrigin(star.getLocalBounds().width / 2, star.getLocalBounds().height / 2);
	star.setPosition(0, 0);
	for (int row = 0; row < 600; row += 40) {
		for (int x = 0; x < 800; x += 40) {
			star.move(40, 0);
			main->draw(star);
		}
		star.move(-(star.getPosition().x), 40);
	}
}

void Graphics::menu()
{ //Next add scrolling ABC's in different colors
	sf::Text title, instr,cpr;
	title.setFont(defaultfont);
	instr.setFont(defaultfont);
	cpr.setFont(defaultfont);
	title.setColor(sf::Color::Blue);
	instr.setColor(sf::Color::Blue);
	cpr.setColor(sf::Color::Yellow);
	title.setString("Speedy Alphabets");
	instr.setString("Press ENTER to play.");
	cpr.setString("Copyright (c) 2015 - Gary Smith");
	title.setStyle(sf::Text::Bold);
	instr.setStyle(sf::Text::Regular);
	cpr.setStyle(sf::Text::Regular);
	title.setCharacterSize(50);
	instr.setCharacterSize(33);
	cpr.setCharacterSize(21);
	title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
	instr.setOrigin(instr.getLocalBounds().width / 2, instr.getLocalBounds().height / 2);
	cpr.setOrigin(cpr.getLocalBounds().width / 2, cpr.getLocalBounds().height / 2);
	title.setPosition(main->getSize().x / 2, (main->getSize().y / 2) - 150);
	instr.setPosition(main->getSize().x / 2, (main->getSize().y / 2));
	cpr.setPosition(main->getSize().x / 2, (main->getSize().y / 2) + 150);
	moveabcs();
	for (int x = 0; x < 26; x++) {
		main->draw(abc[x]);
	}
	main->draw(title);
	main->draw(instr);
	main->draw(cpr);
}

void Graphics::abcs()
{
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int x = 0,y=0; x < 26; x++,y++) {
		abc[x].setFont(defaultfont);
		abc[x].setString(alphabet[x]);
		abc[x].setStyle(sf::Text::Bold);
		abc[x].setCharacterSize(40);
		abc[x].setOrigin(abc[x].getLocalBounds().width / 2, abc[x].getLocalBounds().height / 2);
		abc[x].setPosition((main->getSize().x) + (x * 20), (main->getSize().y / 2) - 75);
		if (y < 3) {
			switch (y) {
			case 0: {
				abc[x].setColor(sf::Color::Red);
			}break;
			case 1:
			{
				abc[x].setColor(sf::Color::White);
			}break;
			case 2:
			{
				abc[x].setColor(sf::Color::Blue);
			}break;
			}
		}
		else {
			y = -1;
		}
	}
}

void Graphics::moveabcs()
{
	if (abcclock.getElapsedTime().asMilliseconds() >= 100) {
		for (int x = 0; x < 26; x++) {
			if ((abc[x].getPosition().x)<= 0) {
				abc[x].setPosition(main->getSize().x, abc[x].getPosition().y);
			}
			abc[x].move(-1, 0);
		}
	}
}

void Graphics::blackhole() {
	sf::CircleShape hole;
	hole.setFillColor(sf::Color(0, 0, 0, 210));
	hole.setOutlineColor(sf::Color(56, 56, 56,120));
	hole.setOutlineThickness(5);
	hole.setRadius(40);
	hole.setOrigin(hole.getLocalBounds().width / 2, hole.getLocalBounds().height / 2);
	hole.setPosition(main->getSize().x / 2, main->getSize().y / 2);
	main->draw(hole);
}

void Graphics::prpe(bool exit) {
	sf::Text ptext;
	ptext.setCharacterSize(12);
	ptext.setColor(sf::Color::Yellow);
	ptext.setFont(defaultfont);
	if (exit) { ptext.setString("Press ESC to exit."); }
	else { ptext.setString("Press ESC to pause."); }
	ptext.setStyle(sf::Text::Underlined);
	ptext.setOrigin(ptext.getLocalBounds().width / 2, ptext.getLocalBounds().height / 2);
	ptext.setPosition(ptext.getLocalBounds().width/2, ptext.getLocalBounds().height/2);
	main->draw(ptext);
}

void Graphics::paused() {
	sf::Text ptext("Game Paused", defaultfont, 35);
	sf::Text esc("Press ESC to return to the main menu", defaultfont, 30);
	sf::Text rtn("Press ENTER to keep playing", defaultfont, 26);
	//esc.setCharacterSize(30);
	//ptext.setCharacterSize(35);
	ptext.setColor(sf::Color::Yellow);
	esc.setColor(sf::Color::Red);
	rtn.setColor(sf::Color::Red);
	//ptext.setFont(defaultfont);
	//esc.setFont(defaultfont);
	//ptext.setString("Game Paused");
	//esc.setString("Press ESC to return to the main menu");
	ptext.setStyle(sf::Text::Underlined);
	esc.setStyle(sf::Text::Regular);
	esc.setOrigin(esc.getLocalBounds().width / 2, esc.getLocalBounds().height / 2);
	ptext.setOrigin(ptext.getLocalBounds().width / 2, ptext.getLocalBounds().height / 2);
	rtn.setOrigin(rtn.getLocalBounds().width / 2, rtn.getLocalBounds().height / 2);
	ptext.setPosition((main->getSize().x/2),(main->getSize().y/2) - 150);
	esc.setPosition((main->getSize().x / 2), (main->getSize().y / 2));
	rtn.setPosition((main->getSize().x / 2), (main->getSize().y / 2) + 150);
	main->draw(ptext);
	main->draw(esc);
	main->draw(rtn);
}

void Graphics::dletters(std::vector<int>* buttons, std::vector<sf::Vector2f>* positions,std::vector<sf::Color> color) {
	if (buttons->size() > 0) {
		std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		sf::Text ltr; //Letter
		ltr.setFont(defaultfont);
		ltr.setCharacterSize(35);
		ltr.setStyle(sf::Text::Regular);
		for (int x = 0; x < buttons->size() - 1; x++) { //Draw all of letters 
			ltr.setColor(color.at(x));
			ltr.setString(alphabets.at(buttons->at(x)));
			ltr.setOrigin(ltr.getLocalBounds().width / 2, ltr.getLocalBounds().height / 2);
			ltr.setPosition(positions->at(x).x, positions->at(x).y);
			main->draw(ltr);
		}
	}
}

void Graphics::showscore(int score) {
	sf::Text scoretxt("Score:" + std::to_string(score), defaultfont, 20);
	scoretxt.setColor(sf::Color::White);
	scoretxt.setStyle(sf::Text::Regular);
	scoretxt.setPosition((main->getSize().x - scoretxt.getLocalBounds().width - 10), 0);
	main->draw(scoretxt);
}

void Graphics::loser(int score) {
	sf::Text lost("You have lost!", defaultfont, 40);
	sf::Text scoret("Score:" + std::to_string(score), defaultfont, 30);
	sf::Text back("Press enter to return the menu.", defaultfont, 17);
	lost.setColor(sf::Color::Red);
	scoret.setColor(sf::Color::White);
	back.setColor(sf::Color::Blue);
	lost.setOrigin(lost.getLocalBounds().width / 2, lost.getLocalBounds().height / 2);
	scoret.setOrigin(scoret.getLocalBounds().width / 2, scoret.getLocalBounds().height / 2);
	back.setOrigin(back.getLocalBounds().width / 2, back.getLocalBounds().height / 2);
	lost.setPosition(main->getSize().x / 2, (main->getSize().y / 2) - 100);
	scoret.setPosition(main->getSize().x / 2, (main->getSize().y / 2));
	back.setPosition(main->getSize().x / 2, (main->getSize().y / 2) + 100);
	main->draw(lost);
	main->draw(scoret);
	main->draw(back);
}


Graphics::~Graphics() {
	main = nullptr;
}