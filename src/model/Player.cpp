#include "Player.hpp"
#include "Constants.hpp"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>


Player::Player(sf::Vector2f position) :
    runningTexture(),
    playerSprite(runningTexture),
    playerShape(),
    position(position),
    velocity({0, 0}),
    current_girder(nullptr),
    animationTimer(0.0f),
    currentFrame(0),
    isJumping(false),
    isClimbing(false),
    landingTimer(0.0f) {

    if (!runningTexture.loadFromFile("assets/img/player_sprites/Player_Sprite.png")) {
        std::cerr << "Fehler beim Laden von assets/Player_Sprite.png!\n";
    }

    sf::Vector2u textureSize = runningTexture.getSize();
    int frameCount = textureSize.x / FRAME_WIDTH;

    for (int i = 0; i < frameCount; ++i) {
        running_frames.push_back(sf::IntRect({i * FRAME_WIDTH, 0}, {FRAME_WIDTH, FRAME_HEIGHT}));
    }
    for (int i = 0; i < 2; ++i) {
        jumping_frames.push_back(sf::IntRect({i * FRAME_WIDTH, FRAME_HEIGHT}, {FRAME_WIDTH, FRAME_HEIGHT}));
    }
    for (int i = 0; i < 4; ++i) {
        climbing_frames.push_back(sf::IntRect({i * FRAME_WIDTH, FRAME_HEIGHT*2}, {FRAME_WIDTH, FRAME_HEIGHT}));
    }


    playerSprite.setTextureRect(running_frames[0]);
    playerSprite.setOrigin({16.0f / 2.0f, 0.0f});

    float scaleX = playerWidth / 16.0f;
    float scaleY = playerHeight / 27.0f;
    playerSprite.setScale({scaleX, scaleY});
    playerSprite.setPosition(position);

    playerShape.setSize({playerWidth, playerHeight});
    playerShape.setOrigin({playerWidth / 2.0f, 0.0f});
    playerShape.setPosition(position);
    playerShape.setFillColor(sf::Color(200, 0, 0, 0));
}

Player::~Player() = default;

sf::Sprite Player::getSprite() {
    return playerSprite;
}

sf::RectangleShape Player::getShape() {
    return playerShape;
}

void Player::move(Direction direction) {
    float scaleX = playerWidth / FRAME_WIDTH;
    float scaleY = playerHeight / FRAME_HEIGHT;

    switch (direction) {
    case Direction::RIGHT:
        velocity.x = constants::MOVEMENT_SPEED;
        playerSprite.setScale({scaleX, scaleY});
        break;

    case Direction::LEFT:
        velocity.x = -1 * constants::MOVEMENT_SPEED;
        playerSprite.setScale({-scaleX, scaleY});
        break;
    
    case Direction::STAY:
        velocity.x = 0;
        break;
    default:
        break;
    }
}

void Player::climbLadder(const Ladder& ladder) {
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

void Player::duckDown() {}

void Player::update(float dt, const std::vector<Girder>& girders) {
    float oldPosition = position.x;
    position.x += velocity.x * dt;

    const float frameDuration = 0.12f;

    // Animations-Logik nach Priorität getrennt
    if (isLanding) {
        landingTimer -= dt;
        playerSprite.setTextureRect(jumping_frames[1]);
        if (landingTimer <= 0.0f) {
            isLanding = false;
        }
    } else if (isJumping) {
        playerSprite.setTextureRect(jumping_frames[0]);
    } else if (isClimbing) {
        animationTimer += dt;
        if (animationTimer >= frameDuration) {
            animationTimer -= frameDuration;
            currentFrame = (currentFrame + 1) % climbing_frames.size();
            playerSprite.setTextureRect(climbing_frames[currentFrame]);
        }
    } else if (velocity.x != 0 && current_girder != nullptr) {
        animationTimer += dt;
        if (animationTimer >= frameDuration) {
            animationTimer -= frameDuration;
            currentFrame = (currentFrame + 1) % running_frames.size();
            playerSprite.setTextureRect(running_frames[currentFrame]);
        }
    } else {
        currentFrame = 0;
        animationTimer = 0.0f;
        playerSprite.setTextureRect(running_frames[0]);
    }

    if (current_girder == nullptr && !isClimbing && !isJumping && !isLanding) {
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
                isLanding = true;
                landingTimer = 0.075f;
                playerSprite.setTextureRect(jumping_frames[1]);
            }
        }
    } else if (current_girder != nullptr) {
        position.y = current_girder->surface_y_at(position.x) - playerHeight;
    }

    check_girder_intersection(girders);
    playerShape.setPosition(position);
    playerSprite.setPosition(position);
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