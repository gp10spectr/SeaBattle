#pragma once
#include "Player.h"
#include <string>

class Game {
private:
	std::vector<Player> players;
	int turn;
public:
	Game(std::string name1, std::string name2, int w, int h);
	const Player& get_player(int i) const;
	Player& get_player(int i);
	int get_current_index() const noexcept;
	const Player& get_current_player() const;
	Player& get_current_player();
	ShotResult play_turn(const Position& pos);
	bool is_over() const;
	int get_winner_index() const;

};
	