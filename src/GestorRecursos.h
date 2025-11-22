#ifndef GESTORRECURSOS_H
#define GESTORRECURSOS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>
#include <iostream>

class GestorRecursos {
public:
    static GestorRecursos& getInstancia() {
        static GestorRecursos instancia;
        return instancia;
    }

    sf::Texture& getTextura(const std::string& archivo) {
        auto& mapa = getInstancia().texturas;
        auto it = mapa.find(archivo);
        if (it != mapa.end()) {
            return *it->second;
        }

        auto textura = std::make_unique<sf::Texture>();
        if (!textura->loadFromFile(archivo)) {
            std::cerr << "Error cargando textura: " << archivo << std::endl;
            // Retorna una textura vacía temporal para no crashear, pero saldrá error en consola
            static sf::Texture texturaError;
            return texturaError;
        }

        mapa[archivo] = std::move(textura);
        return *mapa[archivo];
    }

    sf::Font& getFuente(const std::string& archivo) {
        auto& mapa = getInstancia().fuentes;
        auto it = mapa.find(archivo);
        if (it != mapa.end()) {
            return *it->second;
        }

        auto fuente = std::make_unique<sf::Font>();
        if (!fuente->loadFromFile(archivo)) {
            std::cerr << "Error cargando fuente: " << archivo << std::endl;
            static sf::Font fuenteError;
            return fuenteError;
        }

        mapa[archivo] = std::move(fuente);
        return *mapa[archivo];
    }

private:
    GestorRecursos() {}
    std::map<std::string, std::unique_ptr<sf::Texture>> texturas;
    std::map<std::string, std::unique_ptr<sf::Font>> fuentes;
};

#endif // GESTORRECURSOS_H