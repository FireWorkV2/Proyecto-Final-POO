#ifndef MARCADOR_H
#define MARCADOR_H
#include <SFML/Graphics.hpp>
#include <string>

class Marcador {
public:
    Marcador(float x, float y, sf::Color c1, sf::Color c2, sf::Color texto, std::string icono = "");
    void actualizar(int valor);
    void dibujar(sf::RenderWindow& w);

private:
    void centrar();
    sf::RectangleShape mMarco, mCuerpo, mPantalla;
    sf::Text mTexto;
    sf::Sprite mIcono;
    bool mTieneIcono;
    sf::Texture mTexCinta;
};
#endif