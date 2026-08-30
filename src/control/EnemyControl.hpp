#include "../view/Layer.hpp"
#include "../model/Enemy.hpp"
#include "../model/Player.hpp"

#include <random>

class EnemyControl {
private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::Texture enemyTexture;
    Layer& layer;

    std::random_device rd;
    std::mt19937 generator;

    // Überprüft ob sich die Spielfigur und ein Gegner überschneiden
    bool check_enemy_collision(const sf::Sprite& playerSprite, const sf::Sprite& enemyShape);

    // Generiert einen zufälligen float zwischen minValue und maxValue
    float get_random_position(float minValue, float maxValue);

    sf::Texture getTexture();

public:
    EnemyControl(Layer& layer);
    ~EnemyControl();

    // Erzeugt Gegner auf den Plattformen. Die Anzahl der Gegner darf maxEnemies nicht überschreiten
    void spawn(const std::vector<Girder>& girders, const Girder* girder_to_win);

    // Aktualisiert die Positionen aller Enemies
    void update(float dt, const std::vector<Girder>& girders);

    // Zeichnet die Gegner auf das Fenster
    void draw();

    //Überprüft ob der Spieler von einem Enemy getroffen wurde
    bool check_intersection(Player& player);
};

