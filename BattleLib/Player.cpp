#include "Player.h"
#include <utility>

//only initializer list constructor here because GameField does not have default constructor
Player::Player(std::string player_name, int w, int h)
	: name(std::move(player_name)), field(w, h) {}

const std::string& Player::get_name() const noexcept {
	return name;
}

const GameField& Player::get_field() const noexcept {
	return field;
}

GameField& Player::get_field() noexcept {
	return field;
}

bool Player::defeated() const noexcept {
	if (field.all_sunk()) {
		return true;
	}
	return false;
}
