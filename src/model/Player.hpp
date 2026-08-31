#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include "Ladder.hpp"
#include "Girder.hpp"
#include "Direction.hpp"

// Player ist die steuerbare Spielfigur mit den States:
// - Right, Left und Stay
// Kann außerdem springen um Hindernisse zu überwinden sowie 
// klettern um sich von einer Plattform zur nächsten zu bewegen
class Player
{
    sf::Texture runningTexture;
    sf::Sprite playerSprite;
    sf::RectangleShape playerShape;
    std::vector<sf::IntRect> running_frames;
    std::vector<sf::IntRect> jumping_frames;
    std::vector<sf::IntRect> climbing_frames;


    sf::Vector2f position;
    sf::Vector2f velocity;

    const Girder* current_girder;
    //Sprite Size
    static constexpr int FRAME_WIDTH = 16;
    static constexpr int FRAME_HEIGHT = 27;

    float playerHeight = 40.f;
    float playerWidth = 30.f;

    float animationTimer;
    int currentFrame;

    bool isJumping;
    bool isClimbing;
    bool isLanding;
    float landingTimer;

public:
    explicit Player(sf::Vector2f position);
    ~Player();

    void setPosition(sf::Vector2f newPosition);
    sf::RectangleShape& getShape();
    sf::Sprite getSprite();
    
    // Bestimmt in welche Richtung sich die Spielfigur bewegen soll und setzt velocity entsprechend
    void move(Direction direction);

    // Ist die Spielfigur nicht schon am springen, leitet die Methode den Sprung nach oben ein
    void jump();

    // Prüft ob eine Leiter in der nähe ist und zentriert die Speilfigur au der Leiter.
    // Leitet danach die Bewegung nach oben ein
    void climbLadder(const Ladder& ladder);

    // Bestimmt welche Bewegung die Figur gerade ausführt und bestimmt die neue Position entsprechend
    void update(float dt, const std::vector<Girder>& girders);

    // Prüft ob die Figur mit der unteren Hälfte au einem Girder steht und setzt current_girder.
    // Ist kein Girder in der Nähe zu finden wird current_girder = nullptr gesetzt
    void check_girder_intersection(const std::vector<Girder>& girders);

    // Stellt den ursprünglichen Zustand des Players wieder her
    void reset(sf::Vector2f position);

    void setGirder(const Girder& girder);
    const Girder* getGirder() const;
    sf::Vector2f getVelocity() const;
};