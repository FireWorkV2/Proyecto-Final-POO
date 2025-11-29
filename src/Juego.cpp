#include "Juego.h"
#include "GestorRecursos.h"
#include <algorithm>
#include <fstream> 

Juego::Juego() 
: win(VideoMode(800,600), "UNL BLOXX"), estado(0), vidaVal(3), puntaje(0), combo(0), offsetY(0)
, grua(400,50), torre(400, Torre::BASE_Y), opMenu(0), opGO(0), guardado(false)
, pts(20,20, Color::Yellow, Color::Black, {100,255,100})
, vidas(620,20, Color::Red, Color::Black, {255,50,50}, "assets/vida.png")
{
    srand(time(0)); win.setFramerateLimit(60);
    vista.setSize(800,600); vista.setCenter(400,300); ajustar();

    fondo.setTexture(GestorRecursos::get().getTex("assets/fondo.png")); 
    fondo.setScale(800.f/fondo.getLocalBounds().width, 600.f/fondo.getLocalBounds().height);

    auto btn = [&](Sprite& s, string r, float x, float y, float w) {
        s.setTexture(GestorRecursos::get().getTex(r)); 
        s.setOrigin(s.getLocalBounds().width/2, s.getLocalBounds().height/2);
        s.setScale(w/s.getLocalBounds().width, w/s.getLocalBounds().width);
        s.setPosition(x,y);
    };

    btn(logo, "assets/logosinfondo.png", 230, 300, 350);
    btn(bPlay, "assets/boton_jugar.png", 570, 200, 200);
    btn(bRank, "assets/boton_puntajes.png", 570, 270, 200);
    btn(bInst, "assets/boton_instrucciones.png", 570, 340, 200);
    btn(bExit, "assets/boton_volver.png", 570, 410, 200);

    btn(tGO, "assets/gameover.png", 400, 100, 450);
    btn(bRe, "assets/boton_reintentar.png", 280, 450, 180);
    btn(bVolver, "assets/boton_volver.png", 520, 450, 180);

    cargarInstrucciones(); 
}

void Juego::cargarInstrucciones() {
    ifstream lectura("instrucciones.dat");
    if(!lectura.is_open()) {
        ofstream escritura("instrucciones.dat");
        escritura << "UNL BLOXX - Guia de Comandos" << endl << endl;
        escritura << " - Presiona Espacio o Flecha Abajo" << endl;
        escritura << "   para soltar el bloque." << endl << endl;
        escritura << " - Apila los bloques lo mas alto posible" << endl;
        escritura << "   sin que se caigan." << endl << endl;
        escritura << " - Si un bloque cae, pierdes una vida." << endl;
        escritura << "   El juego termina al perder todas." << endl;
        escritura.close();
        lectura.open("instrucciones.dat");
    }

    string linea;
    textoInstrucciones = "";
    while(getline(lectura, linea)) {
        textoInstrucciones += linea + "\n";
    }
    lectura.close();
}

void Juego::ajustar() {
    float rx = win.getSize().x/800.f, ry = win.getSize().y/600.f;
    float m = min(rx, ry);
    float w = 800*m/win.getSize().x, h = 600*m/win.getSize().y;
    vista.setViewport({(1-w)/2, (1-h)/2, w, h});
}

void Juego::ejecutar() {
    Clock c;
    while(win.isOpen()) { eventos(); actualizar(c.restart()); dibujar(); }
}

void Juego::eventos() {
    Event e;
    while(win.pollEvent(e)) {
        if(e.type == Event::Closed) win.close();
        if(e.type == Event::Resized) ajustar();
        
        if(estado==4 && !guardado && e.type == Event::TextEntered) {
            if(e.text.unicode==8 && !nombre.empty()) nombre.pop_back();
            else if(e.text.unicode==13) {
                if(nombre.empty()) nombre="Jugador"; 
                GestorPuntajes::guardar(nombre, puntaje); guardado=true; 
            }
            else if(e.text.unicode > 32 && e.text.unicode < 128 && nombre.size()<10) {
                nombre += (char)e.text.unicode;
            }
        }

        if(e.type == Event::KeyPressed) {
            if(e.key.code == Keyboard::Escape) {
                if(estado==3 || estado==2) estado=0; else win.close();
            }
            if(estado==0) { // Menu
                if(e.key.code==Keyboard::Up) opMenu=(opMenu+3)%4;
                if(e.key.code==Keyboard::Down) opMenu=(opMenu+1)%4;
                if(e.key.code==Keyboard::Enter) {
                    if(opMenu==0) { reiniciar(); estado=3; }
                    else if(opMenu==1) { ranking=GestorPuntajes::leerMejores(); estado=2; }
                    else if(opMenu==2) estado=1;
                    else win.close();
                }
            }
            else if(estado==3) { // Juego
                if((e.key.code==Keyboard::Space || e.key.code==Keyboard::Down) && grua.tieneBloque())
                    if(auto b=grua.soltar()) bloques.push_back(b);
            }
            else if(estado==4 && guardado) { // GO
                if(e.key.code==Keyboard::Left || e.key.code==Keyboard::Right) opGO=!opGO;
                if(e.key.code==Keyboard::Enter) {
                    if(opGO==0) { reiniciar(); estado=3; } else estado=0;
                }
            }
            else if((estado==1 || estado==2) && e.key.code==Keyboard::Enter) estado=0;
        }
    }
}

void Juego::actualizar(Time dt) {
    if(estado!=3) return;
    float t = dt.asSeconds();
    if(torre.getAltura() < 500) offsetY += (500 - torre.getAltura() - offsetY) * 5 * t;
    
    grua.setY(-offsetY); grua.actualizar(t);
    pts.actualizar(puntaje); vidas.actualizar(vidaVal);

    for(auto i=bloques.begin(); i!=bloques.end(); ) {
        (*i)->actualizar(t);
        if(torre.hayColision(*i)) {
            torre.agregar(*i); puntaje += 10 + (combo++)*5; i=bloques.erase(i); grua.generar();
        } else if((*i)->getSprite().getPosition().y > 650-offsetY) {
            vidaVal--; combo=0; i=bloques.erase(i);
            if(vidaVal<=0) { estado=4; nombre=""; guardado=false; } else grua.generar();
        } else ++i;
    }
}

void Juego::dibujar() {
    win.clear();
    View v = vista; v.move(0, -offsetY); win.setView(v);
    Sprite f = fondo; f.setPosition(0, -offsetY); win.draw(f);

    if(estado==3) { torre.dibujar(win); for(auto& b:bloques) b->dibujar(win); grua.dibujar(win); }

    win.setView(vista);
    if(estado==3) { pts.dibujar(win); vidas.dibujar(win); }
    else {
        Text tx; tx.setFont(GestorRecursos::get().getFont("assets/arial.ttf"));
        
        if(estado==0) { // Menu
            win.draw(logo);
            bPlay.setColor(opMenu==0?Color::White:Color(100,100,100));
            bRank.setColor(opMenu==1?Color::White:Color(100,100,100));
            bInst.setColor(opMenu==2?Color::White:Color(100,100,100));
            bExit.setColor(opMenu==3?Color::White:Color(100,100,100));
            win.draw(bPlay); win.draw(bRank); win.draw(bInst); win.draw(bExit);
        }
        else if(estado==1) { // Instrucciones
            RectangleShape box({600, 400}); box.setPosition(100, 100); 
            box.setFillColor(Color(0, 0, 0, 200)); win.draw(box);
            tx.setCharacterSize(24);
            tx.setString(textoInstrucciones); 
            tx.setPosition(120, 120); win.draw(tx);
            tx.setString("Presiona ENTER para volver al menu.");
            tx.setPosition(200, 450); 
            win.draw(tx);
        }
        else if(estado==2) { // Rank
            tx.setString("TOP 5"); tx.setFillColor(Color::Yellow); tx.setPosition(350,50); win.draw(tx);
            tx.setFillColor(Color::White);
            for(size_t i=0; i<ranking.size(); i++) {
                tx.setString(to_string(i+1)+". "+ranking[i].nombre+" - "+to_string(ranking[i].valor));
                tx.setPosition(250, 150+i*50); win.draw(tx);
            }
            tx.setString("ENTER volver"); tx.setPosition(300,500); win.draw(tx);
        }
        else if(estado==4) { // GO
            win.draw(tGO);
            tx.setString("Puntos: "+to_string(puntaje)); tx.setPosition(350,230); win.draw(tx);
            if(!guardado) {
                tx.setString("Nombre: "+nombre+"_"); tx.setFillColor(Color::Yellow); 
                tx.setPosition(350,300); win.draw(tx);
            } else {
                bRe.setColor(opGO==0?Color::White:Color(100,100,100));
                bVolver.setColor(opGO==1?Color::White:Color(100,100,100));
                win.draw(bRe); win.draw(bVolver);
            }
        }
    }
    win.display();
}

void Juego::reiniciar() {
    vidaVal=3; puntaje=0; combo=0; offsetY=0; bloques.clear();
    torre=Torre(400, Torre::BASE_Y); grua=Grua(400,50);
}