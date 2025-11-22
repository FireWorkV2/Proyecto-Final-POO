#include "Grua.h"
#include "GestorRecursos.h"
#include <cmath>

Grua::Grua(float x, float y)
: mPosicionBase(x, y)
, mAngulo(0.f)
, mTiempo(0.f)
, mTieneBloque(true)
{
    float longitudCuerda = 120.f;

    // 1. Brazo
    mSpriteGancho.setTexture(GestorRecursos::getInstancia().getTextura("assets/gancho.png"));
    sf::FloatRect boundsG = mSpriteGancho.getLocalBounds();
    mSpriteGancho.setOrigin(boundsG.width / 2.f, 0.f);
    mSpriteGancho.setPosition(mPosicionBase);
    mSpriteGancho.setScale(0.6f, longitudCuerda / boundsG.height);

    // 2. Bloque colgante
    mSpriteBloque.setTexture(GestorRecursos::getInstancia().getTextura("assets/bloqueengancho.png"));
    sf::FloatRect boundsB = mSpriteBloque.getLocalBounds();
    float escalaB = 60.f / boundsB.width; 
    mSpriteBloque.setScale(escalaB, escalaB);
    mSpriteBloque.setOrigin(boundsB.width / 2.f, 0.f); 
}

void Grua::generarBloque() {
    mTieneBloque = true;
}

void Grua::setY(float y) {
    mPosicionBase.y = y;
    mSpriteGancho.setPosition(mPosicionBase);
}

void Grua::actualizar(float dt) {
    mTiempo += dt;
    // Balanceo
    mAngulo = 55.f * std::sin(mTiempo * 1.8f);
    mSpriteGancho.setRotation(mAngulo);

    if (mTieneBloque) {
        // Posicionar bloque en la punta usando transformación matricial
        sf::FloatRect bounds = mSpriteGancho.getLocalBounds();
        sf::Vector2f puntaLocal(bounds.width / 2.f, bounds.height);
        sf::Vector2f posicionMundo = mSpriteGancho.getTransform().transformPoint(puntaLocal);
        mSpriteBloque.setPosition(posicionMundo);
        mSpriteBloque.setRotation(mAngulo); 
    }
}

void Grua::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(mSpriteGancho);
    if (mTieneBloque) ventana.draw(mSpriteBloque);
}

std::shared_ptr<Bloque> Grua::soltarBloque() {
    if (mTieneBloque) {
        sf::Vector2f pos = mSpriteBloque.getPosition();
        // Ajuste de spawn por diferencia de origen visual/físico
        auto bloque = std::make_shared<Bloque>(pos.x, pos.y + 30.f);
        bloque->getSprite().setRotation(mSpriteBloque.getRotation());
        bloque->soltar();
        mTieneBloque = false;
        return bloque;
    }
    return nullptr;
}