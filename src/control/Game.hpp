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

    bool isAlive();

    bool goal_reached();

    void restart_and_randomize();

    // build the zig-zag of alternating sloped girders that make up the stage
    static std::vector<Girder> build_girders();

    static std::vector<Ladder> build_ladders(const std::vector<Girder>& girders);

    sf::RenderWindow window;

    // view area and layers
    sf::View view;
    Layer game_layer;

    std::vector<Girder> girders;
    std::vector<Ladder> ladders;
    BarrelControl barrel_control;
    EnemyControl enemy_control;
    const Girder* girder_to_win;
    LadderControl ladder_control;

    Player player;
};

#endif