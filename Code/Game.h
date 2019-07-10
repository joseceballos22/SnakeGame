#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>
#include <string>
#include "Entity.h"
#include "State.h"
#include "GameState.h"
#include "Head.h"
#include "Fruit.h"
#include "Button.h"
#include "LostState.h" 

class Game
{
public:
	Game();
	~Game();

	void start(); //Starts the Game
private:

	//deltaT is the Speed of our Computer
	void update(); //Updates all components in game
	void draw(); //Draws all Components in game
	void processStuff(); //Processes all components in game
	void run(); //Main Loop 

	void initStates(); //Initiallizes all the States of the Game

private:

	sf::RenderWindow window;

	std::stack<State *> states; //Holds all the States in the Game
	
	//Delta Time == the Speed of Our Computer Specific to every Computer
	double deltaT;
	int score; //Saves the Score

};


#endif
