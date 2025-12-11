#include "Bloque.h"
#include "GestorRecursos.h"

Bloque::Bloque(float x, float y, string rutaImagen) : velocidadY(0), cayendo(false) {
    // cargamos la imagen y ajustamos el tamaño
    sprite.setTexture(GestorRecursos::obtenerTextura(rutaImagen));
    float escala = 60.f / sprite.getLocalBounds().width;
    sprite.setScale(escala, escala);
    // origen en el medio
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    sprite.setPosition(x, y);
}

// si esta cayendo se aplica la gravedad
void Bloque::actualizar(float deltaTiempo) {
    if (cayendo) {
        velocidadY += 980 * deltaTiempo; // se aumenta la velocidad
        sprite.move(0, velocidadY * deltaTiempo); // se mueve el sprite
    }
}

void Bloque::dibujar(RenderWindow& ventana) { ventana.draw(sprite); }

// si el bloque cae perfecto (o casi) se lo cambia por un bloque perfecto
void Bloque::hacerPerfecto() {
    sprite.setTexture(GestorRecursos::obtenerTextura("assets/bloqueperfecto.png"), true);
    float escala = 60.f / sprite.getLocalBounds().width;
    sprite.setScale(escala, escala);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}