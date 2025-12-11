#include "Juego.h"
#include "GestorRecursos.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

Juego::Juego() : ventana(VideoMode(800, 600), "UNL BLOXX"), estado(0), vidas(3), puntos(0), combo(0), camaraY(0),
                 grua(400, 50), torre(570), opcionMenu(0), puntajeGuardado(false),
                 marcadorPuntos(20, 20, "assets/box_puntaje.png"), 
                 marcadorVidas(600, 20, "assets/box_vidas.png") 
{
    // vsync para que se vea fluido
    ventana.setVerticalSyncEnabled(true);
    srand(time(0)); 
    vista = ventana.getDefaultView();
    
    // cargamos el fondo
    spriteFondo.setTexture(GestorRecursos::obtenerTextura("assets/fondo.png"));
    spriteFondo.setScale(800.f/spriteFondo.getLocalBounds().width, 600.f/spriteFondo.getLocalBounds().height);
    
    // MENU PRINCIPAL 
    dibujarBoton(logo, "assets/logosinfondo.png", 245, 330, 400);
    dibujarBoton(btnJugar, "assets/boton_jugar.png",         580, 200, 200);
    dibujarBoton(btnRank, "assets/boton_puntajes.png",      580, 270, 200);
    dibujarBoton(btnInstr, "assets/boton_instrucciones.png", 580, 340, 200);
    dibujarBoton(btnSalir, "assets/boton_volver.png",        580, 410, 200);

    // GAME OVER 
    dibujarBoton(tituloGO, "assets/gameover.png", 400, 150, 450); 
    dibujarBoton(btnReintentar, "assets/boton_reintentar.png", 280, 520, 180);
    dibujarBoton(btnVolver, "assets/boton_volver.png", 520, 520, 180);

    cargarTextoInstrucciones();
}

Juego::~Juego() { for (auto b : bloquesEnJuego) delete b; }

void Juego::dibujarBoton(Sprite& s, string r, float x, float y, float w) {
    s.setTexture(GestorRecursos::obtenerTextura(r));
    s.setOrigin(s.getLocalBounds().width/2, s.getLocalBounds().height/2);
    float k = w/s.getLocalBounds().width; s.setScale(k,k); s.setPosition(x,y);
}

void Juego::dibujarTextoCentrado(string txt, float x, float y, int tam, Color color) {
    Text t(txt, GestorRecursos::obtenerFuente(), tam);
    t.setFillColor(color);
    t.setOutlineColor(Color::Black);
    t.setOutlineThickness(2);
    FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width/2, b.top + b.height/2);
    t.setPosition(x, y);
    ventana.draw(t);
}

void Juego::ejecutar() { 
    Clock reloj; 
    while(ventana.isOpen()) { 
        procesarEventos(); 
        actualizarJuego(reloj.restart().asSeconds()); 
        dibujarTodo(); 
    } 
}

// carga instrucciones de archivo si existe, sino lo crea
void Juego::cargarTextoInstrucciones() {
    ifstream archivo("instrucciones.dat");
    if(!archivo.is_open()) {
        ofstream nuevo("instrucciones.dat");
        nuevo << "Espacio o Flecha Abajo para soltar el bloque.\n\nApila los bloques sin que caigan.\n\nSi cae un bloque al vacio, pierdes 1 vida." << endl;
        nuevo.close(); archivo.open("instrucciones.dat");
    }
    string linea; 
    textoInstrucciones = ""; 
    while(getline(archivo, linea)) textoInstrucciones += linea + "\n";
}

void Juego::reiniciarPartida() {
    vidas=3; puntos=combo=camaraY=0; 
    for(auto b : bloquesEnJuego) delete b; // borrar bloques viejos
    bloquesEnJuego.clear();
    torre.reiniciar(); 
    grua.generarBloque(); 
    grua.actualizar(0,0);
}

void Juego::procesarEventos() {
    Event e;
    while(ventana.pollEvent(e)) {
        if (e.type == Event::Closed) ventana.close();
        // escribir nombre en Game Over
        if (estado == 4 && !puntajeGuardado && e.type == Event::TextEntered) {
            if (e.text.unicode == 8 && !nombreJugador.empty()) nombreJugador.pop_back();
            else if (e.text.unicode == 13) { 
                if(nombreJugador.empty()) nombreJugador="Jugador"; 
                GestorPuntajes::guardarPuntaje(nombreJugador, puntos); 
                puntajeGuardado=true; 
            }
            else if (e.text.unicode > 32 && e.text.unicode < 128 && nombreJugador.size()<10) 
                nombreJugador += (char)e.text.unicode;
        }
        if (e.type == Event::KeyPressed) {
            if (estado == 0) { // MENU
                if (e.key.code == Keyboard::Up) opcionMenu=(opcionMenu+3)%4;
                if (e.key.code == Keyboard::Down) opcionMenu=(opcionMenu+1)%4;
                if (e.key.code == Keyboard::Enter) {
                    if(opcionMenu==0) { reiniciarPartida(); estado=3; } 
                    else if(opcionMenu==1) { listaRanking=GestorPuntajes::leerMejores(); estado=2; }
                    else if(opcionMenu==2) estado=1; 
                    else ventana.close();
                }
            } 
            else if (estado == 3 && (e.key.code == Keyboard::Space || e.key.code == Keyboard::Down)) { // JUEGO
                if (auto b = grua.soltarBloque()) bloquesEnJuego.push_back(b);
            } 
            else if (estado == 4 && puntajeGuardado) { // GAME OVER
                if (e.key.code == Keyboard::Left || e.key.code == Keyboard::Right) opcionMenu = !opcionMenu;
                if (e.key.code == Keyboard::Enter) { 
                    if(opcionMenu==0) { reiniciarPartida(); estado=3; } 
                    else estado=0; 
                }
            } 
            else if ((estado == 1 || estado == 2) && e.key.code == Keyboard::Enter) estado=0;
            
            if (e.key.code == Keyboard::Escape) { 
                if(estado==3 || estado==2) estado=0; 
                else ventana.close(); 
            }
        }
    }
}

void Juego::actualizarJuego(float deltaTiempo) {
    if (estado != 3) return;
    // mover camara si la torre crece
    if (torre.obtenerAltura() < 500) 
        camaraY += (500 - torre.obtenerAltura() - camaraY) * 5 * deltaTiempo;
    
    grua.actualizar(deltaTiempo, -camaraY); 
    marcadorPuntos.actualizar(puntos); 
    marcadorVidas.actualizar(vidas);

    for (auto i = bloquesEnJuego.begin(); i != bloquesEnJuego.end(); ) {
        (*i)->actualizar(deltaTiempo);
        if (torre.verificarColision(*i)) {
            bool esPerfecto = torre.agregarBloque(*i); 
            if (esPerfecto) {
                combo++;
                // 1 pt + (combo * 2)
                puntos += (2 * combo); 
            } else {
                // si falla el perfecto, suma solo 1 y resetea combo
                combo = 0;
                puntos += 1;
            }
            grua.generarBloque();
            i = bloquesEnJuego.erase(i);
        } else if ((*i)->sprite.getPosition().y > 650 - camaraY) {
            delete *i; // bloque cae al vacio, lo borramos
            vidas--; combo=0; 
            i = bloquesEnJuego.erase(i); 
            if (vidas <= 0) { 
                estado=4; nombreJugador=""; puntajeGuardado=false; 
            } else grua.generarBloque();
        } else ++i;
    }
}

void Juego::dibujarTodo() {
    ventana.clear();
    View vActual = vista; vActual.move(0, -camaraY); ventana.setView(vActual);
    Sprite fondo = spriteFondo; fondo.setPosition(0, -camaraY); 
    ventana.draw(fondo);
    if (estado == 3) { // JUEGO
        torre.dibujar(ventana); 
        for (auto b : bloquesEnJuego) b->dibujar(ventana); 
        grua.dibujar(ventana); 
    }
    ventana.setView(vista); // vista fija para UI
    if (estado == 3) { 
        marcadorPuntos.dibujar(ventana); 
        marcadorVidas.dibujar(ventana); 
    }
    else {
        auto colorearBtn = [&](Sprite& s, bool activo) { 
            s.setColor(activo ? Color::White : Color(100,100,100)); 
            ventana.draw(s); 
        };
        if (estado == 0) { // MENU
            ventana.draw(logo); 
            colorearBtn(btnJugar, opcionMenu==0); 
            colorearBtn(btnRank, opcionMenu==1); 
            colorearBtn(btnInstr, opcionMenu==2); 
            colorearBtn(btnSalir, opcionMenu==3); 
        }
        else if (estado == 4) { // GAME OVER
            ventana.draw(tituloGO); 
            dibujarTextoCentrado("Puntos: "+to_string(puntos), 400, 300, 24, Color::White);
            if(!puntajeGuardado) 
                dibujarTextoCentrado("Nombre: "+nombreJugador+"_", 400, 360, 24, Color::Yellow);
            else { 
                colorearBtn(btnReintentar, opcionMenu==0); 
                colorearBtn(btnVolver, opcionMenu==1); 
            }
        }
        else if (estado == 1) { // INSTRUCCIONES
            RectangleShape caja({600, 400}); caja.setOrigin(300, 200); caja.setPosition(400, 300);
            caja.setFillColor(Color(0,0,0,220)); ventana.draw(caja);
            
            // Texto mas chico para que entre en la caja
            dibujarTextoCentrado("GUIA DE COMANDOS", 400, 150, 24, Color::Yellow);
            dibujarTextoCentrado(textoInstrucciones, 400, 300, 13, Color::White);
            dibujarTextoCentrado("Pulsa ENTER para volver", 400, 460, 16, Color(200,200,200));
        }
        else if (estado == 2) { // RANKING
            RectangleShape caja({500, 450}); caja.setOrigin(250, 225); caja.setPosition(400, 300);
            caja.setFillColor(Color(0,0,0,220)); ventana.draw(caja);
            
            // Texto mas chico para que entre
            dibujarTextoCentrado("TOP 5", 400, 130, 24, Color::Yellow);
            for(size_t i=0; i<listaRanking.size(); i++) { 
                dibujarTextoCentrado(to_string(i+1)+". "+listaRanking[i].nombre+"  "+to_string(listaRanking[i].puntos), 400, 200+i*40, 20, Color::White); 
            }
            dibujarTextoCentrado("Pulsa ENTER para volver", 400, 480, 16, Color(200,200,200));
        }
    }
    ventana.display();
}