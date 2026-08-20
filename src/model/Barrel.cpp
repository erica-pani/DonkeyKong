#include "Barrel.hpp"

#include <SFML/Graphics/Color.hpp>

#include "Constants.hpp"

Barrel::Barrel(sf::Vector2f position) :
    position(position),
    shape(constants::BARREL_RADIUS) {
        // origin at the circle's centre so `position` is the barrel's centre
        shape.setOrigin({constants::BARREL_RADIUS, constants::BARREL_RADIUS});
        shape.setFillColor(sf::Color(120, 200, 230)); // light blue, stands out on the red girders
        shape.setPosition(position);
}

void Barrel::set_on_girder(const Girder& girder) {
    current_girder = &girder;
    vx = constants::ROLL_SPEED * static_cast<float>(current_girder->downhill_sign());
    vy = 0.f;
}

void Barrel::update(float dt, const std::vector<Girder>& girders) {
    if (get_state() == State::OnGirder) {
        position.x += vx * dt;
        if (current_girder->covers_x(position.x)) {
            // stay glued to the surface: height follows the slope (tan angle)
            position.y = current_girder->surface_y_at(position.x) - constants::BARREL_RADIUS;
        } else {
            // rolled off the lower end -> drop straight down off the ledge.
            current_girder = nullptr;
            vx = 0.f;
            vy = 0.f;
        }
    } else { // Falling
        vy += constants::GRAVITY * dt;
        position.x += vx * dt;
        position.y += vy * dt;
        check_girder_intersection(girders);
    }

    // No respawn here: once the barrel rolls off the last girder it just keeps
    // falling. BarrelControl notices it has left the stage and replaces it.
    shape.setPosition(position);
}

void Barrel::check_girder_intersection(const std::vector<Girder>& girders) {
    for (const Girder& girder : girders) {
        if (!girder.covers_x(position.x)) {
            continue;
        }
        float surface = girder.surface_y_at(position.x);
        if (position.y <= surface && surface <= position.y + constants::BARREL_RADIUS) {
            position.y = surface - constants::BARREL_RADIUS;
            set_on_girder(girder);
            return;
        }
    }
}
