#include "Collider.h"
#include <cmath>
#include <iostream>


Collider::Collider(sf::RectangleShape* body)
	:body(body)
{
}


Collider::~Collider()
{
}


//Returns True If The Two Entities Are colliding Or Returns False If they Are not
bool Collider::checkCollision(const Collider& other)
{
	//std::cout << "Fruit POS" << other.getPos().x << " , " << other.getPos().y << std::endl;
	
	//Distance Between the centers of each Entity 
	sf::Vector2f delta(this->getPos() - other.getPos());

	sf::Vector2f halfSize(this->getHalfSize() + other.getHalfSize());


	if (abs(delta.x) - halfSize.x < 0 && abs(delta.y) - halfSize.y < 0)
	{
		return true;//Objects Colliding 
	}

	//Else 
	return false; //Objects Not Colliding 
}


//Getters
sf::Vector2f Collider::getHalfSize() const
{
	return sf::Vector2f(body->getSize().x / 2.0f, body->getSize().y / 2.0f);
}


sf::Vector2f Collider::getPos() const
{
	return sf::Vector2f(body->getPosition());
}