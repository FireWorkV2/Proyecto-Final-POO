#ifndef GESTORPUNTAJES_H
#define GESTORPUNTAJES_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

struct EntradaPuntaje {
    std::string nombre;
    int puntos;
    bool operator>(const EntradaPuntaje& otro) const {
        return puntos > otro.puntos;
    }
};

class GestorPuntajes {
public:
    static void guardarPuntaje(const std::string& nombre, int puntos);
    static std::vector<EntradaPuntaje> obtenerMejores();
};

#endif