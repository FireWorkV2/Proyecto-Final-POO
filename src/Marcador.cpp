#include "Marcador.h"
#include "GestorRecursos.h"
#include <cmath>
#include <string>

Marcador::Marcador(float x, float y, sf::Color cCinta1, sf::Color cCinta2, sf::Color cTexto, const std::string& rutaIcono)
    : mTieneIcono(false)
{
    inicializarTexturaCinta(cCinta1, cCinta2);

    mCintaBorde.setSize(sf::Vector2f(ANCHO, ALTO));
    mCintaBorde.setPosition(x, y);
    mCintaBorde.setTexture(&mTexturaCinta);
    mCintaBorde.setTextureRect(sf::IntRect(0, 0, ANCHO, ALTO));

    mCuerpoTV.setSize(sf::Vector2f(ANCHO - 2*BORDE, ALTO - 2*BORDE));
    mCuerpoTV.setPosition(x + BORDE, y + BORDE);
    mCuerpoTV.setFillColor(sf::Color(80, 80, 80));
    mCuerpoTV.setOutlineThickness(2.f);

    mPantallaTV.setSize(sf::Vector2f(mCuerpoTV.getSize().x - 2*MARGEN, mCuerpoTV.getSize().y - 2*MARGEN));
    mPantallaTV.setPosition(mCuerpoTV.getPosition().x + MARGEN, mCuerpoTV.getPosition().y + MARGEN);
    mPantallaTV.setFillColor(sf::Color(20, 50, 20)); 
    mPantallaTV.setOutlineColor(sf::Color::Black);
    mPantallaTV.setOutlineThickness(1.f);

    mTextoValor.setFont(GestorRecursos::getInstancia().getFuente("assets/arial.ttf"));
    mTextoValor.setCharacterSize(32);
    mTextoValor.setFillColor(cTexto);
    mTextoValor.setString("0");

    if (!rutaIcono.empty()) {
        mIcono.setTexture(GestorRecursos::getInstancia().getTextura(rutaIcono));
        mTieneIcono = true;
        sf::FloatRect bounds = mIcono.getLocalBounds();
        if (bounds.height > 0) {
            float escala = 32.f / bounds.height;
            mIcono.setScale(escala, escala);
        }
    }
    centrarContenido();
}

void Marcador::inicializarTexturaCinta(sf::Color c1, sf::Color c2) {
    sf::Image imagen;
    imagen.create(32, 32, c1);
    for (int y = 0; y < 32; ++y) {
        for (int x = 0; x < 32; ++x) {
            if ((x + y) % 16 < 8) imagen.setPixel(x, y, c2);
        }
    }
    if (mTexturaCinta.loadFromImage(imagen)) {
        mTexturaCinta.setRepeated(true);
        mTexturaCinta.setSmooth(true);
    }
}

void Marcador::actualizar(int valor) {
    mTextoValor.setString(std::to_string(valor));
    centrarContenido();
}

void Marcador::centrarContenido() {
    sf::FloatRect bTexto = mTextoValor.getLocalBounds();
    float anchoIcono = mTieneIcono ? mIcono.getGlobalBounds().width : 0.f;
    float margen = mTieneIcono ? 10.f : 0.f;
    
    sf::Vector2f centro = mPantallaTV.getPosition() + mPantallaTV.getSize() / 2.f;
    float startX = centro.x - (anchoIcono + margen + bTexto.width) / 2.f;

    if (mTieneIcono) {
        mIcono.setOrigin(0.f, mIcono.getLocalBounds().height / 2.f);
        mIcono.setPosition(startX, centro.y);
    }
    mTextoValor.setOrigin(bTexto.left, bTexto.top + bTexto.height / 2.f);
    mTextoValor.setPosition(startX + anchoIcono + margen, centro.y);
}

void Marcador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(mCintaBorde);
    ventana.draw(mCuerpoTV);
    ventana.draw(mPantallaTV);
    if (mTieneIcono) ventana.draw(mIcono);
    ventana.draw(mTextoValor);
}