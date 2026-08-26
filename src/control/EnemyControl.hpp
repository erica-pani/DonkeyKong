#include "../view/Layer.hpp"
#include "../model/Enemy.hpp"

class EnemyControl {
private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    Layer& layer;

    bool check_intersection();
    float get_random_position(float min, float max);

public:
    EnemyControl(Layer& layer);
    ~EnemyControl();

    void spawn(const std::vector<Girder>& girders);
    void update(float dt, const std::vector<Girder>& girders);
    void draw();
};

