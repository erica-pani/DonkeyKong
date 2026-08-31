#include "Ladder.hpp"

Ladder::Ladder(sf::Vector2f position, float width, float height, int numRungs, const Girder& girder) :
    position(position),
    origin_girder(&girder) {

        assert(numRungs > 1);

        setPosition(position);
        
        float railWidth = 6.f;
        sf::Color woodColor(139, 69, 19); 

        leftRail.setSize({railWidth, height});
        leftRail.setFillColor(woodColor);
        leftRail.setPosition({0.f, 0.f});

        rightRail.setSize({railWidth, height});
        rightRail.setFillColor(woodColor);
        rightRail.setPosition({width - railWidth, 0.f});

        float stepSpacing = height / (numRungs + 1);
        for (int i = 1; i <= numRungs; ++i) {
            sf::RectangleShape rung({width - (2 * railWidth), 4.f});
            rung.setFillColor(woodColor);
            rung.setPosition({railWidth, i * stepSpacing});
            rungs.push_back(rung);
        }
}

Ladder::~Ladder() {}

void Ladder::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
        
    target.draw(leftRail, states);
    target.draw(rightRail, states);
    for (const auto& rung : rungs) {
        target.draw(rung, states);
    }
}

float Ladder::get_ladder_width() const {
    return leftRail.getSize().x + rungs[0].getSize().x + rightRail.getSize().x;
}

bool Ladder::covers_x(float xPosition) const{
    return getPosition().x <= xPosition &&
        getPosition().x + get_ladder_width() >= xPosition;
}

float Ladder::get_center() const {
    return getPosition().x + (get_ladder_width() / 2.f);
}

void Ladder::setGirder(Girder& girder) {
    origin_girder = &girder;
}

const Girder* Ladder::get_girder_pointer() const{
    return origin_girder;
}