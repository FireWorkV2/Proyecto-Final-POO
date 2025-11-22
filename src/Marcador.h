#ifndef MARCADOR_H
#define MARCADOR_H

#include <SFML/Graphics.hpp>
#include <string>

class Marcador {
public:
    Marcador(float x, float y, sf::Color cCinta1, sf::Color cCinta2, sf::Color cTexto, const std::string& rutaIcono = "");
    void actualizar(int valor);
    void dibujar(sf::RenderWindow& ventana);

private:
    void inicializarTexturaCinta(sf::Color c1, sf::Color c2);
    void centrarContenido();

    sf::RectangleShape mCintaBorde;
    sf::Texture mTexturaCinta;
    sf::RectangleShape mCuerpoTV;
    sf::RectangleShape mPantallaTV;
    sf::Text mTextoValor;
    sf::Sprite mIcono;
    bool mTieneIcono;

    // Constantes de diseño internas
    const float ANCHO = 160.f, ALTO = 90.f, BORDE = 12.f, MARGEN = 10.f;
};

#endif // MARCADOR_H