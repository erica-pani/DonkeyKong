#ifndef GIRDER_H
#define GIRDER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

// A single sloped girder (a tilted floor segment). Defined by its two endpoints
// `left` and `right` (with left.x < right.x). The barrel rolls along its surface.
class Girder {
public:
    Girder(sf::Vector2f left, sf::Vector2f right);

    // slope = dy/dx = tan(tilt angle); the simple "gravity" approximation
    float slope() const;

    // height (y) of the girder surface at horizontal position x
    float surface_y_at(float x) const;

    // is x within the girder's horizontal span?
    bool covers_x(float x) const;

    // direction a barrel rolls along this girder: +1 toward +x, -1 toward -x
    // (always toward the lower end)
    int downhill_sign() const;

    sf::Vector2f high_end() const;
    sf::Vector2f low_end() const;
    const sf::RectangleShape& get_shape() const;
    
    float min_x() const;
    float max_x() const;

private:
    sf::Vector2f left;
    sf::Vector2f right;
    sf::RectangleShape shape;
};

#endif
