#ifndef BLOQUE_H
#define BLOQUE_H

#include <SFML/Graphics.hpp>
#include <string>

class Bloque {
public:
    Bloque(float x, float y, const std::string& ruta);
    
    void actualizar(float dt);
    void dibujar(sf::RenderWindow& ventana);
    void setPosicion(float x, float y);
    void setPerfecto(); 
    void soltar();
    void detener();

    sf::Vector2f getPosicion() const { return mSprite.getPosition(); }
    sf::Sprite& getSprite() { return mSprite; }

private:
    sf::Sprite mSprite;
    bool mCayendo;
    float mVelocidadY;
};

#endif