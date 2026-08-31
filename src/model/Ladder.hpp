#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Girder.hpp"

// Ladder ist ein Hilfsmittel für den Spieler um sich zwischen zwei Plattformen hin und her zu bewegen 
// Sieh steht immer genau zwichen zwei aneinander liegenden Plattformen
class Ladder : public sf::Transformable, public sf::Drawable{
private:
    sf::RectangleShape leftRail;
    sf::RectangleShape rightRail;
    std::vector<sf::RectangleShape> rungs;
    sf::Vector2f position;

    const Girder* origin_girder;

    // überschreibt die draw Methode von sf::Drawable um alle Shapes aus der Klasse zusammen zeichnen zu lassen
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float get_ladder_width() const;
public:
    Ladder(sf::Vector2f position, float width, float height, int numRungs, const Girder& girder);
    ~Ladder();

    // Überprüft ob die angegebene Position im Bereich der Ladder ist
    bool covers_x(float xPosition) const;
    
    float get_center() const;
    void setGirder(Girder& girder);
    const Girder* get_girder_pointer() const;
};

