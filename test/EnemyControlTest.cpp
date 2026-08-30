#include <gtest/gtest.h>

#include "../src/model/Constants.hpp"
#include "../src/model/Player.hpp"
#include "../src/control/EnemyControl.hpp"
#include "../src/view/Layer.hpp"

namespace {
    constexpr float mSpeed = constants::MOVEMENT_SPEED;

    Player set_up_player() {
        return Player({300, -300});
    }

    std::vector<Girder> set_up_girders() {
        std::vector<Girder> girders;
        girders.emplace_back(sf::Vector2f{100, -260}, sf::Vector2f{500, -260});
        return girders;
    }
}



TEST(PlayerTest, player_moves_right) {
    Player player = set_up_player();
    std::vector<Girder> girders = set_up_girders();
    player.setGirder(girders[0]);

    player.move(Direction::RIGHT);
    EXPECT_FLOAT_EQ(player.getVelocity().x, mSpeed);

    float dt = 0.35f;
    float newPosition = player.getShape().getPosition().x + mSpeed * dt;
    player.update(dt , girders);

    EXPECT_FLOAT_EQ(player.getShape().getPosition().x, newPosition);
}

TEST(PlayerTest, player_doesnt_move) {
    Player player = set_up_player();
    std::vector<Girder> girders = set_up_girders();
    player.setGirder(girders[0]);

    player.move(Direction::STAY);
    EXPECT_FLOAT_EQ(player.getVelocity().x, 0);

    float dt = 0.35f;
    float newPosition = player.getShape().getPosition().x;
    player.update(dt , girders);

    EXPECT_FLOAT_EQ(player.getShape().getPosition().x, newPosition);
}

TEST(PlayerTest, player_moves_left) {
    Player player = set_up_player();
    std::vector<Girder> girders = set_up_girders();
    player.setGirder(girders[0]);

    player.move(Direction::LEFT);
    EXPECT_FLOAT_EQ(player.getVelocity().x, -mSpeed);

    float dt = 0.35f;
    float newPosition = player.getShape().getPosition().x + -mSpeed * dt;
    player.update(dt , girders);

    EXPECT_FLOAT_EQ(player.getShape().getPosition().x, newPosition);
}