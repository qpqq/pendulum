#include "pendulum.hpp"

void Pendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // draw
    target.draw(&trailWide[0], trailWide.size(), sf::TriangleFan);
    target.draw(&trail[0], trail.size(), sf::LineStrip);
    target.draw(line, 2, sf::Lines, states);
    target.draw(circle, states);
}

void Pendulum::updateFigures() {
    line[0] = sf::Vertex(pivot, white);
    line[1] = sf::Vertex(point, white);

    circle.setPosition(point.x - circleRadius,
                       point.y - circleRadius);
}

Pendulum::Pendulum(float mass, float length) {
    this->length = length;
    this->mass = mass;

    pivot = pivotOrigin;
    point.x = pivot.x + length;
    point.y = pivot.y;

    angle = M_PI / 2;
    angleV = 0;
    angleA = 0;

    circle.setFillColor(white);
    circle.setRadius(circleRadius);
    circle.setPointCount(circleSides);

    isHold = false;
    isClicked = false;

    createTrail();
    updateFigures();
}

void Pendulum::createTrail() {
    sf::Vertex trailPoint;

    trailPoint = {point, cyan};
    trailPoint.color.a = 255;
    trail = std::vector<sf::Vertex>(trailSize, trailPoint);
    trailPoint = {pivot, cyan};
    trailPoint.color.a = 0;
    trailWide = std::vector<sf::Vertex>(trailSize + 1, trailPoint);
}

void Pendulum::updateTrail() {
    float _opacity;
    sf::Vertex trailPoint = {point, cyan};

    _opacity = 255 / (float) (trailSize - 1);
    for (int i = 0; i < trailSize - 1; i++) {
        trail[i] = trail[i + 1];
        trail[i].color.a = (int) (_opacity * (float) i);
    }
    trail[trailSize - 1] = trailPoint;

    _opacity = 255 / (float) trailSize;
    for (int i = 1; i < trailSize; i++) {
        trailWide[i] = trailWide[i + 1];
        trailWide[i].color.a = (int) (_opacity * (float) i);
    }
    trailWide[trailSize] = trailPoint;
}

void Pendulum::update(sf::Time elapsed) {
    if (isHold)
        return;

    angleA = -std::sin(angle) * gravity / length;
    angleA *= rate;
    angleV += angleA * elapsed.asSeconds();
    angle += angleV * elapsed.asSeconds();

    point.x = pivot.x + length * std::sin(angle);
    point.y = pivot.y + length * std::cos(angle);

    updateTrail();
    updateFigures();
}

void Pendulum::hold() {
    isHold = !isHold;
}

void Pendulum::press(sf::Vector2i mousePos) {
    auto x = (float) mousePos.x;
    auto y = (float) mousePos.y;

    if (!circle.getGlobalBounds().contains(x, y))
        return;

    isHold = true;
    isClicked = true;
}

void Pendulum::move(sf::Vector2i mousePos) {
    if (!isClicked)
        return;

    point.x = (float) mousePos.x;
    point.y = (float) mousePos.y;

    length = sqrtf(powf(pivot.x - point.x, 2) + powf(pivot.y - point.y, 2));

    angle = std::atan((pivot.x - point.x) / (pivot.y - point.y));
    if (pivot.y - point.y > 0)
        angle += M_PI;
    angleV = 0;
    angleA = 0;

    updateFigures();
}

void Pendulum::release(sf::Vector2i mousePos) {
    auto x = (float) mousePos.x;
    auto y = (float) mousePos.y;

    if (!circle.getGlobalBounds().contains(x, y))
        return;

    createTrail();

    isHold = false;
    isClicked = false;
}
