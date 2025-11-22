#include "Juego.h"
#include "GestorRecursos.h"
#include <cmath>

Juego::Juego()
    : mVentana(sf::VideoMode(800, 600), "UNL BLOXX (Alpha Version)")
    , mEstado(EstadoJuego::MENU)
    , mMarcadorPuntaje(20.f, 20.f, sf::Color::Yellow, sf::Color::Black, sf::Color(100, 255, 100))
    , mMarcadorVidas(620.f, 20.f, sf::Color::Red, sf::Color::Black, sf::Color(255, 50, 50), "assets/vida.png")
    , mGrua(400.f, 50.f)
    , mTorre(400.f, Torre::BASE_Y)
    , mOpcionSeleccionada(0)
    , mOpcionGameOverSeleccionada(0)
    , mVidas(3), mPuntaje(0), mCombo(0), mPoblacion(0), mOffsetY(0.f)
{
    mVentana.setFramerateLimit(60);
    mFondo.setTexture(GestorRecursos::getInstancia().getTextura("assets/fondo.png"));
    sf::Vector2u size = mFondo.getTexture()->getSize();
    mFondo.setScale(800.f / size.x, 600.f / size.y);

    mOpcionesMenu = {"Jugar", "Instrucciones", "Salir"};
    mOpcionesGameOver = {"Volver a jugar", "Volver al menu principal"};
}

void Juego::ejecutar() {
    sf::Clock reloj;
    while (mVentana.isOpen()) {
        sf::Time dt = reloj.restart();
        procesarEventos();
        actualizar(dt);
        renderizar();
    }
}

void Juego::procesarEventos() {
    sf::Event evento;
    while (mVentana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) mVentana.close();
        if (evento.type == sf::Event::KeyPressed) manejarEntrada(evento.key.code, true);
    }
}

void Juego::manejarEntrada(sf::Keyboard::Key tecla, bool presionado) {
    if (tecla == sf::Keyboard::Escape) {
        mEstado = (mEstado == EstadoJuego::JUGANDO) ? EstadoJuego::MENU : mEstado;
        if (mEstado != EstadoJuego::MENU) mVentana.close();
        return;
    }

    if (mEstado == EstadoJuego::MENU) {
        if (tecla == sf::Keyboard::Up) mOpcionSeleccionada = (mOpcionSeleccionada + 2) % 3;
        else if (tecla == sf::Keyboard::Down) mOpcionSeleccionada = (mOpcionSeleccionada + 1) % 3;
        else if (tecla == sf::Keyboard::Enter) {
            if (mOpcionSeleccionada == 0) { reiniciarJuego(); mEstado = EstadoJuego::JUGANDO; }
            else if (mOpcionSeleccionada == 1) mEstado = EstadoJuego::INSTRUCCIONES;
            else mVentana.close();
        }
    } else if (mEstado == EstadoJuego::INSTRUCCIONES) {
        if (tecla == sf::Keyboard::Enter || tecla == sf::Keyboard::Escape) mEstado = EstadoJuego::MENU;
    } else if (mEstado == EstadoJuego::JUGANDO) {
        if ((tecla == sf::Keyboard::Space || tecla == sf::Keyboard::Down) && mBloquesCayendo.empty() && mGrua.tieneBloque()) {
            if (auto bloque = mGrua.soltarBloque()) mBloquesCayendo.push_back(bloque);
        }
    } else if (mEstado == EstadoJuego::GAME_OVER) {
        if (tecla == sf::Keyboard::Up) mOpcionGameOverSeleccionada = (mOpcionGameOverSeleccionada + 1) % 2;
        else if (tecla == sf::Keyboard::Down) mOpcionGameOverSeleccionada = (mOpcionGameOverSeleccionada + 1) % 2;
        else if (tecla == sf::Keyboard::Enter) {
            if (mOpcionGameOverSeleccionada == 0) { reiniciarJuego(); mEstado = EstadoJuego::JUGANDO; }
            else mEstado = EstadoJuego::MENU;
        }
    }
}

void Juego::actualizar(sf::Time dt) {
    float delta = dt.asSeconds();
    if (mEstado == EstadoJuego::JUGANDO) {
        // Cámara
        float tope = mTorre.getTopY();
        if (tope < 500.f) mOffsetY += (500.f - tope - mOffsetY) * 10.f * delta;

        mMarcadorPuntaje.actualizar(mPuntaje);
        mMarcadorVidas.actualizar(mVidas);

        mGrua.setY(-mOffsetY); 
        mGrua.actualizar(delta);
        // mTorre.actualizar(delta); // Eliminado: no hacía nada

        for (auto it = mBloquesCayendo.begin(); it != mBloquesCayendo.end(); ) {
            (*it)->actualizar(delta);
            if (mTorre.verificarColision(*it)) {
                mTorre.agregarBloque(*it);
                mPuntaje += 10 + mCombo * 5;
                mCombo++;
                it = mBloquesCayendo.erase(it);
                mGrua.generarBloque();
            } else if ((*it)->getPosicion().y > 650.f - mOffsetY) {
                mVidas--; mCombo = 0;
                it = mBloquesCayendo.erase(it);
                if (mVidas <= 0) mEstado = EstadoJuego::GAME_OVER;
                else mGrua.generarBloque();
            } else {
                ++it;
            }
        }
    }
}

void Juego::renderizar() {
    mVentana.clear();
    sf::View vista = mVentana.getDefaultView();
    vista.move(0.f, -mOffsetY);
    mVentana.setView(vista);

    sf::Sprite fondo = mFondo;
    fondo.setPosition(0.f, -mOffsetY);
    mVentana.draw(fondo);

    if (mEstado == EstadoJuego::JUGANDO) {
        mTorre.dibujar(mVentana, true);
        for (auto& b : mBloquesCayendo) b->dibujar(mVentana);
        mGrua.dibujar(mVentana);
    }

    mVentana.setView(mVentana.getDefaultView()); // HUD

    if (mEstado == EstadoJuego::JUGANDO) {
        mMarcadorPuntaje.dibujar(mVentana);
        mMarcadorVidas.dibujar(mVentana);
        // Barra de combo eliminada
    }

    if (mEstado != EstadoJuego::JUGANDO) {
        sf::Text t; t.setFont(GestorRecursos::getInstancia().getFuente("assets/arial.ttf")); t.setFillColor(sf::Color::White);
        if (mEstado == EstadoJuego::MENU) {
            t.setString("UNL BLOXX (Alpha Version)"); t.setCharacterSize(48); t.setPosition(180, 80); mVentana.draw(t);
            t.setCharacterSize(36);
            for (size_t i = 0; i < mOpcionesMenu.size(); ++i) {
                t.setString(mOpcionesMenu[i]); t.setFillColor(i == mOpcionSeleccionada ? sf::Color::Yellow : sf::Color::White);
                t.setPosition(260, 200 + 60 * i); mVentana.draw(t);
            }
        } else if (mEstado == EstadoJuego::INSTRUCCIONES) {
            t.setString("Instrucciones:\n\n- ESPACIO: Soltar bloque.\n- Apila recto para combos.\nENTER/ESC volver.");
            t.setCharacterSize(28); t.setPosition(60, 120); mVentana.draw(t);
        } else if (mEstado == EstadoJuego::GAME_OVER) {
            t.setString("GAME OVER"); t.setCharacterSize(52); t.setFillColor(sf::Color::Red); t.setPosition(240, 100); mVentana.draw(t);
            t.setString("Puntaje: " + std::to_string(mPuntaje)); t.setCharacterSize(32); t.setFillColor(sf::Color::White); t.setPosition(260, 180); mVentana.draw(t);
            t.setCharacterSize(36);
            for (size_t i = 0; i < mOpcionesGameOver.size(); ++i) {
                t.setString(mOpcionesGameOver[i]); t.setFillColor(i == mOpcionGameOverSeleccionada ? sf::Color::Yellow : sf::Color::White);
                t.setPosition(200, 280 + 60 * i); mVentana.draw(t);
            }
        }
    }
    mVentana.display();
}

void Juego::reiniciarJuego() {
    mVidas = 3; mPuntaje = 0; mCombo = 0; mPoblacion = 0; mOffsetY = 0.f;
    mTorre = Torre(400.f, Torre::BASE_Y);
    mGrua = Grua(400.f, 50.f);
    mBloquesCayendo.clear();
    mMarcadorPuntaje.actualizar(0);
    mMarcadorVidas.actualizar(3);
}