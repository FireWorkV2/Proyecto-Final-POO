#include "Torre.h"
#include <cmath>

// constructor de la torre
Torre::Torre(float x, float y) : posBase(x,y) {}
// dibujar la torre y sus bloques
void Torre::dibujar(RenderWindow& w) {
    RectangleShape b({300,10}); b.setOrigin(150,0); b.setPosition(posBase);
    b.setFillColor({100,100,100}); w.draw(b);
    for(auto& bl : lista) bl->dibujar(w);
}
// obtener la altura actual de la torre
float Torre::getAltura() { 
    return lista.empty() ? posBase.y : lista.back()->getSprite().getPosition().y - 25.f; 
}
// agregar un bloque a la torre
void Torre::agregar(shared_ptr<Bloque> b) {
    b->detener(); b->getSprite().setRotation(0);
    float h = b->getSprite().getGlobalBounds().height;
    bool perf = false;

    float xDest = lista.empty() ? posBase.x : lista.back()->getSprite().getPosition().x;
    float yDest = lista.empty() ? posBase.y - h/2 : lista.back()->getSprite().getGlobalBounds().top - h/2;

    if(abs(b->getSprite().getPosition().x - xDest) < 15) {
        b->getSprite().setPosition(xDest, yDest); perf = true;
    } else {
        b->getSprite().setPosition(b->getSprite().getPosition().x, yDest);
    }

    if(perf) b->setPerfecto();
    lista.push_back(b);
}

// verificar si hay colisión con la torre
bool Torre::hayColision(shared_ptr<Bloque> b) {
    FloatRect r = b->getSprite().getGlobalBounds();
    if(lista.empty()) return (r.top + r.height >= posBase.y && abs(b->getSprite().getPosition().x - posBase.x) < 150);
    return r.intersects(lista.back()->getSprite().getGlobalBounds());
}