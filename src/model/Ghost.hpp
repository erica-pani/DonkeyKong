#include "Enemy.hpp"

// Ghost ist ein Enemy der sich innnerhalb der Boundarys bewegt um dem Spieler den weg zum Ziel zu versperren
// Kann sich nur seitlich bewegen 
class Ghost : public Enemy {
private:
    float movement_range = 100.0f;
    float left_boundary;
    float right_boundary;
    float movement_speed = 70.0f;
public:
    Ghost(sf::Vector2f position, const sf::Texture& tex);
    ~Ghost() override;

    // Überschreibt die Methode aus Enemy.
    // Bewegt den Geist nach Links und/oder nach rechts bis eine boundary oder das Ende eine Plattform erreicht ist 
    // und kehrt wieder um
    void update(float dt, const std::vector<Girder>& girders) override;

    float get_right_boundary();
    float get_left_boundary();
};

