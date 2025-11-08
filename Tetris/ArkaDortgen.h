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
	float resG = 32.f;
	float resY = 32.f;
    sf::FloatRect engel;
    

	ArkaDortgen(const std::string& x) :DosyaYol(x),Dosya(DosyaYol),
		Resim(Dosya), Tile(sf::PrimitiveType::Triangles)
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


};

