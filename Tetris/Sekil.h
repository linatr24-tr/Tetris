#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

class Sekil
{
private:
    // Static random generator - tüm Sekil örnekleri arasýnda paylaþýlýr
    static std::random_device rd;
    static std::mt19937 gen;
    static sf::Clock Saat;
    sf::Clock TusSaat;

public:
    
    std::string Yol;
    sf::VertexArray Tile;
    sf::Texture Dosya;
    std::vector<std::vector<int>> matris;
    float bloklukBoyut = 16.f;
    float x = 250;
    float y = 100;
    sf::Color renk;
    float cd = 0.15f;
    bool Tus = false;
    bool Yerdemi = false;
    std::unique_ptr<Sekil> digerSekil;

    Sekil(const std::string& x):Yol(x), Tile(sf::PrimitiveType::Triangles),
        Dosya(Yol)
    {

    }
    // Matrisi VertexArray'e çevir
    void VertexOlustur() {
        Tile.clear();

        for (size_t i = 0; i < matris.size(); i++) {
            for (size_t j = 0; j < matris[i].size(); j++) {
                if (matris[i][j] == 1) {
                    DortgenEkle(
                        x + j * bloklukBoyut,
                        y + i * bloklukBoyut,
                        bloklukBoyut,
                        bloklukBoyut
                    );
                }
            }
        }
    }
    void DortgenEkle(float px, float py, float genislik, float yukseklik) {
        // Ýlk üçgen
        sf::Vertex v1;
        v1.position = { px, py };
        v1.texCoords = { 0.f, 0.f };
        v1.color = renk;
        Tile.append(v1);

        sf::Vertex v2;
        v2.position = { px + genislik, py };
        v2.texCoords = { bloklukBoyut, 0.f };
        v2.color = renk;
        Tile.append(v2);

        sf::Vertex v3;
        v3.position = { px, py + yukseklik };
        v3.texCoords = { 0.f, bloklukBoyut };
        v3.color = renk;
        Tile.append(v3);

        // Ýkinci üçgen
        sf::Vertex v4;
        v4.position = { px + genislik, py };
        v4.texCoords = { bloklukBoyut, 0.f };
        v4.color = renk;
        Tile.append(v4);

        sf::Vertex v5;
        v5.position = { px + genislik, py + yukseklik };
        v5.texCoords = { bloklukBoyut, bloklukBoyut };
        v5.color = renk;
        Tile.append(v5);

        sf::Vertex v6;
        v6.position = { px, py + yukseklik };
        v6.texCoords = { 0.f, bloklukBoyut };
        v6.color = renk;
        Tile.append(v6);
    }
    void ISekilOlustur() {
        matris = {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        };
        renk = sf::Color::Cyan;
    }

    void OSekilOlustur() {
        matris = {
            {1, 1},
            {1, 1}
        };
        renk = sf::Color::Yellow;
    }

    void TSekilOlustur() {
        matris = {
            {0, 1, 0},
            {1, 1, 1},
            {0, 0, 0}
        };
        renk = sf::Color::Magenta;
    }

    void SSekilOlustur() {
        matris = {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
        };
        renk = sf::Color::Green;
    }

    void ZSekilOlustur() {
        matris = {
            {1, 1, 0},
            {0, 1, 1},
            {0, 0, 0}
        };
        renk = sf::Color::Red;
    }

    void JSekilOlustur() {
        matris = {
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 0}
        };
        renk = sf::Color::Blue;
    }

    void LSekilOlustur() {
        matris = {
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 0}
        };
        renk = sf::Color(255, 165, 0); // Turuncu
    }
    static int RastgeleSayi(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }
    void Ciz(sf::RenderWindow& window) {
      
       
            sf::RenderStates states;
            states.texture = &Dosya;
            window.draw(Tile, states);

         
        
    }
    void RastgeleSekilOlustur() {
        int sekilTipi = RastgeleSayi(0, 6);

        switch (sekilTipi) {
        case 0: ISekilOlustur(); break;
        case 1: OSekilOlustur(); break;
        case 2: TSekilOlustur(); break;
        case 3: SSekilOlustur(); break;
        case 4: ZSekilOlustur(); break;
        case 5: JSekilOlustur(); break;
        case 6: LSekilOlustur(); break;
        default: ISekilOlustur(); break;
        }
    }
    void hareket(sf::FloatRect duvar, sf::FloatRect duvar2, sf::FloatRect duvar3) {
        TusCd();
        if (Yerdemi) return;
        if (Tus) return;
        duvar.position.x += 16;
        duvar2.position.y -=16 ;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (duvar.findIntersection(Tile.getBounds())) return;
            Tus = true;
            TusSaat.restart();
            x -= 16.0f;
            VertexOlustur();
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            Tus = true;
            TusSaat.restart();
           // duvar3.position.x -= 16;
            if (duvar3.findIntersection(Tile.getBounds())) return;
            x += 16.0f;
            VertexOlustur();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            Tus = true;
            TusSaat.restart();
            if (duvar2.findIntersection(Tile.getBounds())) return;
            y += 16.0f;
            VertexOlustur();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            Tus = true;
            TusSaat.restart();
            Dondur();
            return; // Dönme iþleminden sonra diðer tuþlarý kontrol etme
        }
        
    }
   static float zaman() {
        return Saat.restart().asSeconds();

    }
    void TusCd() {
        if (Tus) {
            // Kaç saniye geçtiðini kontrol et
            if (TusSaat.getElapsedTime().asSeconds() >= cd) {
                Tus = false;         // 2 saniye geçti, devre dýþý býrak
                TusSaat.restart();  // sayaç sýfýrlanýr
            }
        }
    }
    void gra(sf::FloatRect duvar) {
        if (duvar.findIntersection(Tile.getBounds())) {
            Yerdemi = true;
            if (!digerSekil) { yeni(); }
            return;
        }
        y += 16.0f*zaman() ;
        VertexOlustur();
    }
    void carp(const sf::FloatRect& duvar) {
        if (duvar.findIntersection(Tile.getBounds()))
            x +=16;
    }
    void yeni() {
        
        if (Yerdemi && !digerSekil) { // sadece bir kere oluþtur
            Yerdemi = false;
            digerSekil = std::make_unique<Sekil>("kare.png");
            digerSekil->RastgeleSekilOlustur();
            digerSekil->VertexOlustur();
            
        }
    }
    void GuncelleZincir(sf::FloatRect duvar, sf::FloatRect duvar2, sf::FloatRect duvar3) {
        hareket(duvar, duvar2, duvar3);
        gra(duvar2);

        if (digerSekil) {
            digerSekil->GuncelleZincir(duvar, duvar2, duvar3);
        }
    }

    void CizZincir(sf::RenderWindow& window) {
        Ciz(window);
        if (digerSekil) {
            digerSekil->CizZincir(window);
        }
    }
    void Dondur() {
        if (Yerdemi) return; // Yerdeyse dönmesin

        int satir = matris.size();
        int sutun = matris[0].size();

        // Yeni matris oluþtur (90 derece saat yönünde döndürme için)
        std::vector<std::vector<int>> yeniMatris(sutun, std::vector<int>(satir));

        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                yeniMatris[j][satir - 1 - i] = matris[i][j];
            }
        }

        matris = yeniMatris;
        VertexOlustur();
    }

};

