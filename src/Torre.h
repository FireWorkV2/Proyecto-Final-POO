#ifndef TORRE_H
#define TORRE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bloque.h"

using namespace sf;
using namespace std;

class Torre {
public:
    Torre(float x=400, float y=570);
    void dibujar(RenderWindow& w);
    void agregar(shared_ptr<Bloque> b);
    bool hayColision(shared_ptr<Bloque> b);
    float getAltura();
    static const int BASE_Y = 570;
private:
    vector<shared_ptr<Bloque>> lista;
    Vector2f posBase;
};
#endif