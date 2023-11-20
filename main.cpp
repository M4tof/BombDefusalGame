#include "Board.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <unistd.h>

int main(int argc, char*argv[]) {
    int ROW = 8;
    int COL = 8;
    int BOMBS = 10;
    if(argc==3){
        ROW = atoi(argv[1]);
        COL = atoi(argv[2]);
        BOMBS = ROW*COL/3;
    }
    if(argc==4){
        ROW = atoi(argv[1]);
        COL = atoi(argv[2]);
        BOMBS = atoi(argv[3]);
    }

    sf::Texture Blank; //-1
    sf::Texture T0;    //0
    sf::Texture T1;    //1
    sf::Texture T2;    //2
    sf::Texture T3;    //3
    sf::Texture T4;    //4
    sf::Texture T5;    //5
    sf::Texture T6;    //6
    sf::Texture T7;    //7
    sf::Texture T8;    //8
    sf::Texture Detonated; //9
    sf::Texture Flaged;    //10
    if (!Blank.loadFromFile("./images/Normal.png") || !T1.loadFromFile("./images/1.png") || !T2.loadFromFile("./images/2.png") || !T3.loadFromFile("./images/3.png") || !T4.loadFromFile("./images/4.png")
            || !T5.loadFromFile("./images/5.png") || !T6.loadFromFile("./images/6.png") || !T7.loadFromFile("./images/7.png") || !T8.loadFromFile("./images/8.png") || !Detonated.loadFromFile("./images/Detonated.png") ||
                !Flaged.loadFromFile("./images/Flaged.png") || !T0.loadFromFile("./images/0.png")){
        
        std::cout << "ERROR" << std::endl;
        return -1;
    }
    
    int GAMEOVER=0;
    sf::Text GameFailed;
    sf::Font font;
    
    font.loadFromFile("Arial.ttf");
    GameFailed.setFont(font);
    GameFailed.setString("GAME OVER");
    GameFailed.setCharacterSize(32*(ROW/8));
    GameFailed.setFillColor(sf::Color::Red);
    GameFailed.setOutlineColor(sf::Color::Black);
    GameFailed.setOutlineThickness(6);
    GameFailed.setStyle(sf::Text::Bold | sf::Text::Underlined);
    GameFailed.setPosition(sf::Vector2f(0.f + (ROW*16) - GameFailed.getLocalBounds().width/2 , 0.f + (COL * 16) - GameFailed.getLocalBounds().height/2 ));



    sf::RenderWindow window(sf::VideoMode((32*ROW), (32*COL)), "BombDefusal",sf::Style::Titlebar | sf::Style::Close);
    
    std::vector<std::vector<sf::Sprite>> Sprites(ROW, std::vector<sf::Sprite>(COL, sf::Sprite(Blank)));
    Board gameBoard(ROW, COL, BOMBS);
    window.setFramerateLimit(60);
    int firstClickFLag=1;

    for (int x = 0; x < ROW; x++) {
        for (int y=0;y<COL;y++){
        Sprites[x][y].setPosition(sf::Vector2f(0.f + (x * 32), 0.f + (y * 32)));
        }
    }

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
                    
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        if(posX >= 0 && posX < ROW && posY >= 0 && posY < COL){
                            
                            if(firstClickFLag){
                                firstClickFLag=0;
                                gameBoard.firstClickHandler(posX,posY);
                            }
                            
                            gameBoard.revealField(posX,posY);
                        }
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        if(posX >= 0 && posX < ROW && posY >= 0 && posY < COL){
                            gameBoard.setFlagHere(posX,posY);
                            std::cout << "Flag set" << std::endl;
                        }
                    }

                    std::cout << "Mouse pressed on x: " << posY << " y: " << posX << std::endl;
                    break;
                
                default:
                    break;
            }
        }
    
        window.clear();

        for (int x = 0; x < ROW; x++) {
            for (int y = 0; y < COL; y++){

                switch (gameBoard.whatToDrawHere(x,y)){
                    case -1:
                        Sprites[x][y].setTexture(Blank);
                        break;
                    case 0:
                        Sprites[x][y].setTexture(T0);
                        break;
                    case 1:
                        Sprites[x][y].setTexture(T1);
                        break;
                    case 2:
                        Sprites[x][y].setTexture(T2);
                        break;
                    case 3:
                        Sprites[x][y].setTexture(T3);
                        break;
                    case 4:
                        Sprites[x][y].setTexture(T4);
                        break;                    
                    case 5:
                        Sprites[x][y].setTexture(T5);
                        break;
                    case 6:
                        Sprites[x][y].setTexture(T6);
                        break;
                    case 7:
                        Sprites[x][y].setTexture(T7);
                        break;
                    case 8:
                        Sprites[x][y].setTexture(T8);
                        break;
                    case 9:
                        Sprites[x][y].setTexture(Detonated);
                        std::cout << "BOMB HAS BEEN DETONATED, MISSION FAILED" << std::endl;
                        GAMEOVER=1;
                        window.draw(GameFailed);
                        break;
                    case 10:
                        Sprites[x][y].setTexture(Flaged);
                        break;
                    default:
                        break;
                }
                window.draw(Sprites[x][y]);
            }
        }

        window.display();
        if(GAMEOVER==1){
            window.draw(GameFailed);
            window.display();
            sleep(3);
            exit(0);
        }
        if(gameBoard.gameOver()){
            GameFailed.setString("YOU WON");
            GameFailed.setFillColor(sf::Color::Green);
            window.draw(GameFailed);
            window.display();
            sleep(3);
            exit(0);
        }


    }

    return 0;
}
