#pragma once

#include <cmath>
#include <iostream>
#include <queue>

#include <SFML/Graphics.hpp>

class Pendulum : public sf::Drawable, public sf::Transformable {
private:

    const float gravity = 9.8;
    const sf::Vector2f origin = {250.f, 100.f};
    const float circleRadius = 10.f;
    const int circleSides = 500;
    const float rate = 100;
    static const int trailSize = 100;

    float angle;
    float angleV;
    float angleA;
    float length;
    float mass;

    sf::Vector2f pivot;
    sf::Vector2f point;
    sf::Vertex line[2];
    sf::CircleShape circle;
    sf::Vertex trail[trailSize];

    bool isHold;
    bool isClicked;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:

    void updateFigures();

    Pendulum(float mass, float length);

    void update(sf::Time elapsed);

    void hold();

    void press(sf::Vector2i mousePos);

    void move(sf::Vector2i mousePos);

    void release(sf::Vector2i mousePos);
};
