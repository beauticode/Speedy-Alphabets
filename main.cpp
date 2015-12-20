#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "graphics.h"
#include "halfbrain.h"
int main()
{
	//int mode = 0; //0 = Menu, 1 = Pause, 2 = Play, 3 = Lost
	sf::RenderWindow game(sf::VideoMode(800, 600), "Speedy Alphabets", sf::Style::Default);
	game.setVerticalSyncEnabled(true);
	Graphics gfx(&game);
	Brain smart(game.getSize().x / 2, game.getSize().y / 2);
	while (game.isOpen()) {
		sf::Event e;
		while (game.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
			{
				game.close();
			}break;
			case sf::Event::KeyPressed:
			{
				switch (smart.mode) {
				case 0: {
					switch (e.key.code) {
					case sf::Keyboard::Return: {
						smart.mode = 2;
					}break;
					case sf::Keyboard::Escape: {
						game.close();
					}break;
					}
				}break;
				case 1: {
					switch (e.key.code) {
					case sf::Keyboard::Escape: {
						smart.mode = 0;
					}break;
					case sf::Keyboard::Return:
					{
						smart.mode = 2;
					}break;
					}
				}break;
				case 2: {
					switch (e.key.code) {
					case sf::Keyboard::Escape: {
						smart.mode = 1;
					}break;
					default: {
						smart.chkkeypressed(e.key.code);
					}break;
					}

				}break;
				case 3: {
					switch (e.key.code) {
					case sf::Keyboard::Return: {
						smart.score = 0;
						smart.mode = 0;
						smart.delletters(false, 123456789);
					}break;
					}
				}break;
				}
			}break;
			}
		}
		game.clear(sf::Color::Black);
		gfx.stars();
		switch (smart.mode) {
		case 0: { //Menu
			gfx.menu();
			gfx.prpe(true);
		}break; 
		case 1: { //Paused
			gfx.paused();
		}break;
		case 2: { //Playing
			gfx.blackhole();
			gfx.prpe(false);
			gfx.showscore(smart.score);
			smart.genletters();
			smart.moveletters();
			gfx.dletters(&smart.topress,&smart.tppos,smart.getrandomcolors(smart.topress.size()));
			smart.delletters(false,false);
			smart.chkctr();
		}break;
		case 3: {
			gfx.loser(smart.score);
		}break;
		}
		game.display();
		
	}
}