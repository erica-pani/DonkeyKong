#include "LadderControl.hpp"

#include <algorithm>
#include <cmath>

LadderControl::LadderControl(Layer& layer) :
    layer(layer),
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

void LadderControl::generate_ladders(
    const std::vector<Girder>& girders
) {

    ladders.clear();

    // Girder 0 -> Girder 1
    add_ladder(girders[0], girders[1]);

    // Girder 1 -> Girder 2
    add_ladder(girders[1], girders[2]);
    add_ladder(girders[1], girders[2]);

    // Girder 2 -> Girder 3
    add_ladder(girders[2], girders[3]);
    add_ladder(girders[2], girders[3]);

}

const std::vector<Ladder>& LadderControl::get_ladders() const {
    return ladders;
}

bool LadderControl::overlaps_existing_ladder(
    float x,
    float width,
    const std::vector<Ladder>& ladders,
    const Girder& lower
) const {
    for (const Ladder& ladder : ladders) {

        // Nur Leitern auf derselben Ebene betrachten.
        if (ladder.get_girder_pointer() != &lower) {
            continue;
        }

        float existingX = ladder.getPosition().x;

        bool overlaps =
            x < existingX + width &&
            x + width > existingX;

        if (overlaps) {
            return true;
        }
    }

    return false;
}

void LadderControl::add_ladder(
    const Girder& upper,
    const Girder& lower
) {
    constexpr float ladderWidth = 40.f;
    constexpr int numRungs = 5;
    constexpr int maxAttempts = 100;

    for (int attempt = 0; attempt < maxAttempts; ++attempt) {

        float x = random_x(upper, lower);

        if (overlaps_existing_ladder(
                x,
                ladderWidth,
                ladders,
                lower)) {
            continue;
        }

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

        return;

    }
}

void LadderControl::draw() {
    for (const auto& ladder : ladders) {
        layer.add_to_layer(ladder);
    }
}