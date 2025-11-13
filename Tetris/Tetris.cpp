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

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
    window.setFramerateLimit(60);

    ArkaDortgen Dortgen("dortgen.png");
    sf::FloatRect engel = Dortgen.Ciz(200, 200, 16, 336);

    Sekil s1("kare.png");
    s1.RastgeleSekilOlustur();
    s1.VertexOlustur();
    Dortgen.VertexOlustur();
    Dortgen.Hesapla();
    Dortgen.HesaplaYan();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // TÜM ENGELLERE KARŞI KONTROL
        std::vector<sf::FloatRect> tumEngeller = Dortgen.Engel;
        tumEngeller.insert(tumEngeller.end(), Dortgen.Engel2.begin(), Dortgen.Engel2.end());

        // Dolu blokları da ekle
        for (const auto& doluBlok : s1.Doluvec) {
            // Her dolu şeklin bloklarını ayrı ayrı ekle
            for (size_t i = 0; i < doluBlok.getVertexCount(); i += 6) {
                if (i + 5 < doluBlok.getVertexCount()) {
                    sf::Vector2f pos = doluBlok[i].position;
                    tumEngeller.push_back(sf::FloatRect({ pos.x, pos.y }, { 16, 16 }));
                }
            }
        }

        // GÜVENLİ hareket fonksiyonunu kullan
        s1.hareketGuvenlı(tumEngeller, s1.Doluvec);

        // Gravity - engelleri geç
        s1.gra(tumEngeller);

        s1.Sil();

        window.clear();

        // Çizim
        if (!s1.Sekilvec.empty()) {
            window.draw(s1.Sekilvec.back());
        }

        for (const auto& s : s1.Doluvec) {
            window.draw(s);
        }

        for (const auto& s : Dortgen.Sekilvec) {
            window.draw(s);
        }

        window.display();
    }
}