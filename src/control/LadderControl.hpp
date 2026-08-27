#ifndef LADDERCONTROL_HPP
#define LADDERCONTROL_HPP

#include <random>
#include <vector>

#include "../model/Girder.hpp"
#include "../model/Ladder.hpp"

class LadderControl {
public:
    LadderControl();

    std::vector<Ladder> generate_ladders(
        const std::vector<Girder>& girders
    );

    void add_ladder(std::vector<Ladder> &ladders, const Girder &upper, const Girder &lower);

private:
    float random_x(const Girder& upper, const Girder& lower);

    std::mt19937 generator;
};

#endif