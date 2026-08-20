#ifndef BARREL_H
#define BARREL_H

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Girder.hpp"

// A barrel rolling down the girders. It is a tiny 2-state machine:
//  - OnGirder: glued to the girder surface, rolling downhill at constant speed
//              (the simple tan(angle) "gravity on a slope" approximation).
//  - Falling:  in the air between girders, pulled down by gravity (vy += g*dt),
//              until it crosses the surface of the girder below.
class Barrel {
public:
    enum class State { OnGirder, Falling };

    Barrel(sf::Vector2f position);

    // place the barrel on `girder`, rolling toward its lower end
    void set_on_girder(const Girder& girder);

    // advance the physics by `dt` seconds, given the stage's girders
    void update(float dt, const std::vector<Girder>& girders);

    // Falling iff we are not currently resting on a girder
    State get_state() const { return current_girder ? State::OnGirder : State::Falling; }
    sf::Vector2f get_position() const { return position; }
    float get_vx() const { return vx; }
    float get_vy() const { return vy; }
    const sf::CircleShape& get_shape() const { return shape; }

private:
    // if a girder surface lies within the barrel's lower half, snap onto it
    void check_girder_intersection(const std::vector<Girder>& girders);

    sf::Vector2f position;
    float vx = 0.f;
    float vy = 0.f;

    // the girder we are rolling on, or nullptr while falling.
    const Girder* current_girder = nullptr;

    sf::CircleShape shape;
};

#endif
