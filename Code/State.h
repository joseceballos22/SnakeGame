#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>



class State
{
public:
	State();
	~State();
	

	virtual void update(double deltaT) = 0; //Updates the Components of the State
	virtual void draw(sf::RenderWindow * w) = 0; //Draws the Components of the State
	virtual void processStuff(double deltaT , sf::Vector2f mousePos) = 0;//Process The Components in the State

	virtual void updateKeyBinds(double deltaT) = 0; //All Key Binds Of State go in here 

	virtual void checkForQuit(); //Predefined Quit Key

	void setQuit(bool newQuit);


	bool getQuit() const; //Determines if State should End Goes in Update Function in GAME

	void setHolderScore(int newScore);

	int getHolderScore() const;

	//Allows the States the Option to switch to a diffent State depending on their definitions 
	virtual bool switchState();

private:
	bool quit; //Determines if the State Should Quit Initially False
	int holderScore; //Holds the Score from the GameState to transfer it to the LostState
	
};

#endif