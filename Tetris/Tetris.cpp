#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "ArkaDortgen.h"
#include "Sekil.h"
std::random_device Sekil::rd;
std::mt19937 Sekil::gen(Sekil::rd());
sf::Clock Sekil::Saat;
std::vector<Sekil> SekilListesi;

int main()
{
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
    window.setFramerateLimit(60);
    ArkaDortgen Dortgen("dortgen.png");
    ArkaDortgen Dortgen2("dortgen.png");
    ArkaDortgen Dortgen3("dortgen.png");
    sf::FloatRect engel = Dortgen.Ciz(200, 200, 16, 336);
    sf::FloatRect engel2 = Dortgen2.Ciz(200, 536, 208, 16);
    sf::FloatRect engel3 = Dortgen3.Ciz(392, 200, 16, 336);
    Sekil s1("kare.png");
    s1.RastgeleSekilOlustur();
    s1.VertexOlustur();
  
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
        
        s1.hareket(engel, engel2,engel3);
        s1.gra(engel2);
        window.clear();
        for (auto s : s1.Sekilvec) {
            
            window.draw(s);
            s1.Sekilvec.clear();
        }
        for (auto s : s1.Doluvec) {
            
            window.draw(s);

        }
       // window.draw(s1.Tile);
       // window.draw(s1.Sekilvec.back());
       // window.draw(s1.DoluVer);
         window.draw(Dortgen.Tile, states);
        window.draw(Dortgen2.Tile, states);
        window.draw(Dortgen3.Tile, states);
        

     
   
        // Update the window
        window.display();
    }
}