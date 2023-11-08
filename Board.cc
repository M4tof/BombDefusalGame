#include "Board.h"

void Board::setNumOfBombs(int x,int y){
    int bombs=0;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if (x+i >= 0 && x+i < this->width && y+j >= 0 && y+j < this->height){
                if(boardFields[x+i][y+j]->hasBomb()){
                    bombs++;
                }
            }
        }
    }

    boardFields[x][y]->setNumofBombsDirect(bombs);
}

Board::Board(int _width,int _height){
    this->width = _width;
    this->height = _height;
    this->nrOfFields = width*height;
    boardFields.resize(width,std::vector<Field*>(height,nullptr));

    int numOfBombs = _width * _height /3;
    srand(time(NULL));
    while (numOfBombs >0){
        int x = rand() %  _width;
        int y = rand() % _height;
        if(boardFields[x][y]==nullptr){
            boardFields[x][y] = new BombField(x, y);
            numOfBombs--;
        }
    }
    for(int i=0;i<_width;i++){
        for(int j=0;j<_height;j++){
            if(boardFields[i][j] == nullptr){
                boardFields[i][j] = new SafeField(i,j);
            }
        }
    }
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            setNumOfBombs(i, j);
        }
    }
}

Board::Board(int _width,int _height,int numBombs){
    this->width = _width;
    this->height = _height;
    this->nrOfFields = width*height;
    boardFields.resize(width,std::vector<Field*>(height,nullptr));

    int numOfBombs = numBombs;
    srand(time(NULL));
    while (numOfBombs >0){
        int x = rand() %  _width;
        int y = rand() % _height;
        if(boardFields[x][y]==nullptr){
            boardFields[x][y] = new BombField(x, y);
            numOfBombs--;
        }
    }
    for(int i=0;i<_width;i++){
        for(int j=0;j<_height;j++){
            if(boardFields[i][j] == nullptr){
                boardFields[i][j] = new SafeField(i,j);
            }
        }
    }
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            setNumOfBombs(i, j);
        }
    }
}

void Board::drawBoard(){
    for(int x=0;x<this->width;x++){
        for(int y=0;y<this->height;y++){
            cout << boardFields[x][y]->symbol() << " ";
        }
        cout << endl;
    }
}

void Board::revealField(int x,int y){
    if(x<0||x>=width || y<0|| y>=height){
        return;
    }
    if(boardFields[x][y]->whatToDraw() != -1){
        return;
    }

    boardFields[x][y]->reveal();
    
    if (boardFields[x][y]->whatToDraw()==0){
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                    this->revealField(x+i,y+j);
            }
        }
    }
    else{
        return;
    }

}

int Board::whatToDrawHere(int x, int y){
    return this->boardFields[x][y]->whatToDraw();
}

void Board::setFlagHere(int x,int y){
    this->boardFields[x][y]->setFlag();
}

int Board::gameOver(){
    int correct=0;
    for(int x=0;x<this->width;x++){
        for(int y=0;y<this->height;y++){
            
            if(!boardFields[x][y]->hasBomb()){ //in SafeField
                if(boardFields[x][y]->whatToDraw()>=0 && boardFields[x][y]->whatToDraw()<=8){
                    correct++;
                }
            }
            else{ //in BombField
                if(boardFields[x][y]->isDefused()){
                    correct++;
                }
            }
        
        }
    }

    if(correct==this->nrOfFields){
        return 1;
    }
    else{
        return 0;
    }
}

Board::~Board(){
    for(int x=0;x<this->width;x++){
        for(int y=0;y<this->height;y++){
            delete boardFields[x][y];
        }
    }
    std::cout << "Memory released succesfully" << std::endl;
}

void Board::firstClickHandler(int posX, int posY){
    if(boardFields[posX][posY]->hasBomb()){
        std::cout << "Had to use firstClickHandler ";
        int safeX =-1;
        int safeY =-1;

        for(int x=0;x<this->width;x++){
            for(int y=0;y<this->height;y++){
                if(boardFields[x][y]->hasBomb() == 0 && safeX == -1 && safeY == -1){
                    safeX=x;
                    safeY=y;
                }
            }
        }
        
        if (safeX != -1 && safeY != -1){
            delete boardFields[safeX][safeY];
            boardFields[safeX][safeY] = new BombField(safeX,safeY);
            
            delete boardFields[posX][posY];
            boardFields[posX][posY] = new SafeField(posX,posY);

            for (int i = 0; i < this->width; i++) {
                for (int j = 0; j < this->height; j++) {
                    setNumOfBombs(i, j);
                }
            }

            std::cout << ", used it succesfully "<< std::endl;
        }

        else{
            std::cout << ", but it failed" << std::endl;
        }

    }
}