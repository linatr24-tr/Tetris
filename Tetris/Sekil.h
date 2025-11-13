#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

class Sekil
{
private:
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
    float x = 216;
    float y = 100;
    std::vector<sf::VertexArray> Sekilvec;
    std::vector<sf::VertexArray> Doluvec;
    std::vector<std::vector<int>> Dolu;

    bool Tus = false;
    bool Yerdemi = false;
    float cd = 0.2f;

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
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
    }

    // ÖNEMLİ: Belirtilen pozisyondaki blok bounds'larını hesapla
    std::vector<sf::FloatRect> BlokBoundslariniGetir(float offsetX = 0, float offsetY = 0) const {
        std::vector<sf::FloatRect> bloklar;

        for (size_t i = 0; i < matris.size(); i++) {
            for (size_t j = 0; j < matris[i].size(); j++) {
                if (matris[i][j] == 1) {
                    float blokX = x + offsetX + j * (bloklukBoyut + 1);
                    float blokY = y + offsetY + i * (bloklukBoyut + 1);

                    sf::FloatRect blokBounds({ blokX, blokY }, { bloklukBoyut, bloklukBoyut });
                    bloklar.push_back(blokBounds);
                }
            }
        }

        return bloklar;
    }

    // Geliştirilmiş çarpışma kontrolü - offset parametreli
    bool CarpismaKontrol(const std::vector<sf::FloatRect>& engeller, float offsetX = 0, float offsetY = 0) const {
        std::vector<sf::FloatRect> benimBloklarim = BlokBoundslariniGetir(offsetX, offsetY);

        for (const auto& benimBlok : benimBloklarim) {
            for (const auto& engel : engeller) {
                if (benimBlok.findIntersection(engel).has_value()) {
                    return true; // Çarpışma var
                }
            }
        }

        return false; // Çarpışma yok
    }

    int myrand(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }

    void DortgenEkle(float px, float py, float gen, float uz) {
        sf::Vertex v1;
        v1.position = { px, py };
        v1.texCoords = { 0.f,0.f };
        v1.color = Renk;
        Tile.append(v1);

        sf::Vertex v2;
        v2.position = { px + gen,py };
        v2.texCoords = { bloklukBoyut,0.f };
        v2.color = Renk;
        Tile.append(v2);

        sf::Vertex v3;
        v3.position = { px,py + uz };
        v3.texCoords = { 0.f,bloklukBoyut };
        v3.color = Renk;
        Tile.append(v3);

        sf::Vertex v4;
        v4.position = { px + gen,py };
        v4.texCoords = { bloklukBoyut,0.f };
        v4.color = Renk;
        Tile.append(v4);

        sf::Vertex v5;
        v5.position = { px + gen,py + uz };
        v5.texCoords = { bloklukBoyut,bloklukBoyut };
        v5.color = Renk;
        Tile.append(v5);

        sf::Vertex v6;
        v6.position = { px,py + uz };
        v6.texCoords = { 0.f,bloklukBoyut };
        v6.color = Renk;
        Tile.append(v6);
    }

    void VertexOlustur() {
        Tile.clear();
        Sekilvec.clear();

        for (size_t i = 0; i < matris.size(); i++) {
            for (size_t j = 0; j < matris[i].size(); j++) {
                if (matris[i][j] == 1) {
                    DortgenEkle(
                        x + j * (bloklukBoyut + 1),
                        y + i * (bloklukBoyut + 1),
                        bloklukBoyut,
                        bloklukBoyut
                    );
                }
            }
        }
        Sekilvec.push_back(Tile);
    }

    void ISekilOlustur() {
        matris = { {1}, {1}, {1}, {1} };
        Renk = sf::Color::Cyan;
    }

    void OSekilOlustur() {
        matris = { {1, 1}, {1, 1} };
        Renk = sf::Color::Yellow;
    }

    void TSekilOlustur() {
        matris = { {0, 1, 0}, {1, 1, 1} };
        Renk = sf::Color::Magenta;
    }

    void SSekilOlustur() {
        matris = { {0, 1, 1}, {1, 1, 0} };
        Renk = sf::Color::Green;
    }

    void ZSekilOlustur() {
        matris = { {1, 1, 0}, {0, 1, 1} };
        Renk = sf::Color::Red;
    }

    void JSekilOlustur() {
        matris = { {1, 0, 0}, {1, 1, 1} };
        Renk = sf::Color::Blue;
    }

    void LSekilOlustur() {
        matris = { {0, 0, 1}, {1, 1, 1} };
        Renk = sf::Color(255, 165, 0);
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

    void hareket() {
        TusCd();
        if (Yerdemi) return;
        if (Tus) return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            Tus = true;
            TusSaat.restart();
            // ÖNCESİNDE kontrol et
            // NOT: Doluvec'i de kontrol etmek için main'den geçirmelisiniz
            x -= 17.0f;
            VertexOlustur();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            Tus = true;
            TusSaat.restart();
            x += 17.0f;
            VertexOlustur();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            Tus = true;
            TusSaat.restart();
            if (Yerdemi) return;
            y += 17.0f;
            VertexOlustur();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            Tus = true;
            TusSaat.restart();
            Dondur();
            return;
        }
    }

    // YENİ: Tüm engelleri kabul eden hareket fonksiyonu
    void hareketGuvenlı(const std::vector<sf::FloatRect>& duvarlar,
        const std::vector<sf::VertexArray>& doluBloklar) {
        TusCd();
        if (Yerdemi || Tus) return;

        // Tüm engelleri birleştir
        std::vector<sf::FloatRect> tumEngeller = duvarlar;
        for (const auto& va : doluBloklar) {
            tumEngeller.push_back(va.getBounds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            // Sol hareket kontrol
            if (!CarpismaKontrol(tumEngeller, -17.0f, 0)) {
                x -= 17.0f;
                VertexOlustur();
            }
            Tus = true;
            TusSaat.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            // Sağ hareket kontrol
            if (!CarpismaKontrol(tumEngeller, 17.0f, 0)) {
                x += 17.0f;
                VertexOlustur();
            }
            Tus = true;
            TusSaat.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            // Aşağı hareket kontrol
            if (!CarpismaKontrol(tumEngeller, 0, 17.0f)) {
                y += 17.0f;
                VertexOlustur();
            }
            Tus = true;
            TusSaat.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            DondurGuvenlı(tumEngeller);
            Tus = true;
            TusSaat.restart();
        }
    }

    void Dondur() {
        if (Yerdemi) return;

        int satir = matris.size();
        int sutun = matris[0].size();

        std::vector<std::vector<int>> yeniMatris(sutun, std::vector<int>(satir));

        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                yeniMatris[j][satir - 1 - i] = matris[i][j];
            }
        }

        matris = yeniMatris;
        VertexOlustur();
    }

    // YENİ: Güvenli dönüş
    void DondurGuvenlı(const std::vector<sf::FloatRect>& engeller) {
        if (Yerdemi) return;

        // Eski matrisi sakla
        auto eskiMatris = matris;

        int satir = matris.size();
        int sutun = matris[0].size();

        std::vector<std::vector<int>> yeniMatris(sutun, std::vector<int>(satir));

        for (int i = 0; i < satir; i++) {
            for (int j = 0; j < sutun; j++) {
                yeniMatris[j][satir - 1 - i] = matris[i][j];
            }
        }

        matris = yeniMatris;

        // Döndükten sonra çarpışma kontrolü
        if (CarpismaKontrol(engeller, 0, 0)) {
            // Çarpışma varsa geri al
            matris = eskiMatris;
        }

        VertexOlustur();
    }

    void TusCd() {
        if (Tus) {
            if (TusSaat.getElapsedTime().asSeconds() >= cd) {
                Tus = false;
                TusSaat.restart();
            }
        }
    }

    // YENİ: Blok bazlı çarpışma ile gra - gelecek pozisyonu kontrol eder
    void gra(std::vector<sf::FloatRect> duvar) {
        if (Yerdemi) return;

        float deltaY = 17.0f * zaman();

        // GELECEKTEKİ pozisyonu kontrol et
        if (CarpismaKontrol(duvar, 0, deltaY)) {
            Yerdemi = true;
            Isaretle();
            RastgeleSekilOlustur();
            VertexOlustur();
            Yerdemi = false;
            return;
        }

        // Güvenliyse hareket et
        y += deltaY;
        VertexOlustur();
    }

    static float zaman() {
        return Saat.restart().asSeconds();
    }

    void Isaretle() {
        for (size_t i = 0; i < matris.size(); i++) {
            for (size_t j = 0; j < matris[i].size(); j++) {
                if (matris[i][j] == 1) {
                    float blokX = x + j * (bloklukBoyut + 1);
                    float blokY = y + i * (bloklukBoyut + 1);

                    int satir = static_cast<int>((blokY - 100) / (bloklukBoyut + 1));
                    int sutun = static_cast<int>((blokX - 200) / (bloklukBoyut + 1));

                    if (satir >= 0 && satir < Dolu.size() &&
                        sutun >= 0 && sutun < Dolu[0].size()) {
                        Dolu[satir][sutun] = 1;
                    }
                }
            }
        }
        
        Doluvec.push_back(Tile);
        for (auto& vertexArray : Doluvec) {
            for (size_t i = 0; i < vertexArray.getVertexCount(); i++) {
                vertexArray[i].color = sf::Color::White;
            }
        }
           
        x = 216;
        y = 100;
    }

    // YENİ: Blok bazlı çarpma
    void Carp(sf::FloatRect engel) {
        std::vector<sf::FloatRect> benimBloklar = BlokBoundslariniGetir();

        for (const auto& blok : benimBloklar) {
            if (blok.findIntersection(engel).has_value()) {
                Yerdemi = true;
                Isaretle();
                RastgeleSekilOlustur();
                VertexOlustur();
                Yerdemi = false;
                return;
            }
        }
    }

    void Sil() {
        for (size_t i = 0; i < Dolu.size(); i++) {
            bool satirDolu = true;
            for (size_t j = 0; j < Dolu[i].size(); j++) {
                if (Dolu[i][j] != 1) {
                    satirDolu = false;
                    break;
                }
            }
            if (satirDolu) {
                std::cout << "Tam dolu satır: " << i << std::endl;
            }
        }
    }

    // YENİ: Yan çarpışma kontrolü
    bool yan(std::vector<sf::FloatRect> duvar) {
        if (Yerdemi) return true;
        return CarpismaKontrol(duvar);
    }
};