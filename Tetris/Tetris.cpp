#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include "ArkaDortgen.h"
#include "Sekil.h"
std::random_device Sekil::rd;
std::mt19937 Sekil::gen(Sekil::rd());
sf::Clock Sekil::Saat;


int main()
{
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
    window.setFramerateLimit(60);
    ArkaDortgen Dortgen("dortgen.png");
    ArkaDortgen Dortgen2("dortgen.png");
    ArkaDortgen Dortgen3("dortgen.png");
    //x,y,genişlik,uzunluk
   sf::FloatRect engel=Dortgen.Ciz(200, 200, 16, 336);
    sf::FloatRect engel2=Dortgen2.Ciz(200, 536, 208, 16);
    sf::FloatRect engel3 =Dortgen3.Ciz(392, 200, 16, 336);
    
    Sekil v1("kare.png");
    
    //v1.DortgenEkle(392, 200, 16, 336);
    v1.RastgeleSekilOlustur();
    v1.VertexOlustur();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        sf::RenderStates states;
        states.texture = &Dortgen.Dosya;
        v1.hareket(engel,engel2,engel3);
        if (v1.digerSekil) {
            v1.digerSekil->hareket(engel, engel2,engel3);
            v1.digerSekil->gra(engel2);
          
        }
        
        v1.GuncelleZincir(engel, engel2, engel3);

        window.clear();
        v1.CizZincir(window);
        window.draw(Dortgen.Tile, states);
        window.draw(Dortgen2.Tile, states);
        window.draw(Dortgen3.Tile, states);

     

        // Update the window
        window.display();
    }
}