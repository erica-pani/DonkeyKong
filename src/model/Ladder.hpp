#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Girder.hpp"

class Ladder : public sf::Transformable, public sf::Drawable{
private:
    sf::RectangleShape leftRail;
    sf::RectangleShape rightRail;
    std::vector<sf::RectangleShape> rungs;
    sf::Vector2f position;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float get_ladder_width() const;
    
public:
    Ladder(sf::Vector2f position, float width, float height, int numRungs);
    ~Ladder();

    bool covers_x(float xPosition);

    float get_center() const;
};

