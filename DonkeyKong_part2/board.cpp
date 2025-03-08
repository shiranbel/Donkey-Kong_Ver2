#include <iostream>
#include <fstream>
#include "board.h"


// this function resets the game by "copying" the original board
void Board::reset() {
	for (int i = 0; i < GameConfig::MAX_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], GameConfig::MAX_WIDTH + 1);
	}
}

// this function prints the board to the user according to the color mode given
void Board::print(bool with_color) const {
	system("cls");
	char ch;
	// for color mode - print the charcters according to their color
	if (with_color) {
		for (int i = 0; i < GameConfig::MAX_HEIGHT; i++) {
			for (int j = 0; j < GameConfig::MAX_WIDTH; j++) {
				ch = currentBoard[i][j];   // get the char from the current board
				switch (ch) {
					// for floor characters
				case (char)Floor_chars::equal:
				case (char)Floor_chars::left:
				case (char)Floor_chars::right:
					setColor((int)colors::cyan);
					break;
				case (char)Floor_chars::border:	    // for border
					setColor((int)colors::green); 
					break;
				case (char)characters::donkeyKong:	// for gorilla
					setColor((int)colors::red);
					break;
				case (char)characters::pauline:	    // for princess
					setColor((int)colors::pink);
					break;
				default:	                        // for others 
					setColor((int)colors::console);
					break;
				}
				std::cout << currentBoard[i][j];    // print on screen 
			}
		}
	}
	else {	// for black and white mode print the board as is
		for (int i = 0; i < GameConfig::MAX_HEIGHT - 1; i++)
			std::cout << currentBoard[i] << '\n';
		std::cout << currentBoard[GameConfig::MAX_HEIGHT - 1];
	}
	setColor((int)colors::console);

	printLegend();
}

// // this function prints the legende game
void Board::printLegend() const {
	gotoxy(start_pos_legend.getX(), start_pos_legend.getY());
	std::cout << "LIFE: ";
	gotoxy(start_pos_legend.getX(), start_pos_legend.getY() + 1);
	std::cout << "SCORE: ";
	gotoxy(start_pos_legend.getX(), start_pos_legend.getY() + 2);
	std::cout << "HAMMER MODE: Off";
}

// this function prints the life counter according to mario's condition  
void Board::updateLives(int lives) {
	gotoxy(start_pos_legend.getX() + (int)printing_area:: life , start_pos_legend.getY());  // erasing the current lives
	for (int i = 0; i < GameConfig::MAX_LIFE; i++) {
		std::cout <<SPACE;
	}
	gotoxy(start_pos_legend.getX() + (int)printing_area::life, start_pos_legend.getY());    // drawing the remaining lives
	for (int i = 0; i < lives; i++) {
		std::cout << (char)characters::hero;
	}

}

// this function prints the update score counter 
void Board::updateScore(int score) {
	// erasing the current score
	gotoxy(start_pos_legend.getX() + (int)printing_area::score_x, start_pos_legend.getY() + (int)printing_area::score_y);  
	for (int i = 0; i < (int)printing_area::max_width; i++) {
		std::cout << SPACE; 
	}
	gotoxy(start_pos_legend.getX() + (int)printing_area::score_x , start_pos_legend.getY() + (int)printing_area::score_y);
	std::cout << score;
}

// this function prints the hammer mode: on/off 
void Board::updateHammer(bool with_hammer) {
	// erasing the current mode
	gotoxy(start_pos_legend.getX() + (int)printing_area::hammer_x, start_pos_legend.getY() + (int)printing_area::hammer_y); 
	for (int i = 0; i < (int)printing_area:: three; i++) {
		std::cout << SPACE;
	}
	gotoxy(start_pos_legend.getX() + (int)printing_area::hammer_x, start_pos_legend.getY() + (int)printing_area::hammer_y);
	if (with_hammer)                   // check if mario is with hammer 
		std::cout << "On";             // updte screen mode
	else
		std::cout << "Off";            
}

// this function set the color of the next char that will be printed on board
void Board::setColor(int color) const {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}

// this function reads the board layout from a specified file and initializes
// the board's state, including the positions of characters and other game elements.
void Board::loadBoardFromFile(const std::string& filename) {
	std::ifstream screen1(filename);
	if (!screen1) {   // handle error if the file cannot be opened                         
		std::cout << "Error: File not found.\n";
		return;
	}

	// initialize the board with spaces
	for (int i = 0; i < GameConfig::MAX_HEIGHT; ++i) {
		std::fill(originalBoard[i], originalBoard[i] + GameConfig::MAX_WIDTH, ' ');
		originalBoard[i][GameConfig::MAX_WIDTH] = '\0'; // Null terminate each row
	}

	int curr_row = 0;
	int curr_col = 0;
	char c;

	while (screen1.get(c) && curr_row < GameConfig::MAX_HEIGHT) {
		if (c == '\n') {
			++curr_row;     // move to the next row
			curr_col = 0;   // reset col
			continue;
		}
		// if àhe column number is smaller than the screen width
		if (curr_col < GameConfig::MAX_WIDTH) {
			switch (c) {
			// saving each main character position
			// if a character appears more than once, the last position on the map is saved
			case (char)characters::hero:
				start_pos_hero = { curr_col, curr_row };
				originalBoard[curr_row][curr_col++] = SPACE;   
				break;
			case (char)characters::pauline:
				start_pos_pauline = { curr_col, curr_row };
				originalBoard[curr_row][curr_col++] = SPACE;
				break;
			case (char)characters::donkeyKong:
				start_pos_dkong = { curr_col, curr_row };
				originalBoard[curr_row][curr_col++] = SPACE;
				break;
			case (char)characters::hammer_l:
			case (char)characters::hammer_s:
				start_pos_hammer = { curr_col, curr_row };
				originalBoard[curr_row][curr_col++] = SPACE;
				break;
			case (char)characters::ghost_l:
			case (char)characters::ghost_s:
				ghosts_positions.push_back({ curr_col, curr_row });
				originalBoard[curr_row][curr_col++] = SPACE;
				break;
			case (char)characters::legend:
				start_pos_legend = { curr_col, curr_row };
				originalBoard[curr_row][curr_col++] = SPACE;
				break;
			default:
				// replace any other char is not from game characters in Q
				if (c != (char)Floor_chars::border && c != (char)Floor_chars::ladder && c != (char)Floor_chars::left && c != (char)Floor_chars::right && c != (char)Floor_chars::equal && c != SPACE)
					originalBoard[curr_row][curr_col++] = (char)Floor_chars::border ;
				else  // save other elements game
					originalBoard[curr_row][curr_col++] = c;
				break;
			}
		}
	}
	Position error_pos = { ERROR_POS, ERROR_POS };  // define a error position for comparison

	// place characters back on the board with the last positions if their positions are valid
	if(!(start_pos_hammer == error_pos) )  
		originalBoard[start_pos_hammer.getY()][start_pos_hammer.getX()] = (char)characters::hammer_s;
	if (!(start_pos_dkong == error_pos))
		originalBoard[start_pos_dkong.getY()][start_pos_dkong.getX()] = (char)characters::donkeyKong;
	if (!(start_pos_pauline == error_pos))
		originalBoard[start_pos_pauline.getY()][start_pos_pauline.getX()] =(char)characters::pauline;
	screen1.close(); // close file
}

// this function check if all characters has a valid position
// the function returns a specific error code based on which character's position is invalid 
int Board::checkAllCharacters() const {
	Position errorPos = { ERROR_POS, ERROR_POS };

	if (start_pos_hero == errorPos)
		return (int)GameConfig::errors::missing_mario;
	if (start_pos_pauline == errorPos)
		return (int)GameConfig::errors::missing_pauline;
	if (start_pos_dkong == errorPos)
		return (int)GameConfig::errors::missing_dkong;
	if (start_pos_legend == errorPos)
		return (int)GameConfig::errors::missing_legend;
	return 0;
}


