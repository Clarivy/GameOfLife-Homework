#ifndef LIFESPRITE_H__
#define LIFESPRITE_H__
#include <string>

enum class SpriteState {
    DEAD,
    ALIVE
};


class SpriteBase {

public:
    SpriteBase() = default;
    SpriteBase(const int x, const int y, const SpriteState &state) : m_x(x), m_y(y), m_isAlive(state) {}
    virtual ~SpriteBase() = default;
    SpriteState IsAlive() { return m_isAlive; }
    virtual std::string GetStr() {
        return std::string(IsAlive() == SpriteState::ALIVE ? "O" : ".");
    }
    

private:
    SpriteState m_isAlive;
    int m_x, m_y;
};

class SpriteColorised : public SpriteBase {
};

class SpriteExtended : public SpriteBase {
};

class SpriteGenerations : public SpriteBase {
};

class SpriteWeighted : public SpriteExtended {
};

using SpritePointer = std::shared_ptr<SpriteBase>;
using WorldMapRow = std::vector<SpritePointer>;
using WorldMap2d = std::vector<WorldMapRow>;


SpritePointer CreateSprite(int x, int y, const char type);


#endif