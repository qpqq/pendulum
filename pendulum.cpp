#include "pendulum.hpp"

void Pendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // draw
    target.draw(line, 2, sf::Lines, states);
    target.draw(circle, states);
}

void Pendulum::updateFigures() {
    line[0] = sf::Vertex(pivot);
    line[1] = sf::Vertex(point);

    circle.setPosition(point.x - circleRadius,
                       point.y - circleRadius);
}

Pendulum::Pendulum(float mass, float length) {
    this->length = length;
    this->mass = mass;

    pivot = origin;
    point.x = pivot.x + length;
    point.y = pivot.y;

    angle = M_PI / 2;
    angleV = 0;
    angleA = 0;

    circle.setRadius(circleRadius);
    circle.setPointCount(circleSides);

    isHold = false;
    isClicked = false;

    updateFigures();
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

    isHold = false;
    isClicked = false;
}