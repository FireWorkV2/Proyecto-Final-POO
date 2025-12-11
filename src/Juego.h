#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Grua.h"
#include "Torre.h"
#include "Marcador.h"
#include "GestorPuntajes.h"

using namespace sf; using namespace std;

// Clase principal que maneja todo el juego
class Juego {
public:
    Juego();
    ~Juego();
    void ejecutar();

private:
    void procesarEventos(); 
    void actualizarJuego(float deltaTiempo); 
    void dibujarTodo(); 
    void reiniciarPartida();
    void cargarTextoInstrucciones();
    void dibujarTextoCentrado(string texto, float x, float y, int tam, Color color);
    void dibujarBoton(Sprite& sprite, string ruta, float x, float y, float ancho);

    RenderWindow ventana;
    View vista;
    Sprite spriteFondo, logo, btnJugar, btnRank, btnInstr, btnSalir, tituloGO, btnReintentar, btnVolver;
    
    int estado; // 0:Menu, 1:Instr, 2:Rank, 3:Juego, 4:GameOver
    int opcionMenu;
    int vidas, puntos, combo;
    float camaraY;
    string nombreJugador, textoInstrucciones;
    bool puntajeGuardado;

    Grua grua; 
    Torre torre;
    vector<Bloque*> bloquesEnJuego; 
    Marcador marcadorPuntos, marcadorVidas;
    vector<RegistroPuntaje> listaRanking;
};
#endif