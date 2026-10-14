#include "Position.h"

Position::Position(int x, int y) : x(x), y(y) {}

int Position::getx() const noexcept {
	return x;
}

int Position::gety() const noexcept {
	return y;
}

bool Position::operator==(const Position& other) const {
	return (((*this).x == other.x) && ((*this).y == other.y));
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
	os << "(" << pos.getx() << ", " << pos.gety() << ")";
	return os;
}

bool Position::valid_pos(int width, int height) const {
	return ((((*this).x >= 0 && (*this).x < width)) && (((*this).y >= 0 && (*this).y < height)));
}

std::vector<Position> Position::neighbors() const {
	std::vector<Position> res;
	res.push_back(Position(x - 1, y));
	res.push_back(Position(x, y - 1));
	res.push_back(Position(x + 1, y));
	res.push_back(Position(x, y + 1));
	return res;
}
