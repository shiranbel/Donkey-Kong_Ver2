#include <conio.h>
#include "gameConfig.h"
#include "board.h"
#include "hero.h"
#include "utils.h"
#include "ghost.h"
#include "barrel.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;

// this function introduces the menu to the user with option buttons
void GameConfig::menu() {
	int choice;
	ShowConsoleCursor(false);   // hides cursor
	std::vector<std::string> fileNames = {};

	while (true) {
		// The Menu screen
		gotoxy(0, SCREENS_TOP_MARGIN);
		//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
		cout << "                           WELCOME TO DONKEY KONG GAME!                         " << endl;
		cout << "                                === GAME MENU ===                               " << endl;
		cout << "                           Press:                                               " << endl;
		cout << "                          (1) Start a new game                                  " << endl;
		cout << "                          (2) Start a new game with colors                      " << endl;
		cout << "                          (5) Pick a level                                      " << endl;
		cout << "                          (8) Present instructions and keys                     " << endl;
		cout << "                          (9) EXIT                                              " << endl;
		cout << "                                                                                " << endl;
		std::cout << R"(				       ."`".
				   .-./ _=_ \.-.
				  {  (,(oYo),) }}
				  {{ |   "   |} }
				  { { \(---)/  }}
				  {{  }'-=-'{ } }
				  { { }._:_.{  }}
				  {{  } -:- { } }
				  {_{ }`===`{  _}
				  ((((\)     (/))))" << std::endl;


		choice = _getch();            // user's input
		switch (choice) {
		case NEW_GAME:			      // black and white mode
			system("cls");
			run(false, fileNames);
			break;
		case NEW_GAME_WITH_COLORS:	  // color mode
			system("cls");
			run(true, fileNames);
			break;
		case PICK_A_LEVEL:	          // color mode
			system("cls");
			pickALevel();
			break;
		case INSTRUCTION:			  // instruction screen
			system("cls");
			printInstruction();
			break;
		case EXIT:					  // exit screen
			system("cls");
			printExit();
			return;
		default:
			break;
		}

	}
}

// this function slice vector to the rellevant maps by start index
std::vector<std::string> GameConfig::sliceVector(const std::vector<std::string>& inputVector, int startIndex) {
	// if the index is out of bounds, return an empty vector
	if (startIndex >= inputVector.size()) {
		return {};
	}
	// use vector's range constructor to create a new vector
	return std::vector<std::string>(inputVector.begin() + startIndex, inputVector.end());
}

// this function prints all the files in the vector, slices the vector according to the user's choice,
// and calls run function to start the game with the chosen map
void GameConfig::pickALevel() {
	std::vector<std::string> fileNames;
	getAllBoardFileNames(fileNames);            // get all files name into filenames vector
	
	int index = 1;
	gotoxy(SCREENS_MIDDLE_WIDTH, SCREENS_TOP_MARGIN);
	std::cout << "Pick your level:" << endl;
	gotoxy(SCREENS_MIDDLE_WIDTH, SCREENS_TOP_MARGIN + index);
	index++;
	std::cout << "Press any other key for level 1 :" << endl;
	// print files name and press key
	for (const auto& filename : fileNames) {
		gotoxy(SCREENS_MIDDLE_WIDTH, SCREENS_TOP_MARGIN + index);
		cout << "(" << index-1 << ") " << filename << endl;
		index++;
	}

	char choice = _getch();       // user's input
	index = choice - '0' - 1;     // convert to int

	fileNames = sliceVector(fileNames, index);   
	system("cls");
	gotoxy(TEN, SCREENS_TOP_MARGIN);
	// print a colors game option 
	std::cout << "Do you want to play with colors?  Press:   (1) Yes    (2) No" << endl;

	char color_choice = _getch();  // user's input
	// send the rellevant color 
	if(color_choice == '1')
		run(true, fileNames);
	else
		run(false, fileNames);
}
 
// this function print the type of error by getting a int code error
void GameConfig::printError(int type_of_error) const{
	ShowConsoleCursor(false);					// hides th e cursor

	switch (type_of_error) {
	case (int)errors::no_maps:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                         We didn't find your level Mario                     " << endl;
		cout << "                       Press ESC to return to the main menu.                 " << endl;
		cout << "                                                                             " << endl;
		cout << R"(                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    ~ ~ ~ ~ ~ ~ ~ ~ ^ ^ ^ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
                    ~  Princess     ^     ^     =======        ~
                    ~   ^^^      ^  ~~~  ^   H         T T T   ~
                    ~   ^ ^      ^  ~~~      H<<<        T T   ~
                    ~   ^ ^      ^           H     #########   ~
                    ~     P      ~~~         H     # Score #   ~
                    ~     ~~~    ~~~  Dkong  H     #  100  #   ~
                    ~     ~~~    ~~~               #########   ~
                    ~     ~~~    ~~~    O                  O   ~
                    ~  Mario    #####   O O      X         O O ~
                    ~ ~ ~ ~ ~ ~ #####   O O O    X X X     O O ~
                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)" << endl;
		break;
	case (int)errors::missing_mario:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                               Missing Mario                                 " << endl;
		cout << "                  How can you save a princess without a hero?                " << endl;
		cout << "                       Press ESC to go to the next level.                    " << endl;
		cout << "                                                                             " << endl;
		cout << R"(
                          _____________________________   
                         /        _____________        \  
                         | == .  |             |     o |  
                         |   _   |    Where    |    B  |  
                         |  / \  |             | A   O |  
                         | | O | |      is     |  O    |  
                         |  \_/  |             |       |  
                         |       |    Mario?   | . . . |  
                         |  :::  |             | . . . |  
                         |  :::  |_____________| . . . |  
                         |           S N K             |  
                         \_____________________________/
)" << endl;		       

		break;
	case (int)errors::missing_pauline:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                               Missing Pauline                               " << endl;
		cout << "                         Who do you want to save then?                       " << endl;
		cout << "                       Press ESC to go to the next level.                    " << endl;
		cout << "                                                                             " << endl;
		cout << R"(                                  o  o   o  o
                                  |\/ \^/ \/|
                                  |,-------.|
                                ,-.(|)   (|),-.
                                \_*._ ' '_.* _/
                                 /`-.`--' .-'\ 
                            ,--./    `---'    \,--.
                            \   |(  )     (  )|   /
                             \  | ||       || |  /
                              \ | /|\     /|\ | /
                              /  \-._     _,-/  \
                             //| \\  `---'  // |\\
                            /,-.,-.\       /,-.,-.\ 
                           o   o   o      o   o    o)" << endl;
		break;
	case (int)errors::missing_dkong:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                               Missing Donkey Kong                           " << endl;
		cout << "                No enemies? playing without enemies is very boring           " << endl;
		cout << "                       Press ESC to go to the next level.                    " << endl;
		cout << "                                                                             " << endl;
		cout << R"(                     //\
                     V  \
                      \  \_
                       \,'.`-.  Donkey Kong took a lunch break :)
                        |\ `. `.       
                        ( \  `. `-.                        _,.-:\
                         \ \   `.  `-._             __..--' ,-';/
                          \ `.   `-.   `-..___..---'   _.--' ,'/ 
                           `. `.    `-._        __..--'    ,' /  
                             `. `-_     ``--..''       _.-' ,'   
                               `-_ `-.___        __,--'   ,'     
                                  `-.__  `----"""    __.-'       
                                       `--..____..--'            
)" << endl;
		break;
	case (int)errors::missing_legend:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << R"(
            ____________________              Missing legend
           /                    \        Are we still in matala 1? 
           |     In case of     |    Press ESC to go to the next level. 
           |     Frustration    |
           \____________________/
                    !  !
                    !  !
                    L_ !
                   / _)!
                  / /__L
            _____/ (____)
                   (____)
            _____  (____)
                 \_(____)
                    !  !
                    !  !
                    \__
)" << endl;
		break;
	default:
		break;
	}

	
	char ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the exit screen
void GameConfig::printExit() const {
	ShowConsoleCursor(false);					// hides th e cursor

	// exit screen
	gotoxy(0, SCREENS_TOP_MARGIN);
	cout << "         Farewell, Mario. The princess was waiting for you to save her, " << endl;
	cout << "                         but perhaps another time...                    " << endl;
	std::cout << R"( 
                   _____                 _ ____             
                  / ____|               | |  _ \            
                 | |  __  ___   ___   __| | |_) |_   _  ___ 
                 | | |_ |/ _ \ / _ \ / _` |  _ <| | | |/ _ \
                 | |__| | (_) | (_) | (_| | |_) | |_| |  __/
                  \_____|\___/ \___/ \__,_|____/ \__, |\___|
                                                  __/ |     
                                                 |___/     
)" << std::endl;
}

// this function prints the instructions screen
void GameConfig::printInstruction() const {
	ShowConsoleCursor(false);		// hides the cursor

	// instructions screen
	gotoxy(0, SCREENS_TOP_MARGIN - 1);
	char ch;
	//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
	cout << "                             === INSTRUCTIONS ===                               " << endl;
	cout << "                    Use the following keys to play the game:                    " << endl;
	cout << "                        - W/w : Up / Jump                                       " << endl;
	cout << "                        - X/x : Down                                            " << endl;
	cout << "                        - A/a : Left                                            " << endl;
	cout << "                        - D/d : Right                                           " << endl;
	cout << "                        - S/s : Stay                                            " << endl;
	cout << "                        - P/p : Attack (when hammer mode is on)                 " << endl;
	cout << "                        - N/n : Skip the level                                  " << endl;
	cout << "                     Press ESC to return to the main menu.                      " << endl;
	cout << "				  _._______" << endl;
	cout << "				 | _______ |" << endl;
	cout << "				 ||,-----.||" << endl;
	cout << "				 |||     |||" << endl;
	cout << "				 |||_____|||" << endl;
	cout << "				 |`-------'|" << endl;
	cout << "				 | +     O |" << endl;
	cout << "				 |      O  |" << endl;
	cout << "				 | / /  ##,\"" << endl;
	cout << "				  `------\"" << endl;


	// returns to menu when pressing ESC
	ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the game over screen
void GameConfig::printGameOver() const {
	ShowConsoleCursor(false);		// hides the cursor
	char ch;
	system("cls");					// erases the screen

	// exit screen
	gotoxy(0,SCREENS_TOP_MARGIN);
	std::cout << R"(		  __ _  __ _ _ __ ___   ___    _____   _____ _ __ 
		 / _` |/ _` | '_ ` _ \ / _ \  / _ \ \ / / _ \ '__|
		| (_| | (_| | | | | | |  __/ | (_) \ V /  __/ |   
		 \__, |\__,_|_| |_| |_|\___|  \___/ \_/ \___|_|   
		 |___/           
)" << std::endl;
	cout << "                       Don't give up Mario!! Save the princess                  " << endl;
	cout << "                            Press ESC to return to menu                         " << endl;

	// returns to menu when pressing ESC
	ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");

}

// this function prints the winning screen
void GameConfig::printWinner() const {
	ShowConsoleCursor(false);		// hides cursor
	system("cls");					// erases the screen

	// the victory screen
	gotoxy(0, SCREENS_TOP_MARGIN);
	cout << "	                        == YOU WON!!! ==                         	 " << endl;
	std::cout << R"(                                  ___________
                                 '._==_==_=_.'
                                 .-\:      /-.
                                | (|:.     |) |
                                 '-|:.     |-'
                                   \::.    /
                                    '::. .'
                                      ) (
                                    _.' '._
                                   `"""""""`)" << endl;
	cout << "	                                                                     " << endl;
	cout << "	              \"Oh Mario! You saved me! I LOVE YOU!\"                " << endl;
	cout << "	                  Press ESC to return to menu                        " << endl;

	// returns to menu when pressing ESC
	char ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the pausing screen
void GameConfig::printPause() const {
	ShowConsoleCursor(false);	// hides the cursor
	system("cls");				// eracing the screen
	// visuals
	gotoxy(0, SCREENS_TOP_MARGIN);
	cout << R"(
		.-------.    ____      ___    _    .-'''-.     .-''-.   
		\  _(`)_ \ .'  __ `. .'   |  | |  / _     \  .'_ _   \  
		| (_ o._)|/   '  \  \|   .'  | | (`' )/`--' / ( ` )   ' 
		|  (_,_) /|___|  /  |.'  '_  | |(_ o _).   . (_ o _)  | 
		|   '-.-'    _.-`   |'   ( \.-.| (_,_). '. |  (_,_)___| 
		|   |     .'   _    |' (`. _` /|.---.  \  :'  \   .---. 
		|   |     |  _( )_  || (_ (_) _)\    `-'  | \  `-'    / 
		/   )     \ (_ o _) / \ /  . \ / \       /   \       /  
		`---'      '.(_,_).'   ``-'`-''   `-...-'     `'-..-'   
		    )" << endl;
	cout << "\n";
	cout << "                                Press ESC to resume";
}

// this function checks if the hero is at the same position of the princess
bool GameConfig::checkIsWinner(Hero mario) const {
	return (mario.getBoard()->getCharFromOriginal(mario.getPosition().getX(), mario.getPosition().getY()) == (char)Board::characters::pauline);
}

// this function resets the game when the hero is damaged by resetting the hero and the barrels
void GameConfig::resetGame(Hero& mario, std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts){
	mario.resetMario();						// resets the hero
	mario.getBoard()->returnHammer();
	mario.getBoard()->updateHammer(mario.getWithHammer());

	for (auto& barrel : barrels)
		barrel.erase();

	mario.changelives();					// decreace the hero's remaining lives
	mario.getBoard()->resetNumOfGhosts();

	for (auto& ghost:ghosts)
		ghost.erase();

	barrels.clear();
	ghosts.clear();
	for (int i = 0; i < mario.getBoard()->getVectorGhost().size(); i++)
		ghosts.emplace_back(mario.getBoard());
}

// this function runs the game loop and handles the game's actions and effects
void GameConfig::run(bool with_color, std::vector<std::string>& fileNames) {

	ShowConsoleCursor(false);				// hides cursor
	if(fileNames.empty())        
		getAllBoardFileNames(fileNames);    // get files names
	if (fileNames.empty()) {                // no files
		system("cls");
		printError((int)errors::no_maps);  
		return;
	}

	std::vector<Ghost> ghosts;
	Hero mario;                                  

	for (const auto& filename : fileNames) {
		system("cls");		
		std::vector<Barrel> barrels;              // initializes max barrels vector
		Board board(with_color, filename);        
		int error_type = board.checkAllCharacters();  
		if (error_type) {
			system("cls");
			printError(error_type);
			continue;
		}

		int game_loop_counter = 0;                // used to measure the time of the barrels' exit
		board.print(with_color);                  // prints the board in the given color mode	
		mario.setBoard(&board);                   // set mario's board
		ghosts.clear();  

		for (int i = 0; i < board.getVectorGhost().size(); i++)   // create all ghosts with specific position into vector
			ghosts.emplace_back(&board);
	
		while (!checkIsWinner(mario)) {           // game loop

			board.updateScore(mario.getScore());
			if (mario.getIsFalling()) {           // checks if Mario has fallen and reset the game if necessary 
				mario.setScore(0);                // reset score
				resetGame(mario, barrels,ghosts); // reset game elements
				if (mario.getLife() == 0) {       
					printGameOver();
					return;
				}
			}

			if (game_loop_counter == 0 )          // create barrels
				barrels.emplace_back(&board);
			
			mario.draw();                         // draw the hero
			
			for (auto& ghost : ghosts)            // draw ghosts
				ghost.draw();

			for (auto& barrel : barrels)          // draw barrels
				barrel.draw();

			if ((mario.isCollision())) {          // checks if Mario has collision with barrel and reset the game if necessary 
				mario.setScore(0);
				resetGame(mario, barrels, ghosts);
				if (mario.getLife() == 0) {
					printGameOver();
					return;
				}
			}

			if (mario.getJumpCount() > 0)         // fix jump counter
				mario.handleJump();

			if (_kbhit()) {                       // get keyborad clicks
				char key = _getch();
				if (key == ESC) {                 // check if the player pauses
					while (true) {                // play when pressing ESC
						system("cls");
						printPause();
						if (_getch() == ESC) {
							system("cls");
							board.print(with_color);
							board.updateLives(mario.getLife());
							board.updateHammer(mario.getWithHammer());
							break;
						}
					}
				}
				if (tolower(key) == NEXT) {       // if user prees next for next level, out of loop
					break;
				}
				// if mario press p and he have a hammer, let him attack
				if (key == (char)Hero::keys::attack && mario.getWithHammer()) {  
					mario.attack(ghosts, barrels);
				}
				mario.keyPressed(key);           // preparing Mario for his next movement based on the key.
			}
			Sleep(SLEEP_DURATION);

			mario.erase();                       // illusion of Mario's movement
			mario.move();                        // change position

			if ((mario.isCollision())) {         // check collision after Mario's movement
				mario.setScore(0);
				resetGame(mario, barrels, ghosts);
				if (mario.getLife() == 0) {
					printGameOver();
					return;
				}
			}

			for (auto& ghost : ghosts)           // eraces ghosts
				ghost.erase();
		
			for (auto& ghost : ghosts)           // illusion of ghost's movement
				ghost.move();

			int index = 0;
			for(auto& barrel : barrels) {
				barrel.erase();                  // eraces ghosts
				barrel.move();                   // illusion of ghost's movement
				if (barrel.getIsOnBorder())      // delete barrel from vector
					barrels.erase(barrels.begin() + index);          
				if (barrel.getIsHit()) {         // check if barrel explodes
					barrel.drawExplode();        // draw all the relevant collision points of the barrel's explosion in current map
					
					if ((mario.isCollision())) { // check collision after barrel's explosion
						mario.setScore(0);
						resetGame(mario, barrels, ghosts);
						if (mario.getLife() == 0) {
							printGameOver();
							return;
						}
					}
					
					barrel.eraseExplode();                   // erase all collision points of the barrel's explosion from current map
					barrels.erase(barrels.begin() + index);  // delete barrel from vector
				}
				index++;
			}
			game_loop_counter++;                             // game loop counter 

			if (game_loop_counter > LOOP_COUNTER)            // for barrel creation handle
				game_loop_counter = 0;
		}
	}
	printWinner();
}
