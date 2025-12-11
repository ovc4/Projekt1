#pragma once
#include <SFML/System.hpp>
#include <vector>

class Paletka;
class Pilka;
class Stone;

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
public:
    GameState() = default;

    void capture(const Paletka& paddle, const Pilka& ball, const std::vector<Stone>& stones);

    sf::Vector2f getPaddlePosition() const { return paddlePosition; }
    sf::Vector2f getBallPosition() const   { return ballPosition; }
    sf::Vector2f getBallVelocity() const   { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }

private:
    sf::Vector2f paddlePosition{0.f, 0.f};
    sf::Vector2f ballPosition{0.f, 0.f};
    sf::Vector2f ballVelocity{0.f, 0.f};
    std::vector<BlockData> blocks;
};

#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

inline void GameState::capture(const Paletka& paddle,
                               const Pilka& ball,
                               const std::vector<Stone>& stones)
{
    paddlePosition = { paddle.getX(), paddle.getY() };
    ballPosition   = { ball.getX(),   ball.getY()   };
    ballVelocity   = { ball.getVx(),  ball.getVy()  };

    blocks.clear();
    blocks.reserve(stones.size());

    for (const auto& s : stones) {
        BlockData bd;
        sf::Vector2f pos = s.getPosition();
        bd.x = pos.x;
        bd.y = pos.y;
        bd.hp = s.getHP();
        blocks.push_back(bd);
    }
}



