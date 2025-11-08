#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

class Sekil
{
private:
    // Static random generator - tüm Sekil örnekleri arasında paylaşılır
    static std::random_device rd;
    static std::mt19937 gen;
    static sf::Clock Saat;
    sf::Clock TusSaat;
public:
    std::string Yol;
    sf::Texture Dosya;
    sf::VertexArray Tile;
    float bloklukBoyut = 16.f;
    std::vector<std::vector <int>> matris;
    sf::Color Renk;
    float x = 250;
    float y = 100;
    std::vector<sf::VertexArray> Sekilvec;
    std::vector<sf::VertexArray> Doluvec;
    std::vector<std::vector<int>> Dolu;
        bool Tus = false;
        bool Yerdemi = false;
        float cd = 0.15f;
    Sekil(std::string x) :Yol(x), Dosya(Yol), Tile(sf::PrimitiveType::Triangles)
    {
        
        Dolu = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
    
    }
    int myrand(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }
    void DortgenEkle(float px, float py, float gen, float uz) {
        
        sf::Vertex v1; //dortgen sol ust köşe
        v1.position = { px, py };
        v1.texCoords = { 0.f,0.f };
        v1.color = Renk;
        Tile.append(v1);
        sf::Vertex v2; //dortgen sağ üst köşe
        v2.position={px+gen,py};
        v2.texCoords = {bloklukBoyut,0.f};
        v2.color = Renk;
        Tile.append(v2);
        sf::Vertex v3; //dortgen sol alt kose
        v3.position = { px,py + uz };
        v3.texCoords = {0.f,bloklukBoyut};
        v3.color = Renk;
        Tile.append(v3); //burası bir üçgen
        sf::Vertex v4;
        v4.position = { px + gen,py };
        v4.texCoords = { bloklukBoyut,0.f };
        v4.color = Renk;
        Tile.append(v4); //dortgen sağ üst 2. üçgen sağ üst köşe
        sf::Vertex v5;
        v5.position = {px+gen,py+uz};
        v5.texCoords = { bloklukBoyut,bloklukBoyut };
        v5.color = Renk;
        Tile.append(v5);
        sf::Vertex v6;
        v6.position = { px,py + uz };
        v6.texCoords = {0.f,bloklukBoyut};
        v6.color = Renk;
        Tile.append(v6);
    }
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
        Sekilvec.push_back(Tile);
    }
    void ISekilOlustur() {
        matris = {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        };
        Renk = sf::Color::Cyan;
    }

    void OSekilOlustur() {
        matris = {
            {1, 1},
            {1, 1}
        };
        Renk = sf::Color::Yellow;
    }

    void TSekilOlustur() {
        matris = {
            {0, 1, 0},
            {1, 1, 1},
            {0, 0, 0}
        };
        Renk = sf::Color::Magenta;
    }

    void SSekilOlustur() {
        matris = {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
        };
        Renk = sf::Color::Green;
    }

    void ZSekilOlustur() {
        matris = {
            {1, 1, 0},
            {0, 1, 1},
            {0, 0, 0}
        };
        Renk = sf::Color::Red;
    }

    void JSekilOlustur() {
        matris = {
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 0}
        };
        Renk = sf::Color::Blue;
    }

    void LSekilOlustur() {
        matris = {
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 0}
        };
        Renk = sf::Color(255, 165, 0); // Turuncu
    }
    void RastgeleSekilOlustur() {
        int sekilTipi = myrand(0, 6);

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
        duvar2.position.y -= 16;
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
            if (Yerdemi)return;
            if (duvar.findIntersection(Tile.getBounds())) {
                Yerdemi = true;
                //if () {  
                Isaretle();
                x = 250;
                y = 100;
                RastgeleSekilOlustur();
                VertexOlustur();
                Yerdemi = false;
                return;
                
              
            }
            y += 16.0f * zaman();
            VertexOlustur();
        }
        static float zaman() {
            return Saat.restart().asSeconds();

        }
        void Isaretle() {
            // Tile'deki her vertexi kontrol edip Dolu matrisini güncelle
            for (size_t i = 0; i < Tile.getVertexCount(); i++) {
                sf::Vector2f pos = Tile[i].position;
                int satir = static_cast<int>(pos.y / bloklukBoyut);
                int sutun = static_cast<int>(pos.x / bloklukBoyut);

                // Tahtanın sınırları içinde mi kontrol et
                if (satir >= 0 && satir < Dolu.size() && sutun >= 0 && sutun < Dolu[0].size()) {
                    Dolu[satir][sutun] = 1;
                }
            }
            for (size_t i = 0; i < Dolu.size(); i++) {
                for (size_t j = 0; j < Dolu[i].size(); j++) {
                    if (Dolu[i][j] == 1) {
                        DortgenEkle(
                            x + j * bloklukBoyut,
                            y + i * bloklukBoyut,
                            bloklukBoyut,
                            bloklukBoyut
                        );
                    }
                }
            }
            Doluvec.push_back(Tile);
          
        }

};