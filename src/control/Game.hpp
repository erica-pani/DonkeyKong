#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "../model/Girder.hpp"
#include "../model/Ladder.hpp"
#include "../view/Layer.hpp"
#include "LadderControl.hpp"
#include "BarrelControl.hpp"
#include "EnemyControl.hpp"
#include "../model/Player.hpp"
// Game class
class Game {

public:
    //initialize the game (window and controls)
    Game();

    void start();

private:
    // processes user input, returns true if window has been closed
    bool input();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    // Überprüft ob der Spieler noch am Leben ist
    bool isAlive();

    // Überprüft ob der Spieler das Ziel erreicht hat
    bool goal_reached();

    // Befördert die Spielfigur zurück an den Startpunkt und spawnt Hindernisse, Gegner und Leitern neu
    void restart_and_randomize(bool won);

    // build the zig-zag of alternating sloped girders that make up the stage
    static std::vector<Girder> build_girders();

    sf::RenderWindow window;

    // view area and layers
    sf::View view;
    Layer game_layer;

    sf::Font font;
    sf::Text text;

    std::vector<Girder> girders;
    std::vector<Ladder> ladders;
    const Girder* girder_to_win;

    BarrelControl barrel_control;
    EnemyControl enemy_control;
    LadderControl ladder_control;

    Player player;

    sf::Texture flagTexture;
    sf::Sprite flagSprite;
};

#endif