#include "Grua.h"
#include "GestorRecursos.h"
#include <cmath>

Grua::Grua(float x, float y) : base(x,y), angulo(0), tiempo(0), hay(true) {
    // Carga manual de lista
    texturas.push_back("assets/bloquefich.png"); texturas.push_back("assets/bloquefcm.png");
    texturas.push_back("assets/bloquefca.png"); texturas.push_back("assets/bloquefce.png");
    texturas.push_back("assets/bloquefcjs.png"); texturas.push_back("assets/bloquefcv.png");
    texturas.push_back("assets/bloquefhuc.png"); texturas.push_back("assets/bloquefbcb.png");

    gancho.setTexture(GestorRecursos::get().getTex("assets/gancho.png"));
    gancho.setOrigin(gancho.getLocalBounds().width/2, 0);
    gancho.setPosition(base);
    gancho.setScale(0.6f, 120.f/gancho.getLocalBounds().height);
    generar();
}

void Grua::generar() {
    hay = true;
    texActual = texturas[rand() % texturas.size()];
    bloqueVis.setTexture(GestorRecursos::get().getTex(texActual), true);
    float s = 60.f / bloqueVis.getLocalBounds().width;
    bloqueVis.setScale(s, s);
    bloqueVis.setOrigin(bloqueVis.getLocalBounds().width/2, 0);
}

void Grua::actualizar(float dt) {
    tiempo += dt;
    angulo = 55.f * sin(tiempo * 1.8f);
    gancho.setRotation(angulo);
    
    if(hay) {
        Transform tr = gancho.getTransform();
        bloqueVis.setPosition(tr.transformPoint(gancho.getLocalBounds().width/2, gancho.getLocalBounds().height));
        bloqueVis.setRotation(angulo);
    }
}

void Grua::dibujar(RenderWindow& w) { w.draw(gancho); if(hay) w.draw(bloqueVis); }
void Grua::setY(float y) { base.y = y; gancho.setPosition(base); }

shared_ptr<Bloque> Grua::soltar() {
    if(!hay) return nullptr;
    Transform tr = bloqueVis.getTransform();
    Vector2f pos = tr.transformPoint(bloqueVis.getLocalBounds().width/2, bloqueVis.getLocalBounds().height/2);
    
    auto b = make_shared<Bloque>(pos.x, pos.y, texActual);
    b->getSprite().setRotation(bloqueVis.getRotation());
    b->soltar(); hay = false;
    return b;
}