#ifndef MARCADOR_H
#define MARCADOR_H
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Marcador {
public:
    Marcador(float x, float y, Color c1, Color c2, Color ct, string ico="");
    void actualizar(int val);
    void dibujar(RenderWindow& w);
private:
    RectangleShape m, c, p; Text txt; Sprite icono; Texture texCinta;
};
#endif