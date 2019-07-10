#ifndef BORDER_H
#define BORDER_H


#include "Entity.h"
class Border :
	public Entity
{
public:
	Border(sf::Vector2f position, sf::Texture * texture);
	~Border();

	void update(double deltaT) override;
};


#endif