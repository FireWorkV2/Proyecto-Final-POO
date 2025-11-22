#ifndef BLOQUE_H
#define BLOQUE_H

#include <SFML/Graphics.hpp>

class Bloque {
public:
    Bloque(float x, float y);
    
    void actualizar(float dt);
    void dibujar(sf::RenderWindow& ventana);
    
    void setPosicion(float x, float y);
    sf::Vector2f getPosicion() const { return mSprite.getPosition(); }
    sf::Sprite& getSprite() { return mSprite; }
    
    void setPerfecto(); // Cambia textura a combo
    void soltar();
    void detener();

private:
    sf::Sprite mSprite;
    bool mCayendo;
    float mVelocidadY;
};

#endif // BLOQUE_H