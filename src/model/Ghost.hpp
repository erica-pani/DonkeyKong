#include "Enemy.hpp"

class Ghost : public Enemy {
private:
    float movement_range = 50;
    float left_boundary;
    float right_boundary;
public:
    Ghost(sf::Vector2f position, const sf::Texture& tex);
    ~Ghost() override;

    void update(float dt, const std::vector<Girder>& girders) override;
};

