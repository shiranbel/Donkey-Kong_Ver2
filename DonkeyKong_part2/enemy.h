#pragma once
#include "board.h"
#include "position.h"

class Enemy
{
	Position pos;
protected:
	struct Direction { int x, y; };						// creating a struct called direction
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
	
	char symbol;                                        // his visual on screen
	void draw(char c) const {							// this function prints a char on screen in current position
		gotoxy(pos.getX(), pos.getY());
		std::cout << c;
	}
	bool isHit = false;                                 // for check enemy existence
		                    
	Direction dir;							            // representing the barrel's direction				
	Board* pBoard = nullptr;                            // to give it a board

public:
	//ctor
	Enemy(Board* pboard) : pBoard(pboard) {}
	Enemy() {}

	// movement
	void draw() const {	                      // draws the enemy both on screen and in current board
		draw(symbol);
		pBoard->updateCurrBoard(pos, symbol); // draws symbol in current board
	}      
	void erase();                             // eraces a enemy from screen
	virtual void move() = 0;
	// checks if the given char is a floor character 
	bool isOnFloor(char ch) const { return (ch == (char)Board::Floor_chars::border || ch == (char)Board::Floor_chars::equal || ch == (char)Board::Floor_chars::right || ch == (char)Board::Floor_chars::left); }

	// getters
	bool getIsHit() const { return isHit; }             // returns enemy state, hit/ not hit
	Board* getBoard() const { return  pBoard; }			// returns pointer to the enemy's board
	Position getPosition() const { return pos; }        // returns enemy position

	// setters
	void setIsHit(bool is_hit) { isHit = is_hit; }      // sets is hit mode
	void setPos(Position new_pos) { pos = new_pos; }    // sets position
};