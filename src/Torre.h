#ifndef TORRE_H
#define TORRE_H
#include "Bloque.h"
#include <vector>

// Clase que guarda los bloques apilados
class Torre {
public:
    Torre(float y = 570);
    ~Torre(); 
    void dibujar(RenderWindow& ventana);
    bool agregarBloque(Bloque* b); 
    bool verificarColision(Bloque* b); 
    float obtenerAltura(); 
    void reiniciar();

private:
    vector<Bloque*> bloquesApilados;
    float baseY;
};
#endif