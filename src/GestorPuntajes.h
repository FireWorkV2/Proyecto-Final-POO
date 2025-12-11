#ifndef GESTORPUNTAJES_H
#define GESTORPUNTAJES_H
#include <vector>
#include <string>

using namespace std;

// Estructura para guardar datos
struct RegistroPuntaje { string nombre; int puntos; };

class GestorPuntajes {
public:
    static void guardarPuntaje(string nombre, int puntos);
    static vector<RegistroPuntaje> leerMejores(); 
};
#endif