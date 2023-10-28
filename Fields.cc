#include "Fields.h"
#include <iostream>
#include <curses.h>
#include <stdlib.h>     
#include <time.h>

using namespace std;

Field::Field(int posX,int posY,int _num){
    this->X = posX;
    this->Y = posY;
    this->num = _num;
}

Field::Field(){
    this->X = -1;
    this->Y = -1;
    this->num = -1;
}


int Field::hasBomb(){
    if(this->bombFlag == 1){
        return 1;
    }
    else{
        return 0;
    }
}

void Field::plantBomb(){
    this->bombFlag=1;
}

Board::Board(int _width,int _height){
    this->width = _width;
    this->height = _height;
    this->nrOfFields = width*height;
    
    fieldsContainer = new Field*[width];
    for (int i = 0; i < width; ++i){
        fieldsContainer[i] = new Field[height];
    }
    int n=0;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            fieldsContainer[x][y] = Field(x,y,n);
            n++;
        }
    }
}

Board::~Board(){
    for (int i = 0; i < width; ++i) {
        delete[] fieldsContainer[i];
    }
    delete[] fieldsContainer;
}

void Board::drawBoard(){
    for(int x=0;x<this->width;x++){
        for(int y=0;y<this->height;y++){
            if(fieldsContainer[x][y].hasBomb()){
                cout <<"* ";
            }
            else{
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

void Board::placeBombs(int numOfBombs){
    srand(time(NULL));

    int bombs2Plant = numOfBombs;
    while(bombs2Plant>0){
        int randomX = rand() % this ->width;
        int randomY = rand() % this ->height;
        if (this->fieldsContainer[randomX][randomY].hasBomb() != 1){
            this->fieldsContainer[randomX][randomY].plantBomb();
            bombs2Plant--;
        }
    }
}