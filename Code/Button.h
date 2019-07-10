#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "Entity.h" //A Button is a Entity
#include <string>

/*
	Defining a Button 
	- Body	(Part of Entity) DONT FORGET TO RESIZE IN CONSTRUCTOR 
	- Text
	- Font
	- IdleColor 
	- Hover Color
	- Pressed Color 
*/

//Different types of color the Button can be depending on its State
enum ButtonState{IDLE = 0, HOVER, PRESSED};

class Button : public Entity
{
public:
	Button(sf::Vector2f position, sf::Texture * texture, sf::Vector2f size,
		sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,sf::Font * font,
		std::string value, int textSize, sf::Color textColor);
	~Button();

	void update(double deltaT) override;
	void draw(sf::RenderWindow * w) override;

	void checkState(sf::Vector2f mousePos); //Checks if the Button is Idle,Hover, or Pressed

	bool isPressed(); //Determines if the Button is Pressed 

	//Setter
	void setTextPos(sf::Vector2f newPos);
	void setText(std::string newText); //Changes the Strings Text

	//Getters
	std::string getText() const; //Returns the 

private:
	//Buttons Body included in Entity

	sf::Text text; //The Text of the Button
	ButtonState state; //Determines what state the Button is in 

	sf::Color idleColor; //Holds the Idle Color
	sf::Color hoverColor;
	sf::Color pressedColor;
};

#endif