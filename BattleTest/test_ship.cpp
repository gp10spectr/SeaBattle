#include "pch.h"
#include "Ship.h"

TEST(ShipTest, InitializerConstructor) {
	Position pos1(0, 1);
	Position pos2(0, 2);
	Position pos3(0, 3);
	Position pos4(0, 4);
	std::vector<Position> positions = { pos1, pos2, pos3, pos4 };
	Ship ship(positions);
	EXPECT_EQ(ship.get_positions().size(), 4u);
	EXPECT_EQ(ship.get_positions()[0], Position(0, 1));
	EXPECT_EQ(ship.get_positions()[1], Position(0, 2));
	EXPECT_EQ(ship.get_positions()[2], Position(0, 3));
	EXPECT_EQ(ship.get_positions()[3], Position(0, 4));
}

TEST(ShipTest, OneCellShip) {
	Position pos1(0, 0);
	std::vector<Position> positions = { pos1 };
	Ship ship(positions);
	EXPECT_EQ(ship.get_positions()[0], Position(0, 0));
}

TEST(ShipTest, TwoCellsShip) {
	Position pos1(0, 0);
	Position pos2(1, 0);
	std::vector<Position> positions = { pos1, pos2 };
	Ship ship(positions);
	EXPECT_EQ(ship.get_positions()[0], Position(0, 0));
	EXPECT_EQ(ship.get_positions()[1], Position(1, 0));
}

TEST(ShipTest, ThreeCellsShip) {
	Position pos1(0, 0);
	Position pos2(1, 0);
	Position pos3(2, 0);
	std::vector<Position> positions = { pos1, pos2, pos3 };
	Ship ship(positions);
	EXPECT_EQ(ship.get_positions()[0], Position(0, 0));
	EXPECT_EQ(ship.get_positions()[1], Position(1, 0));
	EXPECT_EQ(ship.get_positions()[2], Position(2, 0));
}

TEST(ShipTest, NegShipPos) {
	Position pos(-1, -1);
	std::vector<Position> positions = { pos };
	EXPECT_THROW(Ship ship(positions), std::invalid_argument);
}

TEST(ShipTest, DiagonalShipPos) {
	Position pos1(0, 0);
	Position pos2(1, 1);
	std::vector<Position> positions = { pos1, pos2 };
	EXPECT_THROW(Ship ship(positions), std::invalid_argument);
}

TEST(ShipTest, FiveCellsShip) {
	Position pos1(0, 0);
	Position pos2(1, 0);
	Position pos3(2, 0);
	Position pos4(3, 0);
	Position pos5(4, 0);
	std::vector<Position> positions = { pos1, pos2, pos3, pos4, pos5 };
	EXPECT_THROW(Ship ship(positions), std::invalid_argument);
}

TEST(ShipTest, CreateWithEmptyVector) {
	std::vector<Position> positions = {};
	EXPECT_THROW(Ship ship(positions), std::invalid_argument);
}

TEST(ShipTest, GapShip) {
	Position pos1(0, 0);
	Position pos2(2, 0);
	std::vector<Position> positions = { pos1, pos2 };
	EXPECT_THROW(Ship ship(positions), std::invalid_argument);
}

TEST(ShipTest, TwoEqualCellsShip) {
	Position pos1(0, 0);
	Position pos2(0, 0);
	std::vector<Position> positions = { pos1, pos2 };
	EXPECT_THROW(Ship ship(positions), std::invalid_argument);
}

TEST(ShipTest, ShipContains) {
	Position pos(0, 0);
	std::vector<Position> positions = { pos };
	Ship ship(positions);
	EXPECT_TRUE(ship.contains(pos));
}

TEST(ShipTest, ShipDoesNotContains) {
	Position pos1(0, 0);
	Position pos2(1, 1);
	std::vector<Position> positions = { pos1 };
	Ship ship(positions);
	EXPECT_FALSE(ship.contains(pos2));
}

TEST(ShipTest, HitCounts) {
	Position pos1(0, 0);
	Position pos2(1, 0);
	Position hit_pos(0, 0);
	std::vector<Position> positions = { pos1, pos2 };
	Ship ship(positions);
	EXPECT_TRUE(ship.hit(hit_pos));
	EXPECT_EQ(ship.get_hits().size(), 1u);
	EXPECT_EQ(ship.get_hits()[0], pos1);
}

TEST(ShipTest, HitMiss) {
	Ship ship({ Position(0, 0), Position(1, 0) });
	EXPECT_FALSE(ship.hit(Position(5, 5)));
	EXPECT_TRUE(ship.get_hits().empty());
}

TEST(ShipTest, HitTwiceInSameCell) {
	Ship ship({ Position(0, 0), Position(1, 0) });
	EXPECT_TRUE(ship.hit(Position(0, 0)));
	EXPECT_FALSE(ship.hit(Position(0, 0)));
}

TEST(ShipTest, SinkAfterAllHits) {
	Ship ship({ Position(0, 0), Position(1, 0), Position(2, 0) });
	EXPECT_FALSE(ship.is_sunk());
	ship.hit(Position(0, 0));
	EXPECT_FALSE(ship.is_sunk());
	ship.hit(Position(1, 0));
	EXPECT_FALSE(ship.is_sunk());
	ship.hit(Position(2, 0));
	EXPECT_TRUE(ship.is_sunk());
}

TEST(ShipTest, OneCellShipSinksAfterOneHit) {
	Ship ship({ Position(0, 0) });
	EXPECT_FALSE(ship.is_sunk());
	ship.hit(Position(0, 0));
	EXPECT_TRUE(ship.is_sunk());
}

TEST(ShipTest, OperatorTestEqual) {
	Ship ship1({ Position(0, 0) });
	Ship ship2({ Position(0, 0) });
	EXPECT_TRUE(ship1 == ship2);
}

TEST(ShipTest, EqualShipsWithDiffHits) {
	Ship ship1({ Position(0, 0), Position(1, 0)});
	Ship ship2({ Position(0, 0), Position(1, 0)});
	ship1.hit(Position(0, 0));
	EXPECT_TRUE(ship1 == ship2);
}

TEST(ShipTest, SunkShipEqualRegularShip) {
	Ship ship1({ Position(0, 0), Position(1, 0) });
	Ship ship2({ Position(0, 0), Position(1, 0) });
	ship1.hit(Position(0, 0));
	ship1.hit(Position(1, 0));
	EXPECT_TRUE(ship1 == ship2);
}

TEST(ShipTest, ShipEqualsItself) {
	Ship ship({ Position(0, 0), Position(1, 0) });
	EXPECT_TRUE(ship == ship);
}

TEST(ShipTest, OperatorTestNotEqual) {
	Ship ship1({ Position(0, 0) });
	Ship ship2({ Position(1, 0) });
	EXPECT_FALSE(ship1 == ship2);
}
