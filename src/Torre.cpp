#include "Torre.h"
#include <cmath>

Torre::Torre(float y) : baseY(y) {}
// cuando se destruye la torre, borramos los bloques
Torre::~Torre() { reiniciar(); }

void Torre::reiniciar() {
    for (auto b : bloquesApilados) delete b; // se libera la memoria
    bloquesApilados.clear();
}

// altura del ultimo bloque
float Torre::obtenerAltura() {
    return bloquesApilados.empty() ? baseY : bloquesApilados.back()->sprite.getPosition().y - 25;
}

void Torre::dibujar(RenderWindow& ventana) {
    // el piso dibujado
    RectangleShape suelo({300, 10}); 
    suelo.setOrigin(150, 0); 
    suelo.setPosition(400, baseY); 
    suelo.setFillColor({100, 100, 100});
    ventana.draw(suelo);
    // Se dibujan todos los bloques
    for (auto b : bloquesApilados) b->dibujar(ventana);
}

bool Torre::agregarBloque(Bloque* b) {
    b->cayendo = false; 
    b->velocidadY = 0; 
    b->sprite.setRotation(0); // se endereza el bloque
    float xDestino = bloquesApilados.empty() ? 400 : bloquesApilados.back()->sprite.getPosition().x;
    float yDestino = bloquesApilados.empty() ? baseY : bloquesApilados.back()->sprite.getGlobalBounds().top;
    
    bool perfecto = false;

    // si cae cerca del centro del sprite , se lo hace perfecto
    if (abs(b->sprite.getPosition().x - xDestino) < 5) {
        b->sprite.setPosition(xDestino, yDestino - b->sprite.getGlobalBounds().height/2);
        b->hacerPerfecto();
        perfecto = true;
    } else {
        b->sprite.setPosition(b->sprite.getPosition().x, yDestino - b->sprite.getGlobalBounds().height/2);
        perfecto = false;
    }
    bloquesApilados.push_back(b);
    return perfecto;
}

bool Torre::verificarColision(Bloque* b) {
    // si no hay nada, se ve el piso
    if (bloquesApilados.empty()) 
        return (b->sprite.getPosition().y + b->sprite.getGlobalBounds().height/2 >= baseY && abs(b->sprite.getPosition().x - 400) < 150);
    // si hay bloques, se ve el ultimo
    return b->sprite.getGlobalBounds().intersects(bloquesApilados.back()->sprite.getGlobalBounds());
}