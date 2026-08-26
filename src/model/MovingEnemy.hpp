#include "Enemy.hpp"

class MovingEnemy : public Enemy {
private:
    float movement_range = 50;
    float left_boundary;
    float right_boundary;
public:
    MovingEnemy(sf::Vector2f position);
    ~MovingEnemy() override;

    void update(float dt, std::vector<Girder>& girders) override;
};

