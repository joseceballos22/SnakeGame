#include "LostState.h"
#include <iostream>


LostState::LostState()
{


	this->font.loadFromFile("Fonts/DejaVuSans.ttf");
	this->backgroundTexture.loadFromFile("Sprites/lost.png");


	this->score = nullptr;//Initially Pointing to Nothing

	//Initializing the Player Score Text 
	this->playerScore.setPosition(sf::Vector2f(350, 200));
	this->playerScore.setFillColor(sf::Color::Black);
	this->playerScore.setFont(this->font);
	this->playerScore.setCharacterSize(80);


	//Initializing the Play Button Text 
	this->playAgain = new Button(sf::Vector2f(275,400),nullptr,sf::Vector2f(300,100),
		sf::Color(200,200,200), sf::Color(140,140,140), sf::Color(100,100,100), &this->font, "Play Again",
		45,sf::Color::Black);
	this->playAgain->setTextPos(sf::Vector2f(300, 400));

	//Initializing the BackGround 
	this->background.setSize(sf::Vector2f(800, 800));
	//this->background.setFillColor(sf::Color::Cyan);
	this->background.setTexture(&this->backgroundTexture);
}


LostState::~LostState()
{
	delete this->playAgain; //Deallocates Memory 
}



//Updates the Components in the State
void LostState::update(double deltaT)
{
	this->updateKeyBinds(deltaT); //Checking if the User wants to Quit the State 
}

//Draws the Components in the State
void LostState::draw(sf::RenderWindow * w)
{
	//Drawing the Background FIRST 
	w->draw(this->background);
	//Drawing the Buttons in the State 
	w->draw(this->playerScore); //Draws the Player Score to the Window
	this->playAgain->draw(w); //Draws the Play Again Button
}

//Processes the Components in the State 
void LostState::processStuff(double deltaT, sf::Vector2f mousePos)
{
	//Updates the Text Score
	this->playerScore.setString(std::to_string(State::getHolderScore()));
	this->playAgain->checkState(mousePos);
}

//Updates the Key presses in the State
void LostState::updateKeyBinds(double deltaT)
{
	State::checkForQuit(); //Checks if the User Wants to Quit
}




//Determines if the User wants to play again

bool LostState::switchState()
{
	//If they Press the PlayAgain Button Start the Game Again
	return (this->playAgain->isPressed());
}



//Updates the Players Score Text 
void LostState::setScore(std::string newScore)
{
	this->playerScore.setString(newScore);
}