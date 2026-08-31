#ifndef LADDERCONTROL_HPP
#define LADDERCONTROL_HPP

#include <random>
#include <vector>

#include "../model/Girder.hpp"
#include "../model/Ladder.hpp"

// Generiert Leitern an zufälligen Stellen um sie an Game zu übergeben
class LadderControl {
public:
    LadderControl();

    // Generiert die Leitern zwichen den Girdern und gibt einen Vektor mit diesen zurück
    std::vector<Ladder> generate_ladders(
        const std::vector<Girder>& girders
    );

    // Erstellt eine Leiter und fügt die dem mitgegebenem Vektor hinzu
    void add_ladder(std::vector<Ladder> &ladders, const Girder &upper, const Girder &lower);

private:
    // Generiert einen zufälligen float auf der X Achse der auf biden Plattformen liegt
    float random_x(const Girder& upper, const Girder& lower);

    std::mt19937 generator;
};

#endif