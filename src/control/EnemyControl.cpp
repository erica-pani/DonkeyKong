#include "EnemyControl.hpp"
#include "../model/Ghost.hpp"

#include <random>
#include <algorithm>
#include <thread>

EnemyControl::EnemyControl(Layer& layer) :
    enemies(),
    layer(layer) {
        if (!enemyTexture.loadFromFile("assets/img/enemy_pngs/ghost_texture.png")) {
        throw std::runtime_error("Fehler beim Laden der Gegnersprite-Textur!");
        }
    }

EnemyControl::~EnemyControl() {
}

void EnemyControl::spawn(const std::vector<Girder>& girders) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution coin_flip(0.5);

    for (const auto& girder : girders) {

        if (coin_flip(gen)) {
            
            float positionX = get_random_position(200.0f, 400.0f);

            enemies.emplace_back(std::make_unique<Ghost>(sf::Vector2f(positionX,
                girder.surface_y_at(positionX)), enemyTexture));
        }
    }
    
}

void EnemyControl::update(float dt, const std::vector<Girder>& girders) {
    for (auto& enemy : enemies) {
        enemy->update(dt, girders);
    }
}

void EnemyControl::draw() {
    for (const auto& enemy : enemies) {
        layer.add_to_layer(enemy->get_shape());
    }
}

bool EnemyControl::check_intersection(Player& player) {
    sf::RectangleShape player_shape = player.getShape();
    for (auto& enemy : enemies) {
        if (check_enemy_collision(player_shape, enemy->get_shape())) {
            return true;
        }
    }
    return false;
}

bool EnemyControl::check_enemy_collision(const sf::RectangleShape& playerShape, const sf::Sprite& enemyShape) {
    sf::FloatRect playerBounds = playerShape.getGlobalBounds();
    sf::FloatRect enemyBounds = enemyShape.getGlobalBounds(); 

    return playerBounds.findIntersection(enemyBounds).has_value();
}

float EnemyControl::get_random_position(float miin, float maax) {
    std::random_device rd;
    std::mt19937 gen(rd());

    float min = miin;
    float max = maax;

    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);
}

sf::Texture EnemyControl::getTexture() {
    sf::Texture tex;
    if (!tex.loadFromFile("assets/img/enemy_pngs/ghost_texture.png")) {
        throw std::runtime_error("Fehler beim Laden von: ");
    }

    return tex;
}