#pragma once
class Position
{
	int x = 0;
	int y = 0;

public:
	// ctor
	Position(int x, int y) : x(x), y(y) {}
	Position() {}

	// getters
	int getX() const { return x; }
	int getY() const { return y; }

	// setters
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	// comparing two position function
	bool operator==(const Position& other) const {	return (x == other.x && y == other.y); }
};

