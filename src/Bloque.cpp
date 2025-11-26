#include "Bloque.h"
#include "GestorRecursos.h"

Bloque::Bloque(float x, float y, string img) : cayendo(false), vy(0) {
    spr.setTexture(GestorRecursos::get().getTex(img));
    float escala = 60.f / spr.getLocalBounds().width;
    spr.setScale(escala, escala);
    spr.setOrigin(spr.getLocalBounds().width/2, spr.getLocalBounds().height/2);
    spr.setPosition(x,y);
}

void Bloque::setPerfecto() {
    spr.setTexture(GestorRecursos::get().getTex("assets/bloqueperfecto.png"), true);
    float escala = 60.f / spr.getLocalBounds().width;
    spr.setScale(escala, escala);
    spr.setOrigin(spr.getLocalBounds().width/2, spr.getLocalBounds().height/2);
}

void Bloque::actualizar(float dt) {
    if(cayendo) {
        vy += 980.f * dt; // Gravedad
        spr.move(0, vy * dt);
    }
}