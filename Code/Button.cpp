#include "Button.h"



Button::Button(sf::Vector2f position, sf::Texture * texture, sf::Vector2f size,
	sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Font * font,
	std::string value, int textSize, sf::Color textColor)
	: Entity(position, texture)
{
	Entity::setSize(size); //Updating the Buttons Size 

	this->state = IDLE; //Initially the Button is in Idle State

	//Setting the Colors 
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	//Setting the Buttons Text
	this->text.setFont(*font);
	this->text.setCharacterSize(textSize);
	this->text.setString(value);
	this->text.setFillColor(textColor);
	//Centering the Text in the Middle of the Button
	this->text.setPosition(Entity::getSize()); 
}


Button::~Button()
{
}


//Update Function for the Button
void Button::update(double deltaT)
{
}

//Draws the Body and Text

void Button::draw(sf::RenderWindow * w)
{
	w->draw(Entity::getBody()); //Drawing the Body
	w->draw(this->text); //Drawing the Text
}


//Checks if the Button is Idle,Hover, or Pressed
void Button::checkState(sf::Vector2f mousePos)
{
	this->state = IDLE; //Default Button is Idle

	//If the Mouse is Hovering Over the Button then its Hover
	if (Entity::getBody().getGlobalBounds().contains(mousePos))
	{
		this->state = HOVER; //Then its Hovered
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Then its Pressed
			this->state = PRESSED;
		}
	}
	switch (this->state)
	{
	case IDLE:
		Entity::setFillCol(this->idleColor);
		break;
	case HOVER:
		Entity::setFillCol(this->hoverColor);
		break;
	case PRESSED:
		Entity::setFillCol(this->pressedColor);
		break;
	default:
		Entity::setFillCol(sf::Color::Red); //SHOULDNT HAPPEN 
	}
}

bool Button::isPressed()
{
	if (this->state == PRESSED)
	{
		return true;
	}
	//Else
	return false;
}

//Setter
void Button::setTextPos(sf::Vector2f newPos)
{
	this->text.setPosition(newPos);
}

void Button::setText(std::string newText)
{
	this->text.setString(newText);
}

//Getter

std::string Button::getText() const
{
	return this->text.getString(); //Returning the String
}