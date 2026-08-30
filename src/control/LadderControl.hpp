#ifndef LADDERCONTROL_HPP
#define LADDERCONTROL_HPP

#include <random>
#include <vector>

#include "../model/Girder.hpp"
#include "../model/Ladder.hpp"
#include "../view/Layer.hpp"

class LadderControl {
public:
    LadderControl(Layer& layer);

    void generate_ladders(
        const std::vector<Girder>& girders
    );

    void add_ladder(const Girder &upper, const Girder &lower);

    void draw();

    const std::vector<Ladder>& get_ladders() const;

private:
    Layer& layer;
    std::vector<Ladder> ladders;
    float random_x(const Girder& upper, const Girder& lower);

    std::mt19937 generator;

     bool overlaps_existing_ladder(
        float x,
        float width,
        const std::vector<Ladder>& ladders,
        const Girder& lower
    ) const;
};

#endif