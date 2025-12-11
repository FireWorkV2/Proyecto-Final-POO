#include "Grua.h"
#include "GestorRecursos.h"
#include <cmath>
#include <cstdlib> 

Grua::Grua(float x, float y) : tiempo(0), angulo(0) {
    // se cargan los sprites de los bloques
    listaTexturas = 
    {"assets/bloquefich.png","assets/bloquefcm.png","assets/bloquefca.png","assets/bloquefce.png",
    "assets/bloquefcjs.png","assets/bloquefcv.png","assets/bloquefhuc.png","assets/bloquefbcb.png"};
    // config del gancho
    spriteGancho.setTexture(GestorRecursos::obtenerTextura("assets/gancho.png"));
    spriteGancho.setOrigin(spriteGancho.getLocalBounds().width/2, 0);
    spriteGancho.setScale(0.6f, 120.f/spriteGancho.getLocalBounds().height);
    spriteGancho.setPosition(x, y);
    generarBloque();
}

// se elige una textura al azar y la ponemos en el gancho
void Grua::generarBloque() {
    hayBloque = true; 
    texturaActual = listaTexturas[rand() % listaTexturas.size()];
    bloqueVisible.setTexture(GestorRecursos::obtenerTextura(texturaActual), true);
    float escala = 60.f / bloqueVisible.getLocalBounds().width;
    bloqueVisible.setScale(escala, escala);
    bloqueVisible.setOrigin(bloqueVisible.getLocalBounds().width/2, 0);
}

void Grua::actualizar(float deltaTiempo, float posY) {
    spriteGancho.setPosition(spriteGancho.getPosition().x, posY);
    // funcion para mover el gancho con forma de seno
    tiempo += deltaTiempo; 
    angulo = 55.f * sin(tiempo * 1.8f);
    spriteGancho.setRotation(angulo);
    // si esta la grua con un bloque, el bloque debe seguir al gancho
    if (hayBloque) {
        bloqueVisible.setPosition(spriteGancho.getTransform().transformPoint(spriteGancho.getLocalBounds().width/2, spriteGancho.getLocalBounds().height));
        bloqueVisible.setRotation(angulo);
    }
}

void Grua::dibujar(RenderWindow& ventana) { 
    ventana.draw(spriteGancho); 
    if (hayBloque) ventana.draw(bloqueVisible); 
}

// se suelta el bloque -> se crea uno dinamico
Bloque* Grua::soltarBloque() {
    if (!hayBloque) return nullptr;
    hayBloque = false;
    // donde esta la punta del gancho
    auto pos = bloqueVisible.getTransform().transformPoint(bloqueVisible.getLocalBounds().width/2, bloqueVisible.getLocalBounds().height/2);
    // se crea un nuevo bloque
    Bloque* nuevoBloque = new Bloque(pos.x, pos.y, texturaActual); 
    nuevoBloque->sprite.setRotation(angulo); 
    nuevoBloque->cayendo = true;
    return nuevoBloque;
}