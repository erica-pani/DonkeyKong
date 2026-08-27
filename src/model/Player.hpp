#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "Ladder.hpp"
#include "Girder.hpp"
#include "Direction.hpp"

class Player
{
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::RectangleShape playerShape;
    std::vector<sf::IntRect> running_frames;

    sf::Vector2f position;

    sf::Vector2f velocity;

    const Girder* current_girder;

    float playerHeight = 40.f;
    float playerWidth = 30.f;

    bool isJumping;
    bool isClimbing;

public:
    Player(sf::Vector2f position);
    ~Player();

    const sf::Sprite& getSprite() const;
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

