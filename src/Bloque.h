#ifndef BLOQUE_H
#define BLOQUE_H
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf; 
using namespace std;

// Clase que representa cada bloque que cae
class Bloque {
public:
    Bloque(float x, float y, string rutaImagen);
    void actualizar(float deltaTiempo); 
    void dibujar(RenderWindow& ventana);
    void hacerPerfecto(); 

    Sprite sprite;
    float velocidadY;
    bool cayendo; 
};
#endif