#include "GestorPuntajes.h"
#include <fstream>
#include <algorithm>

// guarda en el archivo de texto
void GestorPuntajes::guardarPuntaje(string nombre, int puntos) {
    ofstream archivo("puntajes.txt", ios::app);
    archivo << nombre << " " << puntos << endl;
}

// lee el archivo y los ordena
vector<RegistroPuntaje> GestorPuntajes::leerMejores() {
    vector<RegistroPuntaje> lista; 
    string n; int p; 
    ifstream archivo("puntajes.txt");
    while (archivo >> n >> p) lista.push_back({n, p});
    // ordenamos para que queden los mejores arriba
    sort(lista.begin(), lista.end(), [](RegistroPuntaje a, RegistroPuntaje b){ return a.puntos > b.puntos; });
    // dejamos solo los 5 mejores
    if (lista.size() > 5) lista.resize(5);
    return lista;
}