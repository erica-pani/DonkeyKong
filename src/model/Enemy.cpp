#include "Enemy.hpp"
#include <SFML/Graphics.hpp>

Enemy::Enemy(sf::Vector2f position, const sf::Texture& tex):
    enemyShape(),
    current_girder(nullptr),
    position(position),
    velocity({0 ,0}),
    enemyTexture(tex),
    enemySprite(enemyTexture) {

        sf::Vector2f targetSize{42.0f, 45.0f};
        enemySprite.setOrigin({enemyTexture.getSize().x / 2.0f, enemyTexture.getSize().y / 2.0f});

        sf::Vector2f scaleFactor{
            targetSize.x / enemyTexture.getSize().x,
            targetSize.y / enemyTexture.getSize().y,
        };
        enemySprite.setScale(scaleFactor);
        enemySprite.setPosition(position);
    }


Enemy::~Enemy() {

}

void Enemy::update(float dt, const std::vector<Girder>& girders) {}

sf::Vector2f Enemy::get_postion() const{
    return position;
}

sf::Vector2f Enemy::get_velocity() const{
    return velocity;
}

const sf::Sprite& Enemy::get_shape() const{
    return enemySprite;
}

const sf::Texture& Enemy::get_texture() const {
    return enemyTexture;
}

const Girder* Enemy::get_current_girder() {
    return current_girder;
}

void Enemy::set_postion(sf::Vector2f newPosition) {
    position = newPosition;
    enemyShape.setPosition(newPosition);
    enemySprite.setPosition(newPosition);
}

void Enemy::set_velocity(sf::Vector2f newVelo) {
    velocity = newVelo;
}

void Enemy::check_girder_intersection(const std::vector<Girder>& girders) {
    float playerHeight = enemySprite.getGlobalBounds().size.y;
    for (const Girder& girder : girders) {
        if (!girder.covers_x(position.x)) {
            continue;
        }
        float surface = girder.surface_y_at(position.x);
        if (position.y + playerHeight >= surface && surface >= position.y) {
            position.y = surface - playerHeight / 2;
            enemyShape.setPosition(position);
            enemySprite.setPosition(position);
            current_girder = &girder;
            return;
        }
    }
    current_girder = nullptr;
}