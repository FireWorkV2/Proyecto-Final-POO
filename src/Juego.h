#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Grua.h"
#include "Torre.h"
#include "Marcador.h"
#include "GestorPuntajes.h"

class Juego {
public:
    Juego();
    void ejecutar();

private:
    void procesarEventos();
    void actualizar(sf::Time dt);
    void renderizar();
    void ajustarVista();
    void reiniciar();
    
    sf::RenderWindow mVentana;
    sf::View mVista; 
    sf::Sprite mFondo;
    
    // sprites del menu
    sf::Sprite mSprLogoMenu; 
    sf::Sprite mSprBtnJugar;
    sf::Sprite mSprBtnPuntajes;
    sf::Sprite mSprBtnInstr;
    sf::Sprite mSprBtnSalir; 

    // sprites del menu de game over
    sf::Sprite mSprGameOver;
    sf::Sprite mSprBtnReintentar;
    sf::Sprite mSprBtnVolver;
    
    int mEstado; 
    
    Grua mGrua;
    Torre mTorre;
    std::vector<std::shared_ptr<Bloque>> mBloques;
    
    Marcador mM_Puntos, mM_Vidas;
    int mVidas, mPuntaje, mCombo;
    float mOffsetY;
    
    int mOpcionMenu, mOpcionGO;

    std::string mNombreJugador;      
    bool mNombreYaGuardado;          
    std::vector<EntradaPuntaje> mRankingActual;
};

#endif