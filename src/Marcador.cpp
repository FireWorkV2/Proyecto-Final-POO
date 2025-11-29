#include "Marcador.h"
#include "GestorRecursos.h"

// constructor del marcador
Marcador::Marcador(float x, float y, Color c1, Color c2, Color ct, string ico) {
    Image i; i.create(32,32,c1);
    for(int j=0;j<32;j++) for(int k=0;k<32;k++) if((j+k)%16<8) i.setPixel(j,k,c2);
    texCinta.loadFromImage(i); texCinta.setRepeated(true);
    // configurar las formas y el texto
    m.setSize({160,90}); m.setPosition(x,y); m.setTexture(&texCinta); m.setTextureRect({0,0,160,90});
    c.setSize({136,66}); c.setPosition(x+12,y+12); c.setFillColor({80,80,80});
    p.setSize({116,46}); p.setPosition(x+22,y+22); p.setFillColor({20,50,20});
    txt.setFont(GestorRecursos::get().getFont("assets/arial.ttf"));
    txt.setCharacterSize(32); txt.setFillColor(ct); txt.setString("0");

    if(ico!="") { 
        icono.setTexture(GestorRecursos::get().getTex(ico)); 
        float s=32.f/icono.getLocalBounds().height; icono.setScale(s,s); 
    }
    actualizar(0);
}

// actualizar el valor mostrado en el marcador
void Marcador::actualizar(int val) {
    txt.setString(to_string(val));
    FloatRect b = txt.getLocalBounds();
    float cx = p.getPosition().x + p.getSize().x/2;
    float cy = p.getPosition().y + p.getSize().y/2;
    txt.setOrigin(b.left+b.width/2, b.top+b.height/2); txt.setPosition(cx, cy);
    if(icono.getTexture()) icono.setPosition(cx-60, cy-16);
}

// dibujar el marcador en la ventana
void Marcador::dibujar(RenderWindow& w) { w.draw(m); w.draw(c); w.draw(p); if(icono.getTexture()) w.draw(icono); w.draw(txt); }