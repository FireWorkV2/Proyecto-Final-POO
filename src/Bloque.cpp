#include "Bloque.h"
#include "GestorRecursos.h"

static const float TAMANO_BLOQUE = 60.f;

Bloque::Bloque(float x, float y, const std::string& ruta) 
    : mCayendo(false), mVelocidadY(0.f) {
    
    mSprite.setTexture(GestorRecursos::getInstancia().getTextura(ruta));
    
    // escala 60px
    sf::FloatRect bounds = mSprite.getLocalBounds();
    if (bounds.width > 0) {
        float s = TAMANO_BLOQUE / bounds.width;
        mSprite.setScale(s, s);
        mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }
    mSprite.setPosition(x, y);
}

void Bloque::setPerfecto() {
    mSprite.setTexture(GestorRecursos::getInstancia().getTextura("assets/bloqueperfecto.png"), true);
    // Reajustar escala por si la textura cambia de tamaño
    float s = TAMANO_BLOQUE / mSprite.getLocalBounds().width;
    mSprite.setScale(s, s);
    mSprite.setOrigin(mSprite.getLocalBounds().width / 2.f, mSprite.getLocalBounds().height / 2.f);
}

void Bloque::actualizar(float dt) {
    if (mCayendo) {
        mVelocidadY += 980.f * dt; // Gravedad
        mSprite.move(0.f, mVelocidadY * dt);
    }
}

void Bloque::dibujar(sf::RenderWindow& w) { w.draw(mSprite); }
void Bloque::setPosicion(float x, float y) { mSprite.setPosition(x, y); }
void Bloque::soltar() { mCayendo = true; }
void Bloque::detener() { mCayendo = false; mVelocidadY = 0.f; }