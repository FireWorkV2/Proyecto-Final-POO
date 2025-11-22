#include "Torre.h"
#include <cmath>
#include <algorithm>

Torre::Torre(float x, float y) : mBasePos(x, y) {}

void Torre::dibujarBase(sf::RenderWindow& ventana) {
    sf::RectangleShape base(sf::Vector2f(300.f, 10.f));
    base.setOrigin(150.f, 0.f); 
    base.setPosition(mBasePos.x, mBasePos.y);
    base.setFillColor(sf::Color(100, 100, 100));
    base.setOutlineColor(sf::Color::White);
    base.setOutlineThickness(2.f);
    ventana.draw(base);
}

void Torre::dibujar(sf::RenderWindow& ventana, bool mostrarBase) {
    if (mostrarBase) dibujarBase(ventana);
    for (auto& bloque : mBloques) {
        bloque->dibujar(ventana);
    }
}

float Torre::getTopY() const {
    if (mBloques.empty()) return mBasePos.y;
    return mBloques.back()->getPosicion().y - 25.f;
}

void Torre::agregarBloque(std::shared_ptr<Bloque> bloque) {
    bloque->detener();
    bloque->getSprite().setRotation(0.f); 

    float alturaBloque = 45.f; // Altura visual de encastre
    bool esPerfecto = false;

    if (mBloques.empty()) {
        bloque->setPosicion(bloque->getPosicion().x, mBasePos.y - 30.f);
        if (std::abs(bloque->getPosicion().x - mBasePos.x) < 20.f) {
            bloque->setPosicion(mBasePos.x, bloque->getPosicion().y);
            esPerfecto = true;
        }
    } else {
        auto ultimo = mBloques.back();
        float nuevaY = ultimo->getPosicion().y - alturaBloque;
        float xActual = bloque->getPosicion().x;
        if (std::abs(xActual - ultimo->getPosicion().x) < 15.f) {
            xActual = ultimo->getPosicion().x; 
            esPerfecto = true;
        }
        bloque->setPosicion(xActual, nuevaY);
    }

    if (esPerfecto) bloque->setPerfecto();
    mBloques.push_back(bloque);
}

bool Torre::verificarColision(std::shared_ptr<Bloque> bloque) {
    float by = bloque->getPosicion().y;
    float bx = bloque->getPosicion().x;

    if (mBloques.empty()) {
        // Colisión con base
        if (by + 25.f >= mBasePos.y && std::abs(bx - mBasePos.x) < 150.f) return true;
    } else {
        // Colisión con último bloque
        auto ultimo = mBloques.back();
        if (by + 25.f >= ultimo->getPosicion().y - 20.f && std::abs(bx - ultimo->getPosicion().x) < 50.f) return true;
    }
    return false;
}