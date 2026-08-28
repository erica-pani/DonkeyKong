#include "Enemy.hpp"

class Ghost : public Enemy {
private:
    float movement_range = 50.0f;
    float left_boundary;
    float right_boundary;
    float movement_speed = 80.0f;
public:
    Ghost(sf::Vector2f position, const sf::Texture& tex);
    ~Ghost() override;

    void update(float dt, const std::vector<Girder>& girders) override;
};

