#include "EnemyControl.hpp"
#include "../model/MovingEnemy.hpp"

#include <random>

EnemyControl::EnemyControl(Layer& layer) :
    enemies(),
    layer(layer) {}

EnemyControl::~EnemyControl() {}

void EnemyControl::spawn(const std::vector<Girder>& girders) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution coin_flip(0.5);

    for (const auto& girder : girders) {

        if (coin_flip(gen)) {
            
            float positionX = get_random_position(200.0f, 400.0f);

            enemies.emplace_back(std::make_unique<MovingEnemy>(sf::Vector2f(positionX,
                girder.surface_y_at(positionX))));
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

bool EnemyControl::check_intersection() {
    return true;
}

float EnemyControl::get_random_position(float miin, float maax) {
    std::random_device rd;
    std::mt19937 gen(rd());

    float min = miin;
    float max = maax;

    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);
}