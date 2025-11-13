#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class ArkaDortgen
{
public:
	std::string DosyaYol;
	sf::Texture Dosya;
	sf::Sprite Resim;
	sf::VertexArray Tile;
    sf::VertexArray Tilee;
	float resG = 32.f;
	float resY = 32.f;
    sf::FloatRect engel;
    sf::Color Renk = sf::Color::Blue;
    float bloklukBoyut = 16;
    float x = 200;
    float y = 100;
    std::vector<sf::VertexArray> Sekilvec;
    std::vector<sf::FloatRect> Engel;
    std::vector<sf::FloatRect> Engel2;
    int ax = 2;
    int ay = 3;
    unsigned char matris[21][12] = {
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };


	ArkaDortgen(const std::string& x) :DosyaYol(x),Dosya(DosyaYol),
		Resim(Dosya), Tilee(sf::PrimitiveType::Triangles)
	{
        if (Dosya.getSize().x == 0 && Dosya.getSize().y == 0) {
            std::cout << "Dosya yuklenmemis!" << std::endl;
        }
	}
    sf::FloatRect Ciz(float x, float y, float genislik, float yukseklik) {
        // Texture boyutlarý (32x32 varsayýyoruz)
        engel.position.x = x;
        engel.position.y = y;
        engel.size.x = genislik;
        engel.size.y = yukseklik;
        
        // Ýlk üçgen (sol üst, sað üst, sol alt)
        sf::Vertex v1;
        v1.position = { x, y };
        v1.texCoords = { 0.f, 0.f };
        Tile.append(v1);

        sf::Vertex v2;
        v2.position = { x + genislik, y };
        v2.texCoords = { resG, 0.f };
        Tile.append(v2);

        sf::Vertex v3;
        v3.position = { x, y + yukseklik };
        v3.texCoords = { 0.f, resY };
        Tile.append(v3);

        // Ýkinci üçgen (sað üst, sað alt, sol alt)
        sf::Vertex v4;
        v4.position = { x + genislik, y };
        v4.texCoords = { resG, 0.f };
        Tile.append(v4);

        sf::Vertex v5;
        v5.position = { x + genislik, y + yukseklik };
        v5.texCoords = { resG, resY };
        Tile.append(v5);

        sf::Vertex v6;
        v6.position = { x, y + yukseklik };
        v6.texCoords = { 0.f, resY };
        Tile.append(v6);
        return engel;
    }
    void GridEkle(float px, float py, float gen, float uz) {

        sf::Vertex v1; //dortgen sol ust köþe
        v1.position = { px, py };
        v1.texCoords = { 0.f,0.f };
        v1.color = Renk;
        Tilee.append(v1);
        sf::Vertex v2; //dortgen sað üst köþe
        v2.position = { px + gen,py };
        v2.texCoords = { bloklukBoyut,0.f };
        v2.color = Renk;
        Tilee.append(v2);
        sf::Vertex v3; //dortgen sol alt kose
        v3.position = { px,py + uz };
        v3.texCoords = { 0.f,bloklukBoyut };
        v3.color = Renk;
        Tilee.append(v3); //burasý bir üçgen
        sf::Vertex v4;
        v4.position = { px + gen,py };
        v4.texCoords = { bloklukBoyut,0.f };
        v4.color = Renk;
        Tilee.append(v4); //dortgen sað üst 2. üçgen sað üst köþe
        sf::Vertex v5;
        v5.position = { px + gen,py + uz };
        v5.texCoords = { bloklukBoyut,bloklukBoyut };
        v5.color = Renk;
        Tilee.append(v5);
        sf::Vertex v6;
        v6.position = { px,py + uz };
        v6.texCoords = { 0.f,bloklukBoyut };
        v6.color = Renk;
        Tilee.append(v6);
    }
    void VertexOlustur() {
        
        Tilee.clear();


        for (size_t i = 0; i < 21; i++) {
            for (size_t j = 0; j < 12; j++) {
                if (matris[i][j] == 1) {
                    
                    GridEkle(
                        x + j * (bloklukBoyut+1),
                        y + i * (bloklukBoyut+1),
                        bloklukBoyut,
                        bloklukBoyut
                    );
                }
            }
        }
        
        Sekilvec.push_back(Tilee);
    }
   void Hesapla() {
       for (size_t i = 0; i < 21; i++) {
           for (size_t j = 0; j < 12; j++) {
               if (j == 0) continue;
               if (j == 12) continue;
               if (matris[i][j] == 1) {
                   
                   float px = x + static_cast<float>(j) * (bloklukBoyut + 1);
                   float py = y + static_cast<float>(i) * (bloklukBoyut + 1);
                   sf::FloatRect x({ px, py }, { bloklukBoyut, bloklukBoyut });
                   Engel.push_back(x);
               }
           }
       }
    }
   void HesaplaYan() {
       for (size_t i = 0; i < 21; i++) {
           for (size_t j = 0; j < 12; j++) {
               if (j == 0) {
                   if (matris[i][j] == 1) {

                       float px = x + static_cast<float>(j) * (bloklukBoyut + 1);
                       float py = y + static_cast<float>(i) * (bloklukBoyut + 1);
                       sf::FloatRect x({ px, py }, { bloklukBoyut, bloklukBoyut });
                       Engel2.push_back(x);
                   }
               }
           }
       }
   }
  

};

