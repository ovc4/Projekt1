#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;

public:
    Paddle(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f startVel)
        : m_velocity(startVel)
    {
        m_shape.setPosition(startPos);
        m_shape.setSize(rozmiar);
        m_shape.setFillColor(sf::Color::White);
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(m_shape);
    }

    void update(float deltaTime) {
        m_shape.move(m_velocity * deltaTime);
    }

    sf::RectangleShape& getShape() { return m_shape; }

    void setVelocity(sf::Vector2f velocity)
    { m_velocity = velocity; }
    void setPosition(sf::Vector2f position) {
        m_shape.setPosition(position);
    }

};
