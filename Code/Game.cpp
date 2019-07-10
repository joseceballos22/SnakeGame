#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Game::Game() :
	window(sf::VideoMode(800, 800), "SnakeGame", sf::Style::Close)
{
	this->deltaT = 0; //Initially ZERO

	this->initStates(); //Initializing All the States in the Game

	this->score = 0; //Saves the Score Acts as a Middle Man to bridge the gap between GameState and LostState

}



Game::~Game()
{
	//Deallocating Memory Allocated from States
	for (int i = 0; i < this->states.size(); i++)
	{
		delete states.top();

		states.pop(); //Go to the Next One 
	}
}

//Public Function
void Game::start()
{
	this->run(); //Runs the Main Loop 
}




void Game::run()
{
	sf::Clock clock;

	//Main GameLoop
	while (this->window.isOpen())
	{
		this->deltaT = clock.restart().asSeconds(); //Gets the Speed of Our Specific Computer

		//Event Loop Handler
		sf::Event evnt;
		while (this->window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				this->window.close(); 
			}
		}

		this->window.clear(); //Clears the Window
		
		Game::update(); //Updates all the Components in the Game
		Game::processStuff(); //Processes All the Components in the Game
		Game::draw(); //Draws all the Components in the Game

		this->window.display(); //Displays the Window
	}

}


void Game::update()
{
	//Updating the Current State	Ensures its not Empty
	if (!this->states.empty())
	{
		this->states.top()->update(this->deltaT);
	}
}


void Game::draw()
{
	//Drawing the Current State		Ensures its not Empty
	if (!this->states.empty())
	{
		this->states.top()->draw(&this->window);
	}
}

void Game::processStuff()
{

	//Processing the Current State
	if (!this->states.empty())
	{
		//Process Everything First
		this->states.top()->processStuff(this->deltaT, sf::Vector2f(sf::Mouse::getPosition(this->window))); 
		
		//Checking if the State Wants to Quit OR IF THE PLAYER LOST THE GAME 
		if (this->states.top()->getQuit() == true)
		{
			//Before we Quit We will Save the Score 
			this->score = this->states.top()->State::getHolderScore();//Saving the Score 
			//Quitting the State
			delete this->states.top(); //Deallocating the Memory 
			this->states.pop(); //Poping the State Out 
		}
	}

	//Talking about the Lost state Stuff
	if (this->states.size() <= 1)
	{
		this->states.top()->State::setHolderScore(this->score);

		if (this->states.top()->switchState())
		{
			//Clearing the Lost State 
			delete this->states.top();
			this->states.top() = new LostState(); //Re adding the Lost state 

			//They Pushed PlayAgain Therefore Create a New GameState
			this->states.push(new GameState()); //Starting Game Over
		}
	}
}


//Initiallizes all the States of the Game
void Game::initStates()
{
	this->states.push(new LostState()); //If the Player Loses Switch to this State 
	this->states.push(new GameState());  //Inital Game State 
}