#pragma once
#include "GameField.h"
#include <string>

class Player {
private:
	std::string name;
	GameField field;
public:
	Player(std::string player_name, int w, int h);
	const std::string& get_name() const noexcept;
	const GameField& get_field() const noexcept;
	GameField& get_field() noexcept;
	bool defeated() const noexcept;

};
