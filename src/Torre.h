#ifndef TORRE_H
#define TORRE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bloque.h"

class Torre {
public:
    static constexpr float BASE_Y = 570.f; 
    Torre(float x = 400.f, float y = BASE_Y);

    void dibujar(sf::RenderWindow& w, bool verBase);
    void agregarBloque(std::shared_ptr<Bloque> b);
    bool verificarColision(std::shared_ptr<Bloque> b);
    float getTopY() const; 

private:
    std::vector<std::shared_ptr<Bloque>> mBloques;
    sf::Vector2f mBasePos;
};

#endif