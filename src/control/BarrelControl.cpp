#include "BarrelControl.hpp"
#include "../model/Constants.hpp"
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

BarrelControl::BarrelControl(Layer& layer) :
    layer(layer),
    barrels(),
    spawn_timer(0.0f),
    spawn_interval(4.0f){
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
    sf::Sprite player_sprite = player.getSprite();
    for (auto& barrel : barrels) {
        if (check_circle_collision(player_sprite, barrel->get_position())) {
            return true;
        }
    }
    return false;
}

bool BarrelControl::check_circle_collision(const sf::Sprite& playerSprite, sf::Vector2f barrel_position) {
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    float playerLeft = playerSprite.getPosition().x - playerBounds.size.x / 2;
    float playerTop = playerSprite.getPosition().y;
    float playerHeight = playerBounds.size.y; 

    float nearestX = std::max(playerLeft,
        std::min(barrel_position.x, playerLeft + playerBounds.size.x));
    float nearestY = std::max(playerTop,
        std::min(barrel_position.y, playerTop + playerHeight));

    float deltaX = barrel_position.x - nearestX;
    float deltaY = barrel_position.y - nearestY;

    return (deltaX * deltaX + deltaY * deltaY) <= 
        (constants::BARREL_RADIUS * constants::BARREL_RADIUS);
}

void BarrelControl::draw() {
    for (const auto& barrel : barrels) {
        layer.add_to_layer(barrel->get_shape());
    }
}

void BarrelControl::clear_barrels() {
    barrels.clear();
}

void BarrelControl::set_spawn_interval(float interval) {
    spawn_interval = interval;
}

float BarrelControl::get_spawn_interval() {
    return spawn_interval;
}
