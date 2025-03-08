#pragma once
#include "enemy.h"

class Barrel : public Enemy {

	int fall_counter = 0;	                  // counter for checking fall damage 
	Direction last_dir = { 0,0 };	          // for saving last direction
	bool is_on_border = false;                // for check if barrel is on border
	 
	static constexpr int EXPLODE_SLEEP_DURATION = 20;    // explode sleep for animation

public:

	// ctors
	Barrel(Board* pboard) : Enemy(pboard) {
		setPos(pBoard->getStartPosDkong());
		dir = { 0,0 };
		symbol = (char)Board::characters::barrel;
	}
	Barrel() {}

	// methods
	void drawExplode();										// draws the explosion both on screen and current board with explosion effect
	void eraseExplode();									// erases the explosion both on screen and current board and restores from original						
	virtual void move() override;				     		// changes the barrel's position
	bool getIsOnBorder() const { return is_on_border; }     // return isOnBorder data member
};

