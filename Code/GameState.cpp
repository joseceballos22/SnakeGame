#include "GameState.h"
#include <iostream>


GameState::GameState()
{

	//Initializing Textures
	this->headTexture.loadFromFile("Sprites/head.png");
	this->fruitTexture.loadFromFile("Sprites/fruit.png");

	//Initializing Head
	this->head = new Head(sf::Vector2f(400, 400), &headTexture);

	srand(time(0));
	int randNum = rand() % 740 + 40;

	//Initializing Fruit
	this->fruit = new Fruit(sf::Vector2f(randNum, randNum), &fruitTexture);

	this->initBorder(); //Initializes the Border Stuff

	this->counterHF = 0; //Counter for Head Fruit Collision
	this->counterHT = 0; //Counter for Head Tail Collision
	this->counterHB = 0; //Counter for Head Border Collision
	this->pauseCounter = 0; //Counter for the Pause Button


	//Initializing the Background of the GameStates
	this->background.setPosition(sf::Vector2f(0, 0));
	this->background.setFillColor(sf::Color(100, 100, 100)); 

	this->font.loadFromFile("Fonts/DejaVuSans.ttf");

	this->pause = false; 
	this->pauseText.setString("Pause");
	this->pauseText.setPosition(sf::Vector2f(300, 300));
	this->pauseText.setFont(font);
	this->pauseText.setCharacterSize(60);

	this->scoreTexture.loadFromFile("Sprites/blank.png");

	//Setting the ScoreButton
	this->scoreButton = new Button(sf::Vector2f(80,60), &this->scoreTexture, sf::Vector2f(100, 40), sf::Color::Cyan,
		sf::Color::Cyan, sf::Color::Cyan, &this->font, std::to_string(State::getHolderScore()) , 40, sf::Color::Black);
	this->scoreButton->setTextPos(sf::Vector2f(700, 40));

}


GameState::~GameState()
{
	std::cout << "Deleting Head" << std::endl;
	std::cout << "Deleting Fruit" << std::endl;
	delete this->head;
	delete this->fruit;

	//Deallocating Memory of the Borders
	for (int i = 0; i < this->borders.size(); i++)
	{
		delete borders[i];
	}
	delete this->scoreButton; //Deallocating Button Memory 
}

//Updates all the Components of the State
void GameState::update(double deltaT)
{
	this->updateKeyBinds(deltaT); //Checking if the User Wants to Quit the GameState
	
	//If the game is not paused Update the head and fruit Otherwise DONT 
	if (this->pause == false)
	{
		this->head->update(deltaT);
		this->fruit->update(deltaT);
	}
}

//Draws all the Components of the State
void GameState::draw(sf::RenderWindow * w)
{
	//Setting the Background Size to that of the Window	(MUST BE DRAWN FRIST)
	this->background.setSize(sf::Vector2f(w->getSize().x, w->getSize().y));
	w->draw(this->background);


	this->head->draw(w);
	this->fruit->draw(w);
	
	//Drawing the Border
	for (int i = 0; i < this->borders.size(); i++)
	{
		this->borders[i]->draw(w); //Drawing the Borders to the Screen
	}

	if (pause == true)
	{
		//Draw PauseText
		w->draw(this->pauseText); 
	}

	this->scoreButton->draw(w); //Drawing the Score Button to the Screen

}

//Processes All the Components of the State (e.g. Collision Detection)
void GameState::processStuff(double deltaT, sf::Vector2f mousePos)
{
	//Checking Collision Between The Fruit and the Head

	//If this is true they are Colliding 
	if (this->head->getCollider().checkCollision(this->fruit->getCollider()) == true)
	{
		if (counterHF >= 0.3)
		{
			std::cout << "Head And Fruit Are Colliding " << std::endl;
			this->head->growTail(); //Grows the Snake Tail
			this->fruit->setCollide(true); //Moving Fruit
			State::setHolderScore(State::getHolderScore() + 1);
			this->scoreButton->setText(std::to_string(State::getHolderScore())); //Updating the ScoreBoard
			counterHF = 0; //Resetting the Counter
		}
	}

	//Checking if the Head Is Colliding with the Tail
	if (this->head->headToTail() == true)
	{
		if (counterHT >= 0.3)
		{
			std::cout << "Head Touched Tail " << std::endl;
			counterHT = 0; //Resetting Counter
			State::setQuit(true);//Game Over 
		}
	}

	//Checking if the Head is Colliding with the Border

	for (int i = 0; i < this->borders.size(); i++)
	{
		//If the Head and Border are colliding 
		if (this->head->getCollider().checkCollision(this->borders[i]->getCollider()) == true)
		{
			if (counterHB >= 0.3)
			{
				std::cout << "Head is Touching the Border " << std::endl;
				counterHB = 0; //Resetting Counter 
				State::setQuit(true);//Game Over
			}
		}
	}




	counterHF += deltaT; //Head Fruit Collision Counter
	counterHT += deltaT; //Head Tail Collision Counter
	counterHB += deltaT; //Head Border Collision Counter

}

//Defines all the Keyboard Stuff for that state
void GameState::updateKeyBinds(double deltaT)
{
	State::checkForQuit(); //Updates The State::quit if the Key is pressed 

	//Pauses the Game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (pauseCounter >= 0.3)
		{
			if (this->pause == false)
			{
				this->pause = true;
			}
			else
			{
				this->pause = false; //Resetting it 
			}
			std::cout << "Pausing Screen " << this->pause<<  std::endl;
			pauseCounter = 0; //Resetting the Counter
		}
	}
	pauseCounter += deltaT; 
}


//Initializes the Border Stuff
void GameState::initBorder()
{
	this->borderTexture.loadFromFile("Sprites/wall.png");

	int amountNeeded = 83;//Need 76 Borders to Cover the 800x800 Window Sizes Each Border 40x40 
	/*
		20 needed
		_____ 
	18  |    | 18
		|    |
		------
		20 needed 
	*/

	//Position for the Borders
	sf::Vector2f pos(0, 0);

	int flag = 0;//Helps update the position

	for (int i = 0; i < amountNeeded; i++)
	{
		this->borders.push_back(new Border(pos, &this->borderTexture));

		if (i < 20) //Updating the Position for the Long lines 
		{
			pos.x += 40;
			pos.y = 0; 
		}
		else if (i < 60 && i >= 20) //Updating the Position for the border Lines  |     |
		{
			if (i % 2 == 0)
			{
				//i is even
				pos.x = 0;
			}
			else
			{
				//i is odd 
				pos.x = 800;
			}
			if (flag == 2)
			{
				//Update the y POSITION
				pos.y += 40;
				flag = 0; //Resetting Flag
			}
			flag++; //Updating Flag 
		}
		else if (i >= 60)//Updating the Position for the Long lines LAST ONE
		{
			if (i == 60)
			{
				pos.x = 0;//Reset the Starting Position
				pos.y = 800;
			}
			else
			{
				pos.y = 800;
				pos.x += 40;
			}
		}
	}
}
