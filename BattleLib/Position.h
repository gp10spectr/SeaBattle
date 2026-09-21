#pragma once

class Position {
private:
	int x;
	int y;
public:
	int getx() const noexcept;
	int gety() const noexcept;
	void setx();
	void sety();

};