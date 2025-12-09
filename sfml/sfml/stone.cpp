#include "Stone.h"

// inicjalizacja statycznej tablicy kolorów (LUT)
const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
};
