#include "LadderControl.hpp"

#include <algorithm>
#include <cmath>

LadderControl::LadderControl() :
    generator(std::random_device{}()) {
}

float LadderControl::random_x(
    const Girder& upper,
    const Girder& lower
) 
{
    constexpr float ladderWidth = 40.f;

    float minX = std::max(
        upper.min_x(),
        lower.min_x()
    );

    float maxX = std::min(
        upper.max_x(),
        lower.max_x()
    );

    // Die gesamte Leiter muss innerhalb des gemeinsamen Bereichs liegen.
    maxX -= ladderWidth;

    std::uniform_real_distribution<float> distribution(minX, maxX);

    return distribution(generator);
}

std::vector<Ladder> LadderControl::generate_ladders(
    const std::vector<Girder>& girders
) {
    std::vector<Ladder> ladders;

    // Girder 0 -> Girder 1
    add_ladder(ladders, girders[0], girders[1]);

    // Girder 1 -> Girder 2
    add_ladder(ladders, girders[1], girders[2]);
    add_ladder(ladders, girders[1], girders[2]);

    // Girder 2 -> Girder 3
    add_ladder(ladders, girders[2], girders[3]);

    return ladders;
}

void LadderControl::add_ladder(
    std::vector<Ladder>& ladders,
    const Girder& upper,
    const Girder& lower
) {
    constexpr float ladderWidth = 40.f;
    constexpr int numRungs = 5;

    float x = random_x(upper, lower);

    float yTop = upper.surface_y_at(x);
    float yBottom = lower.surface_y_at(x);

    float ladderHeight = std::abs(yBottom - yTop);

    ladders.emplace_back(
        sf::Vector2f{x, yTop},
        ladderWidth,
        ladderHeight,
        numRungs,
        lower
    );
}