#include "MovingEnemy.hpp"

MovingEnemy::MovingEnemy(sf::Vector2f position) :
    Enemy(position),
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
    
        set_velocity({140.0f, 0.0f});
    }
   
MovingEnemy::~MovingEnemy() {
}

void MovingEnemy::update(float dt, std::vector<Girder>& girders) {

    if (get_current_girder() != nullptr) {
        if (get_postion().x >= right_boundary) {
            set_velocity({-140.0f, 0.0f});
        } else if (get_postion().x <= left_boundary) {
            set_velocity({140.0f, 0.0f});
        }
    
        set_postion({get_postion().x + get_velocity().x * dt,
            get_current_girder()->surface_y_at(get_postion().x) - 15});
    }

    check_girder_intersection(girders);
   
}

