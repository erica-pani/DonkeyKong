#include <gtest/gtest.h>

#include <vector>

#include "../src/model/Barrel.hpp"
#include "../src/model/Girder.hpp"
#include "../src/model/Constants.hpp"

// These tests exercise the barrel/girder physics directly. They construct only
// model objects (which hold CPU-side SFML shapes, no window), so they run headless.

namespace {
constexpr float R = constants::BARREL_RADIUS;

// two overlapping girders: g0 slopes down-right, g1 (below it) down-left, so a
// barrel rolling off g0's right end drops onto g1 and reverses direction.
std::vector<Girder> two_girder_stage() {
    std::vector<Girder> girders;
    girders.emplace_back(sf::Vector2f{0, -200}, sf::Vector2f{100, -160}); // down-right
    girders.emplace_back(sf::Vector2f{0, -60},  sf::Vector2f{140, -100}); // down-left
    return girders;
}

Barrel barrel_on(const Girder& g) {
    Barrel barrel({g.high_end().x, g.high_end().y - R});
    barrel.set_on_girder(g);
    return barrel;
}
} // namespace

TEST(GirderTest, geometry) {
    Girder down_right({0, -200}, {100, -160}); // slope 0.4, lower end on the right
    EXPECT_FLOAT_EQ(down_right.slope(), 0.4f);
    EXPECT_FLOAT_EQ(down_right.surface_y_at(50), -180.f);
    EXPECT_EQ(down_right.downhill_sign(), 1);
    EXPECT_FLOAT_EQ(down_right.high_end().x, 0.f);

    Girder down_left({0, -60}, {100, -100}); // lower end on the left
    EXPECT_EQ(down_left.downhill_sign(), -1);
    EXPECT_FLOAT_EQ(down_left.high_end().x, 100.f);
}

TEST(BarrelTest, rolls_glued_to_the_slope) {
    std::vector<Girder> girders = two_girder_stage();
    Barrel barrel = barrel_on(girders[0]);

    barrel.update(0.1f, girders);

    EXPECT_EQ(barrel.get_state(), Barrel::State::OnGirder);
    EXPECT_FLOAT_EQ(barrel.get_position().x, constants::ROLL_SPEED * 0.1f); // moved downhill
    EXPECT_FLOAT_EQ(barrel.get_position().y,                               // y follows the surface
                    girders[0].surface_y_at(barrel.get_position().x) - R);
}

TEST(BarrelTest, zig_zags_onto_the_next_girder) {
    std::vector<Girder> girders = two_girder_stage();
    Barrel barrel = barrel_on(girders[0]);
    ASSERT_GT(barrel.get_vx(), 0.f); // rolling right on g0

    // run until it rolls off g0, falls, and settles on g1 (now rolling left)
    for (int i = 0; i < 2000 &&
         !(barrel.get_state() == Barrel::State::OnGirder && barrel.get_vx() < 0.f); ++i) {
        barrel.update(1.f / 60.f, girders);
    }

    EXPECT_EQ(barrel.get_state(), Barrel::State::OnGirder);
    EXPECT_LT(barrel.get_vx(), 0.f); // direction flipped on the down-left girder
    EXPECT_NEAR(barrel.get_position().y,
                girders[1].surface_y_at(barrel.get_position().x) - R, 0.001f);
}
