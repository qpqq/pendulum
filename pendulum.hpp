#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

class Pendulum : public sf::Drawable, public sf::Transformable {
private:

    const float gravity = 9.8;
    const sf::Vector2f pivotOrigin = {400.f, 100.f};
    const sf::Color white = sf::Color(255, 255, 255);
    const sf::Color cyan = sf::Color(51, 204, 204);
    const float circleRadius = 10.f;
    const int circleSides = 500;
    const float rate = 100;
    const int trailSize = 50;

    float angle;
    float angleV;
    float angleA;
    float length;
    float mass;

    sf::Vector2f pivot;
    sf::Vector2f point;
    sf::Vertex line[2];
    sf::CircleShape circle;
    std::vector<sf::Vertex> trail;

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
