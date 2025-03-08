#include "hero.h"
#include "position.h"
#include "ghost.h"
#include "barrel.h"



// this function erases mario from the screen
void Hero::erase() {
	// check which mode the board is in
	if (pBoard->getSetColor()) {										// if color mode
		char ch = pBoard->getCharFromOriginal(pos.getX(), pos.getY());	// get the char from the current position in the original board
		switch (ch) {													// check in which color do you need to restore now
		case (char)Board::Floor_chars::ladder:							// for ladder
			pBoard->setColor((int)Board::colors::console);
			break;
		default:														// for others
			pBoard->setColor((int)Board::colors::cyan);
			break;
		}
		draw(pBoard->getCharFromOriginal(pos.getX(), pos.getY()));		// restore the character from the original board
		pBoard->setColor((int)Board::colors::console);				    // bring back console color
	}
	else                // if black and white mode
		draw(pBoard->getCharFromOriginal(pos.getX(), pos.getY()));		// restore using console color
}

// this function makes sure that mario is jumping with a height of 2 chars 
void Hero::handleJump() {
	if (jump_counter == 1)
		++jump_counter;
	else if (jump_counter == GameConfig::JUMP_H) // when getting to the top free fall
		jump_counter = 0;
}

// this function takes the pressed key and changes the dir accordingly by checking the current, next and below chars
void Hero::keyPressed(char key) {

	char curr_pos_ch = pBoard->getCharFromOriginal(pos.getX(), pos.getY());				// get the char at the current position
	char curr_pos_ch_under = pBoard->getCharFromOriginal(pos.getX(), pos.getY() + 1);	// get the char below the current position

	// traverse the keys array
	for (size_t i = 0; i < numKeys; i++) {

		if (std::tolower(key) == (char)keys::up) {										// handle up movement
			if (curr_pos_ch != (char)Board::Floor_chars::ladder && !isOnFloor(curr_pos_ch)) {			// jump - if my position is not ladder or floor	
				if (!isOnFloor(curr_pos_ch_under)) { break; }                           // checks if is there a floor under mario - to avoid double jump
				else if (jump_counter < GameConfig::JUMP_H) {							// change direction to up (without changing x direction) and add to jump counter
					dir.y = -1;
					jump_counter++;
				}
			}
			else {																		// climb
				dir = { 0, -1 };														// change direction to straight up
			}
			break;
		}
		else if (std::tolower(key) == (char)keys::down) {								// go down
			if (!isOnFloor(curr_pos_ch_under) && curr_pos_ch != (char)Board::Floor_chars::ladder) { break; }	// block going down while jumping
			else {
				dir = { 0, 1 };															// change direction to straight down
				pressedDown = true;														// remember that it's down from the player and not free fall
			}
		}
		else if (std::tolower(key) == (char)keys::stay) {								// stay 
			if (!isOnFloor(curr_pos_ch_under) && curr_pos_ch != (char)Board::Floor_chars::ladder) { break; }	// block stay while jumping
			else {
				dir = { 0, 0 };															// change direction to stay
			}
		}
		else if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

// this function let mario attack and check if mario is hit on ghost or barrel and increasing the score if necessary
void Hero::attack(std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels) {
	// new positions based on hero's direction
	Position newNextPos = { pos.getX() + ( 2*dir.x ) , pos.getY() + dir.y }; 	
	Position newPos = { pos.getX() + dir.x , pos.getY() + dir.y };
	// get the character from curr board
	char pos_ch = pBoard->getCharFromCurr(newPos.getX(), newPos.getY());
	char next_pos_ch = pBoard->getCharFromCurr(newNextPos.getX(), newNextPos.getY());
	int index_ghost = 0, index_barrel = 0;
	
	// if mario not attack on floor character
	if (!isOnFloor(pos_ch)) {
		gotoxy(newPos.getX(), newPos.getY());
		std::cout << (char)Board::characters::weapon;     // print attack animation
		Sleep(ATTACK_SLEEP_DURATION);
		gotoxy(newPos.getX(), newPos.getY());             // erase
		std::cout << Board::SPACE;
	}
	// if a ghost is hit by the hero's attack, remove it and add score
	if (pos_ch == (char)Board::characters::ghost_s || next_pos_ch == (char)Board::characters::ghost_s) {
		score += GameConfig::HIT_POINTS;
		for (auto& ghost : ghosts) {
			if (ghost.getPosition() == newPos || ghost.getPosition() == newNextPos) {
				ghost.setIsHit(true);  // update ghost hit mode
				ghost.erase();
				ghosts.erase(ghosts.begin() + index_ghost);  // remove
			}
			index_ghost++;
		}
	}
	// if a barrel is hit by the hero's attack, remove it and add score
	if (pos_ch == (char)Board::characters::barrel || next_pos_ch == (char)Board::characters::barrel) {
		score += GameConfig::HIT_POINTS;
		for (auto& barrel : barrels) {
			if (barrel.getPosition() == newPos || barrel.getPosition() == newNextPos) {
				barrel.setIsHit(true);   // update barrel hit mode
				barrel.erase();
				barrels.erase(barrels.begin() + index_barrel);  // remove
			}
			index_barrel++;
		}
	}
}

// this function handles the movement of mario by changing it's position according to the hero's situation and dir
void Hero::move() {
	Position newPos = { pos.getX() + dir.x, pos.getY() + dir.y };
	char next_pos_ch = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY());		// get the char of the next position

	// borders check
	if (newPos.getY() >= GameConfig::MAX_HEIGHT || newPos.getY() < 0) { // if yes, fall and look for obstacle
		dir.y = 0;
		pos.setX(pos.getX() + dir.x);													// change position
		pos.setY(pos.getY() + dir.y);
		if (fall_counter >= GameConfig::MIN_FALL_HEIGHT_MARIO)								// handle fall damage
			is_falling = true;
		else fall_counter = 0;
		return; // finish here
	}
	if (newPos.getX() >= GameConfig::MAX_WIDTH || newPos.getX() < 0) {
		dir.x = 0;	
		char ch_under = pBoard->getCharFromCurr(pos.getX(), pos.getY() + 1);
		if (isOnFloor(ch_under))
			dir.y = 0;// if yes, fall and look for obstacle
		pos.setX(pos.getX() + dir.x);													// change position
		pos.setY(pos.getY() + dir.y);
		return; // finish here
	}

	// free fall: check if there's no floor underneath and we are not in a middle of a jump
	if (pBoard->getCharFromOriginal(pos.getX(), pos.getY() + 1) == Board::SPACE && jump_counter == 0) {
		fall_counter++;
		dir.y = 1;									// fall and look for obstacles
		Position newPos = { pos.getX() + dir.x, pos.getY() + dir.y };
		char next_pos_ch = pBoard->getCharFromCurr(newPos.getX(), newPos.getY());
		if (next_pos_ch == (char)Board::characters::hammer_s ) {
			with_hammer = true;
			gotoxy(newPos.getX(), newPos.getY());
			std::cout << Board::SPACE;
			pBoard->deleteHammer();
		}
		if (isOnFloor(next_pos_ch)) 				// check if it's an obstacle
			dir = { 0, 0 };

		pos.setX(pos.getX() + dir.x);				// change position
		pos.setY(pos.getY() + dir.y);
		return;										// finish here
	}
	
	if (next_pos_ch == (char)Board::characters::hammer_s) {
		with_hammer = true;
		pBoard->updateHammer(with_hammer);
		pBoard->updateCurrBoard(newPos, Board::SPACE);
		pBoard->deleteHammer();
	}
	if (dir.x != 0) {																			// if there's a movement in x direction
		// check if in my current position i'm on floor
		char ch_under = pBoard->getCharFromCurr(pos.getX(), pos.getY() + 1);					// get the char below my current position 
		char next_pos_ch_under = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY() + 1);	// get the char below my next position
		if (isOnFloor(ch_under) || newPos.getY() == (GameConfig::MAX_HEIGHT - 1)) {				// if i'm standing on a floor
			if (fall_counter >= GameConfig::MIN_FALL_HEIGHT_MARIO)								// handle fall damage
				is_falling = true;
			else fall_counter = 0;
		}
		if (!isOnFloor(next_pos_ch_under) && dir.y == 1) {										// handle landing on edge of floor
			dir.y = 0;
			return;
		}
		if (isOnFloor(next_pos_ch)) {															// if my next position is a floor - stop
			dir.y = 0;
			return;
		}
		if (ch_under == (char)Board::Floor_chars::ladder && jump_counter == 0) {				// handle being on a ladder when jumping
			dir.y = 1;
			pos.setX(pos.getX() + dir.x);														// change position
			pos.setY(pos.getY() + dir.y);
			return;																				// finish here
		}
	}
	
	else if (dir.y == -1  && jump_counter == 0 ) {												// handle climbing
		char curr_pos_ch = pBoard->getCharFromCurr(pos.getX(), pos.getY());						// get the current position char
		if (curr_pos_ch == Board::SPACE || next_pos_ch == (char)Board::Floor_chars::border) {	// stop above a floor
			dir = { 0, 0 };
			pos.setX(pos.getX() + dir.x);
			pos.setY(pos.getY() + dir.y);
			return;
		}
	}
	else if (dir.y == 1) {																		// down
		char under_floor_ch = pBoard->getCharFromCurr(newPos.getX(), newPos.getY() + 1);		// get the char under the floor
		if (under_floor_ch == (char)Board::Floor_chars::ladder && pressedDown) {				// if theres a ladder and i'm not free falling
			pressedDown = false;
			erase();																			// force down
			pos = newPos;
			draw();
		}
		else if (isOnFloor(next_pos_ch) || newPos.getY() == (GameConfig::MAX_HEIGHT - 1)) {		// if there's no ladder stay
			dir = { 0, 0 };																		// stay on floor
			if (fall_counter >= GameConfig::MIN_FALL_HEIGHT_MARIO) {							// handle fall damage
				is_falling = true;
			}
			else fall_counter = 0;
			return;
		}
	}
	else if (dir.y == -1 && dir.x == 0) {
		char ch_above = pBoard->getCharFromCurr(newPos.getX(), newPos.getY());
		if (isOnFloor(ch_above)) {																// stop above a floor
			dir = { 0, 0 };
			pos.setX(pos.getX() + dir.x);
			pos.setY(pos.getY() + dir.y);
			return;
		}
	}

	pos = newPos;																				// update position
}

// this function reposition mario to the starting position when eliminated by barrels or fall damage
void Hero::resetMario() {
	with_hammer = false;
	is_falling = false;
	fall_counter = 0;
	pos = pBoard->getStartPosHero();
	dir = { 0, 0 };
}