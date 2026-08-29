#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include "Ladder.hpp"
#include "Girder.hpp"
#include "Direction.hpp"

class Player
{
    sf::Texture runningTexture;
    sf::Sprite playerSprite;
    sf::RectangleShape playerShape;
    std::vector<sf::IntRect> running_frames;
    std::vector<sf::IntRect> jumping_frames;
    std::vector<sf::IntRect> climbing_frames;


    sf::Vector2f position;
    sf::Vector2f velocity;

    const Girder* current_girder;
    //Sprite Size
    static constexpr int FRAME_WIDTH = 16;
    static constexpr int FRAME_HEIGHT = 27;

    float playerHeight = 40.f;
    float playerWidth = 30.f;

    float animationTimer;
    int currentFrame;

    bool isJumping;
    bool isClimbing;
    bool isLanding;
    float landingTimer;

public:
    explicit Player(sf::Vector2f position);
    ~Player();

    sf::Sprite getSprite();
    sf::RectangleShape getShape();
    
    void move(Direction direction);
    void jump();
    void duckDown();
    void climbLadder(Ladder& ladder);

    void update(float dt, const std::vector<Girder>& girders);
    void check_girder_intersection(const std::vector<Girder>& girders);
    void setGirder(const Girder& girder);
    const Girder* getGirder() const;
};