#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include <iostream>

Game::Game() :
    window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Donkey Kong"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window),
    girders(),
    ladders(),
    ladder_control(),
    player({100, -190}),
    barrel_control(game_layer),
    enemy_control(game_layer) {

        girders = build_girders();
        ladders = ladder_control.generate_ladders(girders);
        barrel_control.spawn(girders);
        girder_to_win = &girders.back();
        enemy_control.spawn(girders, girder_to_win);
    
        // limit frame rate
        window.setFramerateLimit(constants::FRAME_RATE);

        // set the view (visible area) for our game
        game_layer.set_view(view);
}

std::vector<Girder> Game::build_girders() {
    // four girders alternating downhill direction so the barrel zig-zags down.
    // Remember: the view is y-inverted (+y = downward), so a larger y means lower on screen.
    std::vector<Girder> girders;
    girders.emplace_back(sf::Vector2f{120, -500}, sf::Vector2f{500, -460});
    girders.emplace_back(sf::Vector2f{80, -360},  sf::Vector2f{540, -400});
    girders.emplace_back(sf::Vector2f{40, -300},  sf::Vector2f{520, -260});
    girders.emplace_back(sf::Vector2f{80, -160},  sf::Vector2f{560, -200});
    girders.emplace_back(sf::Vector2f{20, -500}, sf::Vector2f{80, -500});
    return girders;
}


void Game::start() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsed_time
        sf::Time elapsed_time = clock.restart();
 
        // handle input, check if window is still open
        if (!input()) {
            //player.move(Direction::RIGHT);
            // update the scene according to the passed time
            update(elapsed_time.asSeconds());
            // draw the scene
            draw();
        }
    }
}

// returns true, if the window has been closed
bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }
        // TODO: Process other events
        // examples:
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::D) player.move(Direction::RIGHT);
            if (keyPressed->code == sf::Keyboard::Key::A) player.move(Direction::LEFT);
            if (keyPressed->code == sf::Keyboard::Key::W) player.jump();
            if (keyPressed->code == sf::Keyboard::Key::S) player.duckDown();
            if (keyPressed->code == sf::Keyboard::Key::C) {
                for (Ladder& ladder : ladders) {
                    player.climbLadder(ladder);
                }
            }
        }

        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyReleased->code == sf::Keyboard::Key::D) player.move(Direction::STAY);
            if (keyReleased->code == sf::Keyboard::Key::A) player.move(Direction::STAY);
        }   
    }
    return false;
}

bool Game::goal_reached() {
    if (player.getGirder() == girder_to_win) {
        return true;
    }
    return false;
}

bool Game::isAlive() {
    if (barrel_control.check_barrel_intersection(player) ||
            enemy_control.check_intersection(player)) {
        return false;
    }
    return true;
}

void Game::update(float time_passed) {
    if (!isAlive() || goal_reached()) {
        return;
    }
    barrel_control.update(time_passed, girders);
    enemy_control.update(time_passed, girders);
    player.update(time_passed, girders);
}

void Game::draw() {
    window.clear();

    game_layer.clear();

    // the stage is owned by Game, so Game draws it; the barrel goes on top
    for (const Girder& girder : girders) {
        game_layer.add_to_layer(girder.get_shape());
    }

    for (const Ladder& ladder : ladders) {
        game_layer.add_to_layer(ladder);
    }

    game_layer.add_to_layer(player.getSprite());

    barrel_control.draw();
    enemy_control.draw();
    game_layer.draw();

    window.display();
}
