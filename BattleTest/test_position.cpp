#include "pch.h"
#include "Position.h"
#include <sstream>

TEST(PositionTest, InitializerConstructor) {
	Position pos(1, 0);
	EXPECT_EQ(pos.getx(), 1);
	EXPECT_EQ(pos.gety(), 0);
}

TEST(PositionTest, OperatorTestNotEqual) {
	Position pos1(1, 0);
	Position pos2(0, 0);
	EXPECT_FALSE(pos1 == pos2);
}

TEST(PositionTest, OperatorTestEqual) {
	Position pos1(0, 0);
	Position pos2(0, 0);
	EXPECT_TRUE(pos1 == pos2);
}

TEST(PositionTest, OperatorOut) {
	std::ostringstream oss;
	Position pos(1, 0);
	oss << pos;
	EXPECT_EQ(oss.str(), "(1, 0)");
}

TEST(PositionTest, ValidPosInside) {
	Position pos(1, 0);
	EXPECT_TRUE(pos.valid_pos(10, 10));
}

TEST(PositionTest, ValidPosOutOf) {
	Position pos(10, 10);
	EXPECT_FALSE(pos.valid_pos(9, 9));
}

TEST(PositionTest, ValidPosOnEdge) {
	Position pos(10, 10);
	EXPECT_FALSE(pos.valid_pos(10, 10));
}

TEST(PositionTest, ValidPosOnBorderAndNegative) {
	Position pos1(9, 10);
	Position pos2(-1, 9);
	EXPECT_FALSE(pos1.valid_pos(10, 10));
	EXPECT_FALSE(pos2.valid_pos(10, 10));
}

TEST(PositionTest, NeighborNumber) {
	Position pos(9, 9);
	EXPECT_EQ(pos.neighbors().size(), 4u);
}

TEST(PositionTest, NeighborList) {
	Position pos(9, 9);
	std::vector<Position> res;
	res = pos.neighbors();
	EXPECT_EQ(res[0], Position(8, 9));
	EXPECT_EQ(res[1], Position(9, 8));
	EXPECT_EQ(res[2], Position(10, 9));
	EXPECT_EQ(res[3], Position(9, 10));
}

TEST(PositionTest, NeighborListCenter) {
	Position pos(3, 3);
	std::vector<Position> res;
	res = pos.neighbors();
	EXPECT_EQ(res[0], Position(2, 3));
	EXPECT_EQ(res[1], Position(3, 2));
	EXPECT_EQ(res[2], Position(4, 3));
	EXPECT_EQ(res[3], Position(3, 4));
}
