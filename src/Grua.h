#ifndef GRUA_H
#define GRUA_H
#include <SFML/Graphics.hpp>
#include "Bloque.h"
#include <vector>

// Clase que controla el gancho y genera bloques
class Grua {
public:
    Grua(float x, float y);
    void actualizar(float deltaTiempo, float posY);
    void dibujar(RenderWindow& ventana);
    void generarBloque(); 
    Bloque* soltarBloque(); 
    bool tieneBloque() { return hayBloque; }

private:
    Sprite spriteGancho, bloqueVisible;
    float tiempo, angulo;
    bool hayBloque;
    string texturaActual;
    vector<string> listaTexturas; 
};
#endif