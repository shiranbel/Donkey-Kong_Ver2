#include "ghost.h"
#include <iostream>
#include <random> // For random number generation

// this function return if ghost need change her direction according to probability 
bool Ghost:: getRandomBoolean() const {
	int randomValue = rand() % 100;                     // Generates a number between 0 and 99
	return randomValue < CHANGE_DIR_PROBABILITY;        // 5% chance to be true
}

// this function handles the movement of the ghost by checking the situation at next and under positions
void Ghost::move() {
	Position currPos = getPosition();
	Position newPos = { currPos.getX() + dir.x, currPos.getY() + dir.y };               // get the next position of the barrel
	char next_pos_ch = pBoard->getCharFromCurr(newPos.getX(), newPos.getY());                       // gets the next position's char
	char curr_pos_ch_under = pBoard->getCharFromCurr(currPos.getX(), currPos.getY() + 1); // gets the char below the next position
	char next_pos_ch_under = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY() + 1);         // gets the next char below the next position
	
	// if the ghost's curr position under is at the border and the new Y-coordinate is within the screen height
	if (curr_pos_ch_under == Board::SPACE && newPos.getY() < GameConfig::MAX_HEIGHT) {
		dir = { 0,1 };    // free fall
		setPos(newPos);
		return;
	}
	if (dir.y == 1) {						// when the ghost is falling 
		// if next ghost's pos is on floor or out border high
		if (isOnFloor(next_pos_ch) || newPos.getY() >= GameConfig::MAX_HEIGHT) {		
			dir = { 1, 0 };					
			return;							// finish here
		}
	}
	// check for wall or specific character
	if (isOnFloor(next_pos_ch) || next_pos_ch_under == Board::SPACE || next_pos_ch == (char)Board::characters::ghost_s || newPos.getX() >= GameConfig::MAX_WIDTH) {
		dir.x *= -1; // change direction
		return;
	}
	if (getRandomBoolean()) {
		dir.x *= -1; // change direction
		return;
	}

	setPos(newPos);    // set position
}



