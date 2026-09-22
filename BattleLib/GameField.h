#pragma once
#include "Ship.h"

enum class ShotResult { 
	Miss,
	Hit,
	Sunk,
	AlreadyShot,
	OutOfBounds
};

class GameField {
private:
	int width;
	int height;
	std::vector<Ship> ships;
	std::vector<Position> shots;
public:
	GameField(int w, int h);
	int get_width() const noexcept;
	int get_height() const noexcept;
	const std::vector<Ship>& get_ships() const noexcept;
	const std::vector<Position>& get_shots() const noexcept;
	bool is_inside(const Position& pos) const noexcept;
	bool place_ship(const Ship& ship);
	ShotResult shoot(const Position& pos);
	bool all_sunk() const;


};
