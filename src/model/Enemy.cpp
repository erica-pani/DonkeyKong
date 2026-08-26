#include "Enemy.hpp"
#include <SFML/Graphics.hpp>

Enemy::Enemy(sf::Vector2f position):
    enemyShape(),
    current_girder(nullptr),
    position(position),
    velocity({0 ,0}){
        enemyShape.setSize({25, 35});
        enemyShape.setFillColor(sf::Color(255, 192, 203));
        enemyShape.setPosition(position);
        enemyShape.setOrigin({enemyShape.getSize().x / 2, enemyShape.getSize().y / 2});
    }


Enemy::~Enemy() {

}

void Enemy::update(float dt, std::vector<Girder>& girders) {}

sf::Vector2f Enemy::get_postion() const{
    return position;
}

sf::Vector2f Enemy::get_velocity() const{
    return velocity;
}

const sf::RectangleShape& Enemy::get_shape() const{
    return enemyShape;
}

const Girder* Enemy::get_current_girder() {
    return current_girder;
}

void Enemy::set_postion(sf::Vector2f newPosition) {
    position = newPosition;
    enemyShape.setPosition(newPosition);
}

void Enemy::set_velocity(sf::Vector2f newVelo) {
    velocity = newVelo;
}

void Enemy::check_girder_intersection(const std::vector<Girder>& girders) {
    float playerHeight = enemyShape.getSize().y / 2;
    for (const Girder& girder : girders) {
        if (!girder.covers_x(position.x)) {
            continue;
        }
        float surface = girder.surface_y_at(position.x);
        if (position.y + playerHeight >= surface && surface >= position.y + playerHeight / 1.5f) {
            position.y = surface - playerHeight;
            enemyShape.setPosition(position);
            current_girder = &girder;
            return;
        }
    }
    current_girder = nullptr;
}