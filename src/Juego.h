#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include "Grua.h"
#include "Torre.h"
#include "Marcador.h"

enum class EstadoJuego { MENU, INSTRUCCIONES, JUGANDO, GAME_OVER };

class Juego {
public:
    Juego();
    void ejecutar();

private:
    void procesarEventos();
    void actualizar(sf::Time dt);
    void renderizar();
    void manejarEntrada(sf::Keyboard::Key tecla, bool presionado);
    void reiniciarJuego();

    sf::RenderWindow mVentana;
    EstadoJuego mEstado;
    sf::Sprite mFondo;

    Marcador mMarcadorPuntaje; 
    Marcador mMarcadorVidas;   

    Grua mGrua;
    Torre mTorre;
    std::vector<std::shared_ptr<Bloque>> mBloquesCayendo;

    std::vector<std::string> mOpcionesMenu;
    int mOpcionSeleccionada;
    std::vector<std::string> mOpcionesGameOver;
    int mOpcionGameOverSeleccionada;

    int mVidas, mPuntaje, mCombo, mPoblacion;
    float mOffsetY;
};

#endif // JUEGO_H