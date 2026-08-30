#include "EnemyControl.hpp"
#include "../model/Ghost.hpp"
#include <algorithm>
#include <thread>

EnemyControl::EnemyControl(Layer& layer) :
    enemies(),
    layer(layer),
    rd(),
    generator(rd()) {
        if (!enemyTexture.loadFromFile("assets/img/enemy_pngs/ghost_texture.png")) {
        throw std::runtime_error("Fehler beim Laden der Gegnersprite-Textur!");
        }
    }

EnemyControl::~EnemyControl() {
}

void EnemyControl::spawn(const std::vector<Girder>& girders, const Girder* girder_to_win) {
    std::bernoulli_distribution coin_flip(0.5);

    enemies.clear();
    int maxEns = 2;
    for (const auto& girder : girders) {

        if (coin_flip(generator) && girder_to_win != &girder && maxEns > 0) {
            
            float positionX = get_random_position(200.0f, 400.0f);

            enemies.emplace_back(std::make_unique<Ghost>(sf::Vector2f(positionX,
                girder.surface_y_at(positionX)), enemyTexture));
            maxEns -= 1;
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
    sf::Sprite player_sprite = player.getSprite();
    for (auto& enemy : enemies) {
        if (check_enemy_collision(player_sprite, enemy->get_shape())) {
            return true;
        }
    }
    return false;
}

bool EnemyControl::check_enemy_collision(const sf::Sprite& playerSprite, const sf::Sprite& enemyShape) {
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    sf::FloatRect enemyBounds = enemyShape.getGlobalBounds(); 

    sf::Vector2f margin{9.0f, 9.0f};

    sf::FloatRect shrinkedEnemyBounds(
            enemyBounds.position + margin,           
            enemyBounds.size - (margin * 2.0f)
        );

    return playerBounds.findIntersection(shrinkedEnemyBounds).has_value();
}

float EnemyControl::get_random_position(float minValue, float maxValue) {

    float min = minValue;
    float max = maxValue;

    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(generator);
}

sf::Texture EnemyControl::getTexture() {
    sf::Texture tex;
    if (!tex.loadFromFile("assets/img/enemy_pngs/ghost_texture.png")) {
        throw std::runtime_error("Fehler beim Laden von: ");
    }

    return tex;
}