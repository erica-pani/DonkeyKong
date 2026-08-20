#include "BarrelControl.hpp"
#include "../model/Constants.hpp"
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

BarrelControl::BarrelControl(Layer& layer) :
    layer(layer),
    barrels(),
    spawn_timer(0.f),
    spawn_interval(4.f){
}

void BarrelControl::spawn(const std::vector<Girder>& girders) {
    // Reassigning the unique_ptr destroys the previous barrel (if any).
    sf::Vector2f top = sf::Vector2f(girders[0].high_end().x, - constants::VIEW_HEIGHT);
    barrels.push_back(std::make_unique<Barrel>(
        sf::Vector2f{top.x, top.y - constants::BARREL_RADIUS}));
}

void BarrelControl::update(float dt, const std::vector<Girder>& girders) {
    for (auto& barrel : barrels) {
        barrel->update(dt, girders);
    }

    spawn_timer += dt;
    if (spawn_timer >= spawn_interval) {
        spawn(girders);
        spawn_timer -= spawn_interval;
    }
    
    barrels.erase(
        std::remove_if(barrels.begin(), barrels.end(),
            [](const std::unique_ptr<Barrel>& barrel) {
                return barrel->get_position().y - constants::BARREL_RADIUS > 0.f;
            }
        ),
        barrels.end()
    );
}

bool BarrelControl::check_barrel_intersection(Player& player) {
    sf::Vector2f player_position = player.getShape().getPosition();
    for (auto& barrel : barrels) {
        sf::Vector2f barrel_center = barrel->get_position();

        if (barrel_center.x + constants::BARREL_RADIUS >= player_position.x ||
            barrel_center.x - constants::BARREL_RADIUS <= player_position.x + 20.f){
        }

        if (!(barrel_center.y + constants::BARREL_RADIUS >= player_position.y ||
            barrel_center.y - constants::BARREL_RADIUS <= player_position.y + 30.f)){
            return true;
        }
    }
    return false;
}

void BarrelControl::draw() {
    for (const auto& barrel : barrels) {
        layer.add_to_layer(barrel->get_shape());
    }
}
