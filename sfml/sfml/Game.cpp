#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include "GameState.h"

class Game {
public:
    Game()
        : m_window(sf::VideoMode({640u, 480u}), "Pong SFML 3 - wersja 2024"),
          m_paletka(320.f, 440.f, 100.f, 10.f, 8.f),
          m_pilka(320.f, 200.f, 0.f, 0.f, 8.f),
          m_gen(std::random_device{}()),
          m_vxDist(2.0f, 4.0f),
          m_vyDist(3.0f, 5.0f)
    {
        m_window.setFramerateLimit(60);
        generateLevel();
        std::cout << "Naciśnij SPACJĘ, aby wystartować piłkę (losowy kierunek, piłka leci w dół).\n";
    }

    void run() {
        while (m_window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    // ---- konfiguracja planszy ----
    const float WIDTH  = 640.f;
    const float HEIGHT = 480.f;

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float GAP = 2.f;
    const float TOP_OFFSET = 0.f; // bloczki od samej góry

    // ---- obiekty gry ----
    sf::RenderWindow m_window;
    Paletka m_paletka;
    Pilka  m_pilka;
    std::vector<Stone> m_bloki;

    // ---- stan gry i losowanie ----
    bool m_gameStarted = false;
    std::mt19937 m_gen;
    std::uniform_real_distribution<float> m_vxDist;
    std::uniform_real_distribution<float> m_vyDist;

    int m_frameCounter = 0;

private:
    void generateLevel() {
        m_bloki.clear();
        float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * GAP) / static_cast<float>(ILOSC_KOLUMN);

        for (int y = 0; y < ILOSC_WIERSZY; ++y) {
            for (int x = 0; x < ILOSC_KOLUMN; ++x) {
                float posX = x * (ROZMIAR_BLOKU_X + GAP) + (ROZMIAR_BLOKU_X / 2.f);
                float posY = TOP_OFFSET + y * (ROZMIAR_BLOKU_Y + GAP) + (ROZMIAR_BLOKU_Y / 2.f);

                int L;
                if (y < 1) L = 3;
                else if (y < 3) L = 2;
                else L = 1;

                m_bloki.emplace_back(sf::Vector2f(posX, posY),
                                     sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                                     L);
            }
        }
    }

    void handleEvents() {
        while (const auto event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;

                if (key == sf::Keyboard::Key::Space && !m_gameStarted) {
                    startBall();
                }
            }
        }
    }

    void update() {
        // sterowanie paletką (realtime)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            m_paletka.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            m_paletka.moveRight();
        }
        m_paletka.clampToBounds(WIDTH);

        if (m_gameStarted) {
            m_pilka.move();
            m_pilka.collideWalls(WIDTH, HEIGHT);

            // kolizja z paletką
            if (m_pilka.collidePaddle(m_paletka)) {
                std::cout << "HIT PADDLE\n";
            }

            // kolizja z blokami
            for (auto &s : m_bloki) {
                if (s.isDestroyed()) continue;

                if (circleRectCollides(m_pilka.getX(), m_pilka.getY(), m_pilka.getRadius(), s)) {
                    s.trafienie();
                    m_pilka.bounceY();
                }
            }

            // przegrana: piłka poniżej okna -> KONIEC GRY
            if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
                std::cout << "MISS! KONIEC GRY\n";
                m_window.close();
                return;
            }
        }

        if (++m_frameCounter % 60 == 0) {
            std::cout << "x=" << m_pilka.getX()
                      << " y=" << m_pilka.getY()
                      << " vx=" << m_pilka.getVx()
                      << " vy=" << m_pilka.getVy() << std::endl;
        }
    }

    void render() {
        m_window.clear(sf::Color(20, 20, 30));

        // rysuj bloki
        for (const auto &s : m_bloki) s.draw(m_window);

        // paletka i piłka
        m_paletka.draw(m_window);
        m_pilka.draw(m_window);

        m_window.display();
    }

    // pomocnik: kolizja koło-prostokąt (closest point). Zakłada origin prostokąta = środek
    bool circleRectCollides(float cx, float cy, float r, const sf::RectangleShape& rect) const {
        sf::Vector2f rectPos = rect.getPosition();
        sf::Vector2f half = rect.getSize() / 2.f;

        float left   = rectPos.x - half.x;
        float right  = rectPos.x + half.x;
        float top    = rectPos.y - half.y;
        float bottom = rectPos.y + half.y;

        float closestX = std::max(left, std::min(cx, right));
        float closestY = std::max(top, std::min(cy, bottom));

        float dx = cx - closestX;
        float dy = cy - closestY;
        return (dx*dx + dy*dy) <= (r * r);
    }

    void startBall() {
        float vx = m_vxDist(m_gen);
        if (std::uniform_int_distribution<int>(0, 1)(m_gen) == 0) vx = -vx;
        float vy = m_vyDist(m_gen); // dodatnie -> w dół

        m_pilka.setVelocity(vx, vy);
        m_gameStarted = true;
        std::cout << "Start! vx=" << vx << " vy=" << vy << "\n";
    }
};