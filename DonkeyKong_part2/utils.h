#pragma once
#include <windows.h>
#include <vector>
#include <string>

// the following function were required to be used ny the exercise requirements

void gotoxy(int x, int y);				// positions the cursor at the given position
void ShowConsoleCursor(bool showFlag);	// shows or hides the cursor from the screen
void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);  // get all files game names