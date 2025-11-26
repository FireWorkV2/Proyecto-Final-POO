#ifndef GESTORRECURSOS_H
#define GESTORRECURSOS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

class GestorRecursos {
public:
    static GestorRecursos& get() { static GestorRecursos i; return i; }

    Texture& getTex(string ruta) {
        // Busqueda lineal simple
        for(auto& par : texturas) {
            if(par.first == ruta) return *par.second;
        }
        // Si no existe, cargar y guardar
        Texture* t = new Texture();
        t->loadFromFile(ruta);
        texturas.push_back(make_pair(ruta, t));
        return *t;
    }

    Font& getFont(string ruta) {
        for(auto& par : fuentes) {
            if(par.first == ruta) return *par.second;
        }
        Font* f = new Font();
        f->loadFromFile(ruta);
        fuentes.push_back(make_pair(ruta, f));
        return *f;
    }

private:
    vector<pair<string, Texture*>> texturas;
    vector<pair<string, Font*>> fuentes;
};
#endif