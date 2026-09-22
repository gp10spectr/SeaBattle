#include "GameField.h"
#include <algorithm>

GameField::GameField(int w, int h) {
	width = w;
	height = h;
}

int GameField::get_width() const noexcept {
	return width;
}

int GameField::get_height() const noexcept {
	return height;
}

const std::vector<Ship>& GameField::get_ships() const noexcept {
	return ships;
}

const std::vector<Position>& GameField::get_shots() const noexcept {
	return shots;
}

bool GameField::is_inside(const Position& pos) const noexcept {
	return pos.valid_pos(width, height);
}

bool GameField::place_ship(const Ship& ship) {
	for (size_t i = 0; i < ship.get_positions().size(); i++) {
		if (!is_inside(ship.get_positions()[i])) {
			return false;
		}
	}
	for (size_t i = 0; i < ship.get_positions().size(); i++) {
		for (size_t j = 0; j < ships.size(); j++) {
			if (ships[j].contains(ship.get_positions()[i])) {
				return false;
			}
		}
	}
	ships.push_back(ship);
	return true;
}

ShotResult GameField::shoot(const Position& pos) {
	if (!is_inside(pos)) {
		return ShotResult::OutOfBounds;
	}
	if (std::find(shots.begin(), shots.end(), pos) != shots.end()) {
		return ShotResult::AlreadyShot;
	}
	shots.push_back(pos);
	for (Ship& ship : ships) {
		if (ship.contains(pos)) {
			ship.hit(pos);
			if (ship.is_sunk()) {
				return ShotResult::Sunk;
			}
			return ShotResult::Hit;
		}
	}
	return ShotResult::Miss;
}

bool GameField::all_sunk() const {
	for (const Ship& ship : ships) {
		if (!ship.is_sunk()) {
			return false;
		}
	}
	return true;
}

