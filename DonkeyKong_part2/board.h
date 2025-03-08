#pragma once
#include "gameConfig.h"
#include "position.h"
#include "utils.h"
#include <vector>

class Board {

	// maps
	char originalBoard[GameConfig::MAX_HEIGHT][GameConfig::MAX_WIDTH + 1];
	char currentBoard[GameConfig::MAX_HEIGHT][GameConfig::MAX_WIDTH + 1];

	// map properties
	bool set_color = false;	// for color options
	int index_ghosts = 0;

	// main characters position
	// initialize with "invalid position"
	Position start_pos_hero    = { ERROR_POS, ERROR_POS };     // for saving start pos of mario
	Position start_pos_dkong   = { ERROR_POS, ERROR_POS };     // for saving start pos of dkong
	Position start_pos_legend  = { ERROR_POS, ERROR_POS };     // for saving start pos of legend
	Position start_pos_pauline = { ERROR_POS, ERROR_POS };     // for saving start pos of princess
	Position start_pos_hammer;                                 // foe saving start pos of hammer
	std::vector<Position> ghosts_positions;                    // for handle all ghosts positions from map

	void reset();	// draws the board from original 

public:
	// consts
	static constexpr char SPACE = ' ';
	static constexpr int ERROR_POS = -1; 
	
	// ctor
	Board(bool with_color, const std::string& filename) {
		set_color = with_color;
		loadBoardFromFile(filename);
		reset();
	}

	void print(bool with_color) const;						            	// prints the board on screen
	void printLegend() const;												// setting the color of a printed char on screen
	void loadBoardFromFile(const std::string& filename);                    // load board map of the game from file
	void resetNumOfGhosts() { index_ghosts = 0; }                           // reset index of ghosts vector
	void deleteHammer() { originalBoard[start_pos_hammer.getY()][start_pos_hammer.getX()] = SPACE; }   // delete hammer from board after he have achieved
	void returnHammer() {                                                                              // return hammer to board after disqualification
		originalBoard[start_pos_hammer.getY()][start_pos_hammer.getX()] = (int)characters::hammer_s;
		gotoxy(start_pos_hammer.getX(), start_pos_hammer.getY());
		std::cout << (char)characters::hammer_s;
	}
	int checkAllCharacters() const;                                         // check all characters appearances in map

	// updates
	void updateCurrBoard(Position pos, char ch) { currentBoard[pos.getY()][pos.getX()] = ch; }	// puts a char in a given position in the currnt board
	void updateLives(int lives);                                                                // prints the remaining lives of the hero
	void updateScore(int score);                                                                // prints mario's score                                                                  
	void updateHammer(bool with_hammer);                                                        // print hammer mode

	// getters
	char getCharFromCurr(int x, int y) const { return currentBoard[y][x]; }			// returns the char from current board in the given position
	char getCharFromOriginal(int x, int y) const { return originalBoard[y][x]; }	// returns the char from original board in the given position
	bool getSetColor() const { return set_color; }									// check if the board is in color mode or not
	Position getStartPosHero() const { return start_pos_hero; }						// return start game position of mario
	Position getStartPosDkong() { return start_pos_dkong; }                         // return start game position of donkey kong						
	Position getStartPosGhost()  { return ghosts_positions[index_ghosts++]; }	    // return start game position of ghost by index	
	std::vector<Position> getVectorGhost() const { return ghosts_positions; }	    // return ghosts positions vector

	// setters
	void setColor(int color) const; 		                                // setting the color of a printed char on screen
	 
	// enum classes
	enum class colors {
		cyan = 11,
		green = 10,
		pink = 13,
		console = 7,
		red = 12,
	};
	enum class printing_area {
		life = 6,
		score_x = 7,
		score_y = 1,
		hammer_x = 13,
		max_width = 13,
		hammer_y = 2,
		three = 3,
	};
	enum class characters {
		hero = '@',
		donkeyKong = '&',
		ghost_l = 'X',
		ghost_s = 'x',
		hammer_l = 'P',
		hammer_s = 'p',
		pauline = '$',
		legend = 'L',
		barrel = 'O',
		weapon = '~',
	};
	enum class Floor_chars {
		border = 'Q',
		right = '>',
		left = '<',
		equal = '=',
		ladder = 'H',
	};
};
