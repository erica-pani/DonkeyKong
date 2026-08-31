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

    // Fügt barrels ein neus barrel hinzu
    void spawn(const std::vector<Girder>& girders);

    // Die Methode hat drei Funktionen:
    // - aktualisiert die Position der barrels
    // - spawnt ein neues barrel auf den Timer
    // - löscht die barrels die aus dem Bild gefallen sind
    void update(float dt, const std::vector<Girder>& girders);

    // Zeichnet barrels auf das Fenster
    void draw();

    // Überprüft ob der Spieler von einem barrel getroffen wurde
    bool check_barrel_intersection(Player& player);

    void set_spawn_interval(float interval);
    float get_spawn_interval();

    // leert den Vektor barrels
    void clear_barrels();

private:
    Layer& layer;
    std::vector<std::unique_ptr<Barrel>> barrels;

    float spawn_timer;
    float spawn_interval;

    // Überprüft ob sich die Spielfigur und ein barrel schneiden
    bool check_circle_collision(const sf::Sprite& playerSprite, sf::Vector2f barrel_position);
};

#endif
