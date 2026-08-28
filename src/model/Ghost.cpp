#include "Ghost.hpp"

#include <random>

Ghost::Ghost(sf::Vector2f position, const sf::Texture& tex) :
    Enemy(position, tex),
    right_boundary(position.x + movement_range),
    left_boundary(position.x - movement_range) {
        if (get_current_girder() != nullptr) {
            if (get_current_girder()->get_left().x >= left_boundary) {
                left_boundary = get_current_girder()->get_left().x;
            }

            if (get_current_girder()->get_right().x <= right_boundary) {
                right_boundary = get_current_girder()->get_right().x;
            }
        }
    
        std::random_device rd;
        std::mt19937 gen(rd());
        std::bernoulli_distribution coin_flip(0.5);
        
        if (coin_flip(gen)){
            set_velocity({-movement_speed, 0.0f});
        } else {
            set_velocity({movement_speed, 0.0f});
        }
        
    }
   
Ghost::~Ghost() {
}

void Ghost::update(float dt, const std::vector<Girder>& girders) {
    float currentHeight = get_shape().getGlobalBounds().size.y;
    float oldPosition = get_postion().x;

    if (get_current_girder() != nullptr) {

        if (get_postion().x >= right_boundary) {
            set_velocity({-movement_speed, 0.0f});
        } else if (get_postion().x <= left_boundary) {
            set_velocity({movement_speed, 0.0f});
        }

        float newPosition = get_postion().x + get_velocity().x * dt;
        if (!get_current_girder()->covers_x(newPosition)) {
            newPosition = oldPosition;
            set_velocity({-1.0f * get_velocity().x, 0.0f});
        }
        
        set_postion({newPosition,
            get_current_girder()->surface_y_at(get_postion().x) - currentHeight / 2.0f});
    } 
    check_girder_intersection(girders);
}

