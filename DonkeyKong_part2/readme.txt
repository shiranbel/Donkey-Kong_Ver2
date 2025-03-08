# Donkey Kong - Exercise 2

## ID's: 

- Alfredo Limin: 326855301
- Shiran Belachdev: 211449145


## Description

In this exercise, we continue developing a game, building on the concepts from Exercise 1. 
The objective is to enhance the game by implementing new features such as ghosts, hammers, loading screens from files, and introducing a scoring system.


## Objectives

The primary goal of Exercise 2 is to add the following key components to the game:
- Ghosts: Moving characters that interact with Mario and affect gameplay.
- Hammer: A special item that can be used to destroy obstacles or defeat ghosts.
- Loading Screens from Files: Implementing the ability to load screens from text files.
- Score: Introducing a scoring system based on gameplay actions.

The code was implemented in C++ including functions that were introduced to us in the lectures and the lab classes. 


## Project File Structure

- Donkey Kong
	- Header Files
		- barrel.h
		- board.h
		- enemy.h
		- gameConfig.h
		- ghost.h
		- hero.h
		- position.h
		- utils.h
	- Source Files
		- barrel.cpp
		- board.cpp
		- enemy.cpp
		- gameConfig.cpp
		- ghost.cpp
		- hero.cpp
		- main.cpp
		- position.cpp
		- utils.cpp


## Important Notes

- When loading screens:
	- Every char that is not part of the defined chars in the requirement will act as Q and printed as Q (wall).
	- If there are more than 1 character such as Donkey kong, Mario, Pauline, Hammer or L (legend) the game will print the last char of each type that was read.
	- if the user pressed 'N' (next button) on all screens it will lead him to the winner screen.
	- The screen do not complete "unfinished" borders so that if the designer intended to design the borders differently the game will allow it. either way the board will be 80 by 25 and mario can move on all of it according to the obstacles in his way.
	- A screen is allowed to be loaded without a hammer.
- Ghosts ignore barrels and barrels ignore ghosts (no affect on each other).
- Ghost can be printed in the air (no floor beneath it) but will free fall at the beginning until it lands a floor.
- The hammer is attacking at mario's direction. (on stay it will target on he's current position)
- the score is set to zero when mario is hit and being saved to the next level when skipping a level.


## Additional bonus features
- if the screen cannot be printed there will be an error screen that will explain the reason of the error.
- implementing an option for colors 
- implementing option to start at any level from all files on the directory
- implementing 'next' button by pressing N
- ascii art
- hammer use visual presentation and indicated at the legend as "hammer mode: on/off"
- content writing on screens
- Detailed game screen allows testing various game aspects











