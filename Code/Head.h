#ifndef HEAD_H
#define HEAD_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>
#include "Tail.h"


//Used to Determine the Heads Direction
enum DIRECTION{ UP = 0, RIGHT, DOWN, LEFT };

class Head : public Entity
{
public:
	Head(sf::Vector2f position, sf::Texture * texture);
	~Head();

	void draw(sf::RenderWindow* w) override;

	void update(double deltaT) override;

	void keyboardInput(); //Edits the Heads Direction Depending on the Key Pressed

	void growTail(); //Grows a Tail When Called 

	void updateTails();//Updates the Tails Position so that they follow the head

	bool headToTail(); //Checks if the Head is touching the tail

private:
	DIRECTION dir; //Heads Direction

	double counter; //Controls Timer
	std::vector <Tail *> tail;
	sf::Texture tailTexture;
};

#endif
