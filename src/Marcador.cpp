#include "Marcador.h"
#include "GestorRecursos.h"

Marcador::Marcador(float x, float y, sf::Color c1, sf::Color c2, sf::Color ct, std::string icono) {
    mTieneIcono = !icono.empty();
    sf::Image img; img.create(32, 32, c1);
    for(int i=0; i<32; ++i) for(int j=0; j<32; ++j) if((i+j)%16<8) img.setPixel(i,j,c2);
    mTexCinta.loadFromImage(img); mTexCinta.setRepeated(true);

    mMarco.setSize({160, 90}); mMarco.setPosition(x, y); mMarco.setTexture(&mTexCinta);
    mMarco.setTextureRect({0,0,160,90});

    mCuerpo.setSize({136, 66}); mCuerpo.setPosition(x+12, y+12); mCuerpo.setFillColor({80,80,80});
    mPantalla.setSize({116, 46}); mPantalla.setPosition(x+22, y+22); mPantalla.setFillColor({20,50,20});

    mTexto.setFont(GestorRecursos::getInstancia().getFuente("assets/arial.ttf"));
    mTexto.setCharacterSize(32); mTexto.setFillColor(ct); mTexto.setString("0");

    if(mTieneIcono) {
        mIcono.setTexture(GestorRecursos::getInstancia().getTextura(icono));
        float s = 32.f / mIcono.getLocalBounds().height;
        mIcono.setScale(s,s);
    }
    centrar();
}

void Marcador::actualizar(int v) { mTexto.setString(std::to_string(v)); centrar(); }

void Marcador::centrar() {
    sf::FloatRect b = mTexto.getLocalBounds();
    sf::Vector2f c = mPantalla.getPosition() + mPantalla.getSize()/2.f;
    float wIcon = mTieneIcono ? mIcono.getGlobalBounds().width + 10.f : 0.f;
    float totalW = wIcon + b.width;
    
    float startX = c.x - totalW/2.f;
    if(mTieneIcono) mIcono.setPosition(startX, c.y - mIcono.getGlobalBounds().height/2.f);
    mTexto.setPosition(startX + wIcon, c.y - b.height/2.f - b.top);
}

void Marcador::dibujar(sf::RenderWindow& w) {
    w.draw(mMarco); w.draw(mCuerpo); w.draw(mPantalla);
    if(mTieneIcono) w.draw(mIcono);
    w.draw(mTexto);
}