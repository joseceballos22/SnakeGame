#ifndef LOSTSTATE_H
#define LOSTSTATE_H
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"
#include <string>

/*
	This state will be displaced A menu For the Lost Menu the User Loses 
*/



class LostState :
	public State
{
public:
	LostState();
	~LostState();


	//Updates the Components in the State
	void update(double deltaT) override;
	
	//Draws the Components in the State
	void draw(sf::RenderWindow * w) override;

	//Processes the Components in the State 
	void processStuff(double deltaT, sf::Vector2f mousePos) override;

	//Updates the Key presses in the State
	void updateKeyBinds(double deltaT) override;

	bool switchState() override; //Determines if the User wants to Play Again 

	void setScore(std::string newScore); //sets the Score to Displays 

private:
	sf::Font font; //Default Font
	int *score; //The Score of the User 

	sf::Text playerScore;//Displays the Players Score
	Button* playAgain; //Allows the User the Option to Play Again 

	sf::RectangleShape background; //LostState's Background
	sf::Texture backgroundTexture;

};

#endif