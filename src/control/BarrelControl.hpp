#ifndef BARRELCONTROL_H
#define BARRELCONTROL_H

#include <memory>
#include <vector>

#include "../model/Barrel.hpp"
#include "../model/Girder.hpp"
#include "../model/Player.hpp"
#include "../view/Layer.hpp"

// Owns the barrel and advances/draws it. When the barrel rolls off the stage,
// the control deletes it and creates a fresh one at the top.
class BarrelControl {
public:
    BarrelControl(Layer& layer);

    void spawn(const std::vector<Girder>& girders);
    void update(float dt, const std::vector<Girder>& girders);
    void draw();
    void set_spawn_interval(float interval);
    bool check_barrel_intersection(Player& player);

private:
    Layer& layer;
    std::vector<std::unique_ptr<Barrel>> barrels;

    float spawn_timer;
    float spawn_interval;

    bool check_circle_collision(const sf::RectangleShape& playerShape, sf::Vector2f barrel_position);
};

#endif
