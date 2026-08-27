#include "../view/Layer.hpp"
#include "../model/Enemy.hpp"
#include "../model/Player.hpp"

class EnemyControl {
private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::Texture enemyTexture;
    Layer& layer;

    bool check_enemy_collision(const sf::RectangleShape& playerShape, const sf::Sprite& enemyShape);
    float get_random_position(float min, float max);
    sf::Texture getTexture();

public:
    EnemyControl(Layer& layer);
    ~EnemyControl();

    void spawn(const std::vector<Girder>& girders);
    void update(float dt, const std::vector<Girder>& girders);
    void draw();
    bool check_intersection(Player& player);
};

