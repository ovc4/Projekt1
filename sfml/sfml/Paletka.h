#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;     // pikseli na klatkę
    sf::RectangleShape shape;

    void updateShape() {
        shape.setPosition({x, y});
    }

    // w Paletka.h
    void setPosition(float nx, float ny) {
        x = nx; y = ny;
        updateShape();
    }


public:
    Paletka(float x_in, float y_in, float szer_in, float wys_in, float predkosc_in)
        : x(x_in), y(y_in), szerokosc(szer_in), wysokosc(wys_in), predkosc(predkosc_in)
    {
        shape.setSize({szerokosc, wysokosc});
        shape.setOrigin({szerokosc/2.f, wysokosc/2.f});
        shape.setPosition({x, y});
        shape.setFillColor(sf::Color::White);
    }

    void moveLeft() {
        x -= predkosc;
        updateShape();
    }

    void moveRight() {
        x += predkosc;
        updateShape();
    }

    void clampToBounds(float width) {
        float half = szerokosc / 2.f;
        if (x - half < 0.f) x = half;
        if (x + half > width) x = width - half;
        updateShape();
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(shape);
    }


    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};
