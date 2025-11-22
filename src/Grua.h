#ifndef GRUA_H
#define GRUA_H

#include <SFML/Graphics.hpp>
#include "Bloque.h"
#include <memory>

class Grua {
public:
    Grua(float x, float y);
    
    void actualizar(float dt);
    void dibujar(sf::RenderWindow& ventana);
    void setY(float y); // Sigue a la cámara
    std::shared_ptr<Bloque> soltarBloque();
    void generarBloque();
    bool tieneBloque() const { return mTieneBloque; }

private:
    sf::Sprite mSpriteGancho;
    sf::Sprite mSpriteBloque;
    float mAngulo;
    float mTiempo;
    sf::Vector2f mPosicionBase;
    bool mTieneBloque;
};

#endif // GRUA_H