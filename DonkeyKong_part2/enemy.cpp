#include "enemy.h"
// this function handles the movement of the enemy by checking the situation at next and under positions
void Enemy::erase() {
	// get the current x, y position
	int x = pos.getX();
	int y = pos.getY();
	draw(pBoard->getCharFromOriginal(x, y));								// get the char from the original board
	pBoard->updateCurrBoard(pos, pBoard->getCharFromOriginal(x, y));	    // draw it in the current board
}
