#ifndef GRUA_H
#define GRUA_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bloque.h"

using namespace sf;
using namespace std;

class Grua {
public:
    Grua(float x, float y);
    void actualizar(float dt);
    void dibujar(RenderWindow& w);
    void setY(float y);
    void generar();
    shared_ptr<Bloque> soltar();
    bool tieneBloque() { return hay; }

private:
    Sprite gancho, bloqueVis;
    Vector2f base;
    float angulo, tiempo;
    bool hay;
    vector<string> texturas;
    string texActual;
};
#endif