#ifndef GAMESTATE_H
#define GAMESTATE_H

/*
	Game State includes All the Components of the Snake Game
*/

#include <SFML/Graphics.hpp>
#include <string>
#include "State.h"
#include "Entity.h"
#include "Fruit.h"
#include "Head.h"
#include "Border.h" //Border for the Game 
#include <vector>
#include "Button.h"


class GameState : public State
{
public:
	GameState();
	~GameState();

	void update(double deltaT) override; //Updates all the Components of the State
	void draw(sf::RenderWindow * w) override; //Draws all the Components of the State
	void processStuff(double deltaT, sf::Vector2f mousePos) override; //Processes All the Components of the State (e.g. Collision Detection)

	void updateKeyBinds(double deltaT) override; //Defines all the Keyboard Stuff for that state

	void initBorder(); //Initializes the Border Vector 

private:
	//Snake Stuff
	Head * head;
	sf::Texture headTexture;

	//Fruit Stuff
	Fruit * fruit;
	sf::Texture fruitTexture;

	//Border Stuff
	std::vector<Border *> borders; //Borders to the Game 
	sf::Texture borderTexture;

	//Counter For Head and Fruit Collision
	double counterHF;

	//Counter for Head and Tail Collision
	double counterHT;

	//Counter for Head and Border Collision
	double counterHB;

	//Counter For Pause Button
	double pauseCounter;


	sf::RectangleShape background; 

	bool pause; //Pauses the Screen

	sf::Text pauseText; //Pause screen Text
	sf::Font font;

	sf::Texture scoreTexture;
	Button* scoreButton; //Displays the Score 

};

#endif