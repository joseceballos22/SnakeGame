#include "Entity.h"
#include <iostream>


Entity::Entity(sf::Vector2f position, sf::Texture *texture)
{

	this->c = new Collider(&this->body);
	this->body.setSize(sf::Vector2f(40, 40)); //Every Entity By Default is 40 by 40

	//Setting the Origin For All Entities
	this->body.setOrigin(this->body.getSize().x / 2.0f, this->body.getSize().y / 2.0f); 
	this->body.setPosition(position);
	this->body.setTexture(texture);
}


Entity::~Entity()
{
	std::cout << "Deallocating Collider" << std::endl;
	delete c; //Deallocate Memory  
}


void Entity::draw(sf::RenderWindow * w)
{
	w->draw(this->body); //Drawing the Body to the Window
}

//Getters
sf::Vector2f Entity::getPos() 
{
	return this->body.getPosition();
}
Collider Entity::getCollider()
{
	return *c;
}

sf::RectangleShape Entity::getBody()
{
	return body;
}

sf::Vector2f Entity::getSize()
{
	return body.getSize();
}

//Setters
void Entity::setPos(sf::Vector2f newPos)
{
	this->body.setPosition(newPos);
}


void Entity::setSize(sf::Vector2f newSize)
{
	this->body.setSize(newSize);
}

//Changes the Bodies Fill Color
void Entity::setFillCol(sf::Color newColor)
{
	this->body.setFillColor(newColor);
}