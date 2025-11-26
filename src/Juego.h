#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Grua.h"
#include "Torre.h"
#include "Marcador.h"
#include "GestorPuntajes.h"

using namespace sf;
using namespace std;

class Juego {
public:
    Juego();
    void ejecutar();
private:
    void eventos();
    void actualizar(Time dt);
    void dibujar();
    void ajustar();
    void reiniciar();

    RenderWindow win;
    View vista;
    Sprite fondo, logo, bPlay, bRank, bInst, bExit, tGO, bRe, bVolver;
    
    int estado; // 0:Menu 1:Instr 2:Rank 3:Game 4:GO
    int opMenu, opGO;
    
    Grua grua; Torre torre;
    vector<shared_ptr<Bloque>> bloques;
    Marcador pts, vidas;
    int vidaVal, puntaje, combo;
    float offsetY;

    string nombre; bool guardado;
    vector<Puntaje> ranking;
};
#endif