#ifndef TAIL_H
#define TAIL_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Tail : public Entity
{
public:
	Tail(sf::Vector2f position, sf::Texture * texture);

	void update(double deltaT) override;
	~Tail();
};

#endif