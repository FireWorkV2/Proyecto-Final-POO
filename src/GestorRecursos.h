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
        if (texturas.find(archivo) == texturas.end()) {
            auto tex = std::make_unique<sf::Texture>();
            if (!tex->loadFromFile(archivo)) std::cerr << "Fallo textura: " << archivo << "\n";
            texturas[archivo] = std::move(tex);
        }
        return *texturas[archivo];
    }

    sf::Font& getFuente(const std::string& archivo) {
        if (fuentes.find(archivo) == fuentes.end()) {
            auto font = std::make_unique<sf::Font>();
            if (!font->loadFromFile(archivo)) std::cerr << "Fallo fuente: " << archivo << "\n";
            fuentes[archivo] = std::move(font);
        }
        return *fuentes[archivo];
    }

private:
    GestorRecursos() {}
    std::map<std::string, std::unique_ptr<sf::Texture>> texturas;
    std::map<std::string, std::unique_ptr<sf::Font>> fuentes;
};

#endif