#ifndef GRUA_H
#define GRUA_H

#include <SFML/Graphics.hpp>
#include "Bloque.h"
#include <memory>
#include <vector>

class Grua {
public:
    Grua(float x, float y);
    
    void actualizar(float dt);
    void dibujar(sf::RenderWindow& ventana);
    void setY(float y);
    void generarBloque();
    std::shared_ptr<Bloque> soltarBloque();
    bool tieneBloque() const { return mTieneBloque; }

private:
    void cambiarTextura();

    sf::Sprite mSpriteGancho;
    sf::Sprite mSpriteBloque;
    sf::Vector2f mPosicionBase;
    
    float mAngulo;
    float mTiempo;
    bool mTieneBloque;
    
    std::vector<std::string> mTexturas;
    std::string mTexturaActual;
};

#endif