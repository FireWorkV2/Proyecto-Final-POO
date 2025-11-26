#ifndef BLOQUE_H
#define BLOQUE_H
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Bloque {
public:
    Bloque(float x, float y, string img);
    void actualizar(float dt);
    void dibujar(RenderWindow& w) { w.draw(spr); }
    
    Sprite& getSprite() { return spr; }
    void setPerfecto();
    void soltar() { cayendo=true; }
    void detener() { cayendo=false; vy=0; }

private:
    Sprite spr;
    bool cayendo;
    float vy;
};
#endif