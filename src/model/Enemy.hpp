#pragma once

#include "Girder.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Enemy ist eine Figur die den Spieler daran hindern soll das Ziel zu erreichen
class Enemy {
private:
    const Girder* current_girder;
    sf::RectangleShape enemyShape;
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    sf::Vector2f position;
    sf::Vector2f velocity;

public:
    Enemy(sf::Vector2f position, const sf::Texture& tex);
    virtual ~Enemy();

    sf::Vector2f get_postion() const;
    sf::Vector2f get_velocity() const;
    const sf::Sprite& get_shape() const;
    const sf::Texture& get_texture() const;
    void set_postion(sf::Vector2f newPosition);
    void set_velocity(sf::Vector2f newVelocity);
    const Girder* get_current_girder();

    // berechnet die nächste Position des Gegners
    virtual void update(float dt, const std::vector<Girder>& girders);

    // Überprüft ob der Gegner auf einer Plattform steht und setzt current_girder
    void check_girder_intersection(const std::vector<Girder>& girders);
};
