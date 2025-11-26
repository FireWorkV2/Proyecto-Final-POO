#include "Torre.h"
#include <cmath>

Torre::Torre(float x, float y) : mBasePos(x, y) {}

void Torre::dibujar(sf::RenderWindow& w, bool verBase) {
    if (verBase) {
        sf::RectangleShape base(sf::Vector2f(300.f, 10.f));
        base.setOrigin(150.f, 0.f);
        base.setPosition(mBasePos);
        base.setFillColor(sf::Color(100, 100, 100));
        base.setOutlineColor(sf::Color::White);
        base.setOutlineThickness(2.f);
        w.draw(base);
    }
    for (auto& b : mBloques) b->dibujar(w);
}

void Torre::agregarBloque(std::shared_ptr<Bloque> b) {
    b->detener();
    b->getSprite().setRotation(0.f);

    float altura = b->getSprite().getGlobalBounds().height - 3.f; 
    bool perfecto = false;

    if (mBloques.empty()) {
        b->setPosicion(b->getPosicion().x, mBasePos.y - altura/2.f - 15.f); // Ajuste fino base
        if (std::abs(b->getPosicion().x - mBasePos.x) < 15.f) {
            b->setPosicion(mBasePos.x, b->getPosicion().y);
            perfecto = true;
        }
    } else {
        auto ultimo = mBloques.back();
        float nuevaY = ultimo->getPosicion().y - altura;
        
        if (std::abs(b->getPosicion().x - ultimo->getPosicion().x) < 15.f) {
            b->setPosicion(ultimo->getPosicion().x, nuevaY);
            perfecto = true;
        } else {
            b->setPosicion(b->getPosicion().x, nuevaY);
        }
    }

    if (perfecto) b->setPerfecto();
    mBloques.push_back(b);
}

bool Torre::verificarColision(std::shared_ptr<Bloque> b) {
    float by = b->getPosicion().y;
    float bx = b->getPosicion().x;
    float margenY = 30.f; 

    if (mBloques.empty()) {
        return (by + margenY >= mBasePos.y && std::abs(bx - mBasePos.x) < 150.f);
    } else {
        auto ultimo = mBloques.back();
        return (by + margenY >= ultimo->getPosicion().y - margenY + 5.f && 
                std::abs(bx - ultimo->getPosicion().x) < 50.f);
    }
}

float Torre::getTopY() const {
    return mBloques.empty() ? mBasePos.y : mBloques.back()->getPosicion().y - 25.f;
}