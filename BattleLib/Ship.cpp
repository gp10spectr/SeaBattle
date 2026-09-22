#include "Ship.h"
#include <algorithm>

Ship::Ship(std::vector<Position> pos) {
	size_t size = pos.size();
	if (size <= 0) {
		throw std::invalid_argument("zero size");
	}
	if (size > 4) {
		throw std::invalid_argument("invalid size of ship");
	}
	for (int i = 0; i < size; i++) {
		if (pos[i].getx() < 0 || pos[i].gety() < 0) {
			throw std::invalid_argument("neg coordinates");
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
			if (pos[i] == pos[j]) {
				throw std::invalid_argument("two equal cells are taken");
			}
		}
	}
	bool all_x_same = true;
	bool all_y_same = true;
	int x0 = pos[0].getx();
	int y0 = pos[0].gety();
	for (int i = 1; i < size; i++) {
		if (pos[i].getx() != x0) {
			all_x_same = false;
		}
		if (pos[i].gety() != y0) {
			all_y_same = false;
		}
	}
	if (all_x_same == false && all_y_same == false) {
		throw std::invalid_argument("not a line ship");
	}
	std::vector<int> arrx;
	std::vector<int> arry;
	for (int i = 0; i < size; i++) {
		arrx.push_back(pos[i].getx());
		arry.push_back(pos[i].gety());
	}
	std::sort(arrx.begin(), arrx.end());
	std::sort(arry.begin(), arry.end());
	if (all_x_same == true) {
		for (int i = 0; i < size - 1; i++) {
			if (arry[i + 1] != arry[i] + 1) {
				throw std::invalid_argument("not a straight line ship");
			}
		}
	}
	if (all_y_same == true) {
		for (int i = 0; i < size - 1; i++) {
			if (arrx[i + 1] != arrx[i] + 1) {
				throw std::invalid_argument("not a straight line ship");
			}
		}
	}
	positions = std::move(pos);
}

const std::vector<Position>& Ship::get_positions() const noexcept {
	return positions;
}

const std::vector<Position>& Ship::get_hits() const noexcept {
	return hits;
}

bool Ship::operator==(const Ship& other) const {
	return (*this).positions == other.positions;
}

bool Ship::contains(const Position& pos) const {
	if (std::find((*this).positions.begin(), (*this).positions.end(), pos) != positions.end()) {
		return true;
	}
	return false;
}

bool Ship::hit(const Position& pos) {
	if (!contains(pos)) {
		return false;
	}
	if (std::find((*this).hits.begin(), (*this).hits.end(), pos) != hits.end()) {
		return false;
	}
	hits.push_back(pos);
	return true;
}

bool Ship::is_sunk() const {
	return (positions.size() == hits.size());
}
