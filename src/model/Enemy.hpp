#pragma once

#include "Girder.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Enemy {
private:
    const Girder* current_girder;
    sf::RectangleShape enemyShape;
    sf::Vector2f position;
    sf::Vector2f velocity;

public:
    Enemy(sf::Vector2f position);
    virtual ~Enemy();

    sf::Vector2f get_postion() const;
    sf::Vector2f get_velocity() const;
    const sf::RectangleShape& get_shape() const;
    void set_postion(sf::Vector2f newPosition);
    void set_velocity(sf::Vector2f newVelocity);
    const Girder* get_current_girder();

    virtual void update(float dt, const std::vector<Girder>& girders);

    void check_girder_intersection(const std::vector<Girder>& girders);
};
