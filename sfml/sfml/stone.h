#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape {
private:
    int m_punktyZycia;
    bool m_jestZniszczony;
    static const std::array<sf::Color, 4> m_colorLUT;

    void aktualizujKolor() {
        int idx = m_punktyZycia;
        if (idx < 0) idx = 0;
        if (idx > static_cast<int>(m_colorLUT.size()) - 1) idx = static_cast<int>(m_colorLUT.size()) - 1;
        this->setFillColor(m_colorLUT[idx]);
    }

public:
    // Konstruktor: startPos = środek prostokąta (origin ustawione na środek)
    Stone(const sf::Vector2f& startPos, const sf::Vector2f& rozmiar, int L)
        : m_punktyZycia(L)
        , m_jestZniszczony(false)
    {
        this->setSize(rozmiar);
        this->setOrigin({rozmiar.x / 2.f, rozmiar.y / 2.f});
        this->setPosition(startPos);
        this->setOutlineThickness(2.f);
        this->setOutlineColor(sf::Color(40, 40, 40));
        aktualizujKolor();
    }

    void trafienie() {
        if (m_jestZniszczony) return;
        --m_punktyZycia;
        aktualizujKolor();
        if (m_punktyZycia <= 0) {
            m_jestZniszczony = true;
        }
    }

    bool isDestroyed() const { return m_jestZniszczony; }

    int getHP() const { return m_punktyZycia; }

    // Rysowanie tylko gdy blok nie jest zniszczony
    void draw(sf::RenderTarget& target) const {
        if (!m_jestZniszczony) {
            target.draw(static_cast<const sf::RectangleShape&>(*this));
        }
    }



};
