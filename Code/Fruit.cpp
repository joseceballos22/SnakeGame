#include "Fruit.h"



Fruit::Fruit(sf::Vector2f position, sf::Texture * texture)
	:Entity(position, texture)
{
	this->collide = false; //Initially False
	srand(time(0)); //Random Seed
}


Fruit::~Fruit()
{
}


void Fruit::update(double deltaT)
{
	if (this->collide == true)
	{
		//Spawn in a Random Location 
		int randNumX = rand() % 740 + 40; //Numbers between 40 - 740

		int randNumY = rand() % 600 + 40; 

		Entity::setPos(sf::Vector2f(randNumX, randNumY));
		
		this->collide = false; //Resetting it
	}
}


//Setter
void Fruit::setCollide(bool newCollide)
{
	this->collide = newCollide;
}
