#include "Game.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

std::random_device rd;
std::mt19937 gen(rd());

void print_field(const GameField& field, bool show_tips);
void print_result(ShotResult r, const std::string& name);
Position input_position();
bool input_ship(int length, Ship& out_ship);
void place_ships_manually(GameField& field);
void place_ships_automatically(GameField& field);
Position bot_choose_shot(const GameField& enemy_field);

Position input_position() {
	int x, y;
	std::cout << "Input position for shot first x then y coordinates\n";
	std::cin >> x >> y;
	return Position(x, y);
}

void print_result(ShotResult r, const std::string& name) {
	if (r == ShotResult::Miss) {
		std::cout << name << "Missed a shot\n";
	}
	if (r == ShotResult::Hit) {
		std::cout << name << "U hit a ship. Shoot again\n";
	}
	if (r == ShotResult::Sunk) {
		std::cout << name << "U got a ship down. Shoot again\n";
	}
	if (r == ShotResult::AlreadyShot) {
		std::cout << "U cant shoot one spot twice. Shoot again\n";
	}
	if (r == ShotResult::OutOfBounds) {
		std::cout << "U cant shoot out of field. Shoot again\n";
	}
}

void print_field(const GameField& field, bool show_tips) {
    std::cout << "    ";
    for (int j = 0; j < field.get_width(); j++) std::cout << j << "  ";
    std::cout << '\n';
    for (int i = 0; i < field.get_height(); i++) {
        std::cout << i << "   ";
        for (int j = 0; j < field.get_width(); j++) {
            Position p(j, i);
            bool was_shot = std::find(field.get_shots().begin(), field.get_shots().end(), p) != field.get_shots().end();
            bool is_ship = false;
            bool ship_hit = false;
            for (const Ship& s : field.get_ships()) {
                if (s.contains(p)) {
                    is_ship = true;
                    if (std::find(s.get_hits().begin(),
                        s.get_hits().end(), p) != s.get_hits().end())
                        ship_hit = true;
                    break;
                }
            }
            if (ship_hit)                  std::cout << "X  ";   // hit
            else if (was_shot)             std::cout << "o  ";   // miss
            else if (is_ship && show_tips) std::cout << "S  ";   // own ship
            else                           std::cout << ".  ";   // water
        }
        std::cout << '\n';
    }
}

void place_ships_manually(GameField& field) {
    std::vector<int> lengths = { 4, 3, 2, 1 };
    for (int length : lengths) {
        while (true) {
            std::cout << "\nPlace ship of size " << length << "\n";
            print_field(field, true);
            Position start = input_position();
            char dir;
            std::cout << "Direction (H for horizontal V for vertical): ";
            std::cin >> dir;
            dir = static_cast<char>(std::toupper(dir));
            if (dir != 'H' && dir != 'V') {
                std::cout << "Invalid direction try again.\n";
                continue;
            }
            std::vector<Position> positions;
            for (int i = 0; i < length; i++) {
                if (dir == 'H') positions.push_back(Position(start.getx() + i, start.gety()));
                else            positions.push_back(Position(start.getx(), start.gety() + i));
            }
            bool inside = true;
            for (const Position& p : positions) {
                if (!field.is_inside(p)) { inside = false; break; }
            }
            if (!inside) {
                std::cout << "Ship does not fit try again.\n";
                continue;
            }
            Ship ship(positions);
            if (field.place_ship(ship)) {
                std::cout << "Placed\n";
                print_field(field, true);
                break;
            }
            else {
                std::cout << "Intersects or out of field, try again\n";
            }
        }
    }
    std::cout << "\nAll ships placed\n";
}

void place_ships_automatically(GameField& field) {
    std::vector<int> lengths = { 4, 3, 2, 1 };
    std::uniform_int_distribution<int> dx(0, field.get_width() - 1);
    std::uniform_int_distribution<int> dy(0, field.get_height() - 1);
    std::uniform_int_distribution<int> dd(0, 1);
    for (int length : lengths) {
        bool placed = false;
        for (int attempt = 0; attempt < 1000 && !placed; ++attempt) {
            int x = dx(gen);
            int y = dy(gen);
            char dir = (dd(gen) == 0) ? 'H' : 'V';
            std::vector<Position> positions;
            for (int i = 0; i < length; i++) {
                if (dir == 'H') positions.push_back(Position(x + i, y));
                else            positions.push_back(Position(x, y + i));
            }
            bool inside = true;
            for (const Position& p : positions) {
                if (!field.is_inside(p)) { inside = false; break; }
            }
            if (!inside) continue;
            Ship ship(positions);
            if (field.place_ship(ship)) {
                placed = true;
            }
        }
        if (!placed) {
            std::cerr << "Warning: could not place ship of length "
                << length << " after 1000 attempts\n";
        }
    }
}

Position bot_choose_shot(const GameField& enemy_field) {
    std::vector<Position> candidates;
    for (int y = 0; y < enemy_field.get_height(); y++) {
        for (int x = 0; x < enemy_field.get_width(); x++) {
            Position p(x, y);
            const auto& shots = enemy_field.get_shots();
            if (std::find(shots.begin(), shots.end(), p) == shots.end()) {
                candidates.push_back(p);
            }
        }
    }
    if (candidates.empty()) {
        return Position(-1, -1);
    }
    std::uniform_int_distribution<size_t> pick(0, candidates.size() - 1);
    return candidates[pick(gen)];
}

int main() {
    std::cout << "=== Battleship ===\n\n";
    Game game("Player1", "Player2", 6, 6);
    std::cout << "--- player1 place your ships manually ---\n";
    place_ships_manually(game.get_player(0).get_field());
    std::cout << "\n--- player2 ships placed automatically ---\n";
    place_ships_automatically(game.get_player(1).get_field());
    std::cout << "\n=== Game starts ===\n";
    while (!game.is_over()) {
        system("cls");
        int index = game.get_current_index();
        Player& current = game.get_player(index);
        Player& opponent = game.get_player(1 - index);
        std::cout << "\n--- " << current.get_name() << "'s turn ---\n";
        std::cout << "your field\n";
        print_field(current.get_field(), true);
        std::cout << "enemy field\n";
        print_field(opponent.get_field(), false);

        Position pos(0, 0);
        if (index == 0) {
            pos = input_position();
        }
        else {
            pos = bot_choose_shot(opponent.get_field());
            std::cout << "bot shoots at " << pos << "\n";
        }

        ShotResult r = game.play_turn(pos);
        print_result(r, current.get_name());

        if (r == ShotResult::Hit || r == ShotResult::Sunk) {
            std::cout << "\nenemy field at the moment:\n";
            print_field(opponent.get_field(), false);
        }
    }
    int winner = game.get_winner_index();
    if (winner >= 0) {
        std::cout << "\n--- " << game.get_player(winner).get_name() << " wins ---\n";
    }
    return 0;
}
