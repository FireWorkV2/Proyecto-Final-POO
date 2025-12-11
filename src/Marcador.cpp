#include "Marcador.h"
#include "GestorRecursos.h"

Marcador::Marcador(float x, float y, string rutaImagen) {
    fondo.setTexture(GestorRecursos::obtenerTextura(rutaImagen));
    fondo.setPosition(x, y);
    // ajustamos el tamaño fijo del marcador
    float anchoFijo = 180.0f;
    float altoFijo = 70.0f;
    fondo.setScale(anchoFijo / fondo.getLocalBounds().width, altoFijo / fondo.getLocalBounds().height);
    // Config del texto
    texto.setFont(GestorRecursos::obtenerFuente());
    texto.setCharacterSize(18); 
    texto.setFillColor(Color::White);
    texto.setOutlineColor(Color::Black);
    texto.setOutlineThickness(2);
    actualizar(0);
}

void Marcador::actualizar(int valor) {
    texto.setString(to_string(valor));
    FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
    // centramos el texto en el medio del fondo
    float centroX = fondo.getPosition().x + (180.0f / 2.0f);
    float centroY = fondo.getPosition().y + (80.0f / 2.0f); 
    texto.setPosition(centroX, centroY + 5);
}

void Marcador::dibujar(RenderWindow& ventana) { 
    ventana.draw(fondo); 
    ventana.draw(texto); 
}