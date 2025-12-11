#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Paletka.h"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in)
        : x(x_in), y(y_in), vx(vx_in), vy(vy_in), radius(radius_in)
    {
        shape.setRadius(radius);
        shape.setOrigin({radius, radius}); // (x,y) jest środkiem
        shape.setPosition({x, y});
        shape.setFillColor(sf::Color::White);
    }

    void setPosition(float nx, float ny) {
        x = nx; y = ny;
        shape.setPosition({x,y});
    }
    void setVelocity(float nvx, float nvy) {
        vx = nvx; vy = nvy;
    }

  /*
    void setVelocity(float vx_in, float vy_in) {
        vx = vx_in;
        vy = vy_in;
    }
*/
    void stop() {
        vx = 0.f;
        vy = 0.f;
    }

    void move() {
        x += vx;
        y += vy;
        shape.setPosition({x, y});
    }

    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    void collideWalls(float width, float height) {
        if (x - radius <= 0.f) {
            x = radius;
            if (vx < 0.f) bounceX();
            shape.setPosition({x, y});
            std::cout << "odbicie lewa sciana\n";
        }
        if (x + radius >= width) {
            x = width - radius;
            if (vx > 0.f) bounceX();
            shape.setPosition({x, y});
            std::cout << "odbicie prawa sciana\n";
        }
        if (y - radius <= 0.f) {
            y = radius;
            if (vy < 0.f) bounceY();
            shape.setPosition({x, y});
            std::cout << "odbicie sufit\n";
        }
    }

    bool collidePaddle(const Paletka& p) {
        float palX = p.getX();
        float palY = p.getY();
        float palW = p.getSzerokosc();
        float palH = p.getWysokosc();

        float palLeft = palX - palW / 2.f;
        float palRight = palX + palW / 2.f;
        float palTop = palY - palH / 2.f;

        bool horizontallyOverPaddle = (x >= palLeft) && (x <= palRight);
        bool touchesFromAbove = ( (y + radius) >= palTop ) && ( (y - radius) < palTop );

        if (horizontallyOverPaddle && touchesFromAbove && vy > 0.f) {
            vy = -std::abs(vy); // piłka leci w górę
            y = palTop - radius; // tuż nad paletką
            shape.setPosition({x, y});
            return true;
        }
        return false;
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};

