#include "Grua.h"
#include "GestorRecursos.h"
#include <cmath>
#include <cstdlib>

Grua::Grua(float x, float y) 
    : mPosicionBase(x, y), mAngulo(0.f), mTiempo(0.f), mTieneBloque(true) {
    
    mTexturas = {
        "assets/bloquefich.png", "assets/bloquefcm.png", "assets/bloquefca.png",
        "assets/bloquefce.png", "assets/bloquefcjs.png", "assets/bloquefcv.png",
        "assets/bloquefhuc.png", "assets/bloquefbcb.png", "assets/bloquefiq.png",
        "assets/bloqueconicet.png"
    };

    // configuraciones del gancho
    mSpriteGancho.setTexture(GestorRecursos::getInstancia().getTextura("assets/gancho.png"));
    sf::FloatRect b = mSpriteGancho.getLocalBounds();
    mSpriteGancho.setOrigin(b.width / 2.f, 0.f);
    mSpriteGancho.setPosition(x, y);
    mSpriteGancho.setScale(0.6f, 120.f / b.height); // Cuerda de 120px

    cambiarTextura();
}

void Grua::cambiarTextura() {
    mTexturaActual = mTexturas.empty() ? "assets/bloque1.png" : mTexturas[rand() % mTexturas.size()];
    
    mSpriteBloque.setTexture(GestorRecursos::getInstancia().getTextura(mTexturaActual), true);
    sf::FloatRect b = mSpriteBloque.getLocalBounds();
    if (b.width > 0) {
        float s = 60.f / b.width; 
        mSpriteBloque.setScale(s, s);
        mSpriteBloque.setOrigin(b.width / 2.f, 0.f); // se cuelga desde arriba
    }
}

void Grua::actualizar(float dt) {
    mTiempo += dt;
    mAngulo = 55.f * std::sin(mTiempo * 1.8f); // logica del balanceo
    mSpriteGancho.setRotation(mAngulo);

    if (mTieneBloque) {
        sf::FloatRect b = mSpriteGancho.getLocalBounds();
        sf::Vector2f punta = mSpriteGancho.getTransform().transformPoint(b.width / 2.f, b.height);
        mSpriteBloque.setPosition(punta);
        mSpriteBloque.setRotation(mAngulo);
    }
}

void Grua::dibujar(sf::RenderWindow& w) {
    w.draw(mSpriteGancho);
    if (mTieneBloque) w.draw(mSpriteBloque);
}

void Grua::generarBloque() {
    mTieneBloque = true;
    cambiarTextura();
}

std::shared_ptr<Bloque> Grua::soltarBloque() {
    if (!mTieneBloque) return nullptr;
    sf::FloatRect b = mSpriteBloque.getLocalBounds();
    sf::Vector2f centro = mSpriteBloque.getTransform().transformPoint(b.width / 2.f, b.height / 2.f);
    auto bloque = std::make_shared<Bloque>(centro.x, centro.y, mTexturaActual);
    bloque->getSprite().setRotation(mSpriteBloque.getRotation());
    bloque->soltar();
    mTieneBloque = false;
    return bloque;
}
void Grua::setY(float y) { mPosicionBase.y = y; mSpriteGancho.setPosition(mPosicionBase); }