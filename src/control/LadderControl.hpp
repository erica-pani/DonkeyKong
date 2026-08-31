#ifndef LADDERCONTROL_HPP
#define LADDERCONTROL_HPP

#include <random>
#include <vector>

#include "../model/Girder.hpp"
#include "../model/Ladder.hpp"
#include "../view/Layer.hpp"

// Verwaltet die Leitern
// Erstellt Leitern zufällig zwischen benachbarten Girders und zeichnet sie
class LadderControl {
public:
    LadderControl(Layer& layer);

    // Erstellt eine neue Menge an Leitern anhand der gegebenen Girders
    // Die Positionen der Leitern werden dabei zufällig bestimmt
    void generate_ladders(
        const std::vector<Girder>& girders
    );

    // Erstellt eine einzelne Leiter zwischen einem oberen und einem
    // unteren Girder und fügt sie zu den vorhandenen Leitern hinzu
    void add_ladder(const Girder &upper, const Girder &lower);

    // zeichnet die Leitern
    void draw();

    // gibt eine konstnate Referenz auf alle aktuell vorhandenen Leitern zurück
    const std::vector<Ladder>& get_ladders() const;

private:
    // Referenz auf Layer, auf dem die Leitern gezeichnet werden sollen
    Layer& layer;

    //alle Leitern des aktuellen Levels
    std::vector<Ladder> ladders;

    // zufällige x-Position innerhalb des Bereichs,in dem sich der obere und der untere Girder überschneiden
    float random_x(const Girder& upper, const Girder& lower);

    // Zufallszahlengenerator zur Bestimmung der Leiterpositionen
    std::mt19937 generator;

    // Überprüft, ob eine neue Leiter an der angegebenen x-Position
    // mit einer bereits vorhandenen Leiter auf demselben unteren
    // Girder überlappen würde
     bool overlaps_existing_ladder(
        float x,
        float width,
        const Girder& lower
    ) const;
};

#endif