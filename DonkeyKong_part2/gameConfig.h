#pragma once
#include "position.h"
#include <iostream>
#include <vector>

class Barrel;
class Hero;
class Ghost;

class GameConfig
{
	void run(bool with_color, std::vector<std::string>& fileNames);		// activates gameplay according to the given color mode and vetor files
	void printInstruction() const;					                    // prints the instruction of the game
	void printExit() const;							                    // prints the exit screen
	void printGameOver() const;						                    // prints the game over screen
	void printWinner() const;						                	// prints the winning screen
	void printPause() const;                                            // prints the pause screen
	void printError(int type_of_error) const;                           // print type of error according map
	void resetGame( Hero& mario, std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts);		// resets the game by resetting mario and the barrels
	bool checkIsWinner(Hero mario) const;			                 	// checks if the hero and the princess are at the same position
	void pickALevel();                                                  // prints all level's files 
	std::vector<std::string> sliceVector(const std::vector<std::string>& inputVector, int startIndex);    // slice vector to the rellevant maps 

public:
	// screen consts
	static constexpr int MAX_WIDTH = 80;
	static constexpr int MAX_HEIGHT = 25;
	static constexpr int ESC = 27;
	static constexpr int NEXT = 110;
	static constexpr int NEW_GAME = 49;
	static constexpr int PICK_A_LEVEL = 53;
	static constexpr int INSTRUCTION = 56;
	static constexpr int EXIT = 57;
	static constexpr int TEN = 10;
	static constexpr int NEW_GAME_WITH_COLORS = 50;
	static constexpr int SCREENS_TOP_MARGIN = 5;
	static constexpr int SCREENS_MIDDLE_WIDTH = 30;

	// Mario consts
	static constexpr int JUMP_H = 2;
	static constexpr int MAX_LIFE = 3;
	static constexpr int MIN_FALL_HEIGHT_MARIO = 5;
	static constexpr int HIT_POINTS = 10;

	// barrel consts
	static constexpr int MIN_FALL_HEIGHT_BARREL = 8;
	static constexpr int EXPLOSION_RADIUS = 2;

	// game loop consts
	static constexpr int SLEEP_DURATION = 100;
	static constexpr int LOOP_COUNTER = 30;

	enum class errors {
		missing_mario = 1,
		missing_pauline = 2,
		missing_dkong = 3,
		missing_legend = 4,
		no_maps = 5,
	};
	
	void menu();		// presenting the menu options
};

