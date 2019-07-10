#include "Head.h"
#include <iostream>


Head::Head(sf::Vector2f position, sf::Texture * texture)
	:Entity(position, texture)
{
	this->dir = RIGHT; //Initially The Direction of the Snakes Head is to the RIGHT 

	this->counter = 0;

	this->tailTexture.loadFromFile("Sprites/tail.png");

	//By default The First Tail is the Head
	this->tail.push_back(new Tail(Entity::getPos(), texture));
}


Head::~Head()
{
	//Cleaning Up Memory
	for (int i = 0; i < tail.size(); i++)
	{
		delete tail[i];
	}
}


//Drawing Head And Tail

void Head::draw(sf::RenderWindow * w)
{
	w->draw(Entity::getBody()); //Drawing the Head
	for (int i = 0; i < tail.size(); i++)
	{
		w->draw(tail[i]->Entity::getBody()); //Drawing the Tails
	}
}

//Creating an Update Function for the Head 
void Head::update(double deltaT)
{
	Head::keyboardInput(); //Edits the Heads Direction Depending on the User input

	//UPDATING IT TO FAST
	//0.065
	if (counter >= 0.06)
	{

		//Snakes Head Momentum Constantly Moving 
		if (this->dir == UP)
		{
			Entity::setPos(Entity::getPos() + sf::Vector2f(0, -Entity::getSize().y));
		}
		if (this->dir == RIGHT)
		{
			Entity::setPos(Entity::getPos() + sf::Vector2f(Entity::getSize().x, 0));
		}
		if (this->dir == DOWN)
		{
			Entity::setPos(Entity::getPos() + sf::Vector2f(0, Entity::getSize().y));
		}
		if (this->dir == LEFT)
		{
			Entity::setPos(Entity::getPos() + sf::Vector2f(-Entity::getSize().x, 0));
		}
		this->updateTails(); //Updates the Tails Position
		counter = 0; //Resetting Counter
	}
	counter += deltaT;
}

//Edits the Heads direction depending on what Key is pressed
void Head::keyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dir = UP;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dir = RIGHT; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dir = DOWN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dir = LEFT;
	}
}

//Updates Tail Position so that they follow the head 
void Head::updateTails()
{
	//Start at the back 
	for (int i = tail.size() - 1; i > 0; i--)
	{
		//The position of the last equals the Position of the Prev
		tail[i]->setPos(tail[i - 1]->getPos());
	}
	//And the First One Follows the head
	if (tail.size() >= 1)
	{
		tail[0]->setPos(Entity::getPos());
	}
}

//Grows A Tail When Called 
void Head::growTail()
{
	if (this->tail.size() == 0)
	{
		this->tail.push_back(new Tail(Entity::getPos(), &this->tailTexture));
	}
	else
	{
		this->tail.push_back(new Tail(this->tail[this->tail.size()-1]->getPos(), &this->tailTexture));
	}

}


//Checks if the Head is touching the tail
//If true Head is touching tail Else False Head is Not touching Tail
bool Head::headToTail()
{
	//Only Check if a tail exists
	if (this->tail.size() > 2)
	{
		for (int i = 1; i < this->tail.size(); i++)
		{
			if (Entity::getCollider().checkCollision(this->tail[i]->getCollider()) == true)
			{
				return true;
			}
		}
	}
	//Else 
	return false;
}