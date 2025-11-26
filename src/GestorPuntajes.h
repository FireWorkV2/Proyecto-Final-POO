#ifndef GESTORPUNTAJES_H
#define GESTORPUNTAJES_H
#include <string>
#include <vector>

using namespace std;

struct Puntaje {
    string nombre; int valor;
};

class GestorPuntajes {
public:
    static void guardar(string n, int p);
    static vector<Puntaje> leerMejores();
};
#endif