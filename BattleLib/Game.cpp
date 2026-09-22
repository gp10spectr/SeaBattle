#include "Game.h"
#include <utility>

Game::Game(std::string name1, std::string name2, int w, int h) {
	turn = 0;
	players.emplace_back(name1, w, h);
	players.emplace_back(name2, w, h);
}

const Player& Game::get_player(int i) const {
	return players[i];
}

Player& Game::get_player(int i) {
	return players[i];
}

const Player& Game::get_current_player() const {
	return players[turn];
}

Player& Game::get_current_player() {
	return players[turn];
}

ShotResult Game::play_turn(const Position& pos) {
	int opponent = 1 - turn;
	ShotResult res = players[opponent].get_field().shoot(pos);
	if (res == ShotResult::Miss) {
		turn = opponent;
	}
	return res;
}

bool Game::is_over() const {
	return (players[0].defeated() || players[1].defeated());
}

int Game::get_winner_index() const {
	if (players[0].defeated()) {
		return 1;
	}
	if (players[1].defeated()) {
		return 0;
	}
	return -1;
}
