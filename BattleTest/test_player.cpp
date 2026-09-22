#include "pch.h"
#include "Player.h"

TEST(PlayerTest, InitializerConstructor) {
	Player player("Emperor", 10, 10);
	EXPECT_EQ(player.get_name(), "Emperor");
	EXPECT_EQ(player.get_field().get_width(), 10);
	EXPECT_EQ(player.get_field().get_height(), 10);
}

TEST(PlayerTest, CreatingEmptyField) {
	Player player("Emperor", 10, 10);
	EXPECT_EQ(player.get_field().get_ships().size(), 0);
	EXPECT_EQ(player.get_field().get_shots().size(), 0);
}

TEST(PlayerTest, CreatingEmptyFieldAlso) {
	Player player("Emperor", 10, 10);
	EXPECT_TRUE(player.get_field().get_ships().empty());
	EXPECT_TRUE(player.get_field().get_shots().empty());
}

TEST(PlayerTest, CanPlaceShip) {
	Player p("Emperor", 5, 5);
	p.get_field().place_ship(Ship({ Position(0,0) }));
	EXPECT_EQ(p.get_field().get_ships().size(), 1u);
}

TEST(PlayerTest, DefeatedWithEmptyField) {
	Player player("Emperor", 10, 10);
	EXPECT_TRUE(player.defeated());
}

TEST(PlayerTest, NotDefeated) {
	Player player("Emperor", 10, 10);
	player.get_field().place_ship(Ship({ Position(0, 0) }));
	EXPECT_FALSE(player.defeated());
}

TEST(PlayerTest, DefeatedAfterShot) {
	Player player("Emperor", 10, 10);
	player.get_field().place_ship(Ship({ Position(0, 0) }));
	player.get_field().shoot(Position(0, 0));
	EXPECT_TRUE(player.defeated());
}
