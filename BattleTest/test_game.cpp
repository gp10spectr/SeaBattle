#include "pch.h"
#include "Game.h"

TEST(GameTest, InitializerConstructor) {
	Game game("Player1", "Player2", 10, 10);
	EXPECT_EQ(game.get_player(0).get_name(), "Player1");
	EXPECT_EQ(game.get_player(1).get_name(), "Player2");
	EXPECT_EQ(game.get_player(0).get_field().get_width(), 10);
	EXPECT_EQ(game.get_player(0).get_field().get_height(), 10);
	EXPECT_EQ(game.get_player(1).get_field().get_width(), 10);
	EXPECT_EQ(game.get_player(1).get_field().get_height(), 10);
}

TEST(GameTest, FirstPlayerTurn) {
	Game game("Player1", "Player2", 10, 10);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
}

TEST(GameTest, NextTurnAfterMiss) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(1).get_field().place_ship(Ship({ Position(0, 0) }));
	EXPECT_EQ(game.play_turn(Position(5, 5)), ShotResult::Miss);
	EXPECT_EQ(game.get_current_player().get_name(), "Player2");
}

TEST(GameTest, CurrentPlayerKeepsTurnAfterHit) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(1).get_field().place_ship(Ship({ Position(0, 0), Position(1, 0)}));
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Hit);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
}

TEST(GameTest, CurrentPlayerKeepsTurnAfterHitAndSunk) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(1).get_field().place_ship(Ship({ Position(0, 0), Position(1, 0) }));
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Hit);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
	EXPECT_EQ(game.play_turn(Position(1, 0)), ShotResult::Sunk);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
}

TEST(GameTest, NextTurnAfterHitAndMiss) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(1).get_field().place_ship(Ship({ Position(0, 0), Position(1, 0) }));
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Hit);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
	EXPECT_EQ(game.play_turn(Position(0, 1)), ShotResult::Miss);
	EXPECT_EQ(game.get_current_player().get_name(), "Player2");
}

TEST(GameTest, SameShotDoesntCount) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(1).get_field().place_ship(Ship({ Position(0, 0), Position(1, 0) }));
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Hit);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::AlreadyShot);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
}

TEST(GameTest, OutOfBoundsShotDoesntCount) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(1).get_field().place_ship(Ship({ Position(0, 0), Position(1, 0) }));
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Hit);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
	EXPECT_EQ(game.play_turn(Position(10, 10)), ShotResult::OutOfBounds);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
}

TEST(GameTest, GameIsNotOverAtStarting) {
	Game game("Player1", "Player2", 10, 10);
	EXPECT_FALSE(game.is_over());
	EXPECT_EQ(game.get_winner_index(), -1);
}

TEST(GameTest, GameOverAfterAllShipsSunk) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(1).get_field().place_ship(Ship({ Position(0, 0), Position(1, 0) }));
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Hit);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
	EXPECT_EQ(game.play_turn(Position(1, 0)), ShotResult::Sunk);
	EXPECT_TRUE(game.is_over());
	EXPECT_EQ(game.get_winner_index(), 0);
}

TEST(GameTest, TurnAlternationAcrossMultipleTurns) {
	Game game("Player1", "Player2", 10, 10);
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Miss);
	EXPECT_EQ(game.get_current_player().get_name(), "Player2");
	EXPECT_EQ(game.play_turn(Position(1, 0)), ShotResult::Miss);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
	EXPECT_EQ(game.play_turn(Position(2, 0)), ShotResult::Miss);
	EXPECT_EQ(game.get_current_player().get_name(), "Player2");
	EXPECT_EQ(game.play_turn(Position(3, 0)), ShotResult::Miss);
	EXPECT_EQ(game.get_current_player().get_name(), "Player1");
}

TEST(GameTest, SecondPlayerWinsBySinkingAllShips) {
	Game game("Player1", "Player2", 10, 10);
	game.get_player(0).get_field().place_ship(Ship({ Position(0, 0) }));
	EXPECT_EQ(game.play_turn(Position(9, 9)), ShotResult::Miss);
	EXPECT_EQ(game.get_current_player().get_name(), "Player2");
	EXPECT_EQ(game.play_turn(Position(0, 0)), ShotResult::Sunk);
	EXPECT_TRUE(game.is_over());
	EXPECT_EQ(game.get_winner_index(), 1);
}
