#include "GestorPuntajes.h"
#include <fstream>
#include <algorithm>

void GestorPuntajes::guardar(string n, int p) {
    ofstream arch("puntajes.txt", ios::app);
    if(arch.is_open()) arch << n << " " << p << endl;
}

vector<Puntaje> GestorPuntajes::leerMejores() {
    vector<Puntaje> lista;
    ifstream arch("puntajes.txt");
    string n; int p;
    
    while(arch >> n >> p) lista.push_back({n, p});

    // Ordenar de mayor a menor (lambda simple)
    sort(lista.begin(), lista.end(), [](Puntaje a, Puntaje b){ return a.valor > b.valor; });

    if(lista.size() > 5) lista.resize(5); // Solo top 5
    return lista;
}