#ifndef MARCADOR_H
#define MARCADOR_H
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf; using namespace std;

// Clase para mostrar puntos y vidas
class Marcador {
public:
    Marcador(float x, float y, string rutaImagen);
    void actualizar(int valor); 
    void dibujar(RenderWindow& ventana);
private:
    Sprite fondo; 
    Text texto;
};
#endif