#pragma once

#include "board.h"
#include "gameConfig.h"
#include "position.h"

class Hero {
	// movement
	struct Direction { int x, y; };									// creating a struct called direction
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

	// keys
	static constexpr char keys[] = {'w', 'a', 'x', 'd', 's'};
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	static constexpr int ATTACK_SLEEP_DURATION = 40;
	char symbol = (char)Board::characters::hero;	                // his visual on screen
	int score = 0;                                                  // his score                                  
	int jump_counter = 0;											// counter for checking jump height
	int fall_counter = 0;											// counter for checking fall damage
	int lives = GameConfig::MAX_LIFE;								// representing remaining lives

	bool pressedDown = false;										// checks if the down movement is from free fall or by player
	bool is_falling = false;                                        // flag for if the hero is about to get fall damage
	bool with_hammer = false;                                       // flag for check when mario has a hammer  

	Position pos;	                                                // representing the Hero's position
	Direction dir{ 0, 0 };											// current direction: dir.x, dir.y
	Board* pBoard = nullptr;										// to give it a board

	void draw(char c) const {										// draws a given char at the hero's position
		gotoxy(pos.getX(), pos.getY());
		std::cout << c;
	}

public:
	// ctor
	Hero(Board* pboard) : pBoard(pboard) { 
		pboard->updateLives(lives);
		pos= pBoard->getStartPosHero();
	}
	Hero() {}

	// movement
	void draw() const { draw(symbol); }								// draws the Hero on screen
	void erase();													// erases the hero on screen
	void move();													// changes the hero's position
	void keyPressed(char key);										// gets the key that was pressed by the user

	// getters
	int getJumpCount() const { return jump_counter; }				// return the jump counter
	int getWithHammer() const { return with_hammer; }				// return with hammer
	int getLife() const { return lives; }							// returns the remaining lives
	int getScore() const { return score; }							// returns the remaining score
	bool getIsFalling() const { return is_falling; }				// checks if he is about to get fall damage
	Position getPosition() const { return pos; }					// return the hero's current position
	Board* getBoard() const { return pBoard; }						// returns a pointer to the hero's board

	// setters
	void setBoard(Board* board) {
		this->pBoard = board;
		pBoard->updateLives(lives);
		pBoard->updateScore(score);
		resetMario();
	}
	void setScore(int curr_score) { score = curr_score; }


	bool isOnFloor(char ch) const { return (ch == (char)Board::Floor_chars::border || ch == (char)Board::Floor_chars::equal || ch == (char)Board::Floor_chars::right || ch == (char)Board::Floor_chars::left); } // checks if a given char is a floor character
	bool isCollision() const {return (pBoard->getCharFromCurr(pos.getX(), pos.getY()) == (char)Board::characters::barrel || pBoard->getCharFromCurr(pos.getX(), pos.getY()) == (char)Board::characters::ghost_s);} // checks if the hero's position is on barrel
	void changelives() {		// decreaces the remaining lives by 1
		lives--;
		pBoard->updateLives(lives);	// reprint the remaining lives according to the change
	}        
	void resetMario();								 						// repositions the hero to the starting position
	void handleJump();                                                      // changes the jump counter according to the hero's position
	void attack(std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels);  // let mario attack ghosts and barrels and sum his score   

	enum class keys {
		up = 'w',
		left = 'a',
		right = 'd',
		stay = 's',
		down = 'x',
		attack = 'p',
	};
};
