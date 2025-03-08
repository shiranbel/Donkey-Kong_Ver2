#pragma once
#include "enemy.h"

class Ghost : public Enemy{
	static constexpr int CHANGE_DIR_PROBABILITY = 5;
public:
	// ctors
	Ghost(Board* pboard) : Enemy(pboard) { 
		setPos(pBoard->getStartPosGhost());
		dir = { 1,0 };
		symbol = (char)Board::characters::ghost_s;
	}
	Ghost() {}
										
	bool getRandomBoolean() const;           //  get if ghost need change her direction according to probability   
	virtual void move() override;            // changes the barrel's positio      
};

