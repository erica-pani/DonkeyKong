#include "Player.hpp"
#include "Constants.hpp"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>


Player::Player(sf::Vector2f position) : 
    playerShape(),
    position(position),
    velocity({0, 0}),
    current_girder(nullptr),
    isJumping(false),
    isClimbing(false){
        
        playerShape.setSize({playerWidth, playerHeight});
        playerShape.setOrigin({playerWidth / 2.0f, 0.0f});
        playerShape.setPosition(position);
        playerShape.setFillColor(sf::Color(200, 0, 0));
    }

Player::~Player() {}

sf::RectangleShape& Player::getShape() {
    return playerShape;
}

void Player::move(Direction direction) {
    switch (direction) {
    case Direction::RIGHT:
        velocity.x = constants::MOVEMENT_SPEED;
        break;

    case Direction::LEFT:
        velocity.x = -1 * constants::MOVEMENT_SPEED;
        break;
    
    case Direction::STAY:
        velocity.x = 0;
        break;
    default:
        break;
    }
}

void Player::climbLadder(Ladder& ladder) {
    if (ladder.covers_x(position.x) && ladder.get_girder_pointer() == current_girder) {
        position.x = ladder.get_center(); 
        velocity.y = -1.0f * 200.f;
        isClimbing = true;
        isJumping = false;
        current_girder = nullptr;
    }
    
}

void Player::jump() {
    if (!isJumping && current_girder != nullptr) {
        velocity.y = -1.0f * 300.f;
        isJumping = true;
    }
}

void Player::update(float dt, const std::vector<Girder>& girders) {
    float oldPosition = position.x;
    position.x += velocity.x * dt;
    
    if (current_girder == nullptr && !isClimbing && !isJumping) {

        velocity.y += constants::GRAVITY * dt;
        position.y += velocity.y * dt;
        check_girder_intersection(girders);
        /*bool canMove = false;

        if (velocity.x > 0){
            canMove = current_girder->covers_x(position.x + playerWidth);
        } else if (velocity.x < 0) {
            canMove = current_girder->covers_x(position.x);
        }
        
        if (!canMove) {
            position.x = oldPosition;
        }
        */
    }

    if (isClimbing) {
        position.x = oldPosition;
        position.y += velocity.y * dt;
        check_girder_intersection(girders);
        if (current_girder != nullptr) {
            velocity.y = 0;
            isClimbing = false;
        }
    }
    

    if (isJumping) {
        velocity.y += constants::GRAVITY * dt;
        position.y += velocity.y * dt;

        if (velocity.y > 0) {
            check_girder_intersection(girders);
            if (current_girder != nullptr) {
                velocity.y = 0;
                isJumping = false; 
            }
        }
        
    } else if (current_girder != nullptr) {
        position.y = current_girder->surface_y_at(position.x) - playerHeight;
    }
    check_girder_intersection(girders);
    playerShape.setPosition(position);
}

void Player::check_girder_intersection(const std::vector<Girder>& girders) {
    for (const Girder& girder : girders) {
        if (!girder.covers_x(position.x)) {
            continue;
        }
        float surface = girder.surface_y_at(position.x);
        if (position.y + playerHeight >= surface && surface >= position.y + playerHeight / 1.5f) {
            position.y = surface - playerHeight;
            current_girder = &girder;
            return;
        }
    }
    current_girder = nullptr;
}

void Player::setGirder(const Girder& girder) {
    current_girder = &girder;
}

const Girder* Player::getGirder() const {
    return current_girder;
}

void Player::setPosition(sf::Vector2f newPosition) {
    current_girder = nullptr;
    position = newPosition;
    playerShape.setPosition(newPosition);
}