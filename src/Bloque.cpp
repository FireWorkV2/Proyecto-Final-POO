#include "Bloque.h"
#include "GestorRecursos.h"

Bloque::Bloque(float x, float y)
: mCayendo(false)
, mVelocidadY(0.f)
{
    mSprite.setTexture(GestorRecursos::getInstancia().getTextura("assets/bloque1.png"));
    sf::FloatRect bounds = mSprite.getLocalBounds();
    float escala = 60.f / bounds.width; // Escala a 60px ancho
    mSprite.setScale(escala, escala);
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mSprite.setPosition(x, y);
}

void Bloque::setPerfecto() {
    mSprite.setTexture(GestorRecursos::getInstancia().getTextura("assets/bloqueperfecto.png"));
}

void Bloque::actualizar(float dt) {
    if (mCayendo) {
        mVelocidadY += 980.f * dt; // Gravedad
        mSprite.move(0.f, mVelocidadY * dt);
    }
}

void Bloque::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(mSprite);
}

void Bloque::setPosicion(float x, float y) {
    mSprite.setPosition(x, y);
}

void Bloque::soltar() {
    mCayendo = true;
}

void Bloque::detener() {
    mCayendo = false;
    mVelocidadY = 0.f;
}