#include <gtest/gtest.h>
#include "../src/model/Ghost.hpp"
#include "../src/model/Girder.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <vector>

namespace {
    sf::Texture create_dummy_texture() {
        sf::Texture texture;
        (void)texture.resize({32, 32}); 
        return texture;
    }

    std::vector<Girder> set_up_girders() {
        std::vector<Girder> girders;
        girders.emplace_back(sf::Vector2f{100.0f, -260.0f}, sf::Vector2f{500.0f, -260.0f});
        return girders;
    }
}


TEST(GhostTest, hit_right_boundary) {
    sf::Texture dummyTexture = create_dummy_texture();
    std::vector<Girder> girders = set_up_girders();

    Ghost ghost({350.0f, -260.0f}, dummyTexture);
    
    ghost.check_girder_intersection(girders);
    ASSERT_NE(ghost.get_current_girder(), nullptr);

    ghost.set_velocity({80.0f, 0.0f});

    float rightBoundary = ghost.get_right_boundary(); 
    ghost.set_postion({rightBoundary + 1.0f, -260.0f});

    ghost.update(0.1f, girders);

    EXPECT_LT(ghost.get_velocity().x, 0.0f);
}

TEST(GhostTest, hit_left_boundary) {
    sf::Texture dummyTexture = create_dummy_texture();
    std::vector<Girder> girders = set_up_girders();

    Ghost ghost({350.0f, -260.0f}, dummyTexture);
    
    ghost.check_girder_intersection(girders);
    ASSERT_NE(ghost.get_current_girder(), nullptr);

    ghost.set_velocity({-80.0f, 0.0f});

    float leftBoundary = ghost.get_left_boundary(); 
    ghost.set_postion({leftBoundary - 1.0f, -260.0f});

    ghost.update(0.1f, girders);

    EXPECT_GT(ghost.get_velocity().x, 0.0f);
}


TEST(GhostTest, hit_girder_end) {
    sf::Texture dummyTexture = create_dummy_texture();
    std::vector<Girder> girders = set_up_girders();

    Ghost ghost({500.0f, -260.0f}, dummyTexture);
    
    ghost.check_girder_intersection(girders);
    ASSERT_NE(ghost.get_current_girder(), nullptr);

    ghost.set_velocity({80.0f, 0.0f});

    ghost.update(0.1f, girders);

    EXPECT_LT(ghost.get_velocity().x, 0.0f);
}