#pragma once
#include <vector>
#include <iostream>

class Position {
private:
    int x;
    int y;
public:
    int getx() const noexcept;
    int gety() const noexcept;
    Position(int x, int y);
    bool valid_pos(int width, int height) const;
    std::vector<Position> neighbors() const;
    bool operator==(const Position& other) const;
};

std::ostream& operator<<(std::ostream& os, const Position& pos);
