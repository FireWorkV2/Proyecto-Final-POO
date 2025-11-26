#include "GestorPuntajes.h"

void GestorPuntajes::guardarPuntaje(const std::string& nombre, int puntos) {
    std::ofstream archivo("puntajes.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << nombre << " " << puntos << "\n";
        archivo.close();
    }
}

std::vector<EntradaPuntaje> GestorPuntajes::obtenerMejores() {
    std::vector<EntradaPuntaje> lista;
    std::ifstream archivo("puntajes.txt");
    
    std::string nom;
    int pts;
    if (archivo.is_open()) {
        while (archivo >> nom >> pts) {
            lista.push_back({nom, pts});
        }
        archivo.close();
    }
    // ordenar lista
    std::sort(lista.begin(), lista.end(), std::greater<EntradaPuntaje>());
    // solo las mejores 5 puntuaciones
    if (lista.size() > 5) {
        lista.resize(5);
    }

    return lista;
}