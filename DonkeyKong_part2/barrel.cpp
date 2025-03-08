#include "barrel.h"

// Draws all the relevant collision points of the barrel's explosion in current map
void Barrel::drawExplode() {
	int y = getPosition().getY();
	int x = getPosition().getX();
	// start from the top left corner
	for (int row = y - GameConfig::EXPLOSION_RADIUS; row <= y + GameConfig::EXPLOSION_RADIUS; row++) {
		for (int col = x - GameConfig::EXPLOSION_RADIUS; col <= x + GameConfig::EXPLOSION_RADIUS; col++) {
			Position pos = { col, row };
			// check if pos is out of border
			if (!(col >= GameConfig::MAX_WIDTH  || row >= GameConfig::MAX_HEIGHT )) {
				char ch = pBoard->getCharFromOriginal(col, row);
				// check if there's no obstacle in the printing 
				if (!isOnFloor(ch)) {						// draw only if there's no obstacle
					pBoard->updateCurrBoard(pos, symbol);	// draws in current board
					// explosion effect
					gotoxy(col, row);
					std::cout << '\'';
				}
			}
		}
	}
	Sleep(EXPLODE_SLEEP_DURATION);
}

// Erases all the relevant collision points of the barrel's explosion from current map
void Barrel::eraseExplode() {
	int y = getPosition().getY();
	int x = getPosition().getX();
	// start from the top left corner
	for (int row = y - GameConfig::EXPLOSION_RADIUS; row <= y + GameConfig::EXPLOSION_RADIUS; row++) {
		for (int col = x - GameConfig::EXPLOSION_RADIUS; col <= x + GameConfig::EXPLOSION_RADIUS; col++) {
			Position pos = { col, row };
			// check if pos is out of border
			if (!(col >= GameConfig::MAX_WIDTH  || row >= GameConfig::MAX_HEIGHT)) {
				char ch = pBoard->getCharFromOriginal(col, row);
				// check if there's no obstacle in the erasing
				if (!isOnFloor(ch)) {					// erases only if there's no obstacle
					pBoard->updateCurrBoard(pos, ch);	// erases in the current board
					// explosion effect
					gotoxy(col, row);
					std::cout << Board::SPACE;
				}
			}
		}
	}
}

// this function handles the movement of the barrel by checking the situation at next and under positions
void Barrel::move() {
	Position currPos = getPosition();
	Position newPos = { currPos.getX() + dir.x, currPos.getY() + dir.y };		// get the next position of the barrel
	char next_pos_ch = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY());			// gets the next position's char
	char next_pos_ch_under = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY() + 1); // gets the char below the next position
	
	// if the barrel's next position is at the border and the new Y-coordinate is within the screen height
	if (next_pos_ch == (char)Board::Floor_chars::border && newPos.getY() < GameConfig::MAX_HEIGHT) {				
		is_on_border = true;                            // update is_on_border
		erase();                                        // erase barrel from screen
		return;
	}
	if (next_pos_ch_under == Board::SPACE) {			// if nothing below fall
		dir = { 0,1 };
		fall_counter++;                                 // increase fall damage counter
	}
	if (dir.y == 1) {		     // when the barrel is falling				                                             
		// if next barrel's pos is on floor or out border high
		if (isOnFloor(next_pos_ch) || newPos.getY() >= GameConfig::MAX_HEIGHT) {		
			dir = { 0, 0 };	     // stay and check if it's fall damaged
			// check fall damage size
			if (fall_counter >= GameConfig::MIN_FALL_HEIGHT_BARREL) {
				isHit = true;
			}
			else {               // reset fall counter
				fall_counter = 0;
			}
			return;				 // finish here
		}
	}
	else{ // if there is a floor below follow it's direction 
		char curr_ch_under = pBoard->getCharFromOriginal(currPos.getX(), currPos.getY() + 1);	// get the char below the current position

		if (curr_ch_under == (char)Board::Floor_chars::right) {			
			last_dir = dir;
			dir = { 1, 0 };    // go right
		}
		else if (curr_ch_under == (char)Board::Floor_chars::left) {	
			last_dir = dir;
			dir = { -1, 0 };   // go left
		}
		else if (curr_ch_under == (char)Board::Floor_chars::equal) {	
			dir = last_dir;    // move according to your last direction
		}

		if (next_pos_ch == (char)Board::Floor_chars::border) {			
			dir = { 0, 0 };    // if collides with border stay 
			return;
		}
	}
	setPos(newPos);            // update position
}


