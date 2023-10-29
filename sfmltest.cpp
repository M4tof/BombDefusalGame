#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main() {
    // create the window
    sf::Texture textura;
    if (!textura.loadFromFile("./images/Normal.png")) {
        std::cout << "ERROR" << std::endl;
        return -1;
    }
    textura.setSmooth(true);
    textura.setRepeated(false);

    sf::Texture clicked;
    if(!clicked.loadFromFile("./images/Box.png")){
        std::cout << "ERROR" << std::endl;
        return -1; 
    }
    clicked.setSmooth(true);
    clicked.setRepeated(false);

    sf::RenderWindow window(sf::VideoMode(160, 160), "Test",sf::Style::Titlebar | sf::Style::Close);

    std::vector<std::vector<sf::Sprite>> Sprites(5, std::vector<sf::Sprite>(5, sf::Sprite(textura)));
    
    for (int x = 0; x < 5; x++) {
        for (int y=0;y<5;y++){
        Sprites[x][y].setPosition(sf::Vector2f(0.f + (x * 32), 0.f + (y * 32)));
        }
    }

    // run the program as long as the window is open
    while (window.isOpen()){
        sf::Event event;
        int posX;
        int posY;
        while (window.pollEvent(event)){
            
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    std::cout << "Program closing" << std::endl;
                    break;
                
                case sf::Event::MouseButtonPressed:
                    posX = sf::Mouse::getPosition(window).x /32;
                    posY = sf::Mouse::getPosition(window).y /32;
                    if(posX >= 0 && posX < 5 && posY >= 0 && posY <5){
                        Sprites[posX][posY].setTexture(clicked);
                    }
                    std::cout << "Mouse pressed on x: " << posY << "y: " << posX << std::endl;
                    break;
                
                default:
                    break;
            }
        
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int x = 0; x < 5; x++) {
            for (int y=0;y<5;y++){
            window.draw(Sprites[x][y]);
            }
        }

        // end the current frame
        window.display();
    }

    return 0;
}
