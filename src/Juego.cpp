#include "Juego.h"
#include "GestorRecursos.h"
#include <ctime>
#include <cstdlib>
#include <cmath> 
#include <algorithm> 

enum { MENU, INSTR, RANKING, JUEGO, GAMEOVER };

Juego::Juego()
    : mVentana(sf::VideoMode(800, 600), "UNL BLOXX", sf::Style::Default)
    , mEstado(MENU), mVidas(3), mPuntaje(0), mCombo(0), mOffsetY(0.f)
    , mGrua(400.f, 50.f), mTorre(400.f, Torre::BASE_Y)
    , mM_Puntos(20.f, 20.f, sf::Color::Yellow, sf::Color::Black, sf::Color(100,255,100))
    , mM_Vidas(620.f, 20.f, sf::Color::Red, sf::Color::Black, sf::Color(255,50,50), "assets/vida.png")
    , mOpcionMenu(0), mOpcionGO(0)
    , mNombreYaGuardado(false)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    mVentana.setFramerateLimit(60);
    
    mVista.setSize(800.f, 600.f);
    mVista.setCenter(400.f, 300.f);
    ajustarVista(); 

    mFondo.setTexture(GestorRecursos::getInstancia().getTextura("assets/fondo.png"));
    sf::Vector2u s = mFondo.getTexture()->getSize();
    mFondo.setScale(800.f/s.x, 600.f/s.y);

    mSprLogoMenu.setTexture(GestorRecursos::getInstancia().getTextura("assets/logosinfondo.png"));
    sf::FloatRect bLogo = mSprLogoMenu.getLocalBounds();
    mSprLogoMenu.setOrigin(bLogo.width / 2.f, bLogo.height / 2.f);
    if(bLogo.width > 0) { 
        float scale = 350.f / bLogo.width; 
        mSprLogoMenu.setScale(scale, scale); 
    }
    mSprLogoMenu.setPosition(230.f, 300.f); 

    float xBotones = 570.f; 
    float anchoBoton = 200.f; 

    // Botón Jugar
    mSprBtnJugar.setTexture(GestorRecursos::getInstancia().getTextura("assets/boton_jugar.png"));
    sf::FloatRect bJ = mSprBtnJugar.getLocalBounds();
    mSprBtnJugar.setOrigin(bJ.width/2.f, bJ.height/2.f);
    if(bJ.width > 0) mSprBtnJugar.setScale(anchoBoton/bJ.width, anchoBoton/bJ.width);
    mSprBtnJugar.setPosition(xBotones, 200.f); // Arriba

    // Botón Puntajes
    mSprBtnPuntajes.setTexture(GestorRecursos::getInstancia().getTextura("assets/boton_puntajes.png"));
    sf::FloatRect bP = mSprBtnPuntajes.getLocalBounds();
    mSprBtnPuntajes.setOrigin(bP.width/2.f, bP.height/2.f);
    if(bP.width > 0) mSprBtnPuntajes.setScale(anchoBoton/bP.width, anchoBoton/bP.width);
    mSprBtnPuntajes.setPosition(xBotones, 270.f); // Abajo del anterior

    // Botón Instrucciones
    mSprBtnInstr.setTexture(GestorRecursos::getInstancia().getTextura("assets/boton_instrucciones.png"));
    sf::FloatRect bI = mSprBtnInstr.getLocalBounds();
    mSprBtnInstr.setOrigin(bI.width/2.f, bI.height/2.f);
    if(bI.width > 0) mSprBtnInstr.setScale(anchoBoton/bI.width, anchoBoton/bI.width);
    mSprBtnInstr.setPosition(xBotones, 340.f);

    // Botón Salir
    mSprBtnSalir.setTexture(GestorRecursos::getInstancia().getTextura("assets/boton_volver.png"));
    sf::FloatRect bS = mSprBtnSalir.getLocalBounds();
    mSprBtnSalir.setOrigin(bS.width/2.f, bS.height/2.f);
    if(bS.width > 0) mSprBtnSalir.setScale(anchoBoton/bS.width, anchoBoton/bS.width);
    mSprBtnSalir.setPosition(xBotones, 410.f);

    // ================= GRAFICOS GAME OVER =================
    mSprGameOver.setTexture(GestorRecursos::getInstancia().getTextura("assets/gameover.png"));
    sf::FloatRect bGO = mSprGameOver.getLocalBounds();
    mSprGameOver.setOrigin(bGO.width/2.f, bGO.height/2.f);
    if(bGO.width > 0) mSprGameOver.setScale(450.f/bGO.width, 450.f/bGO.width);
    mSprGameOver.setPosition(400.f, 100.f); 

    float anchoGO = 180.f;
    mSprBtnReintentar.setTexture(GestorRecursos::getInstancia().getTextura("assets/boton_reintentar.png"));
    sf::FloatRect bRe = mSprBtnReintentar.getLocalBounds();
    mSprBtnReintentar.setOrigin(bRe.width/2.f, bRe.height/2.f);
    if(bRe.width > 0) mSprBtnReintentar.setScale(anchoGO/bRe.width, anchoGO/bRe.width);
    mSprBtnReintentar.setPosition(280.f, 450.f); 

    mSprBtnVolver.setTexture(GestorRecursos::getInstancia().getTextura("assets/boton_volver.png"));
    sf::FloatRect bVol = mSprBtnVolver.getLocalBounds();
    mSprBtnVolver.setOrigin(bVol.width/2.f, bVol.height/2.f);
    if(bVol.width > 0) mSprBtnVolver.setScale(anchoGO/bVol.width, anchoGO/bVol.width);
    mSprBtnVolver.setPosition(520.f, 450.f); 
}

void Juego::ajustarVista() {
    float ratioW = mVentana.getSize().x / 800.f;
    float ratioH = mVentana.getSize().y / 600.f;
    float escala = std::min(ratioW, ratioH);
    sf::FloatRect vp;
    vp.width  = (800.f * escala) / mVentana.getSize().x;
    vp.height = (600.f * escala) / mVentana.getSize().y;
    vp.left   = (1.f - vp.width) / 2.f;
    vp.top    = (1.f - vp.height) / 2.f;
    mVista.setViewport(vp);
}

void Juego::ejecutar() {
    sf::Clock clk;
    while(mVentana.isOpen()) {
        procesarEventos();
        actualizar(clk.restart());
        renderizar();
    }
}

void Juego::procesarEventos() {
    sf::Event e;
    while(mVentana.pollEvent(e)) {
        if(e.type == sf::Event::Closed) mVentana.close();
        if(e.type == sf::Event::Resized) ajustarVista();
        
        // Input Nombre
        if (mEstado == GAMEOVER && !mNombreYaGuardado) {
            if (e.type == sf::Event::TextEntered) {
                if (e.text.unicode == 8) { 
                    if (!mNombreJugador.empty()) mNombreJugador.pop_back();
                }
                else if (e.text.unicode == 13) { 
                    if (mNombreJugador.empty()) mNombreJugador = "Jugador";
                    GestorPuntajes::guardarPuntaje(mNombreJugador, mPuntaje);
                    mNombreYaGuardado = true; 
                }
                else if (e.text.unicode < 128 && mNombreJugador.size() < 10) {
                    mNombreJugador += static_cast<char>(e.text.unicode);
                }
            }
        }

        if(e.type == sf::Event::KeyPressed) {
            if(e.key.code == sf::Keyboard::Escape) {
                if(mEstado == JUEGO || mEstado == RANKING) mEstado = MENU; else mVentana.close();
            }
            
            // MENU (4 opc)
            if(mEstado == MENU) {
                if(e.key.code == sf::Keyboard::Up) mOpcionMenu = (mOpcionMenu+3)%4;
                if(e.key.code == sf::Keyboard::Down) mOpcionMenu = (mOpcionMenu+1)%4;
                if(e.key.code == sf::Keyboard::Enter) {
                    if(mOpcionMenu==0) { reiniciar(); mEstado=JUEGO; }
                    else if(mOpcionMenu==1) { mRankingActual = GestorPuntajes::obtenerMejores(); mEstado=RANKING; }
                    else if(mOpcionMenu==2) mEstado=INSTR;
                    else mVentana.close(); 
                }
            }
            // JUEGO
            else if(mEstado == JUEGO) {
                if((e.key.code == sf::Keyboard::Space || e.key.code == sf::Keyboard::Down) && mGrua.tieneBloque()) {
                    if(auto b = mGrua.soltarBloque()) mBloques.push_back(b);
                }
            }
            // GAMEOVER
            else if(mEstado == GAMEOVER && mNombreYaGuardado) {
                if(e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Right) mOpcionGO = !mOpcionGO; 
                if(e.key.code == sf::Keyboard::Enter) {
                    if(mOpcionGO == 0) { reiniciar(); mEstado = JUEGO; } 
                    else { mEstado = MENU; }
                }
            }
            else if((mEstado == INSTR || mEstado == RANKING) && e.key.code == sf::Keyboard::Enter) mEstado=MENU;
        }
    }
}

void Juego::actualizar(sf::Time dt) {
    if(mEstado != JUEGO) return;

    float d = dt.asSeconds();
    float camY = mTorre.getTopY();
    if(camY < 500.f) mOffsetY += (500.f - camY - mOffsetY) * 5.f * d;

    mGrua.setY(-mOffsetY);
    mGrua.actualizar(d);
    
    mM_Puntos.actualizar(mPuntaje);
    mM_Vidas.actualizar(mVidas);

    for(auto it = mBloques.begin(); it != mBloques.end(); ) {
        (*it)->actualizar(d);
        if(mTorre.verificarColision(*it)) {
            mTorre.agregarBloque(*it);
            mPuntaje += 10 + (mCombo++)*5;
            it = mBloques.erase(it);
            mGrua.generarBloque();
        } 
        else if((*it)->getPosicion().y > 650.f - mOffsetY) {
            mVidas--; mCombo=0; it = mBloques.erase(it);
            if(mVidas<=0) { mEstado = GAMEOVER; mNombreJugador = ""; mNombreYaGuardado = false; } else mGrua.generarBloque();
        } 
        else ++it;
    }
}

void Juego::renderizar() {
    mVentana.clear();
    sf::View vMundo = mVista; vMundo.move(0.f, -mOffsetY); mVentana.setView(vMundo);
    sf::Sprite f = mFondo; f.setPosition(0.f, -mOffsetY); mVentana.draw(f);
    if(mEstado == JUEGO) {
        mTorre.dibujar(mVentana, true); for(auto& b : mBloques) b->dibujar(mVentana); mGrua.dibujar(mVentana);
    }
    mVentana.setView(mVista);
    
    if(mEstado == JUEGO) { mM_Puntos.dibujar(mVentana); mM_Vidas.dibujar(mVentana); }
    else {
        sf::Text t; t.setFont(GestorRecursos::getInstancia().getFuente("assets/arial.ttf"));
        
        if(mEstado == MENU) {
            mVentana.draw(mSprLogoMenu);
            mSprBtnJugar.setColor(mOpcionMenu==0 ? sf::Color::White : sf::Color(100,100,100));
            mSprBtnPuntajes.setColor(mOpcionMenu==1 ? sf::Color::White : sf::Color(100,100,100));
            mSprBtnInstr.setColor(mOpcionMenu==2 ? sf::Color::White : sf::Color(100,100,100));
            mSprBtnSalir.setColor(mOpcionMenu==3 ? sf::Color::White : sf::Color(100,100,100));
            
            mVentana.draw(mSprBtnJugar);
            mVentana.draw(mSprBtnPuntajes);
            mVentana.draw(mSprBtnInstr);
            mVentana.draw(mSprBtnSalir);
        } 
        else if(mEstado == INSTR) {
            t.setString("ESPACIO: Soltar bloque.\nENTER: Volver."); 
            t.setCharacterSize(30); t.setPosition(100, 200); t.setFillColor(sf::Color::White);
            mVentana.draw(t);
        }
        else if(mEstado == RANKING) {
            t.setString("MEJORES PUNTAJES"); t.setCharacterSize(40); t.setFillColor(sf::Color::Yellow);
            t.setPosition(200, 50); mVentana.draw(t);
            t.setCharacterSize(30); t.setFillColor(sf::Color::White);
            for(size_t i=0; i<mRankingActual.size(); ++i) {
                std::string linea = std::to_string(i+1) + ". " + mRankingActual[i].nombre + " - " + std::to_string(mRankingActual[i].puntos);
                t.setString(linea); t.setPosition(250, 150 + i*50); mVentana.draw(t);
            }
            t.setString("ENTER para volver"); t.setPosition(250, 500); t.setFillColor(sf::Color::Yellow); mVentana.draw(t);
        }
        else if(mEstado == GAMEOVER) {
            mVentana.draw(mSprGameOver);
            t.setString("Puntos: " + std::to_string(mPuntaje)); 
            t.setFillColor(sf::Color::White); t.setCharacterSize(35);
            sf::FloatRect bt = t.getLocalBounds(); t.setOrigin(bt.width/2.f, 0.f); t.setPosition(400.f, 230.f); 
            mVentana.draw(t);

            if (!mNombreYaGuardado) {
                t.setString("Ingresa tu nombre: " + mNombreJugador + "_"); 
                t.setCharacterSize(25); t.setFillColor(sf::Color::Yellow);
                sf::FloatRect bn = t.getLocalBounds(); t.setOrigin(bn.width/2.f, 0.f); t.setPosition(400.f, 300.f); 
                mVentana.draw(t);
                
                t.setString("(Presiona ENTER para guardar)"); t.setCharacterSize(20); t.setFillColor(sf::Color::White);
                sf::FloatRect ba = t.getLocalBounds(); t.setOrigin(ba.width/2.f, 0.f); t.setPosition(400.f, 340.f); 
                mVentana.draw(t);
            } else {
                if (mOpcionGO == 0) { mSprBtnReintentar.setColor(sf::Color::White); mSprBtnVolver.setColor(sf::Color(100,100,100)); } 
                else { mSprBtnReintentar.setColor(sf::Color(100,100,100)); mSprBtnVolver.setColor(sf::Color::White); }
                mVentana.draw(mSprBtnReintentar); mVentana.draw(mSprBtnVolver);
            }
        }
    }
    mVentana.display();
}

void Juego::reiniciar() {
    mVidas=3; mPuntaje=0; mCombo=0; mOffsetY=0.f;
    mBloques.clear();
    mTorre = Torre(400.f, Torre::BASE_Y);
    mGrua = Grua(400.f, 50.f);
}