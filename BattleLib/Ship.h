#pragma once
#include "Position.h"
#include <vector>
#include <stdexcept>

class Ship {
private:
	std::vector<Position> positions;
	std::vector<Position> hits;
public:
	Ship(std::vector<Position> pos);
	const std::vector<Position>& get_positions() const noexcept;
	const std::vector<Position>& get_hits() const noexcept;
	bool operator==(const Ship& other) const;
	bool contains(const Position& pos) const;
	bool hit(const Position& pos);
	bool is_sunk() const;

};