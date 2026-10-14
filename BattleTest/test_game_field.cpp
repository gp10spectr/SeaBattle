#include "pch.h"
#include "GameField.h"

TEST(GameFieldTest, InitializerConstructor) {
    GameField f(10, 8);
    EXPECT_EQ(f.get_width(), 10);
    EXPECT_EQ(f.get_height(), 8);
    EXPECT_TRUE(f.get_ships().empty());
    EXPECT_TRUE(f.get_shots().empty());
}

TEST(GameFieldTest, PlaceOneShipInEmptyField) {
    GameField field(10, 10);
    Ship ship({ Position(0, 0) });
    EXPECT_TRUE(field.place_ship(ship));
    EXPECT_EQ(field.get_ships().size(), 1u);
}

TEST(GameFieldTest, ShipCountInEmptyField) {
    GameField field(10, 10);
    Ship ship({ Position(10, 0) });
    field.place_ship(ship);
    EXPECT_EQ(field.get_ships().size(), 0);
}

TEST(GameFieldTest, ShipsCross) {
    GameField field(10, 10);
    Ship ship1({ Position(8, 0), Position(9, 0)});
    Ship ship2({ Position(8, 0), Position(8, 1) });
    field.place_ship(ship1);
    field.place_ship(ship2);
    EXPECT_EQ(field.get_ships().size(), 1u);
}

TEST(GameFieldTest, ShipsTouchesDiagonal) {
    GameField field(10, 10);
    Ship ship1({ Position(8, 0), Position(9, 0) });
    Ship ship2({ Position(7, 1), Position(7, 2) });
    field.place_ship(ship1);
    field.place_ship(ship2);
    EXPECT_EQ(field.get_ships().size(), 2u);
}

TEST(GameFieldTest, PlaceFourShips) {
    GameField field(10, 10);
    Ship ship1({ Position(0, 0) });
    Ship ship2({ Position(2, 0), Position(3, 0) });
    Ship ship3({ Position(0, 2), Position(1, 2), Position(2, 2) });
    Ship ship4({ Position(0, 6), Position(1, 6), Position(2, 6), Position(3, 6)});
    field.place_ship(ship1);
    field.place_ship(ship2);
    field.place_ship(ship3);
    field.place_ship(ship4);
    EXPECT_EQ(field.get_ships().size(), 4u);
}

TEST(GameFieldTest, IsInsideChecksBounds) {
    GameField f(10, 10);
    EXPECT_TRUE(f.is_inside(Position(0, 0)));
    EXPECT_TRUE(f.is_inside(Position(9, 9)));
    EXPECT_FALSE(f.is_inside(Position(-1, 0)));
    EXPECT_FALSE(f.is_inside(Position(0, -1)));
    EXPECT_FALSE(f.is_inside(Position(10, 0)));
    EXPECT_FALSE(f.is_inside(Position(0, 10)));
}

TEST(GameFieldTest, PlaceShipOutsideField) {
    GameField f(5, 5);
    Ship s({ Position(4,4), Position(5,4) });
    EXPECT_FALSE(f.place_ship(s));
    EXPECT_TRUE(f.get_ships().empty());
}

TEST(GameFieldTest, ShootOutOfBounds) {
    GameField f(5, 5);
    EXPECT_EQ(f.shoot(Position(-1, 0)), ShotResult::OutOfBounds);
    EXPECT_EQ(f.shoot(Position(5, 5)), ShotResult::OutOfBounds);
    EXPECT_TRUE(f.get_shots().empty());
}

TEST(GameFieldTest, ShootMiss) {
    GameField f(5, 5);
    Ship s({ Position(0,0) });
    f.place_ship(s);
    EXPECT_EQ(f.shoot(Position(2, 2)), ShotResult::Miss);
    ASSERT_EQ(f.get_shots().size(), 1u);
    EXPECT_EQ(f.get_shots()[0], Position(2, 2));
}

TEST(GameFieldTest, ShootHit) {
    GameField f(5, 5);
    Ship s({ Position(0,0), Position(1,0) });
    f.place_ship(s);
    EXPECT_EQ(f.shoot(Position(0, 0)), ShotResult::Hit);
    EXPECT_EQ(f.get_shots().size(), 1u);
}

TEST(GameFieldTest, ShootSunk) {
    GameField f(5, 5);
    Ship s({ Position(0,0), Position(1,0) });
    f.place_ship(s);
    EXPECT_EQ(f.shoot(Position(0, 0)), ShotResult::Hit);
    EXPECT_EQ(f.shoot(Position(1, 0)), ShotResult::Sunk);
}

TEST(GameFieldTest, ShootSameCellTwiceIsAlreadyShot) {
    GameField f(5, 5);
    Ship s({ Position(0,0) });
    f.place_ship(s);
    EXPECT_EQ(f.shoot(Position(0, 0)), ShotResult::Sunk);
    EXPECT_EQ(f.shoot(Position(0, 0)), ShotResult::AlreadyShot);
    EXPECT_EQ(f.get_shots().size(), 1u);
}

TEST(GameFieldTest, AllSunkEmptyFieldReturnsFalse) {
    GameField f(5, 5);
    EXPECT_FALSE(f.all_sunk());
}

TEST(GameFieldTest, AllSunkWithAliveShip) {
    GameField f(5, 5);
    Ship s({ Position(0,0), Position(1,0) });
    f.place_ship(s);
    EXPECT_FALSE(f.all_sunk());
    f.shoot(Position(0, 0));
    EXPECT_FALSE(f.all_sunk());
    f.shoot(Position(1, 0));
    EXPECT_TRUE(f.all_sunk());
}

TEST(GameFieldTest, AllSunkWithMultipleShips) {
    GameField f(10, 10);
    f.place_ship(Ship({ Position(0,0) }));
    f.place_ship(Ship({ Position(5,5) }));
    EXPECT_FALSE(f.all_sunk());
    f.shoot(Position(0, 0));
    EXPECT_FALSE(f.all_sunk());
    f.shoot(Position(5, 5));
    EXPECT_TRUE(f.all_sunk());
}
