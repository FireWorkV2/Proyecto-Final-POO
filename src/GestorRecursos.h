#ifndef GESTORRECURSOS_H
#define GESTORRECURSOS_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

using namespace sf; 
using namespace std;

// Clase para manejar las imagenes y fuentes 
class GestorRecursos {
public:
    // pedir una textura, si está la recibe, sino la carga
    static Texture& obtenerTextura(string ruta) {
        static map<string, Texture> texturas;
        if (texturas.find(ruta) == texturas.end()) texturas[ruta].loadFromFile(ruta);
        return texturas[ruta];
    }
    // lo mismo para la fuente
    static Font& obtenerFuente() {
        static Font fuente; 
        static bool cargada = false;
        if (!cargada) { fuente.loadFromFile("assets/fuentextexto.otf"); cargada = true; }
        return fuente;
    }
};
#endif